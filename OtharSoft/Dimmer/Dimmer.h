




#define TRIAC_ON 13 // 13 ciclos*8.333 us = 108us (Tiempo minimo de activar triac calculado 76 us)



void Init_Dimmer(void);
void init_DimmerValues(void);
void Configure_ZCInterrupt(void);
void TIM_Config(void);
void EXTI9_5_IRQHandler(void);

void TIM1_CC_IRQHandler(void);
void TIM1_UP_TIM10_IRQHandler(void);
