/*********************************************************************************************************
 *
 * File                : LCD_Config.c
 * Hardware Environment:
 * Build Environment   : CooCox CoIDE  Version: 1.7.8
 * Version             : V1.0
 * By                  : Tomás Ariza Crespo
 *
 *
 *********************************************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "Fsmc.h"

/*******************************************************************************
 * Function Name  : LCD_CtrlLinesConfig
 * Description    : Configures LCD Control lines (FSMC Pins) in alternate function
 Push-Pull mode.
 * Input          : None
 * Output         : None
 * Return         : None
 * Attention 	 : None
 *******************************************************************************/
void FSMC_GPIO_Init(void) {
	GPIO_InitTypeDef GPIO_InitStructure;

	/* Enable GPIOs clock */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOE, ENABLE);

	/* Enable FSMC clock */
	RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FSMC, ENABLE);

	/*----------------------------- GPIOs CONFIGURATION ----------------------------*
	 *                                                                              *
	 +-------------------+--------------------+------------------+------------------+
	 +                       SRAM pins assignment                                   +
	 +-------------------+--------------------+------------------+------------------+
	 |             PD0  <-> FSMC_D2           |           PE3  <-> FSMC_A19         |
	 |             PD1  <-> FSMC_D3           |                                     |
	 | 	 			                          |                                     |
	 |             PD4  <-> FSMC_NOE          |           PE7  <-> FSMC_D4          |
	 |             PD5  <-> FSMC_NWE          |           PE8  <-> FSMC_D5          |
	 | 			   PD7  <-> FSMC_NE1          |				                        |
	 | 			   PD8  <-> FSMC_D13          |           PE9  <-> FSMC_D6          |
	 |             PD9  <-> FSMC_D14          |           PE10 <-> FSMC_D7          |
	 |             PD10 <-> FSMC_D15          |           PE11 <-> FSMC_D8          |
	 | 				                          |           PE12 <-> FSMC_D9          |
	 |             PD12 <-> TIM4(ch1)         |           PE13 <-> FSMC_D10         |
	 |             PD14 <-> FSMC_D0           |           PE14 <-> FSMC_D11         |
	 |             PD15 <-> FSMC_D1           |           PE15 <-> FSMC_D12         |
	 +-------------------+--------------------+------------------+------------------|
	 */
	/* GPIOD configuration */
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource0, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource1, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource4, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource5, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource7, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource8, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource9, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource10, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_FSMC);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4
			| GPIO_Pin_5 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10
			| GPIO_Pin_14 | GPIO_Pin_15;

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

	GPIO_Init(GPIOD, &GPIO_InitStructure);

	/* GPIOE configuration */
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource3, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource7, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource8, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource9, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource10, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource11, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource12, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource13, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource14, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource15, GPIO_AF_FSMC);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_7 | GPIO_Pin_8
			| GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13
			| GPIO_Pin_14 | GPIO_Pin_15;

	GPIO_Init(GPIOE, &GPIO_InitStructure);



}
void BLNRST_GPIO_Init(void) {
	GPIO_InitTypeDef GPIO_InitStructure;

	/* Enable GPIOs clock */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOC, ENABLE);

	/* GPIO BackLight PD12 configuration */
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_TIM4);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

	GPIO_Init(GPIOD, &GPIO_InitStructure);

	/* GPIO Reset PC6 configuration */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

	GPIO_Init(GPIOC, &GPIO_InitStructure);
	// Reset active Low. Always inactive(1)
	GPIO_SetBits(GPIOC, GPIO_Pin_6);

}

/*******************************************************************************
 * Function Name  : LCD_FSMCConfig
 * Description    : Configures the Parallel interface (FSMC) for LCD(Parallel mode)
 * Input          : None
 * Output         : None
 * Return         : None
 * Attention		 : None
 *******************************************************************************/
void FSMC_LCD_Init(void) {
	FSMC_NORSRAMInitTypeDef FSMC_NORSRAMInitStructure;
	FSMC_NORSRAMTimingInitTypeDef FSMC_NORSRAMTimingInitStructure;

	FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM1;
	FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
	FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_SRAM;
	FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
	FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode =
			FSMC_BurstAccessMode_Disable;
	FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity =
			FSMC_WaitSignalPolarity_Low;
	FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;
	FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive =
			FSMC_WaitSignalActive_BeforeWaitState;
	FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
	FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
	FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait =
			FSMC_AsynchronousWait_Disable;
	FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;
	FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
	FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct =
			&FSMC_NORSRAMTimingInitStructure;
	//FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);
	/* FSMC Write Timing */
	FSMC_NORSRAMTimingInitStructure.FSMC_AddressSetupTime = 4; /* Address Setup Time  4*/
	FSMC_NORSRAMTimingInitStructure.FSMC_AddressHoldTime = 0;
	FSMC_NORSRAMTimingInitStructure.FSMC_DataSetupTime = 1; /* Data Setup Time 5*/
	FSMC_NORSRAMTimingInitStructure.FSMC_BusTurnAroundDuration = 0x09; //9
	FSMC_NORSRAMTimingInitStructure.FSMC_CLKDivision = 0x00;
	FSMC_NORSRAMTimingInitStructure.FSMC_DataLatency = 0x00;
	FSMC_NORSRAMTimingInitStructure.FSMC_AccessMode = FSMC_AccessMode_A; /* FSMC Access Mode */
	FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct =
			&FSMC_NORSRAMTimingInitStructure;

	FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);

	/* Enable FSMC Bank4_SRAM Bank */
	FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM1, ENABLE);
}

