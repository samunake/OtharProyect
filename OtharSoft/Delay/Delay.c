#include "stm32f4xx_conf.h"
#include "Delay.h"



uint32_t delayTime;
uint8_t TimerInicializated=0;
volatile uint32_t Time1 = 0;
volatile uint32_t Time2 = 0;

void Init_Delay(void) {

	TimerDelay_Init();
	TimerInicializated = 1;
}


void Enable_TimerDelay(void){

	if (!TimerInicializated){return;}
	TIM_Cmd(TIMERDELAY, ENABLE);
}

void Disable_TimerDelay(void){

	TIM_Cmd(TIMERDELAY, DISABLE);
}





void TimerDelay_Init(void) {
	TIM_TimeBaseInitTypeDef Timer_InitStructure;
	NVIC_InitTypeDef NVIC_InitStruct;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);

	Timer_InitStructure.TIM_Prescaler = 83; // 1 us
	Timer_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	Timer_InitStructure.TIM_Period = 999; // TIM2 & TIM5 -> 32 bits
	Timer_InitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	Timer_InitStructure.TIM_RepetitionCounter = 0;

	/* Initialize TIM5 */
	TIM_TimeBaseInit(TIMERDELAY, &Timer_InitStructure);

	/* Enable interrupt each 1ms */
	//TIM_ITConfig(TIMERDELAY, TIM_IT_Update, ENABLE);

	/* Set NVIC parameters */
	NVIC_InitStruct.NVIC_IRQChannel = TIM5_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;

	/* Add Timer to NVIC */
	NVIC_Init(&NVIC_InitStruct);

	/*Start Timer */
	TIM_Cmd(TIMERDELAY, ENABLE);
}
__inline void Delay_ms(uint32_t ms) {

	volatile uint32_t timer = TIM_GetCounter(TIMERDELAY);
	uint32_t milis = ms*1000;
	do {
		/* Count timer ticks */
		while ((TIMERDELAY->CNT - timer) == 0);

		/* Increase timer */
		timer = TIMERDELAY->CNT;

		/* Decrease microseconds */
	} while (--milis);
}
__inline void Delay_us(uint32_t micros) {

	volatile uint32_t timer = TIM_GetCounter(TIMERDELAY);

	do {
		/* Count timer ticks */
		while ((TIMERDELAY->CNT - timer) == 0);

		/* Increase timer */
		timer = TIMERDELAY->CNT;

		/* Decrease microseconds */
	} while (--micros);
}


void TIM5_IRQHandler(void) {

	TIM_ClearITPendingBit(TIMERDELAY,TIM_IT_Update);

	uint8_t i;

	Time1++;
	if (Time2 != 0x00) {
		Time2--;
	}

	/* Call user function */
	MILI_Handler();

}
