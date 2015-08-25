#include "RA8875.h"







typedef struct {
	char * str;
	uint16_t x;
	uint16_t y;
	uint16_t fcolor;
	uint16_t bcolor;
	uint8_t mode;
	uint8_t type;
	uint8_t zoom;

} params_str;

params_str print_arguments;

#define FULL_LCD  1

#define CENTER_LCD  0

#define ACTIVE_PANEL  2






void LCD_Init(void);




void LCD_PrintStr(char *str, uint16_t x, uint16_t y, uint16_t fcolor,
		uint16_t bcolor, uint8_t mode, uint8_t type, uint8_t zoom);
void Show_String(char *str);
void LCD_Clear(uint16_t color,uint8_t size);
void LCD_Reset(void);
void Chk_Wait(void);
void LCD_WriteText(void);

void print_pureImage (void);
void print_BTEImage(uint16_t XL, uint16_t XR, uint16_t YT, uint16_t YB);
void print_BTELogo(uint16_t XL, uint16_t XR, uint16_t YT, uint16_t YB);

void Check_toLCD(char *str);
