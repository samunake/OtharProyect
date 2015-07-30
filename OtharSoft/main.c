#include "stm32f4xx_conf.h"
#include "system_stm32f4xx.h"
#include "Lcd/RA8875/Driver_RA8875.h"
#include "Delay/delay.h"
#include "Test/Test.h"

#include "Clock/defines.h"
#include "Clock/tm_stm32f4_rtc.h"
#include "Clock/attributes.h"

#include <Dimmer.h>

#include <stdio.h>
#include "Buttons/button.h"

char buf[50], buf2[50];
TM_RTC_Time_t datatime;

int main(void) {
	// System Configuration Init
	SystemInit();

	// Initialize RTC
	if (!TM_RTC_Init(TM_RTC_ClockSource_External)) {
		//RTC was first time initialized
		//Do your stuf here
		//eg. set default time
		// Set date and time
		datatime.date = 20;
		datatime.day = 1;
		datatime.month = 1;
		datatime.year = 15;
		datatime.hours = 0;
		datatime.minutes = 0;
		datatime.seconds = 0;

		// Set date and time
		TM_RTC_SetDateTime(&datatime, TM_RTC_Format_BIN);
	}

	// Init Systick for Delays
	Init_SysTick();

	// Rest LCD PC6 = 0
	LCD_Reset();
	Software_Reset();
	// Load FSMC Config, GPIO Config, PLLs, LCD init values
	LCD_Initialization();
	Delay_ms(500);

	// Init PWM on Timer 4 Channel 1 (PD12)
	InitializePWM_TIM4();

	// Check LCD and Set Background to Black
	Display_OFF();
	Delay_ms(10);
	LCD_Clear(Black);
	Display_ON();
	Delay_ms(2000);

	// Initialize GPIOS for Control Lights Output
	initializeGPIOTimer();

	//Set wakeup interrupt every 1 second
	TM_RTC_Interrupts(TM_RTC_Int_1s);

	uint16_t i;
	for (i = 0; i < 4; i++) {

		print_BTEImage(0, i * 200, 0, 120);

	}
	print_BTELogo(0, 675, 0, 420);

	//print_pureImage();

	//	LCDPrintStrROM("Alo Presinde",400,100);

	/*		Active_Window(0, 799, 0, 479);
	 LCDPrintStr("abc", 0, 0, Black, White, 1, 1, "zoom2");
	 LCDPrintStr("Hola Presunta", 0, 30, Black, White, 1, 2, "zoom2");
	 LCDPrintStr("Hola Presunta", 0, 60, Black, White, 1, 3, "zoom2");
	 LCDPrintStr("abc", 0, 90, Black, White, 1, 4, "zoom2");

	 LCDPrintStr("Hola Presunta", 200, 00, Black, White, 2, 1, "zoom2");
	 LCDPrintStr("Hola Presunta", 200, 30, Black, White, 2, 2, "zoom2");
	 LCDPrintStr("Hola Presunta", 200, 60, Black, White, 2, 3, "zoom2");
	 LCDPrintStr("Hola", 200, 90, Black, White, 2, 4, "zoom2");

	 LCDPrintStr("Hola", 300, 100, Black, White, 3, 1, "zoom2");
	 LCDPrintStr("Hola", 300, 150, Black, White, 3, 2, "zoom2");
	 LCDPrintStr("Hola", 300, 200, Black, White, 3, 3, "zoom2");
	 LCDPrintStr("Hola", 300, 250, Black, White, 3, 4, "zoom2");


	 // HOLA PRESIDENTE ASCII
	 *
	 */
	//LCD_WriteText();
	/* CUADRADITO**************************************************
	 *
	 *
	 *
	 * *************************************************************/
	/* Active_Window(100,200,200,300);
	 Graphic_Mode();
	 XY_Coordinate(100,200);
	 LCD_WriteCmd(0x02);//MRWC
	 uint32_t i;
	 for(i=0;i<10201;i++)
	 {
	 LCD_WriteData(Black);
	 Chk_Busy();
	 }
	 //Delay_ms(2000);
	 //ActiveWindow_Clear();*/

	extern uint8_t status_dim1;
	extern uint8_t dimmer1;

	configure_ZeroCrossingInterrupt();
	Init_DimmerTimer();
	while (1) {
		{
			GPIO_SetBits(GPIOA, GPIO_Pin_5);
			Delay_ms(5000);
			GPIO_ResetBits(GPIOA, GPIO_Pin_5);
			Delay_ms(5000);
			//Test();
			//Delay_ms(3000);
			//	dimmer1=256;//0,128
			//	status_dim1 = ON;

		//	setDimmer(2, 799);
			checkDimmers();

			//dimer1+TRIACTIMEON < 980
		}
	}
//Custom request handler function
//Called on wakeup interrupt
		void TM_RTC_RequestHandler() {
			//Get time
			TM_RTC_GetDateTime(&datatime, TM_RTC_Format_BIN);

			//Format time
			sprintf(buf, "%02d.%02d.%04d", datatime.date, datatime.month,
					datatime.year + 2000);
			//Send to LCD
			Active_Window(540, 799, 0, 18);
			LCDPrintStr(buf, 540, 18, White, Black, 1, 2, "zoom2");
			sprintf(buf, "%02d:%02d:%02d", datatime.hours, datatime.minutes,
					datatime.seconds);
			LCDPrintStr(buf, 650, 10, Blue2, Black, 2, 2, "zoom4");

		}
}
