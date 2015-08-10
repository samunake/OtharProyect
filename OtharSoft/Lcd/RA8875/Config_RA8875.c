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
#include "Config_RA8875.h"

/*******************************************************************************
 * Function Name  : InitializeTimer
 * Description    : Initialize Timer - BlackLight Control PWM

 * Input          : None
 * Output         : None
 * Return         : None
 * Attention		 : None
 *******************************************************************************/
void InitializeTimer(void) {
	/*TIM4 is connected to APB1 bus, which has on F407 device 42MHz clock                 
	 But, timer has internal PLL, which double this frequency for timer, up to 84MHz
	 Remember: Not each timer is connected to APB1, there are also timers connected
	 on APB2, which works at 84MHz by default, and internal PLL increase
	 this to up to 168MHz  */
	TIM_TimeBaseInitTypeDef timerInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

	timerInitStructure.TIM_Prescaler = 83; // timer_tick_frequency = 84000000 / (0 + 1) = 84000000
	timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	//TIM_Period = timer_tick_frequency / PWM_frequency - 1
	timerInitStructure.TIM_Period = 19999; // 1Mhz	TIM_Period = 1000000 / 50 - 1 = 19999
	timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	timerInitStructure.TIM_RepetitionCounter = 0;
	/* Initialize TIM4 */
	TIM_TimeBaseInit(TIM4, &timerInitStructure);
	TIM_Cmd(TIM4, ENABLE);
}

/*******************************************************************************
 * Function Name  : InitializePWMChannel
 * Description    : Initialize Timer to BlackLight Control PWM

 * Input          : None
 * Output         : None
 * Return         : None
 * Attention		 : None
 *******************************************************************************/
void InitializePWM_TIM4(void) {
	/*
	 To get proper duty cycle, you have simple equation
	 pulse_length = ((TIM_Period + 1) * DutyCycle) / 100 - 1
	 where DutyCycle is in percent, between 0 and 100%

	 25% duty cycle:     pulse_length = ((8399 + 1) * 25) / 100 - 1 = 2099
	 50% duty cycle:     pulse_length = ((8399 + 1) * 50) / 100 - 1 = 4199
	 75% duty cycle:     pulse_length = ((8399 + 1) * 75) / 100 - 1 = 6299
	 100% duty cycle:    pulse_length = ((8399 + 1) * 100) / 100 - 1 = 8399

	 Remember: if pulse_length is larger than TIM_Period, you will have output HIGH all the time
	 */

	TIM_OCInitTypeDef outputChannelInit;
	/* PWM mode 2 = Clear on compare match */
	/* PWM mode 1 = Set on compare match */
	outputChannelInit.TIM_OCMode = TIM_OCMode_PWM2;
	outputChannelInit.TIM_OutputState = TIM_OutputState_Enable;
	outputChannelInit.TIM_OCPolarity = TIM_OCPolarity_Low;

	outputChannelInit.TIM_Pulse = 14999; // 75% duty cycle
	TIM_OC1Init(TIM4, &outputChannelInit);
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);

	/* outputChannelInit.TIM_Pulse = 4199; // 50% duty cycle
	 TIM_OC2Init(TIM4, &outputChannelInit);
	 TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);*/

	/*outputChannelInit.TIM_Pulse = 8399; // 100% duty cycle
	 TIM_OC3Init(TIM4, &outputChannelInit);
	 TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);*/

	/*outputChannelInit.TIM_Pulse = 8399; // 100% duty cycle
	 TIM_OC4Init(TIM4, &outputChannelInit);
	 TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);*/

}

/*******************************************************************************
 * Function Name  : LCD_CtrlLinesConfig
 * Description    : Configures LCD Control lines (FSMC Pins) in alternate function
 Push-Pull mode.
 * Input          : None
 * Output         : None
 * Return         : None
 * Attention		 : None
 *******************************************************************************/
