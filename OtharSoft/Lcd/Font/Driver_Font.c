#include "stm32f4xx.h"

uint8_t DMA_Access_Font(void) {

	uint8_t key;
	SROM_CLK_DIV(0x03);
	Select_Serial_Waveform_mode3();
	SERIAL_ROM_Read_Cycle_5bus();
	Serial_ROM_direct_access_mode_enable();
	DMA_Address_24bits(0x1e99d0);
	Chk_Busy_DIR_Access();
	DMA_Read_Data_buffer();

}

uint32_t Addr_Font(uint16_t ascii) {
	uint32_t addr;
	if (ascii >= 0x20 && ascii <= 0x7e) {
		addr = (ascii - 0x20) * 8 + 0x1ddf80;
	}
	return addr;

}

void External_Font(void) {

	Text_Mode();
	//Memory_Clear();
	//Select in bit 5 use external font ROM
	External_CGROM();
	// Chip Font select
	GT_serial_ROM_select_GT30L32S4W();
	/*Speed Configuration
	 * 06h,0x03 SYSCLK/4
	 * 05h,20	waveform 3 selected
	 * 05h,&Ef |80  1 DUMMY CICLE*/
	SROM_CLK_DIV(0x03);
	Select_Serial_Waveform_mode3();
	SERIAL_ROM_Read_Cycle_5bus();

}
