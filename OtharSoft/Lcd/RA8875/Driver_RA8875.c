/*********************************************************************************************************
*
* File                : LCD_Driver.c
* Hardware Environment:
* Build Environment   : CooCox CoIDE  Version: 1.7.8
* Version             : V1.0
* By                  : Tomás Ariza Crespo
*
*
*********************************************************************************************************/



/* Includes --------------------------------------------------------------------------------------------*/
#include "Driver_RA8875.h"
#include "Config_RA8875.h"



/* Register Functions ----------------------------------------------------------------------------------*/

//																								STATUS REGISTER

/*******************************************************************************
* Function Name  : Chk_Busy
* Description    : Check whether the Memory Read/Write is busy
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void Chk_Busy(void)
{
	uint8_t temp;
	do
	{
	  temp=LCD_StatusRead();
	}while((temp&0x80)==0x80);
}

/*******************************************************************************
* Function Name  : Chk_Busy_BTE
* Description    : Check whether the BTE is busy
* Input          : None
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void Chk_Busy_BTE(void)
{
	uint8_t temp;
	do
	{
       temp=LCD_StatusRead();
	}while((temp&0x40)==0x40);
}

/*******************************************************************************
* Function Name  : Chk_Busy_DIR_Access
* Description    : Check whether the DIR_Access is busy
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void Chk_Busy_DIR_Access(void)
{
	uint8_t  temp;
	do
	{
       temp=LCD_StatusRead();
	}while((temp&0x01)==0x01);
}
//REG[BFh]
/*******************************************************************************
* Function Name  : Chk_DMA_Busy
* Description    : Check whether the DMA is busy
* Input          : None
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void Chk_DMA_Busy(void)
{
	uint8_t temp;
	do
	{
		temp = LCD_ReadReg(0xbf);
	}while((temp&0x01)==0x01);
}
//																								REG[01h]
/*******************************************************************************
* Function Name  : Display_ON
* Description    : Display on
* Input          : None
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void Display_ON(void)
{
	LCD_WriteReg(0x01,0x80); //PWRR


}
/*******************************************************************************
* Function Name  : Display_OFF
* Description    : Display OFF
* Input          : None
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void Display_OFF(void)
{
	LCD_WriteReg(0x01,0x00); //PWRR

}

/*******************************************************************************
* Function Name  : Normal_Mode_exitSleep
* Description    : Normal mode
* Input          : None
* Output         : None
* Return         : None
* Attention		   : 1. There are 3 ways to wake up from sleep mode:
						Touch Panel wake up, Key Scan wake up ,Software wake up.
					 2. When using IIC interface, this function is not supported.
*******************************************************************************/
void Normal_Mode_exitSleep(void)
{
	LCD_WriteReg_ANDMask(0x01,0xFD); //PWRR
}

/*******************************************************************************
* Function Name  : Sleep_Mode
* Description    : Sleep mode.
* Input          : None
* Output         : None
* Return         : None
* Attention		   : 1. There are 3 ways to wake up from sleep mode:
						Touch Panel wake up, Key Scan wake up ,Software wake up.
					 2. When using IIC interface, this function is not supported.
*******************************************************************************/
void Sleep_Mode(void)
{
	LCD_WriteReg(0x01,0x02); //PWRR

}
/*******************************************************************************
* Function Name  : Software_Reset
* Description    : Software Reset.
* Input          : None
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void Software_Reset(void)
{
	LCD_WriteReg(0x01,0x01); //PWRR
    LCD_WriteData(0x00);// No hay que hacer un writeCmd primero ?
    Delay_ms(1);
}
//																								REG[02h]
/*******************************************************************************
* Function Name  : Start
* Description    : Start writing/reading data to LCD
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void Start_Data(void){

	LCD_WriteCmd(0x02);
}
//																								REG[04h]
/*******************************************************************************
* Function Name  : PCLK_inversion (Pixel Clock Setting Register)
* Description    : PDAT is fetched at PCLK falling edge.
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void PCLK_inversion(void)
{
	LCD_WriteReg_ORMask(0x04,0x80);//PCSR
}


//
/*******************************************************************************
* Function Name  : PCLK_non_inversion (Pixel Clock Setting Register)
* Description    : PDAT is fetched at PCLK rising edge.
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void PCLK_non_inversion(void)
{

	LCD_WriteReg_ANDMask(0x04,0x7f);//PCSR
}

/*******************************************************************************
* Function Name  : PCLK_width
* Description    : PCLK Period Setting  (Pixel clock (PCLK) period setting. )
* Input          : setx:
							00b: PCLK period = System Clock period.
							01b: PCLK period = 2 times of System Clock period.
							10b: PCLK period = 4 times of System Clock period.
							11b: PCLK period = 8 times of System Clock period.
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void PCLK_width(uint8_t setx) //uint8_t[1:0]
{
    LCD_WriteReg_ANDORMask(0x04,0x80,setx);//PCSR
}

//																								REG[05h]
/*******************************************************************************
* Function Name  : Serial_ROM_select0
* Description    : Serial Flash/ROM 0 I/F is selected.
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void Serial_ROM_select0(void)
{
   LCD_WriteReg_ANDMask(0x05,0x7f);//SROC
}

/*******************************************************************************
* Function Name  : Serial_ROM_select1
* Description    : Serial Flash/ROM 0 or 1 I/F is selected.
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Serial_ROM_select1(void)
{
	LCD_WriteReg_ORMask(0x05,0x80);//SROC
}

/*******************************************************************************
* Function Name  : Serial_ROM_Address_set_24bit
* Description    : 24 bits address mode
* Input          : None
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void Serial_ROM_Address_set_24bit(void)
{
    LCD_WriteReg_ANDMask(0x05,0xbf);//SROC
}

/*******************************************************************************
* Function Name  : Serial_ROM_Address_set_32bit
* Description    : 32 bits address mode
* Input          : None
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void Serial_ROM_Address_set_32bit(void)
{
	LCD_WriteReg_ORMask(0x05,0x40);//SROC
}

/*******************************************************************************
* Function Name  : Select_Serial_Waveform_mode0
* Description    : Mode 0.
* Input          : None
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void Select_Serial_Waveform_mode0(void)
{
    LCD_WriteReg_ANDMask(0x05,0xdf);//SROC
}
/*******************************************************************************
* Function Name  : Select_Serial_Waveform_mode3
* Description    : Mode 3.
* Input          : None
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void Select_Serial_Waveform_mode3(void)
{
    LCD_WriteReg_ORMask(0x05,0x20);//SROC
}
/*******************************************************************************
* Function Name  : SERIAL_ROM_Read_Cycle_4bus
* Description    : 4 bus -> no dummy cycle
* Input          : None
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void SERIAL_ROM_Read_Cycle_4bus(void)
{
	LCD_WriteReg_ANDMask(0x05,0xE7);//SROC
}

/*******************************************************************************
* Function Name  : SERIAL_ROM_Read_Cycle_5bus
* Description    : 5 bus -> no dummy cycle
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void SERIAL_ROM_Read_Cycle_5bus(void)
{
	LCD_WriteReg_ANDORMask(0x05,0xEF,0x08);//SROC
}
/*******************************************************************************
* Function Name  : SERIAL_ROM_Read_Cycle_6bus
* Description    : 6 bus -> no dummy cycle
* Input          : None
* Output         : None
* Return         : None
* Attention		  : None
*******************************************************************************/
void SERIAL_ROM_Read_Cycle_6bus(void)
{
	LCD_WriteReg_ORMask(0x05,0x10);//SROC
}

