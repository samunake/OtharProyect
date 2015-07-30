#include "Driver_Lights.h"


/*******************************************************************************
 * Function Name  : initializeGPIO_LIGHTS
 * Description    : Initialize GPIO LIGHTS PINS
 * Input          : None
 * Output         : PE0 -> LIGHT1
 *					PE2 -> lIGHT2
 *					PB8 -> LIGHT3
 *					PB9 -> LIGHT4
 * Return         : None
 * Attention	  : None
 *******************************************************************************/

void initializeGPIO_LIGHTS(void) {
	GPIO_InitTypeDef GPIO_InitStructure;

	/* Enable GPIO E clock */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

	/* GPIOD configuration */

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

	GPIO_Init(GPIOD, &GPIO_InitStructure);

	/* Enable GPIO B clock */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	/* GPIOD configuration */

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

	GPIO_Init(GPIOD, &GPIO_InitStructure);

}

/*******************************************************************************
 * Function Name  : Light1_ON
 * Description    : Set on Light 1
 * Input          : None
 * Output         : NonE
 * Return         : None
 * Attention	  : None
 *******************************************************************************/
void Light1_ON(void) {

	GPIO_SetBits(GPIOE, GPIO_Pin_2);

}
void Light2_ON(void) {

	GPIO_SetBits(GPIOE, GPIO_Pin_0);

}
void Light3_ON(void) {

	GPIO_SetBits(GPIOB, GPIO_Pin_9);

}
void Light4_ON(void) {

	GPIO_SetBits(GPIOB, GPIO_Pin_8);

}

void Light1_OFF(void) {

	GPIO_ResetBits(GPIOE, GPIO_Pin_2);

}
void Light2_OFF(void) {

	GPIO_ResetBits(GPIOE, GPIO_Pin_0);

}
void Light3_OFF(void) {

	GPIO_ResetBits(GPIOB, GPIO_Pin_9);

}
void Light4_OFF(void) {

	GPIO_ResetBits(GPIOB, GPIO_Pin_8);

}
