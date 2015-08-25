#include "Lights.h"
#include "RA8875.h"
#include "../Includes/defines.h"

LIGHT_t LIGHT1, LIGHT2, LIGHT3, LIGHT4;

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
void GPIO_LIGHTS_Init(void) {
	GPIO_InitTypeDef GPIO_InitStructure;

	/* Enable GPIO E clock */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

	/* GPIOD configuration */

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

	GPIO_Init(GPIOE, &GPIO_InitStructure);
}

/************************************************************************
 * Function Name  : Show_String
 * Description    : Clear the screen
 * Input          : Color: Screen Color
 * Output         : None
 * Return         : None
 * Attention		   : None
 *******************************************************************************/
void Lights_Init(void) {

	// Initial values of each Light
	LIGHT1.nom = "Light One";
	LIGHT1.color = Black;
	LIGHT1.dimmer = 0;
	LIGHT1.status = OFF;
	LIGHT1.trigger = OFF;
	LIGHT1.port = GPIOC;
	LIGHT1.port = 6;

	LIGHT2.nom = "Light Two";
	LIGHT2.color = White;
	LIGHT2.dimmer = 0;
	LIGHT2.status = OFF;
	LIGHT2.trigger = OFF;
	LIGHT2.port = GPIOC;
	LIGHT2.port = 7;

	LIGHT3.nom = "Light Three";
	LIGHT3.color = White;
	LIGHT3.dimmer = 0;
	LIGHT3.status = OFF;
	LIGHT3.trigger = OFF;
	LIGHT3.port = GPIOC;
	LIGHT3.port = 8;

	LIGHT4.nom = "Light Four";
	LIGHT4.color = White;
	LIGHT4.dimmer = 0;
	LIGHT4.status = OFF;
	LIGHT4.trigger = OFF;
	LIGHT1.port = GPIOC;
	LIGHT1.port = 9;
}

/************************************************************************
 * Function Name  : Show_String
 * Description    : Clear the screen
 * Input          : Color: Screen Color
 * Output         : None
 * Return         : None
 * Attention		   : None
 *******************************************************************************/
void Toggle_Light(LIGHT_t *LIGHTx) {

	LIGHTx->status = ON;
}

/************************************************************************
 * Function Name  : Show_String
 * Description    : Clear the screen
 * Input          : Color: Screen Color
 * Output         : None
 * Return         : None
 * Attention		   : None
 *******************************************************************************/
void SetDimmerValue(LIGHT_t *LIGHTx, uint16_t value) {

	LIGHTx->dimmer = value;
}

/*******************************************************************************
 * Function Name  : Light1_ON
 * Description    : Set on Light 1
 * Input          : None
 * Output         : NonE
 * Return         : None
 * Attention	  : None
 *******************************************************************************/

void SetLight_On(LIGHT_t *LIGHTx){

	GPIO_SetBits(LIGHTx->port, LIGHTx->pin);
}