void LCD_CtrlLinesFSMC(void) {
	GPIO_InitTypeDef GPIO_InitStructure;

	/* Enable GPIOs clock */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOE, ENABLE);

	/* Enable FSMC clock */
	RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FSMC, ENABLE);

	/*-- GPIOs Configuration ------------------------------------------------------*/
	/*
	 +-------------------+--------------------+------------------+------------------+
	 +                       SRAM pins assignment                                   +
	 +-------------------+--------------------+------------------+------------------+
	 | PD0  <-> FSMC_D2  | PE3  <-> FSMC_A19	 |
	 | PD1  <-> FSMC_D3  |                    |
	 | 	 			 |
	 PD4  <-> FSMC_NOE | PE7  <-> FSMC_D4   |
	 | PD5  <-> FSMC_NWE | PE8  <-> FSMC_D5   |
	 | PD7  <-> FSMC_NE1 |					 |
	 PD8  <-> FSMC_D13 | PE9  <-> FSMC_D6   |
	 | PD9  <-> FSMC_D14 | PE10 <-> FSMC_D7   |
	 | PD10 <-> FSMC_D15 | PE11 <-> FSMC_D8   |
	 | 					| PE12 <-> FSMC_D9   |
	 | PD12 <-> TIM4(ch1)| PE13 <-> FSMC_D10  |
	 | PD14 <-> FSMC_D0  | PE14 <-> FSMC_D11  |
	 | PD15 <-> FSMC_D1  | PE15 <-> FSMC_D12  |
	 +-------------------+--------------------+
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
void LCD_CtrlLinesConfig(void)
/*-- GPIOs Configuration ------------------------------------------------------*/
/*
 PD12 <-> TIM4(ch1)
 PC6 <-> NRST
 */
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/* Enable GPIOs clock */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	/* GPIOD configuration */

	GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_TIM4);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

	GPIO_Init(GPIOD, &GPIO_InitStructure);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

	GPIO_Init(GPIOC, &GPIO_InitStructure);
	// Reset active Low. Always inactive(1)
	GPIO_SetBits(GPIOC, GPIO_Pin_6);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

	GPIO_Init(GPIOA, &GPIO_InitStructure);
	// Reset active Low. Always inactive(1)

}

/*******************************************************************************
 * Function Name  : LCD_FSMCConfig
 * Description    : Configures the Parallel interface (FSMC) for LCD(Parallel mode)
 * Input          : None
 * Output         : None
 * Return         : None
 * Attention		 : None
 *******************************************************************************/
