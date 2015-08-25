#include "Config_I2C.h"




void Init_I2C(){
	configure_I2CGPIOS();
	configure_I2CSettings();
	configure_I2CInterrupts();
}




void configure_I2CGPIOS() {

	/*
	 +------------------+------------------+
	 +          I2C pins assignment        +
	 +------------------+------------------+
	 | PB8  <-> I2C_SCL  | PE1 <-> IRQ	   |
	 | PB9  <-> I2C_SDA  | PE6 <-> SHUTDOWN|
	 +------------------+------------------+*/

	//GPIO settings
	GPIO_InitTypeDef GPIO_InitStructure;
	// GPIOB clock enable
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	// PB8 & PB9 configuration (SDA y SCL open drain)
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	// Connect pins to AF4

//	GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_I2C1);
//		GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_I2C1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_I2C1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_I2C1);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	// PE6 & PE1 configuration (SHUTDOWN & INT)
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}


void configure_I2CSettings() {

	I2C_InitTypeDef I2C_InitStructure;

	// I2C clock enable
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);

	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStructure.I2C_Ack = I2C_Ack_Disable;
	I2C_InitStructure.I2C_ClockSpeed = 100000;
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStructure.I2C_OwnAddress1 = 0X40;
	I2C_InitStructure.I2C_AcknowledgedAddress == I2C_AcknowledgedAddress_7bit;

	I2C_Cmd(I2C1, DISABLE);
	I2C_Init(I2C1, &I2C_InitStructure);
	I2C_Cmd(I2C1, ENABLE);
}

void configure_I2CInterrupts() {

	/* Enable clock for SYSCFG (EXTI) */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	/* Tell system that you will use PE1 for EXTI_Line1 */
	//SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource1);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource2);
	// Set variables used
	EXTI_InitTypeDef EXTI_InitStruct;
	// PC2 is connected to EXTI_Line1
	//EXTI_InitStruct.EXTI_Line = EXTI_Line1;
	EXTI_InitStruct.EXTI_Line = EXTI_Line2;
	// Interrupt mode
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	// Triggers on falling edge
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	// Enable interrupt
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	// Add to EXTI
	EXTI_Init(&EXTI_InitStruct);


	NVIC_InitTypeDef NVIC_InitStructure;

	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	//  Enable the I2C error Interrupt
	NVIC_InitStructure.NVIC_IRQChannel = I2C1_ER_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	//  Enable the I2C event Interrupt
	NVIC_InitStructure.NVIC_IRQChannel = I2C1_EV_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

}
// Generate a START
// I2C_GenerateSTART(I2C1, ENABLE);
// I2C_ReceiveData();




//HANDLER DE INTERRUPCIONES DE I2C1
void I2C1_EV_IRQHandler() {


	    switch(I2C_GetLastEvent(I2C1))
	    {
	    case I2C_EVENT_SLAVE_RECEIVER_ADDRESS_MATCHED :
	        break;
	    case I2C_EVENT_SLAVE_BYTE_RECEIVED:
	     //   i2c_read_packet[Rx_Index] = I2C_ReceiveData(I2C2); // Store the packet in i2c_read_packet.
	     //   Rx_Index++;
	        break;
	    case I2C_EVENT_SLAVE_STOP_DETECTED :
	    //    Rx_Index = 0;
	    //    packets_recv_i2c++;
	    //    i2cProcessPacket();
	        break;
	    case I2C_EVENT_SLAVE_TRANSMITTER_ADDRESS_MATCHED:
	     //   I2C_SendData(I2C2, i2c_packet_to_send[0]);
	     //   Tx_Index++;
	        break;
	    case I2C_EVENT_SLAVE_BYTE_TRANSMITTED:
	    //    I2C_SendData(I2C2, i2c_packet_to_send[Tx_Index]);
	     //   Tx_Index++;
	        break;
	    case I2C_EVENT_SLAVE_ACK_FAILURE:
	    //    Tx_Index = 0;
	   //     packets_sent_i2c++;
	        break;
	    default:
	        break;
	    }


}

//HANDLER DE ERRORES DE I2C1
void I2C1_ER_IRQHandler() {
	Check_toLCD("Error handler I2C ",0,200,400,250);
	//if (TIM_GetITStatus(I2C1, I2C_IT_SB) == SET) {  }


}
