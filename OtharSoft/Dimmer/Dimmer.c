#include "stm32f4xx.h"
//#include "stm32f4xx_exti.h"
//#include "stm32f4xx_syscfg.h"
//#include "misc.h"
//#include "Delay/delay.h"
#include "Dimmer.h"
#include "Driver_Lights.h"


static uint8_t dimmer1, dimmer2, dimmer3, dimmer4;
static uint8_t status_dim1, status_dim2, status_dim3, status_dim4;

/* Configure pin PA0 to be interrupt for zero crossing detection*/



void setDimmer(uint8_t numDim , uint16_t);

void configure_ZeroCrossingInterrupt(void) { //uint8_t valor_dim1

	/*Initialize dimmer values*/
	dimmer1 = 0; //valor_dim1
	dimmer2 = 0;
	dimmer3 = 0;
	dimmer4 = 0;

	/*Initialize dimmer status*/
	status_dim1 = OFF; //ON
	status_dim2 = OFF;
	status_dim3 = OFF;
	status_dim4 = OFF;

	/* Set variables used */
	GPIO_InitTypeDef GPIO_InitStruct;
	EXTI_InitTypeDef EXTI_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;

	/* Enable clock for GPIOA */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	/* Enable clock for SYSCFG */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	/* Set pin as input */
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	/* Tell system that you will use PA0 for EXTI_Line1 */
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);

	/* PA0 is connected to EXTI_Line0 */
	EXTI_InitStruct.EXTI_Line = EXTI_Line0;
	/* Enable interrupt */
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	/* Interrupt mode */
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	/* Triggers on rising and falling edge */
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
	/* Add to EXTI */
	EXTI_Init(&EXTI_InitStruct);

	/* Add IRQ vector to NVIC */
	/* PD0 is connected to EXTI_Line0, which has EXTI0_IRQn vector */
	NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn;
	/* Set priority */
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x00;
	/* Set sub priority */
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x00;
	/* Enable interrupt */
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	/* Add to NVIC */
	NVIC_Init(&NVIC_InitStruct);
}

void Init_DimmerTimer(void) {
	/*TIM4 is connected to APB1 bus, which has on F407 device 42MHz clock
	 But, timer has internal PLL, which double this frequency for timer, up to 84MHz
	 Remember: Not each timer is connected to APB1, there are also timers connected
	 on APB2, which works at 84MHz by default, and internal PLL increase
	 this to up to 168MHz  */
	TIM_TimeBaseInitTypeDef timerInitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

	timerInitStructure.TIM_Prescaler = 699; // timer_tick_frequency = 84000000 / 700 = 120 KHz --> 8.333 us
	//Onda de 60Hz -> Semiciclo de 8.3 ms -> El timer cuenta 1000 veces en cada semiciclo
	timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	timerInitStructure.TIM_Period = 979; // valor hasta el que cuenta el timer
	//El timer no tiene asociada interrupción, solo usamos su valor para contar ciclos
	timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	timerInitStructure.TIM_RepetitionCounter = 0;
	/* Initialize TIM1 */
	TIM_TimeBaseInit(TIM1, &timerInitStructure);
	//TIM_Cmd(TIM1, ENABLE);
}

void checkDimmers(void) {

	//Check dimmer1
	if (TIM_GetCounter(TIM1) == dimmer1) {
		Light2_ON();
	}
	if (TIM_GetCounter(TIM1) == dimmer1 + TRIACTIMEON) {
		GPIO_ResetBits(GPIOE, GPIO_Pin_2);
	}

	//Check dimmer2
	if (TIM_GetCounter(TIM1) == dimmer2) {
		GPIO_SetBits(GPIOE, GPIO_Pin_2);
	}
	if (TIM_GetCounter(TIM1) == dimmer2 + TRIACTIMEON) {
		GPIO_ResetBits(GPIOE, GPIO_Pin_2);
	}

	//Check dimmer3
	if (TIM_GetCounter(TIM1) == dimmer3) {
		GPIO_SetBits(GPIOE, GPIO_Pin_2);
	}
	if (TIM_GetCounter(TIM1) == dimmer3 + TRIACTIMEON) {
		GPIO_ResetBits(GPIOE, GPIO_Pin_2);
	}

	//Check dimmer4
	if (TIM_GetCounter(TIM1) == dimmer4) {
		GPIO_SetBits(GPIOE, GPIO_Pin_2);
	}
	if (TIM_GetCounter(TIM1) == dimmer4 + TRIACTIMEON) {
		GPIO_ResetBits(GPIOE, GPIO_Pin_2);
	}

}

void EnableTimerInterrupt() {
	NVIC_InitTypeDef nvicStructure;
	nvicStructure.NVIC_IRQChannel = TIM1_UP_TIM10_IRQn;
	nvicStructure.NVIC_IRQChannelPreemptionPriority = 0;
	nvicStructure.NVIC_IRQChannelSubPriority = 1;
	nvicStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvicStructure);
}

/* Set interrupt handler */
/* Handle PA0 interrupt */
void EXTI0_IRQHandler(void) {
	/* Make sure that interrupt flag is set */
	if (EXTI_GetITStatus(EXTI_Line0) != RESET) {

		/* Suponiendo que las bases de los transistores de control de MOCs estan conectados a PA1,PA2,PA3 y PA4*/

		/* Actions to do when PA0 interrupts*/
		if (status_dim1 == ON) {

			TIM_Cmd(TIM1, ENABLE);
			//RCC_APB2PeriphClockC md(RCC_APB2Periph_TIM1, ENABLE);
			TIM_SetCounter(TIM1, 0);

			/*			Delay_ms(256 - dimmer1 + 7 / 84000000); //Con un reloj de 84MHz
			 GPIO_SetBits(GPIOE, GPIO_Pin_2);
			 //	Delay_ms((8.3ms - 8.3/(256-dimmer1) - 7 / 84000000);
			 GPIO_ResetBits(GPIOE, GPIO_Pin_2);
			 */}
		if (status_dim2 == ON) {
			GPIO_SetBits(GPIOA, GPIO_Pin_2);
			Delay_ms(256 - dimmer2 + 4 / 84000000);
			GPIO_ResetBits(GPIOA, GPIO_Pin_2);
		}
		if (status_dim3 == ON) {
			GPIO_SetBits(GPIOA, GPIO_Pin_3);
			Delay_ms(256 - dimmer3 + 4 / 84000000);
			GPIO_ResetBits(GPIOA, GPIO_Pin_3);
		}
		if (status_dim4 == ON) {
			GPIO_SetBits(GPIOA, GPIO_Pin_4);
			Delay_ms(256 - dimmer4 + 4 / 84000000);
			GPIO_ResetBits(GPIOA, GPIO_Pin_4);
		}

		//TIM_Cmd(TIM1, DISABLE);
		//RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, DISABLE);
		/* Clear interrupt flag */
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}

