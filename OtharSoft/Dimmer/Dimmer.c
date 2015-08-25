//#include "stm32f4xx_exti.h"
//#include "stm32f4xx_syscfg.h"
//#include "misc.h"
//#include "Delay/delay.h"
#include "Dimmer.h"
#include "Lights.h"
#include <stdio.h>

#define TIME_TRIAC 200


extern LIGHT_t LIGHT1,LIGHT2,LIGHT3,LIGHT4;

uint16_t captureTime = 0;
char text[50];
uint32_t show1 = 0;
uint32_t show2 = 0;
uint32_t show3 = 0;
uint16_t captureTime1 = 0;
uint16_t captureTime2 = 0;
uint16_t captureTime3 = 0;

/* Configure pin PA0 to be interrupt for zero crossing detection*/

void Init_Dimmer(void) {

	GPIO_LIGHTS_Init();
	Configure_ZCInterrupt();
	init_DimmerValues();
	TIM_Config();

}

void init_DimmerValues(void) {

	LIGHT1.dimmer=0;
	LIGHT2.dimmer=0;
	LIGHT3.dimmer=0;
	LIGHT4.dimmer=0;

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
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
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
	TIM_OCInitTypeDef TIM_OCInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	/* TIM1 clock enable */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	timerInitStructure.TIM_Prescaler = 167; // timer_tick_frequency = 168000000 / 167+1 = 1 MHz --> 1 us
	timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	timerInitStructure.TIM_Period = 0xffff; // Max value. 16 bits. if not set uses 14 bits.

	/* Initialize TIM1 */
	TIM_TimeBaseInit(TIM1, &timerInitStructure);

	/* Output Compare Timing Mode configuration: Channel1 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

	TIM_OC1Init(TIM1, &TIM_OCInitStructure);

	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Disable);

	TIM_ITConfig(TIM1,
			TIM_IT_CC1 | TIM_IT_CC2 | TIM_IT_CC3 | TIM_IT_CC4 | TIM_IT_Update,
			ENABLE);

	TIM_Cmd(TIM1, ENABLE);

	TIM_SetCompare1(TIM1, LIGHT1.dimmer);
	TIM_SetCompare2(TIM1, LIGHT2.dimmer);
	TIM_SetCompare3(TIM1, LIGHT3.dimmer);
	TIM_SetCompare4(TIM1, LIGHT4.dimmer);

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

		if(show3>=250){
		captureTime3 = TIM_GetCounter(TIM1);
		Active_Window(1, 260, 80, 100);
		sprintf(text, "ZC  : %06i", captureTime3);
		LCD_PrintStr(text, 1, 80, 0x051F, 0x0000, 2, 2, 4);
		show3=0;
		}

		EXTI_ClearITPendingBit(EXTI_Line9);


		/* Enable the CC1,CC2,CC3,CC4 Interrupt Request */
		TIM_ITConfig(TIM1,	TIM_IT_CC1 | TIM_IT_CC2 | TIM_IT_CC3 | TIM_IT_CC4
						| TIM_IT_Update, ENABLE);
		TIM_SetCounter(TIM1, 0);
		TIM_SetCompare1(TIM1, LIGHT1.dimmer);
		show1++;
		show2++;
		show3++;
	}
	/*Active_Window(1, 260, 0, 18);
	 sprintf(text, "Cont= : %04i", dimmer1);
	 LCD_PrintStr(text, 650, 10, 0x051F, 0x0000, 2, 2, "zoom4");
	 EXTI_ClearITPendingBit(EXTI_Line8);*/

}

void TIM1_CC_IRQHandler(void) {

	if (TIM_GetITStatus(TIM1, TIM_IT_CC1) == SET) {
		captureTime1 = TIM_GetCounter(TIM1);
		TIM_ClearITPendingBit(TIM1, TIM_IT_CC1);
		//Check dimmer1

		if (LIGHT1.status == ON) { //&& SATUSTRIGGER==0
			//SetLight_On()			//TIM_ITConfig(TIM1,	TIM_IT_CC1 , DISABLE);

			if (show1 >= 250) {
				Active_Window(1, 460, 0, 18);
				//	Clear_Active_Window();
				Foreground_color(0x0000);
				sprintf(text, "PASO 1= : %06u :%04u", (unsigned int)captureTime1, (unsigned int)show1);
				LCD_PrintStr(text, 1, 5, 0x051F, 0x0000, 2, 2, 4);
				show1 = 0;
				captureTime2 = TIM_GetCounter(TIM1);
				/*Active_Window(1, 460, 40, 60);
				 Foreground_color(0x0000);
				 sprintf(text, "PASO 2: %i", captureTime2);
				 LCD_PrintStr(text, 650, 10, 0x051F, 0x0000, 2, 2, "zoom4");
				 show1 = 0;*/

			}

			/*	if (STATUS_LIGHT1 == ON && STATUS_TRIGGER1 == 0) { //&& SATUSTRIGGER==0
			 Light1_ON();
			 captureTime = TIM_GetCapture1(TIM1);
			 TIM_SetCompare1(TIM1, captureTime + TIME_TRIAC);
			 STATUS_TRIGGER1 = 1;
			 captureTime1 = TIM_GetCounter(TIM1);

			 if (show1 >= 250) {
			 Active_Window(1, 260, 0, 18);
			 Foreground_color(0x0000);
			 sprintf(text, "PASO 1= : %i", captureTime1);
			 LCD_PrintStr(text, 650, 10, 0x051F, 0x0000, 2, 2, "zoom4");
			 show1 = 0;
			 }

			 } else if (STATUS_TRIGGER1 == 1) {

			 Light1_OFF();
			 TIM_SetCompare1(TIM1, dimmer1);
			 STATUS_TRIGGER1 = 0;
			 captureTime2 = TIM_GetCounter(TIM1);

			 if (show2 >= 250) {
			 Active_Window(1, 260, 40, 60);
			 Foreground_color(0x0000);
			 sprintf(text, "PASO 2= : %i", captureTime2);
			 LCD_PrintStr(text, 650, 10, 0x051F, 0x0000, 2, 2, "zoom4");
			 show2 = 0;
			 }
			 }*/
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
}
void TIM1_UP_TIM10_IRQHandler(void) {
	if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET) {
		captureTime2 = TIM_GetCounter(TIM1);
		TIM_SetCompare1(TIM1, LIGHT1.dimmer);
			TIM_SetCompare2(TIM1, LIGHT2.dimmer);
			TIM_SetCompare3(TIM1, LIGHT3.dimmer);
			TIM_SetCompare4(TIM1, LIGHT4.dimmer);
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
		//TIM_SetCounter(TIM1, 0);
		//TIM_Cmd(TIM1, DISABLE);
		TIM_ITConfig(TIM1,
				TIM_IT_CC1 | TIM_IT_CC2 | TIM_IT_CC3 | TIM_IT_CC4
						| TIM_IT_Update, DISABLE);
		// Triac Off
		//Light1_OFF();
		GPIO_ResetBits(GPIOB, GPIO_Pin_7);
		GPIO_ResetBits(GPIOE, GPIO_Pin_0);
		GPIO_ResetBits(GPIOE, GPIO_Pin_1);

		if (show2 >= 250) {
			Active_Window(1, 460, 40, 60);
			//	Clear_Active_Window();
			Foreground_color(0x0000);
			sprintf(text, "PASO 2: %06u : %04u", (unsigned int)captureTime1, (unsigned int)show2);
			LCD_PrintStr(text, 1, 40, 0x051F, 0x0000, 2, 2, 4);
			show2 = 0;

		}
	}

}
