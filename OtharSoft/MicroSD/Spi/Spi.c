	/*--------------------- GPIOs Configuration ------------------------------------*/
	/*
	 +-------------------+--------------------+------------------+------------------+
	 +                        SPI pins assignment                                   +
	 +-------------------+--------------------+------------------+------------------+
	 |                                                                              |
	 |                 PB2      <->     /CS  			CHIP_SELECT                 |		 
	 |                 PB3      <->     SPI1_SCK        CLOCK                       |
	 | 	 			   PB4      <->     SPI1_MISO       DATA_OUT                    |
	 |                 PB5      <->     SPI1_MOSI       DATA_IN                     |
	 |                 PB6      <->     CD   			CARD_DETECT                 |
	 | 				   PB7      <->     WP	 			WRITE_PROTECT  		        |
	 |                                                                              |
	 +-------------------------------------+----------------------------------------+
	 */



#include "spi.h"
void SPI_GPIO_Config(void) {
	GPIO_InitTypeDef GPIO_InitStructure;

	/* Enable GPIOs clock */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	/* Enable SPI clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	
	/* SPI pins configuration */
	
	/*Connect SPI pins to AF5 */  
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource3, GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource4, GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource5, GPIO_AF_SPI1);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 ;

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	/* SPI SCK pin configuration */
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	/* Configure MicroSD Card CS pin in output pushpull mode ********************/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	/* Configure MicroSD Card_Detect & Write_Protectpin in input pushpull mode pullup********************/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	}

void SPI_MicroSD_Init(void){
	SPI_InitTypeDef SPI_InitStruct;
	
	SPI_GPIO_Config();
	
	/* Deselect Card first  */
	CS_HIGH();
	
	SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStruct.SPI_Mode = SPI_Mode_Master;
	SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low; // pag 865 datasheet
	SPI_InitStruct.SPI_CPHA = SPI_CPHA_1Edge;
	/* SPI1 in on bus APB2 (84Mhz)/16 = 5.25Mhz */
	SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;
	SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;
	
	/* Disable the MicroSD  */
	SPI_Cmd(MicroSD, DISABLE); // REG CR1.BIT 6 (SPE) = 0 
	
	SPI_Init(MicroSD, &SPI_InitStruct);
	
	/* Enable the MicroSD_SPI  */
	SPI_Cmd(MicroSD, ENABLE);
	
}
    
uint8_t SPI_Send_Byte(uint8_t data) {
	
	/* Check if SPI is enabled . If disabled return 0*/
	CHECK_SPI_ENABLED(MicroSD);
	
	/* Wait for previous transmissions to complete if DMA TX enabled for SPI */
	WAIT_SPI_TX(MicroSD);
	WAIT_SPI_BUSY(MicroSD);
	
	/* Fill output buffer with data */
	SPI_I2S_SendData(MicroSD,data);
	
	/* Wait for read transmission to complete */
	WAIT_SPI_RX(MicroSD);
	WAIT_SPI_BUSY(MicroSD);
	
	/* Return data from buffer */
	return SPI_I2S_ReceiveData(MicroSD);
}

uint16_t SPI_Send_HalfWord(uint16_t data) {
	
		
	/* Check if SPI is enabled . If disabled return 0*/
	CHECK_SPI_ENABLED(MicroSD);
	
	/* Wait for previous transmissions to complete if DMA TX enabled for SPI */
	WAIT_SPI_TX(MicroSD);
	WAIT_SPI_BUSY(MicroSD);
	
	/* Fill output buffer with data */
	SPI_I2S_SendData(MicroSD,data);
	
	/* Wait for transmission to complete */
	WAIT_SPI_RX(MicroSD);
	WAIT_SPI_BUSY(MicroSD);
	
	/* Return data from buffer */
	return SPI_I2S_ReceiveData(MicroSD);
}

void SPI_SendBlock_Byte(uint8_t* dataOut, uint8_t* dataIn, uint32_t count) {
	uint32_t i;
	
	/* Check if SPI is enabled . If disabled return 0*/
	CHECK_SPI_ENABLED(MicroSD);
		
	for (i = 0; i < count; i++) {
		
		/* Wait for previous transmissions to complete if DMA TX enabled for SPI */
		WAIT_SPI_TX(MicroSD);
		WAIT_SPI_BUSY(MicroSD);
		
		/* Fill output buffer with data */
		SPI_I2S_SendData(MicroSD,dataOut[i]);
				
		/* Wait for read transmission to complete */
		WAIT_SPI_RX(MicroSD);
		WAIT_SPI_BUSY(MicroSD);
		
		/* Read data register */
		dataIn[i] = SPI_I2S_ReceiveData(MicroSD);
	}
}

