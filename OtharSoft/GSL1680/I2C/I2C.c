#include "stm32f4xx_conf.h"
#include "I2C.h"

#define I2C_TRANSMITTER_MODE   0
#define I2C_RECEIVER_MODE      1

#define GSLX680_I2C_ADDR 		0x40
#define GSL_DATA_REG_ADDR		0x80
#define GSL_STATUS_REG_ADDR		0xe0
#define GSL_PAGE_REG_ADDR		0xf0

#ifndef I2C_TIMEOUT
#define I2C_TIMEOUT					20000
#endif

uint16_t I2C_Timeout;
uint8_t GSL_ready_flag;
char buf[50];
uint8_t resul[4];

//extern _screen screen;

void Init_Touch() {
	Init_I2C();
	Delay_ms(50);
	Init_chipGSL();
	Delay_ms(50);
}

//GSL1680 Touch Interrupts Handler
void EXTI2_IRQHandler() {

	//TOUCH DETECTED
	if (EXTI_GetITStatus(EXTI_Line2) != RESET) {

		//Check If GSL chip is already initialized
		if (GSL_ready_flag == 1) {

			//Load touch coords in struct
			Read_Coords();
			Active_Window(650, 400, 60, 200);
			sprintf(buf, "Coord X:   %03c ", (unsigned char)resul[0]);
			LCD_PrintStr(buf, 10, 60, White, Black, 1, 1, 0);

			sprintf(buf, "Coord Y:   %03i ", (unsigned char)resul[1]);
			LCD_PrintStr(buf, 10, 80, White, Black, 1, 1, 0);

			sprintf(buf, "Num finger:   %03d ", (unsigned char)resul[2]);
			LCD_PrintStr(buf, 10, 100, White, Black, 1, 1, 0);

			sprintf(buf, "Finger coord:   %03u ", (unsigned char)resul[3]);
			LCD_PrintStr(buf, 10, 120, White, Black, 1, 1, 0);
			//Check if a button is touched and acts regarding that button
			//IfButtonTouched_Act();
		} else {
			Check_toLCD("Error Ready Flag");
		}

		//Clear flag interrupt

		EXTI_ClearITPendingBit(EXTI_Line1);
	}
}

void Read_Coords() {

	uint8_t touch_data[8] = { 0 };
	i2c_Read(GSL_DATA_REG_ADDR, touch_data, 8);
	resul[2] = touch_data[0];
	resul[0] = ((((uint32_t) touch_data[5]) << 8) | (uint32_t) touch_data[4])
			& 0x00000FFF; // 12 bits of X coord
	resul[1] = ((((uint32_t) touch_data[7]) << 8) | (uint32_t) touch_data[6])
			& 0x00000FFF; // 12 bits of Y coord

	resul[3] = (uint32_t) touch_data[7] >> 4; // finger that did the touch
}

/*
 void Read_Coords() {

 uint8_t touch_data[8] = { 0 };
 i2c_Read(GSL_DATA_REG_ADDR, touch_data, 8);
 screen.touch_event.n_fingers = touch_data[0];
 screen.touch_event.coords.x = ((((uint32_t) touch_data[5]) << 8)
 | (uint32_t) touch_data[4]) & 0x00000FFF; // 12 bits of X coord
 screen.touch_event.coords.y = ((((uint32_t) touch_data[7]) << 8)
 | (uint32_t) touch_data[6]) & 0x00000FFF; // 12 bits of Y coord
 screen.touch_event.coords.finger = (uint32_t) touch_data[7] >> 4; // finger that did the touch
 }*/