void LCD_FSMCConfig(void) {
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
void LCD_Configuration(void) {
	/* Configure the LCD Control FSMC pins --------------------------------------------*/
	LCD_CtrlLinesFSMC();
	Delay_ms(50);
	/* Configure the LCD BACKLIGHT Y NRST pins --------------------------------------------*/
	LCD_CtrlLinesConfig();

	Delay_ms(50);
	/* Configure the FSMC Parallel interface -------------------------------------*/
	LCD_FSMCConfig();
	Delay_ms(50);
}

/*******************************************************************************
 * Function Name  : RA8875_PLL_ini
 * Description    : Initialization RA8875 system clock
 * Input          : None
 * Output         : None
 * Return         : None
 * Attention		   : None
 *******************************************************************************/
void PLL_init(void) {

	LCD_WriteReg(0x88, 0x0b); //system clock = 20*(13+1)/1*(2^2)=60MHz
	Delay_ms(20);
	LCD_WriteReg(0x89, 0x02);
	Delay_ms(20);

}

/*******************************************************************************
 * Function Name  : LCD_Initializtion
 * Description    : RA8875 Resets
 * Input          : None
 * Output         : None
 * Return         : None
 * Attention		 : None
 *******************************************************************************/

void LCD_Initialization(void) {
	LCD_Configuration();

	InitializeTimer();

	PLL_init();

	//ER-TFTM050-3 SETTINGS
	//==============	Display Window	800x480 ==================
	uint16_t temp;
	LCD_WriteReg(0x10, 0x0F); //SYSR 16bit MCU interface   and 65k color display
	Delay_ms(10);
	LCD_WriteReg(0x04, 0x81); //PCLK inverse	(Falling Edge - SYSCLK*2)
	Delay_ms(10);
	temp = LCD_StatusRead();

	//Horizontal set
	LCD_WriteReg(0x14, 0x63); //HDWR//Horizontal Display Width Setting Bit[6:0]
	// Delay_ms(10);
	LCD_WriteReg(0x15, 0x00); //Horizontal Non-Display Period Fine Tuning Option Register (HNDFTR) 0
	//   Delay_ms(10);
	LCD_WriteReg(0x16, 0x03); //HNDR//Horizontal Non-Display Period Bit[4:0]  3
	//   Delay_ms(10);
	LCD_WriteReg(0x17, 0x03); //HSTR//HSYNC Start Position[4:0]   3
	//  Delay_ms(10);
	LCD_WriteReg(0x18, 0x0B); //HPWR//HSYNC Polarity ,The period width of HSYNC.  B
	//   Delay_ms(10);

	//Vertical set
	LCD_WriteReg(0x19, 0xdf); //VDHR0 //Vertical Display Height Bit [7:0]
	//   Delay_ms(10);
	LCD_WriteReg(0x1a, 0x01); //VDHR1 //Vertical Display Height Bit [8] 01
	//   Delay_ms(10);
	LCD_WriteReg(0x1b, 0x20); //VNDR0 //Vertical Non-Display Period Bit [7:0] 20
	//   Delay_ms(10);
	LCD_WriteReg(0x1c, 0x00); //VNDR1 //Vertical Non-Display Period Bit [8] 00
	//   Delay_ms(10);
	LCD_WriteReg(0x1d, 0x16); //VSTR0 //VSYNC Start Position[7:0] 16
	//   Delay_ms(10);
	LCD_WriteReg(0x1e, 0x00); //VSTR1 //VSYNC Start Position[8] 00
	//   Delay_ms(10);
	LCD_WriteReg(0x1f, 0x01); //VPWR //VSYNC Polarity ,VSYNC Pulse Width[6:0] 01
	//   Delay_ms(10);

	//Active window  set
	//setting active window X (0,799) ---(0X0000,0X031F)
	LCD_WriteReg(0x30, 0x00); //Horizontal Start Point 0 of Active Window (HSAW0)
	//   Delay_ms(10);
	LCD_WriteReg(0x31, 0x00); //Horizontal Start Point 1 of Active Window (HSAW1)
	//   Delay_ms(10);
	LCD_WriteReg(0x34, 0x1f); //Horizontal End Point 0 of Active Window (HEAW0)
	//   Delay_ms(10);
	LCD_WriteReg(0x35, 0x03); //Horizontal End Point 1 of Active Window (HEAW1)
	//  Delay_ms(10);

	//setting active window Y (0,479)---(0X0000,0X01DF)
	LCD_WriteReg(0x32, 0x00); //Vertical Start Point 0 of Active Window (VSAW0)
	//   Delay_ms(10);
	LCD_WriteReg(0x33, 0x00); //Vertical Start Point 1 of Active Window (VSAW1)
	//   Delay_ms(10);
	LCD_WriteReg(0x36, 0xdf); //Vertical End Point of Active Window 0 (VEAW0)
	//   Delay_ms(10);
	LCD_WriteReg(0x37, 0x01); //Vertical End Point of Active Window 1 (VEAW1)

}

/******************************************************************************
 * Function Name  : LCD_BGR2RGB
 * Description    : RRRRRGGGGGGBBBBB convert to BBBBBGGGGGGRRRRR
 * Input          : RGB color
 * Output         : None
 * Return         : RGB color
 * Attention		 :
 *******************************************************************************/
uint16_t LCD_BGR2RGB(uint16_t color) {
	uint16_t r, g, b, rgb;

	b = (color >> 0) & 0x1f;
	g = (color >> 5) & 0x3f;
	r = (color >> 11) & 0x1f;

	rgb = (b << 11) + (g << 5) + (r << 0);

	return (rgb);
}
