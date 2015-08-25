#include "stm32f4xx.h"


typedef struct {

	char *nom;
	uint16_t color;
	uint8_t status;
	uint16_t dimmer;
	uint8_t trigger;
	uint16_t port;
	uint16_t pin;


} LIGHT_t;

typedef enum {
	ON = 0X01,
	OFF= 0X00,
} status,trigger;

//void setLight(LIGHT_t *light, unsigned char sta);
void Toggle_Light(LIGHT_t *LIGHTx);
void SetDimmerValue(LIGHT_t *LIGHTx, uint16_t value);
void SetLight_On(LIGHT_t *LIGHTx);

void GPIO_LIGHTS_Init(void);

