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

#include "LCD_Config.h"


/* Defines -------------------------------------------------------------------*/
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

/*********************************************************************************************************/

void Chk_Busy(void);
void Chk_Busy_BTE(void);
void Chk_Busy_DIR_Access(void);
void Chk_DMA_Busy(void);

void Display_ON(void);
void Display_OFF(void);
void Normal_Mode_exitSleep(void);
void Sleep_Mode(void);
void Software_Reset(void);
void PCLK_inversion(void);
void PCLK_non_inversion(void);
void PCLK_width(uint8_t setx);
void Serial_ROM_select0(void);
void Serial_ROM_select1(void);


void Active_Window(uint16_t XL,uint16_t XR ,uint16_t YT ,uint16_t YB);
void Graphic_Mode(void);
void Text_color(uint16_t color);
void Geometric_Coordinate(uint16_t X,uint16_t Y,uint16_t X1  ,uint16_t Y1);
void LcdClear(u16 color);
