
#include "stm32f4xx.h"






#define MicroSD			 SPI1


#define CHECK_SPI_ENABLED(SPIx)   if (!((SPIx)->CR1 & SPI_CR1_SPE)) {return;}
/*#define CHECK_SPI_ENABLED(SPIx,data)   if (!((SPIx)->CR1 & SPI_CR1_SPE)) {return (data);}*/
//#define CHECK_SPI_BUSY(SPIx) (((SPIx)->SR & (SPI_SR_TXE | SPI_SR_RXNE)) == 0 || ((SPIx)->SR & SPI_SR_BSY))

/* Wait while Tx Buffer not Empty */
#define WAIT_SPI_TX(SPIx) 		while(SPI_I2S_GetFlagStatus(SPIx,SPI_I2S_FLAG_TXE)==0)
	
#define WAIT_SPI_RX(SPIx) 		while(SPI_I2S_GetFlagStatus(SPIx,SPI_I2S_FLAG_RXNE)==0)
#define CHECK_SPI_BUSY(SPIx) 	SPI_I2S_GetFlagStatus(SPIx,SPI_I2S_FLAG_BSY)
#define WAIT_SPI_BUSY(SPIx)		while(SPI_I2S_GetFlagStatus(SPIx,SPI_I2S_FLAG_BSY))


	

void SPI_GPIO_Config(void);
void SPI_MicroSD_Init(void);
uint8_t SPI_Send_Byte(uint8_t data);
uint16_t SPI_Send_HalfWord(uint16_t data);
void SPI_SendBlock_Byte(uint8_t* dataOut, uint8_t* dataIn, uint32_t count);
void SPI_SendBlock_HalfWord(uint16_t* dataOut, uint16_t* dataIn, uint32_t count);
void SPI_WriteData_Byte(uint8_t* dataOut, uint32_t count);
void SPI_WriteData_HalfWord(uint16_t* dataOut, uint32_t count);
void SPI_ReadData_Byte(uint8_t* dataIn, uint8_t dummy, uint32_t count);
void SPI_ReadData_HalfWord(uint8_t* dataIn, uint16_t dummy, uint32_t count);