void I2C_Start(uint8_t address, uint8_t direction, uint8_t ack) {
	/* Generate I2C start pulse */
	I2C1->CR1 |= I2C_CR1_START;
	/* Wait till I2C is busy */
	I2C_Timeout = I2C_TIMEOUT;
	while (!(I2C1->SR1 & I2C_SR1_SB)) {
		if (--I2C_Timeout == 0x00) {
			Check_toLCD("Error Start");

			return 1;
		}
		Check_toLCD("Start Ok");

	}
	/* Enable ack if we select it */
	if (ack) {
		I2C1->CR1 |= I2C_CR1_ACK;
	}
	/* Send write/read bit */
	if (direction == I2C_TRANSMITTER_MODE) {
		/* Send address with zero last bit */
		I2C1->DR = address & ~I2C_OAR1_ADD0;

		/* Wait till finished */
		I2C_Timeout = I2C_TIMEOUT;
		while (!(I2C1->SR1 & I2C_SR1_ADDR)) {
			if (--I2C_Timeout == 0x00) {
				Check_toLCD("Error Start Tx");
				return 1;
			}
			Check_toLCD("Start Tx Ok");
		}
	}
	if (direction == I2C_RECEIVER_MODE) {
		/* Send address with 1 last bit */
		I2C1->DR = address | I2C_OAR1_ADD0;

		/* Wait till finished */
		I2C_Timeout = I2C_TIMEOUT;
		while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED)) {
			if (--I2C_Timeout == 0x00) {
				Check_toLCD("Error Start Rx");
				return 1;
			}
			Check_toLCD("Start Rx Ok");
		}
	}
	/* Read status register to clear ADDR flag */
	I2C1->SR2;
}

void I2C_Stop() {
	/* Wait till transmitter not empty */
	I2C_Timeout = I2C_TIMEOUT;
	while (((!(I2C1->SR1 & I2C_SR1_TXE)) || (!(I2C1->SR1 & I2C_SR1_BTF)))) {
		if (--I2C_Timeout == 0x00) {
			Check_toLCD("Error Stop");
			return 1;
		}
		Check_toLCD("Stop Ok");
	}
	/* Generate stop */
	I2C1->CR1 |= I2C_CR1_STOP;
}

uint8_t I2C_ReadAck() {
	uint8_t data;

	/* Enable ACK */I2C1->CR1 |= I2C_CR1_ACK;

	/* Wait till not received */
	I2C_Timeout = I2C_TIMEOUT;
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED)) {
		if (--I2C_Timeout == 0x00) {
			Check_toLCD("Error Read Ack");
			return 1;
		}
		Check_toLCD("Read Ack Ok");
	}


	/* Read data */
	data = I2C1->DR;

	/* Return data */
	return data;
}

uint8_t I2C_ReadNack() {
	uint8_t data;

	/* Disable ACK */I2C1->CR1 &= ~I2C_CR1_ACK;

	/* Generate stop */I2C1->CR1 |= I2C_CR1_STOP;

	/* Wait till received */
	I2C_Timeout = I2C_TIMEOUT;
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED)) {
		if (--I2C_Timeout == 0x00) {
			Check_toLCD("Error Read Nack");
			return 1;
		}
		Check_toLCD("Read Nack Ok");
	}
	/* Read data */
	data = I2C1->DR;
	/* Return data */
	return data;
}

uint8_t i2c_Write(uint8_t reg, uint8_t *buf, int cnt) {

	uint8_t i;
	//Send START condition and wait till done
	I2C_Start(0x40, I2C_TRANSMITTER_MODE, I2C_Ack_Disable);
	//Write the address where we want to write
	I2C_WriteData(reg);
	//Write data into the defined address
	for (i = 0; i < cnt; i++) { //cont debe ser < 126 por el tamaño del registro (ver firmware)
		I2C_WriteData(buf[i]);
	}
	Check_toLCD("I2C Write OK");
	//Send STOP condition
	I2C_Stop(I2C1);
}

uint8_t i2c_Read(uint8_t reg, uint8_t *buf, int cnt) { //uint8_t reg, uint8_t *buf, int cnt

	uint8_t i;

	I2C_Start(0x40, I2C_TRANSMITTER_MODE, I2C_Ack_Disable);
	I2C_WriteData(reg);
	I2C_Stop();

	I2C_Start(0x40, I2C_RECEIVER_MODE, I2C_Ack_Disable);
	for (i = 0; i < cnt; i++) {
		if (i == (cnt - 1)) {
			/* Last byte */
			buf[i] = I2C_ReadNack();
		} else {
			buf[i] = I2C_ReadAck();
		}
	}
	Check_toLCD("I2C Read OK");
}

uint8_t I2C_WriteData(uint8_t data) {
	/* Wait till I2C is not busy anymore */
	I2C_Timeout = I2C_TIMEOUT;
	while (!(I2C1->SR1 & I2C_SR1_TXE) && I2C_Timeout) {
		if (--I2C_Timeout == 0x00) {
			Check_toLCD("Error Write Data");
			return 1;

		}

		/* Send I2C data */
		I2C1->DR = data;
	}
}
