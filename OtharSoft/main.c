
#include "stm32f4xx_conf.h"
#include "system_stm32f4xx.h"
#include "Lcd/RA8875/Driver_RA8875.h"
#include "Delay/delay.h"
#include "Test/Test.h"


int main(void)
{
	// System Configuration Init
	SystemInit();

	// Init Systick for Delays
	Init_SysTick();

	// Rest LCD PC6 = 0
	LCD_Reset();

	// Load FSMC Config, GPIO Config, PLLs, LCD init values
	LCD_Initialization();
	Delay_ms(500);

	// Init PWM on Timer 4 Channel 1 (PD12)
	InitializePWM_TIM4();

	Display_OFF();
	Delay_ms(10);
	Display_ON();
	LCD_Clear(White);
	Delay_ms(2000);



	Active_Window(0,799,0,479);
	LCDPrintStr("Hola Presunta",400,100,Black,White,1,1,"zoom2");
	LCDPrintStr("Hola Presunta",400,200,Black,White,1,2,"zoom2");
	LCDPrintStr("Hola Presunta",400,300,Black,White,1,3,"zoom2");
	LCDPrintStr("Hola Presunta",400,400,Black,White,1,4,"zoom2");
	uint8_t temp;
	//temp = DMA_Access_Font();
	//LCD_WriteText();
	//LCD_Write2();
	/*Memory_Clear();*/
	//Delay_ms(2500);



			Active_Window(100,200,200,300);
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

    while(1)


    {


    	Test();


    }
}
