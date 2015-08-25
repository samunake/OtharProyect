#include "stm32f4xx.h"

#define FSMC_DATA              (*((volatile unsigned short *) 0x60000000)) /* RS = 0 */
#define FSMC_CMD     	       (*((volatile unsigned short *)   0x60100000)) /* RS = 1 */









void FSMC_GPIO_Init(void);
void BLNRST_GPIO_Init(void);

void FSMC_LCD_Init(void);
void LCD_Init(void);


__inline void FSMC_WriteCmd(uint16_t index);
__inline void FSMC_WriteIndex(uint16_t index);
__inline void FSMC_WriteData(uint16_t data);
__inline uint16_t FSMC_ReadData(void);
__inline uint16_t FSMC_ReadReg(uint16_t LCD_Reg);
__inline void FSMC_WriteReg(uint16_t LCD_Reg,uint16_t LCD_RegValue);
__inline void FSMC_WriteReg_ORMask(uint16_t LCD_Reg,uint16_t mask);
__inline void FSMC_WriteReg_ANDMask(uint16_t LCD_Reg,uint16_t mask);
__inline void FSMC_WriteReg_ANDORMask(uint16_t LCD_Reg,uint16_t AND_mask,uint16_t OR_mask);
__inline uint16_t FSMC_StatusRead(void);