/*******************************************************************************
 * Function Name  : LCD_Configuration
 * Description    : Configure the LCD Control pins and FSMC Parallel interface
 * Input          : None
 * Output         : None
 * Return         : None
 * Attention		 : None
 *******************************************************************************/
void FSMC_Init(void) {
	/* Configure the LCD Control FSMC pins --------------------------------------------*/
	FSMC_GPIO_Init();
	Delay_ms(50);

	/* Configure the LCD BACKLIGHT Y NRST pins --------------------------------------------*/
	BLNRST_GPIO_Init();
	Delay_ms(50);

	/* Configure the FSMC Parallel interface -------------------------------------*/
	FSMC_LCD_Init();
	Delay_ms(50);
}

/*******************************************************************************
* Function Name  : LCD_WriteReg
* Description    :
* Input          : - index:
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
__inline void FSMC_WriteCmd(uint16_t index)
{
	FSMC_CMD = index;
}
/*******************************************************************************
* Function Name  : LCD_WriteReg
* Description    :
* Input          : - index:
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
__inline void FSMC_WriteData(uint16_t data)
{

	FSMC_DATA = data;
	//Delay_ms(1); //  Espacio de 5 clclos entre wr y wr (5.9*5 > 84ns) pag59 datasheet RA

}

/*******************************************************************************
* Function Name  : LCD_ReadData
* Description    :
* Input          : None
* Output         : None
* Return         :
* Attention		 : None
*******************************************************************************/
__inline uint16_t FSMC_ReadData(void)
{
	return FSMC_DATA;
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
__inline void FSMC_WriteReg(uint16_t LCD_Reg,uint16_t LCD_RegValue)
{
	/* Write 16-bit Index, then Write Reg */
	FSMC_WriteCmd(LCD_Reg);
	//Delay_ms(1);
	/* Write 16-bit Reg */
	FSMC_WriteData(LCD_RegValue);
}

/*******************************************************************************
* Function Name  : LCD_WriteReg
* Description    : Reads the selected LCD Register.
* Input          : None
* Output         : None
* Return         : LCD Register Value.
* Attention		 : None
*******************************************************************************/
__inline uint16_t FSMC_ReadReg(uint16_t LCD_Reg)
{
	/* Write 16-bit Index (then Read Reg) */
	FSMC_WriteCmd(LCD_Reg);

	/* Read 16-bit Reg */
	return FSMC_ReadData();
}

/*******************************************************************************
* Function Name  : LCD_WriteRegORMask
* Description    : Reads the selected LCD Register.
* Input          : None
* Output         : None
* Return         : LCD Register Value.
* Attention		 : None
*******************************************************************************/
__inline void FSMC_WriteReg_ORMask(uint16_t LCD_Reg,uint16_t mask)
{
	uint16_t temp;
	/* Write 16-bit Index (then Read Reg) */
	FSMC_WriteCmd(LCD_Reg);
	/* Read 16-bit Reg */
	temp = FSMC_ReadData();
	/* Apply mask */
	temp |= mask;
	/* Write Reg with OR mask */
	FSMC_WriteReg(LCD_Reg,temp);
}

/*******************************************************************************
* Function Name  : LCD_WriteRegANDMask
* Description    : Reads the selected LCD Register.
* Input          : None
* Output         : None
* Return         : LCD Register Value.
* Attention		 : None
*******************************************************************************/
__inline void FSMC_WriteReg_ANDMask(uint16_t LCD_Reg,uint16_t mask)
{
	uint16_t temp;
	/* Write 16-bit Index (then Read Reg) */
	FSMC_WriteCmd(LCD_Reg);
	/* Read 16-bit Reg */
	temp = FSMC_ReadData();
	/* Apply mask */
	temp &= mask;
	/* Write Reg with AND mask */
	FSMC_WriteReg(LCD_Reg,temp);
}


/*******************************************************************************
* Function Name  : LCD_WriteRegANDORMask
* Description    : Reads the selected LCD Register.
* Input          : None
* Output         : None
* Return         : LCD Register Value.
* Attention		 : None
*******************************************************************************/
__inline void FSMC_WriteReg_ANDORMask(uint16_t LCD_Reg,uint16_t AND_mask,uint16_t OR_mask)
{
	uint16_t temp;
	/* Write 16-bit Index (then Read Reg) */
	FSMC_WriteCmd(LCD_Reg);
	/* Read 16-bit Reg */
	temp = FSMC_ReadData();
	/* Apply mask */
	temp &= AND_mask;
	temp |= OR_mask;
	/* Write Reg with AND mask */
	FSMC_WriteReg(LCD_Reg,temp);
}

__inline uint16_t FSMC_StatusRead(void)
{

    return (FSMC_CMD);
}
