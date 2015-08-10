/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_tim.h"
#include "misc.h"

/** @addtogroup TIM_Input_Capture
 * @{
 */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
TIM_ICInitTypeDef TIM_ICInitStructure;
uint16_t uhIC3ReadValue1 = 0;
uint16_t uhIC3ReadValue2 = 0;
uint16_t uhCaptureNumber = 0;
uint16_t uwCapture = 0;
uint16_t sepasa = 0;
float uwTIM1Freq = 0.0;
float uwTIM1Freqpasa = 0.0;
uint8_t showcounter = 0;
char text[50];

/* Private function prototypes -----------------------------------------------*/
void TIMFrec_Config(void);

/* Private functions ---------------------------------------------------------*/

/**
 * @brief  Main program
 * @param  None
 * @retval None
 */
void InputCapture(void) {
	/*!< At this stage the microcontroller clock setting is already configured,
	 this is done through SystemInit() function which is called from startup
	 file (startup_stm32f4xx.s) before to branch to application main.
	 To reconfigure the default setting of SystemInit() function, refer to
	 system_stm32f4xx.c file
	 */

	/* TIM1 Configuration */
	TIM_Config();

	/* TIM1 configuration: Input Capture mode ---------------------
	 The external signal is connected to TIM1 CH2 pin (PE.11)
	 The Rising edge is used as active edge,
	 The TIM1 CCR2 is used to compute the frequency value
	 ------------------------------------------------------------ */

	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStructure.TIM_ICFilter = 0x0;

	TIM_ICInit(TIM1, &TIM_ICInitStructure);

	/* TIM enable counter */
	TIM_Cmd(TIM1, ENABLE);

	/* Enable the CC2 Interrupt Request */
	TIM_ITConfig(TIM1, TIM_IT_CC2, ENABLE);

}

/**
 * @brief  Configure the TIM1 Pins.
 * @param  None
 * @retval None
 */
void TIMFrec_Config(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef timerInitStructure;

	/* TIM1 clock enable */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	timerInitStructure.TIM_Prescaler = 8399; // timer_tick_frequency = 84000000 / 83+1 = 1 MHz --> 1 us
	//Onda de 60Hz -> Semiciclo de 8.3 ms -> El timer cuenta 1000 veces en cada semiciclo
	timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	timerInitStructure.TIM_Period = 0xFFFF; // max value. 16 bits. if not set uses 14 bits.

	/* Initialize TIM1 */
	TIM_TimeBaseInit(TIM1, &timerInitStructure);

	/* GPIOA clock enable */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	/* TIM1 channel 2 pin (PA9) configuration */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* Connect TIM pins to AF2 */
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_TIM1);

	/* Enable the TIM1 global Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_CC_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

}

/**
 * @brief  This function handles TIM1 global interrupt request.
 * @param  None
 * @retval None
 */
void CAmbio_TIM1_CC_IRQHandler(void) {
	if (TIM_GetITStatus(TIM1, TIM_IT_CC2) == SET) {
		/* Clear TIM1 Capture compare interrupt pending bit */
		TIM_ClearITPendingBit(TIM1, TIM_IT_CC2);
		if (uhCaptureNumber == 0) {
			/* Get the Input Capture value */
			uhIC3ReadValue1 = TIM_GetCapture2(TIM1);
			uhCaptureNumber = 1;
		} else if (uhCaptureNumber == 1) {
			/* Get the Input Capture value */
			uhIC3ReadValue2 = TIM_GetCapture2(TIM1);

			/* Capture computation */
			if (uhIC3ReadValue2 > uhIC3ReadValue1) {
				uwCapture = (uhIC3ReadValue2 - uhIC3ReadValue1);
			} else if (uhIC3ReadValue2 < uhIC3ReadValue1) {
				uwCapture = ((65535 - uhIC3ReadValue1) + uhIC3ReadValue2);
				sepasa = uwCapture;
				uwTIM1Freqpasa = (uint32_t) 20000 / (1.0 * sepasa);
				// sepasa
				Active_Window(1, 660, 30, 48);
				Foreground_color(0x0000);
				sprintf(text, "frec pasa: %02f :%05d :%05d ", uwTIM1Freqpasa,uhIC3ReadValue1,uhIC3ReadValue2);
				LCDPrintStr(text, 650, 10, 0x051F, 0x0000, 2, 2, "zoom2");


			} else {
				uwCapture = 0;
			}
			/* Frequency computation */
			uwTIM1Freq = (uint32_t) 20000 / (1.0 * uwCapture);

			uhCaptureNumber = 0;
			if (showcounter == 251) {
				Active_Window(1, 460, 0, 18);
				Foreground_color(0x0000);
				sprintf(text, "frec: %02f  :%05d :%05d", uwTIM1Freq,uhIC3ReadValue1,uhIC3ReadValue2);
				LCDPrintStr(text, 650, 10, 0x051F, 0x0000, 2, 2, "zoom2");
				showcounter=0;

			}

			showcounter++;
		}

	}
}



