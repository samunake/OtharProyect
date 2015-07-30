#include "stm32f4xx.h"
#include "Driver_RA8875.h"
#include "Driver_Font.h"


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

void TextMode_Normal(){

	Text_Mode();
	Text_Cursor_Disable();
	Text_Cursor_Blink_Disable();
	Memory_Write_LeftRight_TopDown();
	MemoryWrite_Cursor_autoIncrease();
	MemoryRead_Cursor_autoIncrease();


}
