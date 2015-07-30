

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


void LCDPrintStrROM(char *str, uint16_t x, uint16_t y);
void LCDPrintStr(char *str, uint16_t x, uint16_t y, uint16_t fcolor,
		uint16_t bcolor, uint8_t mode, uint8_t type, uint8_t zoom);
void Show_String(char *str);
void LCD_Clear(uint16_t color);
void LCD_Reset(void);
void Chk_Wait(void);
void LCD_WriteText(void);
