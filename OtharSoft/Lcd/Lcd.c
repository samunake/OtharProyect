#include "Fsmc.h"
//#include "LightButton.h"
#include "SquareButton.h"
#include "Logo.h"
#include "RA8875.h"
#include "defines.h"
#include "Lcd.h"
/*******************************************************************************
 * Function Name  : LCD_Initializtion
 * Description    : RA8875 Resets
 * Input          : None
 * Output         : None
 * Return         : None
 * Attention		 : None
 *******************************************************************************/

	uint8_t linea = 0;

void LCD_Init(void) {
	FSMC_Init();

	BackLight_Timer();

	PLL_init();

	//ER-TFTM050-3 SETTINGS
	//==============	Display Window	800x480 ==================
	uint16_t temp;
	FSMC_WriteReg(0x10, 0x0F); //SYSR 16bit MCU interface   and 65k color display
	Delay_ms(10);
	FSMC_WriteReg(0x04, 0x81); //PCLK inverse	(Falling Edge - SYSCLK*2)
	Delay_ms(10);
	temp = FSMC_StatusRead();

	//Horizontal set
	FSMC_WriteReg(0x14, 0x63); //HDWR//Horizontal Display Width Setting Bit[6:0]
	// Delay_ms(10);
	FSMC_WriteReg(0x15, 0x00); //Horizontal Non-Display Period Fine Tuning Option Register (HNDFTR) 0
	//   Delay_ms(10);
	FSMC_WriteReg(0x16, 0x03); //HNDR//Horizontal Non-Display Period Bit[4:0]  3
	//   Delay_ms(10);
	FSMC_WriteReg(0x17, 0x03); //HSTR//HSYNC Start Position[4:0]   3
	//  Delay_ms(10);
	FSMC_WriteReg(0x18, 0x0B); //HPWR//HSYNC Polarity ,The period width of HSYNC.  B
	//   Delay_ms(10);

	//Vertical set
	FSMC_WriteReg(0x19, 0xdf); //VDHR0 //Vertical Display Height Bit [7:0]
	//   Delay_ms(10);
	FSMC_WriteReg(0x1a, 0x01); //VDHR1 //Vertical Display Height Bit [8] 01
	//   Delay_ms(10);
	FSMC_WriteReg(0x1b, 0x20); //VNDR0 //Vertical Non-Display Period Bit [7:0] 20
	//   Delay_ms(10);
	FSMC_WriteReg(0x1c, 0x00); //VNDR1 //Vertical Non-Display Period Bit [8] 00
	//   Delay_ms(10);
	FSMC_WriteReg(0x1d, 0x16); //VSTR0 //VSYNC Start Position[7:0] 16
	//   Delay_ms(10);
	FSMC_WriteReg(0x1e, 0x00); //VSTR1 //VSYNC Start Position[8] 00
	//   Delay_ms(10);
	FSMC_WriteReg(0x1f, 0x01); //VPWR //VSYNC Polarity ,VSYNC Pulse Width[6:0] 01
	//   Delay_ms(10);

	//Active window  set
	//setting active window X (0,799) ---(0X0000,0X031F)
	FSMC_WriteReg(0x30, 0x00); //Horizontal Start Point 0 of Active Window (HSAW0)
	//   Delay_ms(10);
	FSMC_WriteReg(0x31, 0x00); //Horizontal Start Point 1 of Active Window (HSAW1)
	//   Delay_ms(10);
	FSMC_WriteReg(0x34, 0x1f); //Horizontal End Point 0 of Active Window (HEAW0)
	//   Delay_ms(10);
	FSMC_WriteReg(0x35, 0x03); //Horizontal End Point 1 of Active Window (HEAW1)
	//  Delay_ms(10);

	//setting active window Y (0,479)---(0X0000,0X01DF)
	FSMC_WriteReg(0x32, 0x00); //Vertical Start Point 0 of Active Window (VSAW0)
	//   Delay_ms(10);
	FSMC_WriteReg(0x33, 0x00); //Vertical Start Point 1 of Active Window (VSAW1)
	//   Delay_ms(10);
	FSMC_WriteReg(0x36, 0xdf); //Vertical End Point of Active Window 0 (VEAW0)
	//   Delay_ms(10);
	FSMC_WriteReg(0x37, 0x01); //Vertical End Point of Active Window 1 (VEAW1)

}

/************************************************************************
 * Function Name  : LCDPrintStr
 * Description    : Clear the screen
 * Input          : Color: Screen Color
 * Output         : None
 * Return         : None
 * Attention		   : None
 *******************************************************************************/
void LCD_PrintStr(char *str, uint16_t x, uint16_t y, uint16_t fcolor,
		uint16_t bcolor, uint8_t mode, uint8_t type, uint8_t zoom) {

	External_Font();
	//Active_Window(0, 799, 0, 479);
	//Set Text Mode (Fonts)
	TextMode_Normal();
	//Memory_Clear();

	// Text coordinate start position
	Font_Coordinate(x, y);
	// Text Color
	Foreground_color(fcolor);
	// BAckgroud color
	Background_color(bcolor);
	// Do align
	FullAlignment();
	// Size selection
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
	FSMC_WriteCmd(0x02);
	Show_String(str);
	//recovery
	FSMC_WriteReg(0x21, 0x00);
	FSMC_WriteReg(0x2f, 0x00);
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
	FSMC_WriteCmd(0x02);
	while (*str != '\0') {
		FSMC_WriteData(*str);
		++str;
		Chk_Busy();
	}
}