/*******************************************************************************
* Function Name  : SERIAL_ROM_Font_mode
* Description    : Font mode
* Input          : None
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void SERIAL_ROM_Font_mode(void)
{
	LCD_WriteReg_ANDMask(0x05,0xFB);//SROC
}

/*******************************************************************************
* Function Name  : SERIAL_ROM_DMA_mode
* Description    : DMA mode
* Input          : None
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void SERIAL_ROM_DMA_mode(void)
{
	LCD_WriteReg_ORMask(0x05,0x04);//SROC
}

/*******************************************************************************
* Function Name  : SERIAL_ROM_Single_mode
* Description    : Single Mode
* Input          : None
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void SERIAL_ROM_Single_mode(void)
{
	LCD_WriteReg_ANDMask(0x05,0xFD);//SROC
}

/*******************************************************************************
* Function Name  : SERIAL_ROM_Dual_mode0
* Description    : Dual Mode 0
* Input          : None
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/

void SERIAL_ROM_Dual_mode0(void)
{
	LCD_WriteReg_ANDORMask(0x05,0xFE,0x02);//SROC
}

/*******************************************************************************
* Function Name  : SERIAL_ROM_Dual_mode1
* Description    : Dual Mode 1
* Input          : None
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void SERIAL_ROM_Dual_mode1(void)
{
	LCD_WriteReg_ORMask(0x05,0x03);//SROC
}

/*******************************************************************************
* Function Name  : SROM_CLK_DIV
* Description    : Serial Flash/ROM Clock Frequency Setting
* Input          : CLK_DIV £ºSerial Flash/ROM Clock Frequency Setting
*									0xb: SFCL frequency = System clock frequency
*											 (When DMA enable and Color depth = 256 color
*											  SFCL frequency = System clock frequency /2)
*									10b: SFCL frequency = System clock frequency / 2
*									11b: SFCL frequency = System clock frequency / 4
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void SROM_CLK_DIV(uint8_t CLK_DIV)
{
	LCD_WriteReg(0x06,CLK_DIV);//SFCLR
}

//REG[10h]
/*******************************************************************************
* Function Name  : Color_256
* Description    : Color Depth Setting £¬8-bpp generic TFT, i.e. 256 colors
* Input          : None
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void Color_256(void)
{
	LCD_WriteReg_ANDMask(0x10,0xF3);//SYSR
}

/*******************************************************************************
* Function Name  : Color_65K
* Description    : Color Depth Setting 16-bpp generic TFT, i.e. 65K colors.
* Input          : None
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void Color_65K(void)
{
	LCD_WriteReg_ORMask(0x10,0x08);//SYSR
}

/*******************************************************************************
* Function Name  : MPU_8bit_Interface
* Description    : MCUIF Selection £¬ 8-bit MCU Interface.
* Input          : None
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void MPU_8bit_Interface(void)
{
	LCD_WriteReg_ANDMask(0x10,0xFC);//SYSR
}

/*******************************************************************************
* Function Name  : MPU_16bit_Interface
* Description    : MCUIF Selection £¬ 16-bit MCU Interface.
* Input          : None
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void MPU_16bit_Interface(void)
{
	LCD_WriteReg_ORMask(0x10,0x02);//SYSR
}

//																									REG[12h]
/*******************************************************************************
* Function Name  : GPI_data
* Description    : General Purpose Input.
* Input          : None
* Output         : None
* Return         : None
* Attention		   : KEY_EN : REG[C0h] bit 7
*******************************************************************************/
uint8_t GPI_data(void)
{
  //Mirar para que se utiliza esta funcion //////////////////////////////////////////////////
   return LCD_ReadReg(0x12);
}

//REG[13h]
/*******************************************************************************
* Function Name  : GPO_data
* Description    : General Purpose Output
* Input          : setx GPO[3:0] : General Purpose Output
* Output         : None
* Return         : None
* Attention		 : KEY_EN : REG[C0h] bit 7
*******************************************************************************/
void GPO_data(uint8_t setx)
{
   LCD_WriteReg(0x13,setx);
}

//REG[20h]
/*******************************************************************************
* Function Name  : One_Layer
* Description    : Layer Setting Control £¬One layer configuration is selected.
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void One_Layer(void)
{
	LCD_WriteReg_ANDMask(0x20,0x7f);//DPCR
}

/*******************************************************************************
* Function Name  : Two_Layers
* Description    : Layer Setting Control £¬Two layers configuration is selected..
* Input          : None
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void Two_Layers(void)
{
	LCD_WriteReg_ORMask(0x20,0x80);//DPCR
}

/*******************************************************************************
* Function Name  : HDIR_SEG0_SEGn
* Description    : Horizontal Scan Direction, for n = SEG number. SEG0 to SEG(n-1).
* Input          : None
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void HDIR_SEG0_SEGn(void)
{
	LCD_WriteReg_ANDMask(0x20,0xf7);//DPCR
}

/*******************************************************************************
* Function Name  : HDIR_SEGn_SEG0
* Description    : Horizontal Scan Direction, for n = SEG number. SEG(n-1) to SEG0.
* Input          : None
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void HDIR_SEGn_SEG0(void)
{
	LCD_WriteReg_ORMask(0x20,0x08);//DPCR
}

/*******************************************************************************
* Function Name  : VDIR_COM0_COMn
* Description    : Vertical Scan direction, for n = COM numbe £ºCOM0 to COM(n-1)
* Input          : None
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void VDIR_COM0_COMn(void)
{
	LCD_WriteReg_ANDMask(0x20,0xfb);//DPCR
}

/*******************************************************************************
* Function Name  : VDIR_COMn_COM0
* Description    : Vertical Scan direction, for n = COM numbe £ºCOM(n-1) to COM0
* Input          : None
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void VDIR_COMn_COM0(void)
{
	LCD_WriteReg_ORMask(0x20,0x04);//DPCR
}

//REG[21h]
/*******************************************************************************
* Function Name  : CGROM_Font
* Description    : CGRAM/CGROM Font Selection Bit in Text Mode £¬CGROM font is selected.
* Input          : None
* Output         : None
* Return         : None
* Attention		 :  The bit is used to select the bit-map source when text-
					mode is active(REG[40h] bit 7 is 1), when CGRAM is
					writing(REG[41h] bit 3-2 =01b), the bit  must be set as ¡°0¡±.
*******************************************************************************/
void CGROM_Font(void)
{
	LCD_WriteReg_ANDMask(0x21,0x7F);//FNCR0
}
/*******************************************************************************
* Function Name  : CGROM_Font
* Description    : CGRAM/CGROM Font Selection Bit in Text Mode £¬CGRAM font is selected.
* Input          : None
* Output         : None
* Return         : None
* Attention		 :  The bit is used to select the bit-map source when text-
					mode is active(REG[40h] bit 7 is 1), when CGRAM is
					writing(REG[41h] bit 3-2 =01b), the bit  must be set as ¡°0¡±.
*******************************************************************************/
void CGRAM_Font(void)
{
	LCD_WriteReg_ORMask(0x21,0x80);//FNCR0
}

