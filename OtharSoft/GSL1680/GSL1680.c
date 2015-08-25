#include "GSL1680.h"

extern uint8_t GSL_ready_flag;

/*The known GSL registers are:
 0x00-0x7F: these registers are used to load portions of the firmware
 0x80: contains the number of touches in the screen. If zero, the user isn't touching the screen; if one, only one finger is on the screen; if two, there are two fingers; and so on.
 0x84-0x87: contains the coordinates for the first touch.
 0x88-0x8B: contains the coordinates for the second touch.
 0x8C-0xAB: contains the coordinates for the third, fourth, and so on (up to five in some devices, up to ten in other), touches, in the same format than the previous ones (four bytes for each touch).
 0xE0: STATUS register
 0xE4, 0xBC-0xBF: some kind of control registers. Needed for uploading the firmware and soft resetting the chip (there's not more data available about them).
 0xF0: PAGE register. Contains the memory page number currently mapped in the 0x00-0x7F registers.
 */
uint8_t buf[126];

void Init_chipGSL() {

	// CTP startup procedure
	Enable_Chip();
	Reset_Chip();
	load_fw();
	startup_chip();
	Reset_Chip();
	Disable_Chip();
	Delay_ms(50);
	Enable_Chip();
	Delay_ms(30);
	Disable_Chip();
	Delay_ms(5);
	Enable_Chip();
	Delay_ms(20);
	Reset_Chip();
	startup_chip();
	//Set chip ready flag
	GSL_ready_flag = 1;
}

void Enable_Chip() {
	//GPIO_SetBits(GPIOE, GPIO_Pin_6);
	GPIO_SetBits(GPIOC, GPIO_Pin_3);
}

void Disable_Chip() {
	//GPIO_ResetBits(GPIOE, GPIO_Pin_6);
	GPIO_ResetBits(GPIOC, GPIO_Pin_3);
}

void Reset_Chip() {
	//RESET CHIP PROCEDURE
	buf[0] = 0x88;
	i2c_Write(GSL_STATUS_REG_ADDR, buf, 1);
	Delay_ms(10);
	buf[0] = 0x04;
	i2c_Write(0xe4, buf, 1);
	Delay_ms(10);
	buf[0] = 0x00;
	buf[1] = 0x00;
	buf[2] = 0x00;
	buf[3] = 0x00;
	i2c_Write(0xbc, buf, 4);
	Delay_ms(10);
}

void startup_chip(void) {
	uint8_t buf[4];
	buf[0] = 0x00;
	i2c_Write(0xe0, buf, 1);
}

void load_fw(void) {
	uint8_t addr;
	uint8_t Wrbuf[4];
	uint8_t source_line = 0;
	uint16_t source_len = sizeof(GSLX680_FW) / sizeof(struct fw_data);

	for (source_line = 0; source_line < source_len; source_line++) {
		addr = GSLX680_FW[source_line].offset;
		Wrbuf[0] = (char) (GSLX680_FW[source_line].val & 0x000000ff);
		Wrbuf[1] = (char) ((GSLX680_FW[source_line].val & 0x0000ff00) >> 8);
		Wrbuf[2] = (char) ((GSLX680_FW[source_line].val & 0x00ff0000) >> 16);
		Wrbuf[3] = (char) ((GSLX680_FW[source_line].val & 0xff000000) >> 24);
		i2c_Write(addr, Wrbuf, 4);
	}
}

