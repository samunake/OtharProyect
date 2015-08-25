

#include "stm32f4xx_conf.h"
#include "system_stm32f4xx.h"
#include "stm32f4xx_rtc.h"
#include "defines.h"
#include "Clock/tm_stm32f4_rtc.h"
#include "attributes.h"
#include "Dimmer.h"

#define LUNES  1
#define MARTES 2
#define MIERCOLES 3
#define JUEVES  4
#define VIERNES  5
#define SABADO  6
#define DOMINGO  7


void InitAlarm(void);

void Configure_AlarmInterrupt(void);

void Set_Alarm(void); //uint8_t DayWeekSel, uint8_t DateWeekNum ,uint8_t hour, uint8_t minute, uint8_t second

void RTC_Alarm_IRQHandler(void);