/*******************************************************************************
* Function Name  : Internal_CGROM
* Description    : External/Internal CGROM Selection Bit £¬
				   Internal CGROM is selected.(REG[2Fh] must be set 00h )
* Input          : None
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/

void Internal_CGROM(void)
{
	LCD_WriteReg_ANDMask(0x21,0xdf);//FNCR0
}
/*******************************************************************************
* Function Name  : External_CGROM
* Description    : External/Internal CGROM Selection Bit £¬
									  External CGROM is selected.
* Input          : None
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void External_CGROM(void)
{
	LCD_WriteReg_ORMask(0x21,0x20);//FNCR0
}

/*******************************************************************************
* Function Name  : ISO8859_1
* Description    :  When FNCR0 B7 = 0 and B5 = 0, Internal CGROM supports the
										8x16 character sets with the standard coding of ISO/IEC 8859-
										1~4, which supports English and most of European country
										languages.

										Selection ISO/IEC 8859-1.
* Input          : None
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void ISO8859_1(void)
{
	LCD_WriteReg_ANDMask(0x21,0xFC);//FNCR0
}

/*******************************************************************************
* Function Name  : ISO8859_2
* Description    :  When FNCR0 B7 = 0 and B5 = 0, Internal CGROM supports the
										8x16 character sets with the standard coding of ISO/IEC 8859-
										1~4, which supports English and most of European country
										languages.

										Selection ISO/IEC 8859-2.
* Input          : None
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void ISO8859_2(void)
{
	LCD_WriteReg_ANDORMask(0x21,0xFD,0x01);//FNCR0
}

/*******************************************************************************
* Function Name  : ISO8859_3
* Description    :  When FNCR0 B7 = 0 and B5 = 0, Internal CGROM supports the
										8x16 character sets with the standard coding of ISO/IEC 8859-
										1~4, which supports English and most of European country
										languages.

										Selection ISO/IEC 8859-3.
* Input          : None
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void ISO8859_3(void)
{
	LCD_WriteReg_ANDORMask(0x21,0xFE,0x02);//FNCR0
}
/*******************************************************************************
* Function Name  : ISO8859_4
* Description    :  When FNCR0 B7 = 0 and B5 = 0, Internal CGROM supports the
										8x16 character sets with the standard coding of ISO/IEC 8859-
										1~4, which supports English and most of European country
										languages.

										Selection ISO/IEC 8859-4.
* Input          : None
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void ISO8859_4(void)
{
	LCD_WriteReg_ORMask(0x21,0x03);//FNCR0
}


//REG[22h]
/*******************************************************************************
* Function Name  : No_FullAlignment
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void No_FullAlignment(void)
{
	LCD_WriteReg_ANDMask(0x22,0x7F);//FNCR1
}

/*******************************************************************************
* Function Name  : FullAlignment
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void FullAlignment(void)
{
	LCD_WriteReg_ORMask(0x22,0x80);//FNCR1
}

/*******************************************************************************
* Function Name  : Font_with_BackgroundColor
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void Font_with_BackgroundColor(void)
{
	LCD_WriteReg_ANDMask(0x22,0xBF);//FNCR1
}

/*******************************************************************************
* Function Name  : Font_with_BackgroundTransparency
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void Font_with_BackgroundTransparency(void)
{
	LCD_WriteReg_ORMask(0x22,0x40);//FNCR1
}

/*******************************************************************************
* Function Name  : NoRotate_Font
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void NoRotate_Font(void)
{
	LCD_WriteReg_ANDMask(0x22,0xEF);//FNCR1
}

/*******************************************************************************
* Function Name  : Rotate90_Font
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void Rotate90_Font(void)
{
	LCD_WriteReg_ORMask(0x22,0x10);//FNCR1
}

/*******************************************************************************
* Function Name  : Horizontal_FontEnlarge_x1
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void Horizontal_FontEnlarge_x1(void)
{
	LCD_WriteReg_ANDMask(0x22,0xF3);//FNCR1
}

/*******************************************************************************
* Function Name  : Horizontal_FontEnlarge_x2
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void Horizontal_FontEnlarge_x2(void)
{
	LCD_WriteReg_ANDORMask(0x22,0xF7,0x04);//FNCR1
}

/*******************************************************************************
* Function Name  : Horizontal_FontEnlarge_x3
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void Horizontal_FontEnlarge_x3(void)
{
	LCD_WriteReg_ANDORMask(0x22,0xFB,0x08);//FNCR1
}

/*******************************************************************************
* Function Name  : Horizontal_FontEnlarge_x4
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void Horizontal_FontEnlarge_x4(void)
{
	LCD_WriteReg_ORMask(0x22,0x0C);//FNCR1
}

/*******************************************************************************
* Function Name  : Vertical_FontEnlarge_x1
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void Vertical_FontEnlarge_x1(void)
{
	LCD_WriteReg_ANDMask(0x22,0xFC);//FNCR1
}

/*******************************************************************************
* Function Name  : Vertical_FontEnlarge_x2
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void Vertical_FontEnlarge_x2(void)
{
	LCD_WriteReg_ANDORMask(0x22,0xFD,0x01);//FNCR1
}

/*******************************************************************************
* Function Name  : Vertical_FontEnlarge_x3
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void Vertical_FontEnlarge_x3(void)
{
	LCD_WriteReg_ANDORMask(0x22,0xFE,0x02);//FNCR1
}

/*******************************************************************************
* Function Name  : Vertical_FontEnlarge_x4
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void Vertical_FontEnlarge_x4(void)
{
	LCD_WriteReg_ORMask(0x22,0x03);//FNCR1
}


//REG[23h]
/*******************************************************************************
* Function Name  : CGRAM_Select_Number
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void CGRAM_Select_Number(uint8_t setx)
{
	LCD_WriteReg(0x23,setx);
}


//REG[24h]REG[25h]REG[26h]REG[27h]
/*******************************************************************************
* Function Name  : Scroll_Offset
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void Scroll_Offset(uint16_t X,uint16_t Y)
{
	LCD_WriteReg(0x24,X);

	LCD_WriteReg(0x25,X>>8);

	LCD_WriteReg(0x26,Y);

	LCD_WriteReg(0x27,Y>>8);
}


//REG[29h]
/*******************************************************************************
* Function Name  : Line_distance
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void Line_distance(uint8_t setx)
{
	LCD_WriteReg(0x29,setx);
}


//REG[2Ah]REG[2Bh]REG[2Ch]REG[2Dh]
/*******************************************************************************
* Function Name  : Font_Coordinate
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void Font_Coordinate(uint16_t X,uint16_t Y)
{

	LCD_WriteReg(0x2A,X);

	LCD_WriteReg(0x2B,X>>8);

	LCD_WriteReg(0x2C,Y);

	LCD_WriteReg(0x2D,Y>>8);
}



//REG[2Eh]
/*******************************************************************************
* Function Name  : Font_size_16x16_8x16
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void Font_size_16x16_8x16(void)
{
	LCD_WriteReg_ANDMask(0x2E,0x3F);//FWTSR
}

/*******************************************************************************
* Function Name  : Font_size_24x24_12x24
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void Font_size_24x24_12x24(void)
{
	LCD_WriteReg_ANDORMask(0x2E,0x7F,0x40);//FWTSR
}

/*******************************************************************************
* Function Name  : Font_size_32x32_16x32
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void Font_size_32x32_16x32(void)
{
	LCD_WriteReg_ORMask(0x2E,0x80);//FWTSR
}

/*******************************************************************************
* Function Name  : Font_spacing_set
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void Font_spacing_set(uint8_t setx) //uint8_t[5:0]
{
	uint8_t temp;
    temp=setx&0x3F;//Nos quedamos con los bits 5:0 de setx

    LCD_WriteReg_ANDORMask(0x2E,0xC0,temp);//FWTSR
}

//REG[2Fh]
/*******************************************************************************
* Function Name  : GT_serial_ROM_select_GT21L16TW
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void GT_serial_ROM_select_GT21L16TW(void)//GT21L16T1W
{
	LCD_WriteReg_ANDMask(0x2F,0x1F);
}


/*******************************************************************************
* Function Name  : GT_serial_ROM_select_GT21L16TW
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void GT_serial_ROM_select_GT30L16U2W(void)
{
	LCD_WriteReg_ANDORMask(0x2F,0x1F,0x20);
}


/*******************************************************************************
* Function Name  : GT_serial_ROM_select_GT30L24T3Y
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void GT_serial_ROM_select_GT30L24T3Y(void)//GT30H24T3Y
{
	LCD_WriteReg_ANDORMask(0x2F,0x1F,0x40);
}

/*******************************************************************************
* Function Name  : GT_serial_ROM_select_GT30L24M1Z
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void GT_serial_ROM_select_GT30L24M1Z(void)
{
	LCD_WriteReg_ANDORMask(0x2F,0x1F,0x60);
}


/*******************************************************************************
* Function Name  : GT_serial_ROM_select_GT30L32S4W
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void GT_serial_ROM_select_GT30L32S4W(void)//GT30H32S4W
{
	LCD_WriteReg_ANDORMask(0x2F,0x1F,0x80);
}


/*******************************************************************************
* Function Name  : Font_code_GB2312
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void Font_code_GB2312(void)
{
	LCD_WriteReg_ANDMask(0x2F,0xE3);
}

/*******************************************************************************
* Function Name  : Font_code_GB12345
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void Font_code_GB12345(void)//GB18030
{
	LCD_WriteReg_ANDORMask(0x2F,0xE3,0x04);
}

/*******************************************************************************
* Function Name  : Font_code_BIG5
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void Font_code_BIG5(void)
{
	LCD_WriteReg_ANDORMask(0x2F,0xE3,0x08);
}

/*******************************************************************************
* Function Name  : Font_code_UNICODE
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void Font_code_UNICODE(void)
{
	LCD_WriteReg_ANDORMask(0x2F,0xE3,0x0C);
}

/*******************************************************************************
* Function Name  : Font_code_ASCII
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void Font_code_ASCII(void)
{
	LCD_WriteReg_ANDORMask(0x2F,0xE3,0x10);
}

/*******************************************************************************
* Function Name  : Font_code_UNIJIS
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void Font_code_UNIJIS(void)
{
	LCD_WriteReg_ANDORMask(0x2F,0xE3,0x14);
}


/*******************************************************************************
* Function Name  : Font_code_JIS0208
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void Font_code_JIS0208(void)
{
	LCD_WriteReg_ANDORMask(0x2F,0XE3,0x18);
}

/*******************************************************************************
* Function Name  : Font_code_LATIN
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void Font_code_LATIN(void)
{
	LCD_WriteReg_ANDORMask(0x2F,0xE3,0x1C);
}

/*******************************************************************************
* Function Name  : Font_Standard
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void Font_Standard(void)
{
	LCD_WriteReg_ANDMask(0x2F,0xFC);
}

/*******************************************************************************
* Function Name  : Font_Arial
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void Font_Arial(void)
{
	LCD_WriteReg_ANDORMask(0x2F,0xFD,0x01);
}

/*******************************************************************************
* Function Name  : Font_Roman
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void Font_Roman(void)
{
	LCD_WriteReg_ANDORMask(0x2F,0xFE,0x02);
}


/*******************************************************************************
* Function Name  : Font_Bold
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void Font_Bold(void) //for ASCII
{
	LCD_WriteReg_ORMask(0x2F,0x03);
}

//																					REG[30h]~REG[37h]
/*******************************************************************************
* Function Name  : Active Window
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Active_Window(uint16_t XL,uint16_t XR ,uint16_t YT ,uint16_t YB)
{
    //setting active window X
	LCD_WriteReg(0x30,XL); //Horizontal Start Point 0 of Active Window (HSAW0)
	LCD_WriteReg(0x31,XL>>8); //Horizontal Start Point 1 of Active Window (HSAW1)
	LCD_WriteReg(0x34,XR); //Horizontal End Point 0 of Active Window (HEAW0)
	LCD_WriteReg(0x35,XR>>8); //Horizontal End Point 1 of Active Window (HEAW1)

    //setting active window Y
	LCD_WriteReg(0x32,YT); //Vertical Start Point 0 of Active Window (VSAW0)
	LCD_WriteReg(0x33,YT>>8); //Vertical Start Point 1 of Active Window (VSAW1)
	LCD_WriteReg(0x36,YB); //Vertical End Point of Active Window 0 (VEAW0)
	LCD_WriteReg(0x37,YB>>8); //Vertical End Point of Active Window 1 (VEAW1)
}

//REG[38h]~REG[3Fh]
/*******************************************************************************
* Function Name  : Scroll_Window
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void Scroll_Window(uint16_t XL,uint16_t XR ,uint16_t YT ,uint16_t YB)
{

	LCD_WriteReg(0x38,XL);
	LCD_WriteReg(0x39,XL>>8);

	LCD_WriteReg(0x3c,XR);
	LCD_WriteReg(0x3d,XR>>8);

	LCD_WriteReg(0x3a,YT);
	LCD_WriteReg(0x3b,YT>>8);

    LCD_WriteReg(0x3e,YB);
	LCD_WriteReg(0x3f,YB>>8);
}


//																					REG[40h]
/*******************************************************************************
* Function Name  : Graphic_Mode
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Graphic_Mode(void)
{
	LCD_WriteReg_ANDMask(0x40,0x7F);
}

/*******************************************************************************
* Function Name  : Text_Mode
* Description    : Graphic mode or text mode selection. bit 7 bit[6-0] cursor blink...transparenci...
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Text_Mode(void)
{
	LCD_WriteReg_ORMask(0x40,0x80);
}


/*******************************************************************************
* Function Name  : Text_Cursor_Disable
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Text_Cursor_Disable(void)
{
	LCD_WriteReg_ANDMask(0x40,0xBF);
}


/*******************************************************************************
* Function Name  : Text_Cursor_Enable
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Text_Cursor_Enable(void)
{
	LCD_WriteReg_ORMask(0x40,0x40);
}


/*******************************************************************************
* Function Name  : Text_Cursor_Blink_Disable
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Text_Cursor_Blink_Disable(void)
{
	LCD_WriteReg_ANDMask(0x40,0xDF);
}


/*******************************************************************************
* Function Name  : Text_Cursor_Blink_Enable
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Text_Cursor_Blink_Enable(void)
{
	LCD_WriteReg_ORMask(0x40,0x20);
}


/*******************************************************************************
* Function Name  : Memory_Write_LeftRight_TopDown
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Memory_Write_LeftRight_TopDown(void)
{
	LCD_WriteReg_ANDMask(0x40,0xF3);
}


/*******************************************************************************
* Function Name  : Memory_Write_RightLeft_TopDown
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Memory_Write_RightLeft_TopDown(void)
{
	LCD_WriteReg_ANDORMask(0x40,0xF3,0x04);
}


/*******************************************************************************
* Function Name  : Memory_Write_DownTop_LeftRight
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Memory_Write_DownTop_LeftRight(void)
{
	LCD_WriteReg_ANDORMask(0x40,0xF3,0x0C);
}


/*******************************************************************************
* Function Name  : Memory_Write_TopDown_LeftRight
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Memory_Write_TopDown_LeftRight(void)
{
	LCD_WriteReg_ANDORMask(0x40,0xF3,0x08);
}


/*******************************************************************************
* Function Name  : MemoryWrite_Cursor_autoIncrease
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void MemoryWrite_Cursor_autoIncrease(void)
{
	LCD_WriteReg_ANDMask(0x40,0xFD);
}


/*******************************************************************************
* Function Name  : MemoryWrite_Cursor_NoautoIncrease
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void MemoryWrite_Cursor_NoautoIncrease(void)
{
	LCD_WriteReg_ORMask(0x40,0x02);
}


/*******************************************************************************
* Function Name  : MemoryRead_Cursor_autoIncrease
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void MemoryRead_Cursor_autoIncrease(void)
{
	LCD_WriteReg_ANDMask(0x40,0xFE);
}


/*******************************************************************************
* Function Name  : MemoryRead_Cursor_NoautoIncrease
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void MemoryRead_Cursor_NoautoIncrease(void)
{
	LCD_WriteReg_ORMask(0x40,0x01);
}


//REG[41h]
/*******************************************************************************
* Function Name  : No_Graphic_Cursor
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void No_Graphic_Cursor(void)
{
	LCD_WriteReg_ANDMask(0x41,0x7F);
}

/*******************************************************************************
* Function Name  : Graphic_Cursor
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Graphic_Cursor(void)
{
	LCD_WriteReg_ORMask(0x41,0x80);
}

/*******************************************************************************
* Function Name  : Graphic_Cursor_Set1
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Graphic_Cursor_Set1(void)
{
	LCD_WriteReg_ANDMask(0x41,0x8F);
}

/*******************************************************************************
* Function Name  : Graphic_Cursor_Set2
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Graphic_Cursor_Set2(void)
{
	LCD_WriteReg_ANDORMask(0x41,0x8F,0x10);
}

/*******************************************************************************
* Function Name  : Graphic_Cursor_Set3
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Graphic_Cursor_Set3(void)
{
	LCD_WriteReg_ANDORMask(0x41,0x8F,0x20);
}

/*******************************************************************************
* Function Name  : Graphic_Cursor_Set4
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Graphic_Cursor_Set4(void)
{
	LCD_WriteReg_ANDORMask(0x41,0x8F,0x30);
}

/*******************************************************************************
* Function Name  : Graphic_Cursor_Set5
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Graphic_Cursor_Set5(void)
{
	LCD_WriteReg_ANDORMask(0x41,0x8F,0x40);
}

/*******************************************************************************
* Function Name  : Graphic_Cursor_Set6
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Graphic_Cursor_Set6(void)
{
	LCD_WriteReg_ANDORMask(0x41,0x8F,0x50);
}

/*******************************************************************************
* Function Name  : Graphic_Cursor_Set7
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Graphic_Cursor_Set7(void)
{
	LCD_WriteReg_ANDORMask(0x41,0x8F,0x60);
}

/*******************************************************************************
* Function Name  : Graphic_Cursor_Set8
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Graphic_Cursor_Set8(void)
{
	LCD_WriteReg_ANDORMask(0x41,0x8F,0x70);
}

/*******************************************************************************
* Function Name  : Write_To_Bank1and2
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Write_To_Bank1and2(void)
{
	LCD_WriteReg_ANDMask(0x41,0xF3);
}

/*******************************************************************************
* Function Name  : Write_To_CGRAM
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Write_To_CGRAM(void)
{
	LCD_WriteReg_ANDORMask(0x41,0xF3,0x04);
}

/*******************************************************************************
* Function Name  : Write_To_GraphicCursor
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Write_To_GraphicCursor(void)
{
	LCD_WriteReg_ANDORMask(0x41,0xF3,0x08);
}

/*******************************************************************************
* Function Name  : Write_To_Pattern
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Write_To_Pattern(void)
{
	LCD_WriteReg_ANDORMask(0x41,0xF3,0x0C);
}

/*******************************************************************************
* Function Name  : Write_To_Bank1
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Write_To_Bank1(void)
{
	LCD_WriteReg_ANDMask(0x41,0xFE);
}

/*******************************************************************************
* Function Name  : Write_To_Bank2
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Write_To_Bank2(void)
{
	LCD_WriteReg_ORMask(0x41,0x01);
}


//REG[44h]
/*******************************************************************************
* Function Name  : Text_Blink_Time
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Text_Blink_Time(uint8_t setx)
{
	LCD_WriteReg(0x44,setx);

}

//REG[45h]
/*******************************************************************************
* Function Name  : Text_Blink_Time
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Memory_read_LeftRight_TopDown(void)
{
	LCD_WriteReg_ANDMask(0x45,0xFC);
}

/*******************************************************************************
* Function Name  : Memory_read_RightLeft_TopDown
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Memory_read_RightLeft_TopDown(void)
{
	LCD_WriteReg_ORMask(0x45,0x01);
}

/*******************************************************************************
* Function Name  : Memory_read_TopDown_LeftRight
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Memory_read_TopDown_LeftRight(void)
{
	LCD_WriteReg_ORMask(0x45,0x02);
}

/*******************************************************************************
* Function Name  : Memory_read_DownTop_LeftRight
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Memory_read_DownTop_LeftRight(void)
{
	LCD_WriteReg_ORMask(0x45,0x03);
}


//REG[46h]~REG[49h]
/*******************************************************************************
* Function Name  : XY_Coordinate
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void XY_Coordinate(uint16_t X,uint16_t Y)
{
	LCD_WriteReg(0x46,X);
    LCD_WriteReg(0x47,X>>8);

    LCD_WriteReg(0x48,Y);
    LCD_WriteReg(0x49,Y>>8);
}

//REG[4Ah]~REG[4Dh]
/*******************************************************************************
* Function Name  : Memory_read_Coordinate
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Memory_read_Coordinate(uint16_t X,uint16_t Y)
{

	LCD_WriteReg(0x4a,X);
	LCD_WriteReg(0x4b,X>>8);

	LCD_WriteReg(0x4c,Y);
	LCD_WriteReg(0x4d,Y>>8);
}

//REG[4Eh]
/*******************************************************************************
* Function Name  : Text_Cursor_Horizontal_Size
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Text_Cursor_Horizontal_Size(uint8_t setx)//uint8_t[3:0]
{
	LCD_WriteReg(0x4e,setx);//CURS

}

//REG[4Fh]
/*******************************************************************************
* Function Name  : Text_Cursor_Vertical_Size
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Text_Cursor_Vertical_Size(uint8_t setx)//uint8_t[3:0]
{
	LCD_WriteReg(0x4f,setx);//CURS

}


//REG[50h]
/*******************************************************************************
* Function Name  : no_BTE_write
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void no_BTE_write(void)
{
	LCD_WriteReg_ANDMask(0x50,0x7F);
}

/*******************************************************************************
* Function Name  : BTE_enable
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void BTE_enable(void)
{
	LCD_WriteReg_ORMask(0x50,0x80);
}

/*******************************************************************************
* Function Name  : BTE_contiguous_Data
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void BTE_contiguous_Data(void)
{
	LCD_WriteReg_ORMask(0x50,0x40);//BECR0
}

/*******************************************************************************
* Function Name  : BTE_rectangular_Data
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void BTE_rectangular_Data(void)
{
	LCD_WriteReg_ANDMask(0x50,0xBF);//BECR0
}

//REG[51h]
/*******************************************************************************
* Function Name  : BTE_ROP_Code
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void BTE_ROP_Code(uint8_t setx)
{
    LCD_WriteReg(0x51,setx);//BECR1
}

//REG[52h]
/*******************************************************************************
* Function Name  : Layer1_Visible
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Layer1_Visible(void)
{
	LCD_WriteReg_ANDMask(0x52,0xF8);//LTPR0
}

/*******************************************************************************
* Function Name  : Layer2_Visible
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Layer2_Visible(void)
{
	LCD_WriteReg_ANDORMask(0x52,0xF8,0x01);//LTPR0
}

/*******************************************************************************
* Function Name  : Transparent_Mode
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Transparent_Mode(void)
{
	LCD_WriteReg_ANDORMask(0x52,0xF8,0x03);//LTPR0
}

/*******************************************************************************
* Function Name  : Lighten_Overlay_Mode
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Lighten_Overlay_Mode(void)
{
	LCD_WriteReg_ANDORMask(0x52,0xF8,0x02);//LTPR0
}

/*******************************************************************************
* Function Name  : Boolean_OR
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Boolean_OR(void)
{
	LCD_WriteReg_ANDORMask(0x52,0xF8,0x04);//LTPR0
}

/*******************************************************************************
* Function Name  : Boolean_AND
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Boolean_AND(void)
{
	LCD_WriteReg_ANDORMask(0x52,0xF8,0x05);//LTPR0
}

/*******************************************************************************
* Function Name  : Floating_window_mode
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Floating_window_mode(void)
{
	LCD_WriteReg_ANDORMask(0x52,0xF8,0x06);//LTPR0
}

/*******************************************************************************
* Function Name  : Floating_Window_transparent_with_BGTR_enable
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Floating_Window_transparent_with_BGTR_enable(void)
{
	LCD_WriteReg_ORMask(0x52,0x20);//LTPR0
}

/*******************************************************************************
* Function Name  : Floating_Window_transparent_with_BGTR_disable
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Floating_Window_transparent_with_BGTR_disable(void)
{
	LCD_WriteReg_ANDMask(0x52,0xDF);//LTPR0
}

/*******************************************************************************
* Function Name  : Layer1_2_scroll
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Layer1_2_scroll(void)
{
	LCD_WriteReg_ANDMask(0x52,0x3F);//LTPR0

}

/*******************************************************************************
* Function Name  : Layer1_scroll
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Layer1_scroll(void)
{
	LCD_WriteReg_ANDORMask(0x52,0x3F,0x40);//LTPR0
}

/*******************************************************************************
* Function Name  : Layer2_scroll
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Layer2_scroll(void)
{
	LCD_WriteReg_ANDORMask(0x52,0x3F,0x80);//LTPR0
}

/*******************************************************************************
* Function Name  : Buffer_scroll
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Buffer_scroll(void)
{
	LCD_WriteReg_ANDORMask(0x52,0x3F,0xC0);//LTPR0
}

//																					REG[53h]
/*******************************************************************************
* Function Name  : layer2_1_transparency
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void layer2_1_transparency(uint8_t setx)
{
	LCD_WriteReg(0x53,setx);//LTPR1
}

//																					REG[54h]~ [5Fh]
/*******************************************************************************
* Function Name  : BTE_Source_Destination
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void BTE_Source_Destination	(uint16_t XL,uint16_t XR ,uint16_t YT ,uint16_t YB)
{
    uint8_t temp,temp1;

    LCD_WriteReg(0x54,XL);//HSBE0
    LCD_WriteReg(0x55,XL>>8);//HSBE1

    LCD_WriteReg(0x58,XR);//HDBE0
    LCD_WriteReg(0x59,XR>>8);//HDBE1

    LCD_WriteReg(0x56,YT);//VSBE0

    temp=YT>>8;

    //LCD_WriteReg_ANDMask(0x57,0x80);

    temp1 = LCD_ReadReg(0x57);
    temp1 &= 0x80;
    temp=temp|temp1;
    LCD_WriteReg(0x57,temp);//VSBE1

    LCD_WriteReg(0x5a,YB);//VDBE0
    temp=YB>>8;
    temp1 = LCD_ReadReg(0x5b);
    temp1 &= 0x80;
    temp=temp|temp1;
    LCD_WriteReg(0x5b,temp);//VDBE1
}

/*******************************************************************************
* Function Name  : Source_Layer1
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Source_Layer1(void)
{
	LCD_WriteReg_ANDMask(0x57,0x7F);//VSBE1

}

/*******************************************************************************
* Function Name  : Source_Layer2
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Source_Layer2(void)
{
	LCD_WriteReg_ANDMask(0x57,0x8);//VSBE1
}


/*--------------------------------------------------------------------				Reg [5b]									---------------*/

