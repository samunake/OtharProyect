/*********************************************************************************************************
*
* File                : LCD.h
* Hardware Environment:
* Build Environment   : RealView MDK-ARM  Version: 4.20
* Version             : V1.0
* By                  :
*
*                                  (c) Copyright 2005-2011, WaveShare
*                                       http://www.waveshare.net
*                                          All Rights Reserved
*
*********************************************************************************************************/


/* Includes ------------------------------------------------------------------*/

#include "stm32f4xx.h"
//#include "LCD/AsciiLib.h"
#include "Lcd/RA8875/Interface_RA8875.h"
#include "Delay/Delay.h"

/* Private define ------------------------------------------------------------*/
/*********************************************************************
* Overview: Horizontal and vertical display resolution
*                  (from the glass datasheet).
*********************************************************************/
//#define DISP_HOR_RESOLUTION				800
//#define DISP_VER_RESOLUTION				480

//#define DISP_ORIENTATION					0
#define DISP_ORIENTATION					90
//#define DISP_ORIENTATION					180
//#define DISP_ORIENTATION					270

/* Private define ------------------------------------------------------------*/

#if  ( DISP_ORIENTATION == 90 ) || ( DISP_ORIENTATION == 270 )

#define  MAX_X  800
#define  MAX_Y  480

#elif  ( DISP_ORIENTATION == 0 ) || ( DISP_ORIENTATION == 180 )

#define  MAX_X  480
#define  MAX_Y  800

#endif



/* LCD color */
#define White          0xFFFF
#define Black          0x0000
#define Grey           0xF7DE
#define Blue           0x001F
#define Blue2          0x051F
#define Red            0xF800
#define Magenta        0xF81F
#define Green          0x07E0
#define Cyan           0x7FFF
#define Yellow         0xFFE0

/* Private function prototypes -----------------------------------------------*/

void InitializeTimer(void);
void InitializePWM_TIM4(void);
void LCD_FSMCConfig(void);
void LCD_CtrlLinesFSMC(void);
void LCD_CtrlLinesConfig(void);
void LCD_Configuration(void);
void LCD_Initialization(void);

void LCD_Clear(uint16_t Color);


/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
