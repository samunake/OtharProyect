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
