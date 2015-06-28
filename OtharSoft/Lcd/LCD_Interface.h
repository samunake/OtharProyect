#include "stm32f4xx.h"

/* Private define ------------------------------------------------------------*/

#define LCD_DATA              (*((volatile unsigned short *) 0x60000000)) /* RS = 0 */
#define LCD_CMD             (*((volatile unsigned short *)   0x60100000)) /* RS = 1 */




__inline void LCD_WriteIndex(uint16_t index);
__inline void LCD_WriteData(uint16_t data);
__inline uint16_t LCD_ReadData(void);
__inline uint16_t LCD_ReadReg(uint16_t LCD_Reg);
__inline void LCD_WriteReg(uint16_t LCD_Reg,uint16_t LCD_RegValue);
__inline uint16_t LCD_WriteReg_ORMask(uint16_t LCD_Reg,uint16_t mask);
__inline uint16_t LCD_WriteReg_ANDMask(uint16_t LCD_Reg,uint16_t mask);
__inline uint16_t LCD_WriteReg_ANDORMask(uint16_t LCD_Reg,uint16_t AND_mask,uint16_t OR_mask);
