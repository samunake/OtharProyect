#include "Alarm.h"
#include "stm32f4xx_conf.h"
#include "RA8875.h"
#include "Dimmer.h"
#include <stdio.h>

void InitAlarm() {

	Configure_AlarmInterrupt();
	Set_Alarm();

}

void Configure_AlarmInterrupt() {

	//Enable SYSCFG clock for EXTI lines
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	/* Disable Alarm A */
	RTC_WriteProtectionCmd(DISABLE);
	RTC_AlarmCmd(RTC_Alarm_A, DISABLE);
	RTC_ITConfig(RTC_IT_ALRA, DISABLE);

	EXTI_InitTypeDef EXTI_InitStruct;

	/* Configure EXTI 17 as interrupt */
	EXTI_InitStruct.EXTI_Line = EXTI_Line17;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;

	/* Clear RTC Alarm pending bit */
	EXTI_ClearITPendingBit(EXTI_Line17);

	/* Initialite Alarm EXTI interrupt */
	EXTI_Init(&EXTI_InitStruct);

	//vinculate EXTILine17 interrupt to NVIC
	NVIC_InitTypeDef NVIC_InitStruct;
	/* Configure the RTC Alarm Interrupt */
	NVIC_InitStruct.NVIC_IRQChannel = RTC_Alarm_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = RTC_PRIORITY;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = RTC_ALARM_SUBPRIORITY;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;

	/* Initialize RTC Alarm Interrupt */
	NVIC_Init(&NVIC_InitStruct);

}

void Set_Alarm() { //uint8_t DayWeekSel, uint8_t DateWeekNum ,uint8_t hour, uint8_t minute, uint8_t second

	RTC_TimeTypeDef timeType;
	//Set alarm time and format
	timeType.RTC_Hours = 2; //hour
	timeType.RTC_Minutes = 3; //minute
	//timeType.RTC_Seconds = 2;
	timeType.RTC_H12 = RTC_H12_AM;

	RTC_AlarmTypeDef alarmType;
	alarmType.RTC_AlarmTime = timeType;
	alarmType.RTC_AlarmDateWeekDaySel = RTC_AlarmDateWeekDaySel_Date;
	alarmType.RTC_AlarmDateWeekDay = 1;
	alarmType.RTC_AlarmMask = RTC_AlarmMask_None;

	RTC_SetAlarm(RTC_Format_BCD, RTC_Alarm_A, &alarmType);

	/* Enable Alarm A */
	RTC_AlarmCmd(RTC_Alarm_A, ENABLE);
	/* Enable Alarm A interrupt */
	RTC_ITConfig(RTC_IT_ALRA, ENABLE);
	/* Clear Alarm A pending bit */
	RTC_ClearFlag(RTC_IT_ALRA);

}

void RTC_Alarm_IRQHandler(void) {
	// Check alarm interrupt status

	//if ((Status_Light1 | Status_Light2 | Status_Light3 | Status_Light4) == OFF) {

		//Esto habrça que hacerlo para ver en que botones esta configurada
		//la alarma y encender esas salidas

		//Set_ZCInterrupt();
	//}

	if (RTC_GetITStatus(RTC_IT_ALRA) != RESET) {
		// Clear RTC Alarm A interrupt flag
		RTC_ClearITPendingBit(RTC_IT_ALRA);

		//Thing to do when alarm A goes ON
		Active_Window(0, 799, 0, 479);
		//LCD_Clear(Yellow);
		LCD_PrintStr("Son las 02:03", 200, 100, Yellow, Red, 2, 2, "zoom4");

	}

	// RTC Alarm B check
	if (RTC_GetITStatus(RTC_IT_ALRB) != RESET) {
		// Clear RTC Alarm A interrupt flag
		RTC_ClearITPendingBit(RTC_IT_ALRB);

		//Thing to do when alarm A goes ON

	}

}
