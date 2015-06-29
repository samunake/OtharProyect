#include "RA8875/Driver_RA8875.h"
/************************************************************************
* Function Name  : LcdClear
* Description    : Clear the screen
* Input          : Color: Screen Color
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void LCD_Clear(uint16_t color)
{
	//Text_Fo(color); // Set the color
	Geometric_Coordinate(0,0,800,479);
	LCD_WriteReg(0x90,0xb0);

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
void LCD_Reset(void)
{

	 //RA8875 RESET pin
	GPIO_ResetBits(GPIOC,GPIO_Pin_6);
	Delay_ms(1);
	GPIO_SetBits(GPIOC,GPIO_Pin_6);
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
void Chk_Wait(void)
{
 //while(MCU_WAIT==0);
}

void Show_String(uint8_t *str,uint8_t n)
{
  Text_Mode();
  LCD_CmdWrite(0x02);
  while(*str != '\0')
  {
     LCD_DataWrite(*str);
     ++str;
     Chk_Busy();
     //Chk_Wait();
   }
}

void String(char *str)
{
    LCD_WriteReg(0x40,0x80);//Set the character mode
	LCD_WriteCmd(0x02);
	while(*str != '\0')
	{
	 LCD_WriteData(*str);
	 ++str;
	 Chk_Busy();
	}
}


void LCD_WriteText(){

					Foreground_color(White);//Set the foreground color
					Background_color(Black);//Set the background color
					Active_Window(0,799,0,479);;//Set the work window size
				//	Memory_Clear();
					External_CGROM();
					SROM_CLK_DIV(0x03);
					Font_size_16x16_8x16();//Letras de 16x16 pixels
					Font_spacing_set(0x01);//Interespaciado de 1 pixel
					GT_serial_ROM_select_GT30L32S4W();//Selección del chip
					Select_Serial_Waveform_mode3();
					SERIAL_ROM_Read_Cycle_5bus(); //
					FullAlignment();
					Line_distance(4);// 4 pixeles de distancia entre lineas



				    Vertical_FontEnlarge_x4();
				    Horizontal_FontEnlarge_x4();

					Font_Coordinate(208,45);//Text written to the position
				    Text_Mode();
				    LCD_WriteCmd(0x02);//start write data
				    String("hola presidente");









	Font_Coordinate(400,240);//Empieza a escribir en 400, 240

	Text_Mode();

	/*SERIAL_ROM_Read_Cycle_6bus();

	Font_code_GB2312();//Selección del code setting

	Font_Roman();//Tipo de letra

	Text_Cursor_Disable();
	Write_To_Bank1and2();
	Write_To_Bank1();*/



	LCD_WriteReg(0x02,55);
	LCD_WriteData(56);
	LCD_WriteData(57);
	LCD_WriteData(58);
	//recovery
	LCD_WriteReg(0x21,0x00);
	LCD_WriteReg(0x2f,0x00);

//	Active_Window(100,200,100,200);




}
