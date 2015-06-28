#include "Interface_RA8875.h"
#include "stm32f4xx.h"




/*******************************************************************************
* Function Name  : LCD_WriteReg
* Description    :
* Input          : - index:
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
__inline void LCD_WriteCmd(uint16_t index)
{
	LCD_CMD	= index;
}
/*******************************************************************************
* Function Name  : LCD_WriteReg
* Description    :
* Input          : - index:
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
__inline void LCD_WriteData(uint16_t data)
{

	LCD_DATA = data;
//	Delay_ms(1); //  Espacio de 5 clclos entre wr y wr (5.9*5 > 84ns) pag59 datasheet RA

}

/*******************************************************************************
* Function Name  : LCD_ReadData
* Description    :
* Input          : None
* Output         : None
* Return         :
* Attention		 : None
*******************************************************************************/
__inline uint16_t LCD_ReadData(void)
{
	return LCD_DATA;
}


/*******************************************************************************
* Function Name  : LCD_WriteReg
* Description    : Writes to the selected LCD register.
* Input          : - LCD_Reg: address of the selected register.
*                  - LCD_RegValue: value to write to the selected register.
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
__inline void LCD_WriteReg(uint16_t LCD_Reg,uint16_t LCD_RegValue)
{
	/* Write 16-bit Index, then Write Reg */
	LCD_WriteCmd(LCD_Reg);
	Delay_ms(1);
	/* Write 16-bit Reg */
	LCD_WriteData(LCD_RegValue);
}

/*******************************************************************************
* Function Name  : LCD_WriteReg
* Description    : Reads the selected LCD Register.
* Input          : None
* Output         : None
* Return         : LCD Register Value.
* Attention		 : None
*******************************************************************************/
__inline uint16_t LCD_ReadReg(uint16_t LCD_Reg)
{
	/* Write 16-bit Index (then Read Reg) */
	LCD_WriteCmd(LCD_Reg);

	/* Read 16-bit Reg */
	return LCD_ReadData();
}

/*******************************************************************************
* Function Name  : LCD_WriteRegORMask
* Description    : Reads the selected LCD Register.
* Input          : None
* Output         : None
* Return         : LCD Register Value.
* Attention		 : None
*******************************************************************************/
__inline uint16_t LCD_WriteReg_ORMask(uint16_t LCD_Reg,uint16_t mask)
{
	uint16_t temp;
	/* Write 16-bit Index (then Read Reg) */
	LCD_WriteCmd(LCD_Reg);
	/* Read 16-bit Reg */
	temp = LCD_ReadData();
	/* Apply mask */
	temp |= mask;
	/* Write Reg with OR mask */
	LCD_WriteReg(LCD_Reg,temp);
}

/*******************************************************************************
* Function Name  : LCD_WriteRegANDMask
* Description    : Reads the selected LCD Register.
* Input          : None
* Output         : None
* Return         : LCD Register Value.
* Attention		 : None
*******************************************************************************/
__inline uint16_t LCD_WriteReg_ANDMask(uint16_t LCD_Reg,uint16_t mask)
{
	uint16_t temp;
	/* Write 16-bit Index (then Read Reg) */
	LCD_WriteCmd(LCD_Reg);
	/* Read 16-bit Reg */
	temp = LCD_ReadData();
	/* Apply mask */
	temp &= mask;
	/* Write Reg with AND mask */
	LCD_WriteReg(LCD_Reg,temp);
}


/*******************************************************************************
* Function Name  : LCD_WriteRegANDORMask
* Description    : Reads the selected LCD Register.
* Input          : None
* Output         : None
* Return         : LCD Register Value.
* Attention		 : None
*******************************************************************************/
__inline uint16_t LCD_WriteReg_ANDORMask(uint16_t LCD_Reg,uint16_t AND_mask,uint16_t OR_mask)
{
	uint16_t temp;
	/* Write 16-bit Index (then Read Reg) */
	LCD_WriteCmd(LCD_Reg);
	/* Read 16-bit Reg */
	temp = LCD_ReadData();
	/* Apply mask */
	temp &= AND_mask;
	temp |= OR_mask;
	/* Write Reg with AND mask */
	LCD_WriteReg(LCD_Reg,temp);
}

__inline uint16_t LCD_StatusRead(void)
{

    return (LCD_CMD);
}
/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
