//#include "stm32f4xx_exti.h"
//#include "stm32f4xx_syscfg.h"
//#include "misc.h"
//#include "Delay/delay.h"
#include "Dimmer.h"
#include "Driver_Lights.h"

static uint8_t dimmer1,dimmer2,dimmer3,dimmer4;
static uint8_t status_dim1, status_dim2, status_dim3, status_dim4;
char text[50];

/* Configure pin PA0 to be interrupt for zero crossing detection*/

void Init_Dimmer(void) {

	GPIO_LIGHTS_Init();
	Configure_ZCInterrupt();
	init_DimmerValues();
	TIM_Config();

}

void init_DimmerValues(void) {

	/*Initialize dimmer values*/
	dimmer1 = 0; //valor_dim1
	dimmer2 = 0;
	dimmer3 = 0;
	dimmer4 = 0;

	/*Initialize dimmer status*/
	status_dim1 = ON; //ON
	status_dim2 = OFF;
	status_dim3 = OFF;
	status_dim4 = OFF;

}

void Configure_ZCInterrupt(void) { //uint8_t valor_dim1


	/* Set variables used */
	GPIO_InitTypeDef GPIO_InitStruct;
	EXTI_InitTypeDef EXTI_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;

	/* Enable clock for GPIOA */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	/* Enable clock for SYSCFG */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	/* Set pin as input */
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	/* Tell system that you will use PB8 for EXTI_Line8 */
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource9);

	/* PB8 is connected to EXTI_Line0 */
	EXTI_InitStruct.EXTI_Line = EXTI_Line9;
	/* Interrupt mode */
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	/* Triggers on rising and falling edge */
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
	/* Enable interrupt */
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	/* Add to EXTI */
	EXTI_Init(&EXTI_InitStruct);

	/* Add IRQ vector to NVIC */
	/* PD0 is connected to EXTI_Line0, which has EXTI0_IRQn vector */
	NVIC_InitStruct.NVIC_IRQChannel = EXTI9_5_IRQn;
	/* Set priority */
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x00;
	/* Set sub priority */
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x00;
	/* Enable interrupt */
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	/* Add to NVIC */
	NVIC_Init(&NVIC_InitStruct);
}

void TIM_Config(void) {

	TIM_TimeBaseInitTypeDef timerInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	/* TIM1 clock enable */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	timerInitStructure.TIM_Prescaler = 167; // timer_tick_frequency = 168000000 / 167+1 = 1 MHz --> 1 us
	timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	timerInitStructure.TIM_Period = 8999; // Max value. 16 bits. if not set uses 14 bits.
	TIM_SetCompare1(TIM1, dimmer1);
	TIM_SetCompare2(TIM1, dimmer2);
	TIM_SetCompare3(TIM1, dimmer3);
	TIM_SetCompare4(TIM1, dimmer4);
	/* Initialize TIM1 */
	TIM_TimeBaseInit(TIM1, &timerInitStructure);

	/* Enable the CC1,CC2,CC3,CC4 Interrupt Request */
	TIM_ITConfig(TIM1, TIM_IT_CC1 | TIM_IT_CC2 | TIM_IT_CC3 | TIM_IT_CC4 | TIM_IT_Update, ENABLE);

	/* Enable the TIM1 Compare Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_CC_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	/* Enable the TIM1 global Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_TIM10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void EXTI9_5_IRQHandler(void) {
	/* Make sure that interrupt flag is set */
	if (EXTI_GetITStatus(EXTI_Line9) != RESET) {

		EXTI_ClearITPendingBit(EXTI_Line9);
		TIM_Cmd(TIM1, ENABLE);
		TIM_SetCounter(TIM1, 0);

		/*Active_Window(1, 260, 0, 18);
		 sprintf(text, "Cont= : %04i", dimmer1);
		 LCDPrintStr(text, 650, 10, 0x051F, 0x0000, 2, 2, "zoom4");
		 EXTI_ClearITPendingBit(EXTI_Line8);*/
	}
}

void TIM1_CC_IRQHandler(void) {

	if (TIM_GetITStatus(TIM1, TIM_IT_CC1) == SET) {
		TIM_ClearITPendingBit(TIM1, TIM_IT_CC1);
		//Check dimmer1
		if (status_dim1 == ON ) { //&& SATUSTRIGGER==0
			Light1_ON();
		//	TIM_SetCompare1(getcounter+triacon);
		//	SATUSTRIGGER=1;
		}
		//ELSE IF(STAUTAUSTRIGGER==1){
		//	LIHGHT1_OOF
		//	SETCOMPARE


	}
	if (TIM_GetITStatus(TIM1, TIM_IT_CC2) == SET) {
		/* Clear TIM1 Capture compare interrupt pending bit */
		TIM_ClearITPendingBit(TIM1, TIM_IT_CC2);
		GPIO_SetBits(GPIOB, GPIO_Pin_7);

	}

	if (TIM_GetITStatus(TIM1, TIM_IT_CC3) == SET) {
		TIM_ClearITPendingBit(TIM1, TIM_IT_CC3);
		GPIO_SetBits(GPIOE, GPIO_Pin_0);
		//Check dimmer1

	}
	if (TIM_GetITStatus(TIM1, TIM_IT_CC4) == SET) {
		TIM_ClearITPendingBit(TIM1, TIM_IT_CC4);
		//Check dimmer1
		GPIO_SetBits(GPIOE, GPIO_Pin_1);
	}

}

void TIM1_UP_TIM10_IRQHandler(void) {
	if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET) {
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
		TIM_SetCounter(TIM1, 0);
		TIM_Cmd(TIM1, DISABLE);
		// Triac Off
		Light1_OFF();
		/*GPIO_ResetBits(GPIOB, GPIO_Pin_7);
		 GPIO_ResetBits(GPIOE, GPIO_Pin_0);
		 GPIO_ResetBits(GPIOE, GPIO_Pin_1);*/
	}
}


