#include "Driver_Lights.h"

#define ON  0x01
#define OFF 0x00

static uint8_t dimmer1, dimmer2, dimmer3, dimmer4;
static uint8_t status_dim1, status_dim2, status_dim3, status_dim4;

#define TRIAC_ON 13 // 13 ciclos*8.333 us = 108us (Tiempo minimo de activar triac calculado 76 us)

void Configure_ZeroCrossingInterrupt(void);

void Init_DimmerTimer(void);

void EXTI0_IRQHandler(void);
