#include "Lcd.h"
#include "Test.h"
#include "defines.h"

void Test(void) {
	//Active_Window(0,799,0,479);
	//Memory_Clear();
	LCD_Clear(Blue,CENTER_LCD);
	Delay_ms(1000);
	Chk_Busy();
	//Memory_Clear();
	LCD_Clear(Red,CENTER_LCD);
	Delay_ms(1000);
	Chk_Busy();
	//Memory_Clear();
	LCD_Clear(Green,CENTER_LCD);
	Delay_ms(1000);

}

void Test_Font(void) {

	/*	Active_Window(0, 799, 0, 479);
	 LCD_PrintStr("Letra 8x16 : Standart :zoom 1", 0, 0, White, Black, 1, 1, 0);
	 LCD_PrintStr("Letra 8x16 : Standart :zoom 2", 0, 50, White, Black, 1, 1, 1);
	 LCD_PrintStr("Letra 8x16 : Standart :zoom 3", 0, 100, White, Black, 1, 1, 2);
	 LCD_PrintStr("Letra 8x16 : Standart :zoom 4", 0, 150, White, Black, 1, 1, 3);
	 *//*
	 LCD_PrintStr("Letra 8x16 : Arial :zoom 0", 0, 0, White, Black, 1, 2, 0);
	 LCD_PrintStr("Letra 8x16 : Arial :zoom 1", 0, 50, White, Black, 1, 2, 1);
	 LCD_PrintStr("Letra 8x16 : Arial :zoom 2", 0, 100, White, Black, 1, 2, 2);
	 LCD_PrintStr("Letra 8x16 : Arial :zoom 3", 0, 150, White, Black, 1, 2, 3);
	 *//*
	 LCD_PrintStr("Letra 8x16 : Roman :zoom 0", 0, 0, White, Black, 1, 3, 0);
	 LCD_PrintStr("Letra 8x16 : Roman :zoom 1", 0, 50, White, Black, 1, 3, 1);
	 LCD_PrintStr("Letra 8x16 : Roman :zoom 2", 0, 100, White, Black, 1, 3, 2);
	 LCD_PrintStr("Letra 8x16 : Roman :zoom 3", 0, 150, White, Black, 1, 3, 3);
	 *//*
	 LCD_PrintStr("Letra 8x16 : Gold :zoom 0", 0, 0, White, Black, 1, 4, 0);
	 LCD_PrintStr("Letra 8x16 : Gold :zoom 1", 0, 50, White, Black, 1, 4, 1);
	 LCD_PrintStr("Letra 8x16 : Gold :zoom 1", 0, 100, White, Black, 1, 4, 2);
	 LCD_PrintStr("Letra 8x16 : Gold :zoom 1", 0, 150, White, Black, 1, 4, 3);
	 *//*
	 Active_Window(0, 799, 0, 479);
	 LCD_PrintStr("Letra 8x16 : Standart :zoom 1", 0, 0, White, Black, 2, 1, 0);
	 LCD_PrintStr("Letra 8x16 : Standart :zoom 2", 0, 50, White, Black, 2, 1, 1);
	 LCD_PrintStr("Letra 8x16 : Standart :zoom 3", 0, 125, White, Black, 2, 1, 2);
	 // LCD_PrintStr("Letra 8x16 : Standart :zoom 4", 0, 290, White, Black, 2, 1, 3);
	 /*
	 LCD_PrintStr("Letra 8x16 : Arial :zoom 0", 0, 0, White, Black, 1, 2, 0);
	 LCD_PrintStr("Letra 8x16 : Arial :zoom 1", 0, 50, White, Black, 1, 2, 1);
	 LCD_PrintStr("Letra 8x16 : Arial :zoom 2", 0, 100, White, Black, 1, 2, 2);
	 LCD_PrintStr("Letra 8x16 : Arial :zoom 3", 0, 150, White, Black, 1, 2, 3);
	 *//*
	 LCD_PrintStr("Letra 8x16 : Roman :zoom 0", 0, 0, White, Black, 1, 3, 0);
	 LCD_PrintStr("Letra 8x16 : Roman :zoom 1", 0, 50, White, Black, 1, 3, 1);
	 LCD_PrintStr("Letra 8x16 : Roman :zoom 2", 0, 100, White, Black, 1, 3, 2);
	 LCD_PrintStr("Letra 8x16 : Roman :zoom 3", 0, 150, White, Black, 1, 3, 3);
	 *//*
	 LCD_PrintStr("Letra 8x16 : Gold :zoom 0", 0, 0, White, Black, 1, 4, 0);
	 LCD_PrintStr("Letra 8x16 : Gold :zoom 1", 0, 50, White, Black, 1, 4, 1);
	 LCD_PrintStr("Letra 8x16 : Gold :zoom 1", 0, 100, White, Black, 1, 4, 2);
	 LCD_PrintStr("Letra 8x16 : Gold :zoom 1", 0, 150, White, Black, 1, 4, 3);
	 */

	LCD_PrintStr("Letra 8x16 : Standart :zoom 0", 0, 10, White, Black, 1, 1, 0);
	LCD_PrintStr("Letra 12x24 : Standart :zoom 0", 0, 50, White, Black, 2, 1, 0);
	LCD_PrintStr("Letra 8x16 : Arial :zoom 0", 0, 100, Blue, Black, 1, 2, 0);
	LCD_PrintStr("Letra 12x24 : Arial :zoom 0", 0, 150, Blue, Black, 2, 2, 0);
	LCD_PrintStr("Letra 8x16 : Roman :zoom 0", 0, 200, Red, Black, 1, 3, 0);
	LCD_PrintStr("Letra 12x24 : Roman :zoom 0", 0, 250, Red, Black, 2, 3, 0);
/*
	LCD_PrintStr("Letra 8x16 : Standart :zoom 1", 400, 50, White, Black, 1, 1, 1);
	LCD_PrintStr("Letra 12x24 : Standart :zoom 1", 400, 100, White, Black, 2, 1,1);
	LCD_PrintStr("Letra 8x16 : Arial :zoom 1", 400, 150, White, Black, 1, 2, 1);
	LCD_PrintStr("Letra 12x24 : Arial :zoom 1", 400, 200, White, Black, 2, 2, 1);
	LCD_PrintStr("Letra 8x16 : Roman :zoom 1", 400, 250, White, Black, 1, 3, 1);
	LCD_PrintStr("Letra 12x24 : Roman :zoom 1", 400, 300, White, Black, 2, 3, 1);
*/
}

void Test_Square(void) {
	/* CUADRADITO**************************************************
	 *
	 *
	 *
	 * *************************************************************/
	Active_Window(100, 200, 200, 300);
	Graphic_Mode();
	XY_Coordinate(100, 200);
	FSMC_WriteCmd(0x02); //MRWC
	uint32_t i;
	for (i = 0; i < 10201; i++) {
		FSMC_WriteData(Blue2);
		Chk_Busy();
	}
	Delay_ms(2000);

}
