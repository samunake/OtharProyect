#include "stm32f4xx_conf.h"

uint32_t delayTime;

void Init_SysTick(void){

	delayTime=0;
	(SysTick_Config(SystemCoreClock / 1000));//1000000
}



void SysTick_Handler(void){
	if(delayTime>0)
		delayTime--;
}

void Delay_us(uint32_t time){
	delayTime=time;
	while(delayTime!=0);

}

void Delay_ms(uint32_t time){
	delayTime=time;//*1000
	while(delayTime!=0);

}
