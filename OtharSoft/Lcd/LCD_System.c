/*******************************************************************************
* Function Name  : LcdClear
* Description    : Clear the screen
* Input          : Color: Screen Color
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void LCD_Clear(u16 color)
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


void LCD_WriteText(){

	SROM_CLK_DIV(3);
	Select_Serial_Waveform_mode3();
	SERIAL_ROM_Read_Cycle_6bus();

	GT_serial_ROM_select_GT30L32S4W();//Selección del chip
	Font_code_GB2312();//Selección del code setting
	Font_Roman();//Tipo de letra
	Font_spacing_set(0x01);//Interespaciado de 1 pixel
	Font_size_16x16_8x16();//Letras de 16x16 pixels
	Font_Coordinate(400,240);//Empieza a escribir en 400, 240
	Line_distance(4);// 4 pixeles de distancia entre lineas

	Text_Mode();
	Text_Cursor_Disable();
	Write_To_Bank1and2();
	Write_To_Bank1();



	LCD_WriteReg(0x020,55);
	LCD_WriteData(56);
	LCD_WriteData(57);
	LCD_WriteData(58);


}