/************************************************************************
 * Function Name  : LCD_Clear
 * Description    : Clear the screen
 * Input          : Color: Screen Color
 * Output         : None
 * Return         : None
 * Attention		   : None
 *******************************************************************************/
void LCD_Clear(uint16_t color, uint8_t size) {
	if (size == 0) {
		Active_Window(0, 799, 70, 400);
	}
	if (size == 1) {
		Active_Window(0, 799, 0, 479);
	}
	if (size == 2) {
		//	Active_Window(0, 799, 0, 479);
		}
	Foreground_color(color); // Set the color
	Geometric_Coordinate(0, 0, 800, 479);
	FSMC_WriteReg(0x90, 0xb0);

}

/*******************************************************************************
 * Function Name  : LCD_Reset
 * Description    :
 * Input          : None
 * Output         : None
 * Return         : None
 * Attention		   : None
 *******************************************************************************/
void LCD_Reset(void) {

	//RA8875 RESET pin
	GPIO_ResetBits(GPIOC, GPIO_Pin_6);
	Delay_ms(10);
	GPIO_SetBits(GPIOC, GPIO_Pin_6);
	Delay_ms(10);
}

/*******************************************************************************
 * Function Name  : Chk_Wait
 * Description    :
 * Input          : None
 * Output         : None
 * Return         : None
 * Attention	     : None
 *******************************************************************************/
void Chk_Wait(void) {
	//while(MCU_WAIT==0);
}

/************************************************************************
 * Function Name  : Show_String
 * Description    : Clear the screen
 * Input          : Color: Screen Color
 * Output         : None
 * Return         : None
 * Attention		   : None
 *******************************************************************************/
void print_BTEImage(uint16_t XL, uint16_t XR, uint16_t YT, uint16_t YB) {
	uint16_t i;
	Graphic_Mode();
	//Set destiny point
	BTE_Source_Destination(XL, XR, YT, YB);
	//Set Image width and weight
	BTE_Size_setting(200, 240);
	//set BTE write and ROP source = Destination
	BTE_ROP_Code(0xC0);
	BTE_enable();

	FSMC_WriteCmd(0x02); //MRWC
	for (i = 0; i < 48000; i++) {
		FSMC_WriteData(SquareButton[i]);
		Chk_Busy();
	}
}

/************************************************************************
 * Function Name  : Show_String
 * Description    : Clear the screen
 * Input          : Color: Screen Color
 * Output         : None
 * Return         : None
 * Attention		   : None
 *******************************************************************************/
void print_BTELogo(uint16_t XL, uint16_t XR, uint16_t YT, uint16_t YB) {
	uint16_t i;
	Graphic_Mode();
	//Set destiny point
	BTE_Source_Destination(XL, XR, YT, YB);
	//Set Image width and weight
	BTE_Size_setting(110, 40);
	//set BTE write and ROP source = Destination
	BTE_ROP_Code(0xC0);
	BTE_enable();

	FSMC_WriteCmd(0x02); //MRWC
	for (i = 0; i < 4400; i++) {
		FSMC_WriteData(logo[i]);
		Chk_Busy();
	}
}

/************************************************************************
 * Function Name  : Show_String
 * Description    : Clear the screen
 * Input          : Color: Screen Color
 * Output         : None
 * Return         : None
 * Attention		   : None
 *******************************************************************************/
void print_pureImage(void) { /*(0,200,120,360)*/
	uint16_t i;
	//Active Window
	Active_Window(0, 199, 100, 339);
	//Coordinates
	XY_Coordinate(0, 100);
	Graphic_Mode();
	FSMC_WriteCmd(0x02); //set CMD02 to  prepare data write
	for (i = 0; i < 48000; i++) {
		//FSMC_WriteData(image[i]); //write black data
		Chk_Busy();
	}
}

/************************************************************************
 * Function Name  : Show_String
 * Description    : Clear the screen
 * Input          : Color: Screen Color
 * Output         : None
 * Return         : None
 * Attention		   : None
 *******************************************************************************/
void Check_toLCD(char *str) {

	Active_Window(0,799,0,479);
	Foreground_color(Black);

	LCD_PrintStr(str, 10, 10+linea, Blue2, Black, 2, 1, 0);
	/*----SALTO DE LINA RA8875 CURSOR---*/
	linea+=20;
	if(linea>460) {
		linea= 10;
		LCD_Clear(Black,FULL_LCD);
	}
}

void print_Buttons(void) {

	/**************Print LightButtons***********************/
	uint16_t i;
	for (i = 0; i < 4; i++) {

		print_BTEImage(0, i * 200, 0, 120);
	}
}
void print_Logo(void) {
	/**************Print Logo***********************/
	print_BTELogo(0, 675, 0, 420);
}