/*******************************************************************************
* Function Name  : Destination_Layer1
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Destination_Layer1(void)
{
	LCD_WriteReg_ANDMask(0x5b,0X7f);//VDBE1
}

/*******************************************************************************
* Function Name  : Destination_Layer2
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Destination_Layer2(void)
{
	LCD_WriteReg_ANDMask(0x5b,0x80);//VDBE1

}

/*******************************************************************************
* Function Name  : BTE_Size_setting
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void BTE_Size_setting(uint16_t X,uint16_t Y)
{
	LCD_WriteReg(0x5c,X);//BEWR0
	LCD_WriteReg(0x5d,X>>8);//BEWR1

	LCD_WriteReg(0x5e,Y);//BEHR0
	LCD_WriteReg(0x5f,Y>>8);//BEHR1
}


//REG[60h]~REG[69h]
/*******************************************************************************
* Function Name  : Background_color
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Background_color(uint16_t color)
{

	LCD_WriteReg(0x60,(color&0xf800)>>11);

    LCD_WriteReg(0x61,(color&0x07e0)>>5);

    LCD_WriteReg(0x62,(color&0x001f));
}

/*******************************************************************************
* Function Name  : Foreground_color
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Foreground_color(uint16_t color)
{

	 LCD_WriteReg(0x63,(color&0xf800)>>11);

	 LCD_WriteReg(0x64,(color&0x07e0)>>5);

	 LCD_WriteReg(0x65,(color&0x001f));
}

/*******************************************************************************
* Function Name  : Text_Background_Color
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Text_Background_Color(uint8_t setR,uint8_t setG,uint8_t setB)
{
	LCD_WriteReg(0x60,setR);

	LCD_WriteReg(0x61,setG);

	LCD_WriteReg(0x62,setB);
}

/*******************************************************************************
* Function Name  : Text_Foreground_Color
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Text_Foreground_Color(uint8_t setR,uint8_t setG,uint8_t setB)
{
	LCD_WriteReg(0x63,setR);

	LCD_WriteReg(0x64,setG);

	LCD_WriteReg(0x65,setB);

}

/*******************************************************************************
* Function Name  : BTE_Background_color
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void BTE_Background_color(uint8_t setR,uint8_t setG,uint8_t setB)
{
	LCD_WriteReg(0x60,setR);

	LCD_WriteReg(0x61,setG);

	LCD_WriteReg(0x62,setB);
}

/*******************************************************************************
* Function Name  : BTE_Foreground_color
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void BTE_Foreground_color(uint8_t setR,uint8_t setG,uint8_t setB)
{
	LCD_WriteReg(0x63,setR);

	LCD_WriteReg(0x64,setG);

	LCD_WriteReg(0x65,setB);
}

/*******************************************************************************
* Function Name  : BTE_Background_red
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void BTE_Background_red(uint8_t setx)
{
	LCD_WriteReg(0x60,setx);
}

/*******************************************************************************
* Function Name  : BTE_Background_green
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void BTE_Background_green(uint8_t setx)
{
	LCD_WriteReg(0x61,setx);
}

/*******************************************************************************
* Function Name  : BTE_Background_blue
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void BTE_Background_blue(uint8_t setx)
{
	LCD_WriteReg(0x62,setx);
}

/*******************************************************************************
* Function Name  : BTE_Foreground_red
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void BTE_Foreground_red(uint8_t setx)
{
	LCD_WriteReg(0x63,setx);
}

/*******************************************************************************
* Function Name  : BTE_Foreground_green
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void BTE_Foreground_green(uint8_t setx)
{
	LCD_WriteReg(0x64,setx);
}

/*******************************************************************************
* Function Name  : BTE_Foreground_blue
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void BTE_Foreground_blue(uint8_t setx)
{
	LCD_WriteReg(0x65,setx);
}

/*******************************************************************************
* Function Name  : Pattern_Set_8x8
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Pattern_Set_8x8(void)
{
	uint8_t temp;
	temp = LCD_ReadReg(0x66); //PTNO
	temp &= 0x7f;
	LCD_WriteData(temp);
}

/*******************************************************************************
* Function Name  : Pattern_Set_16x16
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Pattern_Set_16x16(void)
{
	LCD_WriteReg_ORMask(0x66,0X80);//PTNO

}

/*******************************************************************************
* Function Name  : Pattern_Set_number
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Pattern_Set_number(uint8_t setx)
{
	uint8_t temp;
	temp = LCD_ReadReg(0x66); //PTNO
	temp &= 0x80;
	LCD_WriteData(temp|setx);

}

/*******************************************************************************
* Function Name  : BackgroundColor_TransparentMode
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void BackgroundColor_TransparentMode(uint8_t setR,uint8_t setG,uint8_t setB)
{
	LCD_WriteReg(0x67,setR);//BGTR_R

	LCD_WriteReg(0x68,setG);//BGTR_G

	LCD_WriteReg(0x69,setB);//BGTR_B
}

//																				REG[70h]~REG[74h]
/*******************************************************************************3
* Function Name  : Enable_TP
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Enable_TP(void)
{
    LCD_WriteReg_ORMask(0x70,0X80);//TPCR0
}
/*******************************************************************************
* Function Name  : Disable_TP
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Disable_TP(void)
{
	LCD_WriteReg_ANDMask(0x70,0X7f);//TPCR0
}

/*******************************************************************************33333333333333333333333332323232
* Function Name  : Pattern_Set_16x16
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/

void Disable_Touch_WakeUp(void)
{
	LCD_WriteReg_ANDMask(0x70,0Xf7);//TPCR0

}

/*******************************************************************************
* Function Name  : Pattern_Set_16x16
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/


void Enable_Touch_WakeUp(void)
{
	LCD_WriteReg_ORMask(0x70,0X08);//TPCR0
}

/*******************************************************************************
* Function Name  : Pattern_Set_16x16
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void TP_manual_mode(void)
{
	LCD_WriteReg_ORMask(0x71,0x40);//TPCR1

}
/*******************************************************************************
* Function Name  : Pattern_Set_16x16
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void TP_auto_mode(void)
{
	LCD_WriteReg_ANDORMask(0x71,0xbf,0x04);

}

/*******************************************************************************
* Function Name  : Pattern_Set_16x16
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void TP_IDLE_mode(void)
{
	LCD_WriteReg_ANDMask(0x71,0xF0);//TPCR1

 }

/*******************************************************************************
* Function Name  : Pattern_Set_16x16
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void TP_event_mode(void)
{
	LCD_WriteReg_ANDORMask(0x71,0xF0,0x01);//TPCR1
}
/*******************************************************************************
* Function Name  : Pattern_Set_16x16
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void TP_latch_X(void)
{
	LCD_WriteReg_ANDORMask(0x71,0xE0,0x02);//TPCR1
}

/*******************************************************************************
* Function Name  : Pattern_Set_16x16
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void TP_latch_Y(void)
{
	LCD_WriteReg_ANDORMask(0x71,0xE0,0x03);//TPCR1
 }



// void TP_LDLE(void)
// {
//     uint8_t temp;
//     LCD_CmdWrite(0x71);//TPCR1
//     temp=LCD_DataRead();
//     temp &= 0xc0;
//     LCD_WriteData(temp);
// }


/*******************************************************************************
* Function Name  : Pattern_Set_16x16
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
uint8_t ADC_X(void)
{
    uint8_t temp;
    LCD_CmdWrite(0x72);//TPXH	 X_coordinate high byte
    //Chk_Busy();
    temp=LCD_DataRead();
    return temp;
}

/*******************************************************************************
* Function Name  : Pattern_Set_16x16
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
uint8_t ADC_Y(void)
{
    uint8_t temp;
    LCD_CmdWrite(0x73);//TPYH	  Y_coordinate high byte
    //Chk_Busy();
    temp=LCD_DataRead();
    return temp;
}

/*******************************************************************************
* Function Name  : Pattern_Set_16x16
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
uint8_t ADC_XY(void)
{
    uint8_t temp;
    LCD_CmdWrite(0x74);//TPXYL	  uint8_t[3:2] Y_coordinate low byte  uint8_t[1:0] X_coordinate low byte
    temp=LCD_DataRead();
    return temp;
}

//																											REG[80h]~REG[83h]
/*******************************************************************************
* Function Name  : Pattern_Set_16x16
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Graphic_Cursor_Coordinate(uint16_t X,uint16_t Y)
{
	LCD_WriteReg(0x80,X);
	LCD_WriteReg(0x81,X>>8);

	LCD_WriteReg(0x82,Y);
	LCD_WriteReg(0x83,Y>>8);
}

//---------------------------------//
//																											REG[84h]
/*******************************************************************************
* Function Name  : Pattern_Set_16x16
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Graphic_Cursor_Color_0(uint8_t setx)
{
	LCD_WriteReg(0x84,setx);
}

void Graphic_Cursor_Color_1(uint8_t setx)
{
	LCD_WriteReg(0x85,setx);
}

//---------------------------------------------//
/*******************************************************************************
* Function Name  : Pattern_Set_16x16
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************			REG[8A]					*/
void PWM1_enable(void)
{
	LCD_WriteReg_ORMask(0x8a,0x80);//P1CR
}
/*******************************************************************************
* Function Name  : Pattern_Set_16x16
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void PWM1_disable(void)
{
	LCD_WriteReg_ANDMask(0x8a, 0x7f);//P1CR
}
/*******************************************************************************
* Function Name  : Pattern_Set_16x16
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void PWM1_disable_level_low(void)
{
	LCD_WriteReg_ANDMask(0x8a, 0xbf);//P1CR
}
/*******************************************************************************
* Function Name  : Pattern_Set_16x16
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void PWM1_disable_level_high(void)
{
	LCD_WriteReg_ORMask(0x8a, 0x40);//P1CR
}
/*******************************************************************************
* Function Name  : Pattern_Set_16x16
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
 void PWM1_fnuction_sel(void)
{
	 LCD_WriteReg_ANDMask(0x8a, 0xef);//P1CR
 }
 /*******************************************************************************
 * Function Name  : Pattern_Set_16x16
 * Description    :
 * Input          : None
 * Output         : None
 * Return         : None
 * Attention	     : None
 *******************************************************************************/
 void PWM1_system_clk_out(void)
{
	 LCD_WriteReg_ORMask(0x8a, 0x10);//P1CR
 }
 /*******************************************************************************
 * Function Name  : Pattern_Set_16x16
 * Description    :
 * Input          : None
 * Output         : None
 * Return         : None
 * Attention	     : None
 *******************************************************************************/
 void PWM1_clock_ratio(uint8_t setx)
{

	 uint8_t temp,temp1;
	 temp1= setx&0x0f;
	 LCD_CmdWrite(0x8a);
	 temp = LCD_DataRead();
	 temp &= 0xf0;
	 temp |= temp1 ;
	 LCD_WriteData(temp);
 }
 /*******************************************************************************
 * Function Name  : Pattern_Set_16x16
 * Description    :
 * Input          : None
 * Output         : None
 * Return         : None
 * Attention	     : None
 *******************************************************************************/
 void PWM1_duty_cycle(uint8_t setx) //bit0~7
{
	 LCD_WriteReg(0x8b, setx);//PTNO
}
 /*******************************************************************************
 * Function Name  : Pattern_Set_16x16
 * Description    :
 * Input          : None
 * Output         : None
 * Return         : None
 * Attention	     : None
 *******************************************************************************/
