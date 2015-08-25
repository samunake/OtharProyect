#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#include "defines.h"


uint8_t Wait_BTF();

uint8_t i2c_Write(uint8_t reg, uint8_t *buf, int cnt);

uint8_t i2c_Read(uint8_t reg, uint8_t *buf, int cnt);

uint8_t I2C_WriteData(uint8_t data);

void Read_Coords();

void Init_Touch();
