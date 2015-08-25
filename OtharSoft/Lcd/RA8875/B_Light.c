#include "RA8875.h"


/*******************************************************************************
 * Function Name  : BackLight_Timer
 * Description    : Initialize Timer - BlackLight Control PWM

 * Input          : None
 * Output         : None
 * Return         : None
 * Attention		 : None
 *******************************************************************************/
void BackLight_Timer(void) {
	/*TIM4 is connected to APB1 bus, which has on F407 device 42MHz clock
	 But, timer has internal PLL, which double this frequency for timer, up to 84MHz
	 Remember: Not each timer is connected to APB1, there are also timers connected
	 on APB2, which works at 84MHz by default, and internal PLL increase
	 this to up to 168MHz  */
	TIM_TimeBaseInitTypeDef timerInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

	timerInitStructure.TIM_Prescaler = 83; // timer_tick_frequency = 84000000 / (0 + 1) = 84000000
	timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	//TIM_Period = timer_tick_frequency / PWM_frequency - 1
	timerInitStructure.TIM_Period = 19999; // 1Mhz	TIM_Period = 1000000 / 50 - 1 = 19999
	timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	timerInitStructure.TIM_RepetitionCounter = 0;
	/* Initialize TIM4 */
	TIM_TimeBaseInit(TIM4, &timerInitStructure);
	TIM_Cmd(TIM4, ENABLE);
}

/*******************************************************************************
 * Function Name  : BackLight_Init
 * Description    : Initialize Timer to BlackLight Control PWM

 * Input          : None
 * Output         : None
 * Return         : None
 * Attention		 : None
 *******************************************************************************/
void BackLight_Init(void) {
	/*
	 To get proper duty cycle, you have simple equation
	 pulse_length = ((TIM_Period + 1) * DutyCycle) / 100 - 1
	 where DutyCycle is in percent, between 0 and 100%

	 25% duty cycle:     pulse_length = ((8399 + 1) * 25) / 100 - 1 = 2099
	 50% duty cycle:     pulse_length = ((8399 + 1) * 50) / 100 - 1 = 4199
	 75% duty cycle:     pulse_length = ((8399 + 1) * 75) / 100 - 1 = 6299
	 100% duty cycle:    pulse_length = ((8399 + 1) * 100) / 100 - 1 = 8399

	 Remember: if pulse_length is larger than TIM_Period, you will have output HIGH all the time
	 */

	TIM_OCInitTypeDef outputChannelInit;
	/* PWM mode 2 = Clear on compare match */
	/* PWM mode 1 = Set on compare match */
	outputChannelInit.TIM_OCMode = TIM_OCMode_PWM2;
	outputChannelInit.TIM_OutputState = TIM_OutputState_Enable;
	outputChannelInit.TIM_OCPolarity = TIM_OCPolarity_Low;

	outputChannelInit.TIM_Pulse = 14999; // 75% duty cycle
	TIM_OC1Init(TIM4, &outputChannelInit);
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);

	/* outputChannelInit.TIM_Pulse = 4199; // 50% duty cycle
	 TIM_OC2Init(TIM4, &outputChannelInit);
	 TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);*/

	/*outputChannelInit.TIM_Pulse = 8399; // 100% duty cycle
	 TIM_OC3Init(TIM4, &outputChannelInit);
	 TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);*/

	/*outputChannelInit.TIM_Pulse = 8399; // 100% duty cycle
	 TIM_OC4Init(TIM4, &outputChannelInit);
	 TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);*/

}
