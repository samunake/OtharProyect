
#include "stm32f4xx_conf.h"
#include "system_stm32f4xx.h"
#include "Lcd/LCD_Functions.h"
#include "Delay/delay.h"
#include "Test/Test.h"


int main(void)
{
	SystemInit();
	Init_SysTick();  // Inicia Delay
	LCD_Reset();
	LCD_Initialization();
	Delay_ms(500);
	InitializePWM_TIM4();
	Display_OFF();
	Delay_ms(10);
	Display_ON();
	LCD_Clear(Red);
	/*Memory_Clear();*/
	Delay_ms(2500);
	/*Text_color(Green); // Set the color
	Geometric_Coordinate(100,200,200,400);
	LCD_WriteReg(0x90,0xb0);*/





	Active_Window(100,200,200,300);
	//Graphic_Mode();
	XY_Coordinate(100,200);
	LCD_WriteCmd(0x02);//MRWC
	uint32_t i;
	for(i=0;i<10201;i++)
	{
		LCD_WriteData(Blue);
		Chk_Busy();
	}
	Delay_ms(2000);
	//ActiveWindow_Clear();

    while(1)


    {
    	//temp = LCD_StatusRead();

    	//Test();


    }
}