void PWM2_enable(void)
{
	LCD_WriteReg_ORMask(0x8c, 0x80);//MCLR
 }
/*******************************************************************************
* Function Name  : Pattern_Set_16x16
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void PWM2_disable(void)
{
	LCD_WriteReg_ANDMask(0x8c, 0x7f);//MCLR
 }
/*******************************************************************************
* Function Name  : Pattern_Set_16x16
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void PWM2_disable_level_low(void)
{
	LCD_WriteReg_ANDMask(0x8c, 0xbf);//MCLR
}
/*******************************************************************************
* Function Name  : Pattern_Set_16x16
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void PWM2_disable_level_high(void)
{
	LCD_WriteReg_ORMask(0x8c, 0x40);//MCLR
}
/*******************************************************************************
* Function Name  : Pattern_Set_16x16
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
 void PWM2_fnuction_sel(void)
{
	 LCD_WriteReg_ANDMask(0x8c, 0xef);//MCLR
 }
 /*******************************************************************************
 * Function Name  : Pattern_Set_16x16
 * Description    :
 * Input          : None
 * Output         : None
 * Return         : None
 * Attention	     : None
 *******************************************************************************/
  void PWM2_system_clk_out(void)
{
	  LCD_WriteReg_ORMask(0x8c, 0x10);//MCLR
 }
  /*******************************************************************************
  * Function Name  : Pattern_Set_16x16
  * Description    :
  * Input          : None
  * Output         : None
  * Return         : None
  * Attention	     : None
  *******************************************************************************/
  void PWM2_clock_ratio(uint8_t setx) //bit0~3
{
    uint8_t temp,temp1;
    temp1= setx&0x0f;
    LCD_CmdWrite(0x8c);//MCLR
    temp = LCD_DataRead();
    temp &= 0xf0;
    temp |= temp1 ;
    LCD_WriteData(temp);
 }
  /*******************************************************************************
  * Function Name  : Pattern_Set_16x16
  * Description    :
  * Input          : None
  * Output         : None
  * Return         : None
  * Attention	     : None
  *******************************************************************************/
 void PWM2_duty_cycle(uint8_t setx) //bit0~7
{
	 LCD_WriteReg(0x8d,setx);
}


