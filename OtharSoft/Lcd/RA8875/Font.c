
#include "RA8875.h"
#include "defines.h"



uint8_t DMA_Access_Font(void) {

	//External_CGROM();
	//GT_serial_ROM_select_GT30L32S4W();
	//Font_code_ASCII();
	Serial_ROM_select0();
	Serial_ROM_Address_set_24bit();
	Serial_ROM_direct_access_mode_enable();
	SROM_CLK_DIV(0x03);
	Select_Serial_Waveform_mode3();
	SERIAL_ROM_Read_Cycle_5bus();
	SERIAL_ROM_Single_mode();

}
uint8_t *temp;
uint8_t  get_FontByte(uint8_t ascii) {

	uint8_t i;

	DAM_Address_24bits(Addr_Font(ascii));
	Chk_Busy_DIR_Access();
	for(i=0;i<48;i++){
	temp[i]= DAM_Read_Data_buffer();
	}
	return *temp;
	// Register E2 return byte for Data

}

/*uint24_t Font_Size(uint24_t AddressBase){

 }*/

void Print_String(char *c) {
	uint8_t ascii = 0;
	uint8_t data;
	//LCD_WriteCmd(0x02);
	while (*c != '\0') {
		ascii = *c;
		data = get_FontByte(ascii);
		LCD_WriteCmd(0x02);
		while (*temp != '\0'){
			LCD_WriteData(data);
			++temp;
			data = *temp;
		}
		LCD_WriteReg(0x02, 55);
		//LCD_WriteData(data);
		c++;
	}
}

uint32_t Addr_Font(uint16_t ascii) {
	uint32_t addr;
	if (ascii >= 0x20 && ascii <= 0x7e) {
		addr = (ascii - 0x20) * 48 + 0x1dff00;
	}
	return addr;

}

void External_Font(void) {

	External_CGROM();
	CGROM_Font();
	GT_serial_ROM_select_GT30L32S4W();
	Font_code_ASCII();
	Serial_ROM_select0();
	Serial_ROM_Address_set_24bit();
	SROM_CLK_DIV(0x03);
	Select_Serial_Waveform_mode3();
	SERIAL_ROM_Read_Cycle_5bus();
	SERIAL_ROM_Font_mode();
	SERIAL_ROM_Single_mode();

	/*Speed Configuration
	 * 06h,0x03 SYSCLK/4
	 * 05h,20	waveform 3 selected
	 * 05h,&Ef |80 1 DUMMY CICLE*/

}

void TextMode_Normal(void){

	Text_Mode();
	Text_Cursor_Disable();
	Text_Cursor_Blink_Disable();
	Memory_Write_LeftRight_TopDown();
	MemoryWrite_Cursor_autoIncrease();
	MemoryRead_Cursor_autoIncrease();


}

void showTypeFonts(void){
		LCDPrintStrROM("Alo Presinde",400,100);

			Active_Window(0, 799, 0, 479);
		 LCDPrintStr("abc", 0, 0, Black, White, 1, 1, "zoom2");
		 LCDPrintStr("Hola Presunta", 0, 30, Black, White, 1, 2, "zoom2");
		 LCDPrintStr("Hola Presunta", 0, 60, Black, White, 1, 3, "zoom2");
		 LCDPrintStr("abc", 0, 90, Black, White, 1, 4, "zoom2");

		 LCDPrintStr("Hola Presunta", 200, 00, Black, White, 2, 1, "zoom2");
		 LCDPrintStr("Hola Presunta", 200, 30, Black, White, 2, 2, "zoom2");
		 LCDPrintStr("Hola Presunta", 200, 60, Black, White, 2, 3, "zoom2");
		 LCDPrintStr("Hola", 200, 90, Black, White, 2, 4, "zoom2");

		 LCDPrintStr("Hola", 300, 100, Black, White, 3, 1, "zoom2");
		 LCDPrintStr("Hola", 300, 150, Black, White, 3, 2, "zoom2");
		 LCDPrintStr("Hola", 300, 200, Black, White, 3, 3, "zoom2");
		 LCDPrintStr("Hola", 300, 250, Black, White, 3, 4, "zoom2");


		 // HOLA PRESIDENTE ASCII


		//LCD_WriteText();
		/* CUADRADITO**************************************************
		 *
		 *
		 *
		 * *************************************************************/
		/* Active_Window(100,200,200,300);
		 Graphic_Mode();
		 XY_Coordinate(100,200);
		 LCD_WriteCmd(0x02);//MRWC
		 uint32_t i;
		 for(i=0;i<10201;i++)
		 {
		 LCD_WriteData(Black);
		 Chk_Busy();
		 }
		 //Delay_ms(2000);
		 //ActiveWindow_Clear();*/
}
