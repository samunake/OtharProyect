#include "RA8875/Driver_RA8875.h"
#include "LCD_System.h"

params_str print_arguments;


/************************************************************************
 * Function Name  : LCDPrintStr
 * Description    : Clear the screen
 * Input          : Color: Screen Color
 * Output         : None
 * Return         : None
 * Attention		   : None
 *******************************************************************************/
void LCDPrintStr(char *str, uint16_t x, uint16_t y, uint16_t fcolor,
		uint16_t bcolor, uint8_t mode, uint8_t type, uint8_t zoom) {

	Active_Window(0, 799, 0, 479);
	//Set Text Mode (Fonts)
	Text_Mode();
	//Memory_Clear();
	//Select in bit 5 use external font Rom
	External_CGROM();
	// Chip Font select
	GT_serial_ROM_select_GT30L32S4W();
	/*Spped Configuration
	 * 06h,0x03 SYSCLK/4
	 * 05h,20	waveform 3 selected
	 * 05h,&Ef |80  1 DUMMY CICLE*/
	SROM_CLK_DIV(0x03);
	Select_Serial_Waveform_mode3();
	SERIAL_ROM_Read_Cycle_5bus();
	// Text coordinate start position
	Font_Coordinate(x, y);
	// Text Color
	Foreground_color(fcolor);
	// BAckgroud color
	Background_color(bcolor);
	// Do align
	FullAlignment();
	// Size selection
	Font_code_ASCII();
	switch (mode) {

	case 1:
		Font_size_16x16_8x16(); //Letras de 16x16 pixels
		Font_spacing_set(0x01); //Interespaciado de 1 pixel
		Line_distance(4);
		FullAlignment();
		break;
	case 2:
		Font_size_24x24_12x24(); //Letras de 16x16 pixels
		Font_spacing_set(0x01); //Interespaciado de 1 pixel
		Line_distance(4);
		FullAlignment();
		break;
	case 3:
		Font_size_32x32_16x32(); //Letras de 16x16 pixels
		Font_spacing_set(0x01); //Interespaciado de 1 pixel
		Line_distance(4);
		FullAlignment();
		break;

	default:
		Font_size_16x16_8x16(); //Letras de 16x16 pixels
		Font_spacing_set(0x01); //Interespaciado de 1 pixel
		Line_distance(4);
		FullAlignment();
	}
	// Seltion font type (Arial, times,standard...)
	switch (type) {

	case 1:
		Font_Standard();
		break;

	case 2:
		Font_Arial();
		break;

	case 3:
		Font_Roman();
		break;
	case 4:
		Font_Bold();
		break;

	/*default:
		Font_Arial();*/


	}

	switch (zoom) {

	case 0:
		Vertical_FontEnlarge_x1();
		Horizontal_FontEnlarge_x1();
		break;
	case 1:
		Vertical_FontEnlarge_x2();
		Horizontal_FontEnlarge_x2();

		break;
	case 2:
		Vertical_FontEnlarge_x3();
		Horizontal_FontEnlarge_x3();

		break;
	case 3:
		Vertical_FontEnlarge_x4();
		Horizontal_FontEnlarge_x4();

		break;

	default:
		Vertical_FontEnlarge_x1();
		Horizontal_FontEnlarge_x1();
	}

	//start write data
	Start_Data();
	Show_String(str);
	//recovery
	LCD_WriteReg(0x21, 0x00);
	LCD_WriteReg(0x2f, 0x00);
}
/************************************************************************
 * Function Name  : Show_String
 * Description    : Clear the screen
 * Input          : Color: Screen Color
 * Output         : None
 * Return         : None
 * Attention		   : None
 *******************************************************************************/
void Show_String(char *str) {
	Text_Mode();
	LCD_WriteCmd(0x02);
	while (*str != '\0') {
		LCD_WriteData(*str);
		++str;
		Chk_Busy();
	}
}

/************************************************************************
 * Function Name  : LcdClear
 * Description    : Clear the screen
 * Input          : Color: Screen Color
 * Output         : None
 * Return         : None
 * Attention		   : None
 *******************************************************************************/
void LCD_Clear(uint16_t color) {
	Foreground_color(color); // Set the color
	Geometric_Coordinate(0, 0, 800, 479);
	LCD_WriteReg(0x90, 0xb0);

	Display_ON();
}

/*******************************************************************************
 * Function Name  : lcd_Reset
 * Description    :
 * Input          : None
 * Output         : None
 * Return         : None
 * Attention		   : None
 *******************************************************************************/
void LCD_Reset(void) {

	//RA8875 RESET pin
	GPIO_ResetBits(GPIOC, GPIO_Pin_6);
	Delay_ms(1);
	GPIO_SetBits(GPIOC, GPIO_Pin_6);
	Delay_ms(10);
}

/*******************************************************************************
 * Function Name  : Font_BTE_read_write_Interrupt_Disable
 * Description    :
 * Input          : None
 * Output         : None
 * Return         : None
 * Attention	     : None
 *******************************************************************************/
void Chk_Wait(void) {
	//while(MCU_WAIT==0);
}

void LCD_WriteText() {

	Foreground_color(White); //Set the foreground color
	Background_color(Black); //Set the background color

	Active_Window(0, 799, 0, 479);
	; //Set the work window size

	//	Memory_Clear();
	External_CGROM();
	SROM_CLK_DIV(0x03);

	//mode
	Font_size_16x16_8x16(); //Letras de 16x16 pixels
	Font_spacing_set(0x01); //Interespaciado de 1 pixel
	Line_distance(4); // 4 pixeles de distancia entre lineas

	GT_serial_ROM_select_GT30L32S4W(); //Selección del chip
	Select_Serial_Waveform_mode3();
	SERIAL_ROM_Read_Cycle_5bus(); //
	FullAlignment();

	Vertical_FontEnlarge_x4();
	Horizontal_FontEnlarge_x4();

	Font_Coordinate(208, 45); //Text written to the position
	Text_Mode();
	LCD_WriteCmd(0x02); //start write data
	Show_String("hola presidente");

	Font_Coordinate(400, 240); //Empieza a escribir en 400, 240

	Text_Mode();

	/*SERIAL_ROM_Read_Cycle_6bus();

	 Font_code_GB2312();//Selección del code setting

	 Font_Roman();//Tipo de letra

	 Text_Cursor_Disable();
	 Write_To_Bank1and2();
	 Write_To_Bank1();*/

	LCD_WriteReg(0x02, 55);
	LCD_WriteData(56);
	LCD_WriteData(57);
	LCD_WriteData(58);
	//recovery
	LCD_WriteReg(0x21, 0x00);
	LCD_WriteReg(0x2f, 0x00);

//	Active_Window(100,200,100,200);

}
