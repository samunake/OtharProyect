#include "stm32f4xx_conf.h"


void Init_I2C();

void configure_I2CGPIOS();

void configure_I2CSettings();

void configure_I2CInterrupts();

//HANDLER DE INTERRUPCIONES DE I2C1
void I2C1_EV_IRQHandler(void);

//HANDLER DE ERRORES DE I2C1
void I2C1_ER_IRQHandler(void);
