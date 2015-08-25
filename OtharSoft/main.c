#include "stm32f4xx_conf.h"
#include "system_stm32f4xx.h"

#include "Test/Test.h"

#include "defines.h"
#include "Clock/tm_stm32f4_rtc.h"
#include "attributes.h"

//#include "Dimmer.h"
#include "Lcd.h"
#include "Delay.h"
#include <stdio.h>

char buf[50], buf2[50];

int main(void) {

	// System Configuration Init
	SystemInit();


	// Set date and clock if is the first time
	SetTime();

	//Init Timer Delay
	Init_Delay();

	//Load FSMC Init, GPIO Init, PLLs and LCD initial values
	LCD_Init();
	// Initializate PWM on Timer 4 Channel 1 (PD12). Start LCD
	//LCD_Reset();

	BackLight_Init();

	// Rest LCD PC6 = 0


	Delay_ms(500);

	// Check LCD and Set Background to Black
	Display_OFF();
	Delay_ms(10);
	LCD_Clear(Black,FULL_LCD);
	Display_ON();
	Delay_ms(2000);

	//Set wakeup interrupt every 1 second
	//TM_RTC_Interrupts(TM_RTC_Int_1s);

	//Init_Dimmer();

	/**************Check Fecuency 220v ine. 50Hz************/
	//InputCapture();

	print_Logo();



	//GPIO_LIGHTS_Init();

	//GPIO_LIGHTS_Init();

	Init_Touch();

	while (1) {
		/*GPIO_SetBits(GPIOE, GPIO_Pin_2);
		Delay_ms(5000);
		GPIO_ResetBits(GPIOE, GPIO_Pin_2);
		Delay_ms(5000);
		*/
		//Test();
	}
}

