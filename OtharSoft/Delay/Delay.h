#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "attributes.h"
#include "misc.h"
#include "stm32f4xx_tim.h"
#include "stdlib.h"



extern volatile uint32_t Time1;
extern volatile uint32_t Time2;

#define TIMERDELAY TIM5
/**
 * @brief  Gets the Time1 variable value
 * @param  None
 * @retval Current time in milliseconds
 */
#define DELAY_TIME1()					(Time1)

/**
 * @brief  Sets value for Time1 variable
 * @param  time: Time in milliseconds
 * @retval None
 */
#define SET_DELAY_TIME1(time)			(Time1 = (time))

/**
 * @brief  Gets the Time2 variable value
 * @param  None
 * @retval Current time in milliseconds
 * @note   This is not meant for public use
 */
#define DELAY_TIME2()				(Time2)

/**
 * @brief  Sets value for Time2 variable
 * @param  time: Time in milliseconds
 * @retval None
 * @note   This is not meant for public use
 */
#define SET_DELAY_TIME2(time)			(Time2 = (time))


__weak void MILI_Handler(void);


void Init_Delay(void);
void Enable_TimerDelay(void);
void Disable_TimerDelay(void);

extern void Delay_ms(uint32_t milis);
extern void Delay_us(uint32_t micros);
void TimerDelay_Init(void);
void TIM5_IRQHandler(void);