//---------------------------------------------//
//																							REG[8Eh]
 /*******************************************************************************
 * Function Name  : Pattern_Set_16x16
 * Description    :
 * Input          : None
 * Output         : None
 * Return         : None
 * Attention	     : None
 *******************************************************************************/
void Stop_Memory_Clear(void)
{
	LCD_WriteReg_ANDMask(0x8e,0x7f);
}
/*******************************************************************************
* Function Name  : Pattern_Set_16x16
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Memory_Clear(void)
{
	LCD_WriteReg_ORMask(0x8e,0x80);
	Chk_Busy();
}
/*******************************************************************************
* Function Name  : Pattern_Set_16x16
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Clear_Full_Window(void)
{
	LCD_WriteReg_ANDMask(0x8e,0xbf);
}
/*******************************************************************************
* Function Name  : Pattern_Set_16x16
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Clear_Active_Window(void)
{
	LCD_WriteReg_ORMask(0x8e,0x40);
}


//---------------------------------------------//
//																				REG[90h]
/*******************************************************************************
* Function Name  : Pattern_Set_16x16
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Draw_line(void)
{
	LCD_WriteReg(0x90,0x00);
	LCD_WriteData(0x80);
}
/*******************************************************************************
* Function Name  : Pattern_Set_16x16
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Draw_square(void)
{
	LCD_WriteReg(0x90,0x10);
	LCD_WriteData(0x90);
}
/*******************************************************************************
* Function Name  : Pattern_Set_16x16
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Draw_square_fill(void)
{
	LCD_WriteReg(0x90,0x10);
	LCD_WriteData(0xb0);
}
/*******************************************************************************
* Function Name  : Pattern_Set_16x16
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Draw_circle(void)
{
	LCD_WriteReg(0x90,0x40);
}
/*******************************************************************************
* Function Name  : Pattern_Set_16x16
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Draw_circle_fill(void)
{
	LCD_WriteReg(0x90,0x60);
}
/*******************************************************************************
* Function Name  : Pattern_Set_16x16
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Draw_Triangle(void)
{
	LCD_WriteReg(0x90,0x00);
	LCD_WriteData(0x81);
}
/*******************************************************************************
* Function Name  : Pattern_Set_16x16
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Draw_Triangle_fill(void)
{
	LCD_WriteReg(0x90,0x01);
	LCD_WriteData(0xA1);
}

//---------------------------------------------//
//																				REG[90h]~/EG[9Dh]

/*******************************************************************************
* Function Name  : Geometric_Coordinate
* Description    : Set screen color
* Input          : Color: Screen Color
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void Geometric_Coordinate(uint16_t X,uint16_t Y,uint16_t X1  ,uint16_t Y1)
{
	LCD_WriteReg(0x91,X);
	LCD_WriteReg(0x92,X>>8);

	LCD_WriteReg(0x93,Y);
	LCD_WriteReg(0x94,Y>>8);

	LCD_WriteReg(0x95,X1);
	LCD_WriteReg(0x96,X1>>8);

	LCD_WriteReg(0x97,Y1);
	LCD_WriteReg(0x98,Y1>>8);
}

/******************************************************************************
* Function Name  : Circle_Coordinate_Radius
* Description    : Geometric Pattern Drawing Engine :Circle Of Circlar Corner Input
* Input          : - X:
*                  - Y:
*       				   - R
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void Circle_Coordinate_Radius(uint16_t X,uint16_t Y,uint16_t R)
{
	LCD_WriteReg(0x99,X);
	LCD_WriteReg(0x9a,X>>8);

	LCD_WriteReg(0x9b,Y);
	LCD_WriteReg(0x9c,Y>>8);

	LCD_WriteReg(0x9d,R);
}
//---------------------------------------------//
//																						REG[A0h]
/*******************************************************************************
* Function Name  : Pattern_Set_16x16
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Draw_Ellipse(void)
{
	LCD_WriteReg(0xA0,0x00);
	LCD_WriteData(0x80);
}
/*******************************************************************************
* Function Name  : Pattern_Set_16x16
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Draw_Ellipse_fill(void)
{
	LCD_WriteReg(0xA0,0x40);
	LCD_WriteData(0xC0);
}
/*******************************************************************************
* Function Name  : Pattern_Set_16x16
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Draw_Ellipse_Curve(void)
{
	LCD_WriteReg_ANDORMask(0xA0,0x1F,0x90);
}
/*******************************************************************************
* Function Name  : Pattern_Set_16x16
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Draw_Ellipse_Curve_Fill(void)
{
	LCD_WriteReg_ANDORMask(0xA0,0x1F,0xD0);
}
/*******************************************************************************
* Function Name  : Pattern_Set_16x16
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Draw_Ellipse_Curve_part(uint8_t setx)
{
	uint8_t temp,temp1;
	LCD_CmdWrite(0xA0);//DCR
	temp = LCD_DataRead();
	temp1 = setx&0x03;
	temp &=0xfc;
	temp |=temp1;
	LCD_WriteData(temp);
}
/*******************************************************************************
* Function Name  : Pattern_Set_16x16
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Draw_Circle_Square(void)
{
	LCD_WriteReg(0xA0,0x20);
	LCD_WriteData(0xA0);
}
/*******************************************************************************
* Function Name  : Pattern_Set_16x16
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Draw_Circle_Square_fill(void)
{
	LCD_WriteReg(0xA0,0x60);
	LCD_WriteData(0xE0);
}

/******************************************************************************
* Function Name  : Ellipse_Coordinate_setting
* Description    : Geometric Pattern Drawing Engine :Ellipse Of Circlar Corner Input
* Input          : - X:
*                  - Y:
*       				   - ELL_A:Long axis
*       		       - ELL_B:short axis
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void Ellipse_Coordinate_setting(uint16_t X,uint16_t Y,uint16_t ELL_A,uint16_t ELL_B)
{
	LCD_WriteReg(0xA5,X);
	LCD_WriteReg(0xA6,X>>8);

	LCD_WriteReg(0xA7,Y);
	LCD_WriteReg(0xA8,Y>>8);

	LCD_WriteReg(0xA1,ELL_A);
	LCD_WriteReg(0xA2,ELL_A>>8);

	LCD_WriteReg(0xA1,ELL_A);
	LCD_WriteReg(0xA2,ELL_A>>8);

	LCD_WriteReg(0xA3,ELL_B);
	LCD_WriteReg(0xA4,ELL_B>>8);

}


/******************************************************************************
* Function Name  : Circle_Square_Coordinate_setting
* Description    : Geometric Pattern Drawing Engine :Square Of Circlar Corner Input
* Input          : - x0:
*                  - y0:
*       				   - x1:
*       		       - y1:
*       				   - ELL_A:Long axis
*       		       - ELL_B:short axis
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void Circle_Square_Coordinate_setting(uint16_t X0,uint16_t Y0 ,uint16_t X1 ,uint16_t Y1 ,uint16_t ELL_A,uint16_t ELL_B)
{

	LCD_WriteReg(0x91,X0);
	LCD_WriteReg(0x92,X0>>8);

	LCD_WriteReg(0x93,Y0);
	LCD_WriteReg(0x94,Y0>>8);

	LCD_WriteReg(0x95,X1);
	LCD_WriteReg(0x96,X1>>8);

	LCD_WriteReg(0x97,Y1);
	LCD_WriteReg(0x98,Y1>>8);

	LCD_WriteReg(0xA1,ELL_A);
	LCD_WriteReg(0xA2,ELL_A>>8);

	LCD_WriteReg(0xA3,ELL_B);
	LCD_WriteReg(0xA4,ELL_B>>8);

}

/******************************************************************************
* Function Name  : Draw_Triangle_3point_Coordinate
* Description    : Geometric Pattern Drawing Engine :Triangle Of Circlar Corner Input
* Input          : - P1_X:
*                  - P1_Y:
*       				   - P2_X
*       		       - P2_Y
*       				   - P3_X
*       		       - P3_Y
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void Draw_Triangle_3point_Coordinate(uint16_t P1_X,uint16_t P1_Y,uint16_t P2_X,uint16_t P2_Y,uint16_t P3_X,uint16_t P3_Y)
{
	LCD_WriteReg(0x91,P1_X);
	LCD_WriteReg(0x92,P1_X>>8);

	LCD_WriteReg(0x93,P1_Y);
	LCD_WriteReg(0x94,P1_Y>>8);

	LCD_WriteReg(0x95,P2_X);
	LCD_WriteReg(0x96,P2_X>>8);

	LCD_WriteReg(0x97,P2_Y);
	LCD_WriteReg(0x98,P2_Y>>8);

	LCD_WriteReg(0xA9,P3_X);
	LCD_WriteReg(0xAA,P3_X>>8);

	LCD_WriteReg(0xAB,P3_Y);
	LCD_WriteReg(0xAC,P3_Y>>8);

}



//---------------------------------------------//
//																							REG[B0]~REG[B3]
/*******************************************************************************
* Function Name  : Pattern_Set_16x16
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void DMA_Start_address_setting(uint32_t set_address)
{
	LCD_WriteReg(0xb0,set_address);

	LCD_WriteReg(0xb1,set_address>>8);

	LCD_WriteReg(0xb2,set_address>>16);

	LCD_WriteReg(0xb3,set_address>>24);
}
/*******************************************************************************
* Function Name  : Pattern_Set_16x16
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
//input pic data quantity  for example  pic size = 800*480 = 384000
void DMA_Continuous_mode_size_setting(uint32_t set_size)
{
	LCD_WriteReg(0xb4,set_size);

	LCD_WriteReg(0xb6,set_size>>8);

	LCD_WriteReg(0xb8,set_size>>16);
}
/*******************************************************************************
* Function Name  : Pattern_Set_16x16
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void DMA_block_mode_size_setting(uint16_t BWR,uint16_t BHR,uint16_t SPWR)
{
	LCD_WriteReg(0xb4,BWR);
	LCD_WriteReg(0xb5,BWR>>8);

	LCD_WriteReg(0xb6,BHR);
	LCD_WriteReg(0xb7,BHR>>8);

	LCD_WriteReg(0xb8,SPWR);
	LCD_WriteReg(0xb9,SPWR>>8);

}

//---------------------------------------------//
//																						REG[BFh]
/*******************************************************************************
* Function Name  : Pattern_Set_16x16
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void DMA_Continuous_mode(void)
{
	LCD_WriteReg(0xbf,0x00);
}
/*******************************************************************************
* Function Name  : Pattern_Set_16x16
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void DMA_Block_mode(void)
{
	LCD_WriteReg(0xbf,0x02);
}
/*******************************************************************************
* Function Name  : Pattern_Set_16x16
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void DMA_Start_enable(void)
{
	LCD_WriteReg_ORMask(0xbf,0x01);
}

//---------------------------------------------//
//																						REG[C0h]
/*******************************************************************************
* Function Name  : Pattern_Set_16x16
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Key_Scan_Enable(void)
{
	LCD_WriteReg_ORMask(0xc0,0x80);
}
/*******************************************************************************
* Function Name  : Pattern_Set_16x16
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/

void Key_Scan_setting(uint8_t setx)//uint8_t[2:0]
{
	LCD_WriteReg_ANDORMask(0xc0,0x80, setx&0x07);
}
/*******************************************************************************
* Function Name  : Pattern_Set_16x16
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Long_Key_Scan_enable(void)
{
	LCD_WriteReg_ORMask(0xc0,0x40);
}
/*******************************************************************************
* Function Name  : Pattern_Set_16x16
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Key_Scan_Wakeup_Function_Enable(void)
{
	LCD_WriteReg_ORMask(0xc1,0x80);
}
/*******************************************************************************
* Function Name  : Pattern_Set_16x16
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Long_Key_Timing_Adjustment(uint8_t setx)
{
	LCD_WriteReg_ORMask(0xc1,setx&0x1c);

}

//																											REG[D0]
/*******************************************************************************
* Function Name  : Floating_window_start_point
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Floating_window_start_point(uint16_t X,uint16_t Y)
{
	LCD_WriteReg(0xd0,X);
    LCD_WriteReg(0xd1,X>>8);

    LCD_WriteReg(0xd2,Y);
    LCD_WriteReg(0xd1,X>>8);
}

/*******************************************************************************
* Function Name  : Floating_window_size
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Floating_window_size(uint16_t width_X,uint16_t high_Y)
{

	LCD_WriteReg(0xd4,width_X);
	LCD_WriteReg(0xd5,width_X>>8);

	LCD_WriteReg(0xd6,high_Y);
	LCD_WriteReg(0xd7,high_Y>>8);
}

/*******************************************************************************
* Function Name  : Floating_window_display_point
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Floating_window_display_point(uint16_t X,uint16_t Y)
{
	LCD_WriteReg(0xd8,X);
	LCD_WriteReg(0xd9,X>>8);

	LCD_WriteReg(0xda,Y);
	LCD_WriteReg(0xdb,Y>>8);
}


																						//REG[E0h]
/*******************************************************************************
* Function Name  : Serial_ROM_direct_access_mode_enable
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Serial_ROM_direct_access_mode_enable(void)
{
	LCD_WriteReg(0xE0,0x01);
}

void Serial_ROM_direct_access_mode_disable(void)
{
	LCD_WriteReg(0xE0,0x00);
}
/*******************************************************************************
* Function Name  : DMA_Address_32bits
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void DMA_Address_32bits(uint32_t set_address)
{

  LCD_WriteReg(0xE1,set_address>>24);
  LCD_WriteData(set_address>>16);
  LCD_WriteData(set_address>>8);
  LCD_WriteData(set_address);

}

/*******************************************************************************
* Function Name  : DMA_Address_24bits
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void DMA_Address_24bits(uint32_t set_address)
{

  LCD_WriteReg(0xE1,set_address>>16);
  LCD_WriteData(set_address>>8);
  LCD_WriteData(set_address);
}

/*******************************************************************************
* Function Name  : DMA_Read_Data_buffer
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
uint8_t DMA_Read_Data_buffer(void)
{
    return LCD_ReadReg(0xE2);
}
//																						REG[F0h]
/*******************************************************************************
* Function Name  : KEYSCAN_Interrupt_Enable
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void KEYSCAN_Interrupt_Enable(void)
{
	LCD_WriteReg_ORMask(0xf0,0x10);
}

/*******************************************************************************
* Function Name  : KEYSCAN_Interrupt_Disable
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void KEYSCAN_Interrupt_Disable(void)
{
	LCD_WriteReg_ANDMask(0xf0,0x0f);
}

/*******************************************************************************
* Function Name  : DMA_Interrupt_Enable
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void DMA_Interrupt_Enable(void)
{
	LCD_WriteReg_ORMask(0xf0,0x08);
}

/*******************************************************************************
* Function Name  : DMA_Interrupt_Disable
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void DMA_Interrupt_Disable(void)
{
	LCD_WriteReg_ANDMask(0xf0,0x17);
}

/*******************************************************************************
* Function Name  : Touch_Panel_Interrupt_Enable
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Touch_Panel_Interrupt_Enable(void)
{
	LCD_WriteReg_ORMask(0xf0,0x04);
}

/*******************************************************************************
* Function Name  : Touch_Panel_Interrupt_Disable
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Touch_Panel_Interrupt_Disable(void)
{
	LCD_WriteReg_ANDMask(0xf0,0x1b);
}

/*******************************************************************************
* Function Name  : BTE_Interrupt_Enable
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void BTE_Interrupt_Enable(void)
{
	LCD_WriteReg_ORMask(0xf0,0x02);
}

/*******************************************************************************
* Function Name  : BTE_Interrupt_Disable
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void BTE_Interrupt_Disable(void)
{
	LCD_WriteReg_ANDMask(0xf0,0x1d);
}

/*******************************************************************************
* Function Name  : Font_BTE_read_write_Interrupt_Enable
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Font_BTE_read_write_Interrupt_Enable(void)
{
	LCD_WriteReg_ORMask(0xf0,0x01);
}

/*******************************************************************************
* Function Name  : Font_BTE_read_write_Interrupt_Disable
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Font_BTE_read_write_Interrupt_Disable(void)
{
	LCD_WriteReg_ANDMask(0xf0,0x1E);
}

//																							REG[F1h]
/*******************************************************************************
* Function Name  : Clear_keyscan_interrupt
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Clear_keyscan_interrupt(void)
{
	LCD_WriteReg_ORMask(0xf1,0x10);

}

/*******************************************************************************
* Function Name  : Keyscan_Status
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
uint8_t Keyscan_Status(void)
{

  uint8_t temp = LCD_ReadReg(0xf1);
  if ((temp&0x10)==0x10)
     return 1;
  else
     return 0;
}

/*******************************************************************************
* Function Name  : Clear_DMA_interrupt
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Clear_DMA_interrupt(void)
{
	LCD_WriteReg_ORMask(0xf1,0x08);
}

/*******************************************************************************
* Function Name  : DMA_Status
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
uint8_t DMA_Status(void)
{
	uint8_t temp = LCD_ReadReg(0xf1);
	if ((temp&0x08)==0x08)
		return 1;
	else
	    return 0;
}

/*******************************************************************************
* Function Name  : clear_TP_interrupt
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void clear_TP_interrupt(void)
{
	LCD_WriteReg_ORMask(0xf1,0x04);
}

/*******************************************************************************
* Function Name  : Touch_Status
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
uint8_t Touch_Status(void)
{
	uint8_t temp = LCD_ReadReg(0xf1);
	if ((temp&0x04)==0x04)
		return 1;
	else
	    return 0;
}

/*******************************************************************************
* Function Name  : Clear_BTE_interrupt
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Clear_BTE_interrupt(void)
{
	LCD_WriteReg_ORMask(0xf1,0x02);
}

/*******************************************************************************
* Function Name  : BTE_Status
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
uint8_t BTE_Status(void)
{
	uint8_t temp = LCD_ReadReg(0xf1);
	if ((temp&0x02)==0x02)
		return 1;
	else
	    return 0;
}

/*******************************************************************************
* Function Name  : Clear_Font_BTE_read_write_Interrupt
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Clear_Font_BTE_read_write_Interrupt(void)
{
	LCD_WriteReg_ORMask(0xf1,0x01);
}

/*******************************************************************************
* Function Name  : Font_BTE_read_write_Status
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
uint8_t Font_BTE_read_write_Status(void)
{
	uint8_t temp = LCD_ReadReg(0xf1);
		if ((temp&0x01)==0x01)
			return 1;
		else
		    return 0;
}