void SPI_SendBlock_HalfWord(uint16_t* dataOut, uint16_t* dataIn, uint32_t count) {
	uint32_t i;
	
	/* Check if SPI is enabled . If disabled return 0*/
	CHECK_SPI_ENABLED(MicroSD);
		
	for (i = 0; i < count; i++) {
		
		/* Wait for previous transmissions to complete if DMA TX enabled for SPI */
		WAIT_SPI_TX(MicroSD);
		WAIT_SPI_BUSY(MicroSD);
		
		/* Fill output buffer with data */
		SPI_I2S_SendData(MicroSD,dataOut[i]);
				
		/* Wait for read transmission to complete */
		WAIT_SPI_RX(MicroSD);
		WAIT_SPI_BUSY(MicroSD);
		
		/* Read data register */
		dataIn[i] = SPI_I2S_ReceiveData(MicroSD);
	}
}

void SPI_WriteData_Byte(uint8_t* dataOut, uint32_t count) {
	uint32_t i;	
	
	/* Check if SPI is enabled . If disabled return 0*/
	CHECK_SPI_ENABLED(MicroSD);
		
	for (i = 0; i < count; i++) {
		/* Wait for previous transmissions to complete if DMA TX enabled for SPI */
		WAIT_SPI_TX(MicroSD);
		WAIT_SPI_BUSY(MicroSD);
		
		/* Fill output buffer with data */
		SPI_I2S_SendData(MicroSD,dataOut[i]);
		
		/* Wait for previous transmissions to complete if DMA TX enabled for SPI */
		WAIT_SPI_RX(MicroSD);
		WAIT_SPI_BUSY(MicroSD);
		
		/* Read data register */
		(void)SPI_I2S_ReceiveData(MicroSD);
	}
}

void SPI_WriteData_HalfWord(uint16_t* dataOut, uint32_t count) {
	uint32_t i;	
	
	/* Check if SPI is enabled . If disabled return 0*/
	CHECK_SPI_ENABLED(MicroSD);
	
	
	
	for (i = 0; i < count; i++) {
		/* Wait for previous transmissions to complete if DMA TX enabled for SPI */
		WAIT_SPI_TX(MicroSD);
		WAIT_SPI_BUSY(MicroSD);
		
		/* Fill output buffer with data */
		SPI_I2S_SendData(MicroSD,dataOut[i]);
		
		/* Wait for previous transmissions to complete if DMA TX enabled for SPI */
		WAIT_SPI_RX(MicroSD);
		WAIT_SPI_BUSY(MicroSD);
		
		/* Read data register */
		(void)SPI_I2S_ReceiveData(MicroSD);
	}
}

/* Dummy 16-bit value to be sent over SPI, to receive data back. In most cases 0x00 or 0xFF */
void SPI_ReadData_Byte(uint8_t* dataIn, uint8_t dummy, uint32_t count) {
	uint32_t i;
	
	/* Check if SPI is enabled . If disabled return 0*/
	CHECK_SPI_ENABLED(MicroSD);
		
	for (i = 0; i < count; i++) {
		/* Wait for previous transmissions to complete if DMA TX enabled for SPI */
		WAIT_SPI_TX(MicroSD);
		/* Fill output buffer with data */
		SPI_I2S_SendData(MicroSD,dummy);
		
		/* Wait for previous transmissions to complete if DMA TX enabled for SPI */
		WAIT_SPI_RX(MicroSD);
		
		/* Save data to buffer */
		dataIn[i] = SPI_I2S_ReceiveData(MicroSD);
	}
}

void SPI_ReadData_HalfWord(uint8_t* dataIn, uint16_t dummy, uint32_t count) {
	uint32_t i;
	
	/* Check if SPI is enabled . If disabled return 0*/
	CHECK_SPI_ENABLED(MicroSD);
		
	for (i = 0; i < count; i++) {
		
		/* Wait for previous transmissions to complete if DMA TX enabled for SPI */
		WAIT_SPI_TX(MicroSD);
		/* Fill output buffer with data */
		SPI_I2S_SendData(MicroSD,dummy);
		
		/* Wait for previous transmissions to complete if DMA TX enabled for SPI */
		WAIT_SPI_RX(MicroSD);
		
		/* Save data to buffer */
		dataIn[i] = SPI_I2S_ReceiveData(MicroSD);
	}
}
