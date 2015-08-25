


/* LCD color */
#define White          0xFFFF
#define Black          0x0000
#define Grey           0xF7DE
#define Blue           0x001F
#define Blue2          0x051F
#define Red            0xF800
#define Magenta        0xF81F
#define Green          0x07E0
#define Cyan           0x7FFF
#define Yellow         0xFFE0



//Days in a week
#define LUNES  1
#define MARTES 2
#define MIERCOLES 3
#define JUEVES  4
#define VIERNES  5
#define SABADO  6
#define DOMINGO  7

/*******    Common defines *************/
/*#ifndef Status
typedef enum {
	INACTIVE= 0X00,
	ACTIVE = 0X01,
} Status;
#endif*/
/**********  Touch defines **************/
/*#ifndef LightsSelected
typedef enum {
	No_LightsSel = 0b00000000,
	Light_1 = 0b11000000,
	Light_2 = 0b00110000,
	Light_3 = 0b00001100,
	Light_4 = 0b00000011,
	Lights_1_2 = 0b11110000,
	Lights_1_3 = 0b11001100,
	Lights_1_4 = 0b11000011,
	Lights_2_3 = 0b00111100,
	Lights_2_4 = 0b00110011,
	Lights_3_4 = 0b00001111,
	Lights_1_2_3 = 0b11111100,
	Lights_1_2_4 = 0b11110011,
	Lights_1_3_4 = 0b11001100,
	Lights_2_3_4 = 0b00111111,
	allLights_sel = 0b11111111,
} LightsSelected;
#endif

#ifndef AlarmSel
typedef enum {
	NO_AlarmSel = 0X00, SET_ON = 0X01, SET_OFF = 0x02,
} AlarmSel;
#endif

#ifndef BUTTONS
typedef enum {
	BUTTONS = 0X00, DIMMERS = 0X01, SEL_PROGRAM = 0x02, PROGRAM = 0x03,
} MenuTypes;
#endif
*/
/**************  Alarm defines  ********/
/*#define	ALRM_ON 0X00
#define	ALRM_OFF 0X01

#ifndef _alarm
typedef struct{
	char *name;
	Status status;
	LightsSelected ALRM_lightsSet;
	RTC_TimeTypeDef alarmTime;
} _alarm;
#endif

*/

/**************  Lights defines  ********/
/*#ifndef LIGHT_t
typedef struct {
	char *name;
	uint16_t color;
	Status status;
	uint16_t dimmer;
	Status trigger;

} LIGHT_t;
#endif*/

/************ I2C defines *****************/
/*#ifndef _coord
typedef struct {
	uint32_t x, y;
	uint8_t finger;
}_coord;
#endif

#ifndef _touch_event
typedef struct  {
	uint8_t n_fingers;
_coord coords;
}_touch_event;
#endif*/
/**********  GSL1680 defines *************/
/*#define SCREEN_MAX_X 		800
#define SCREEN_MAX_Y 		480
#define GSLX680_I2C_ADDR 		0x40
#define GSL_DATA_REG_ADDR		0x80
#define GSL_STATUS_REG_ADDR		0xe0
#define GSL_PAGE_REG_ADDR		0xf0

#ifndef _screen
typedef struct {
	uint8_t numLightsON;
	LightsSelected lightsSet;
	MenuTypes menu;
	AlarmSel alarmSel;
	_alarm alarms[2];
	_touch_event touch_event;
  LIGHT_t LIGHTS[4];
} _screen ;
#endif*/



