//#include "car_pic.h"
#include "boton.h"
#include "button.h"
#include "logo.h"

void print_BTEImage(uint16_t XL, uint16_t XR, uint16_t YT, uint16_t YB) {
	uint16_t i;
	Graphic_Mode();
	//Set destiny point
	BTE_Source_Destination(XL, XR, YT, YB);
	//Set Image width and weight
	BTE_Size_setting(200, 240);
	//set BTE write and ROP source = Destination
	BTE_ROP_Code(0xC0);
	BTE_enable();

	LCD_WriteCmd(0x02); //MRWC
	for (i = 0; i < 48000; i++) {
		LCD_WriteData(image[i]);
		Chk_Busy();
	}
}

void print_BTELogo(uint16_t XL, uint16_t XR, uint16_t YT, uint16_t YB) {
	uint16_t i;
	Graphic_Mode();
	//Set destiny point
	BTE_Source_Destination(XL, XR, YT, YB);
	//Set Image width and weight
	BTE_Size_setting(110, 40);
	//set BTE write and ROP source = Destination
	BTE_ROP_Code(0xC0);
	BTE_enable();

	LCD_WriteCmd(0x02); //MRWC
	for (i = 0; i < 4400; i++) {
		LCD_WriteData(logo[i]);
		Chk_Busy();
	}
}
void print_pureImage(void) { /*(0,200,120,360)*/
	uint16_t i;
	//Active Window
	Active_Window(0, 199, 100, 339);
	//Coordinates
	XY_Coordinate(0, 100);
	Graphic_Mode();
	LCD_WriteCmd(0x02); //set CMD02 to  prepare data write
	for (i = 0; i < 48000; i++) {
		LCD_WriteData(image[i]); //write black data
		Chk_Busy();
	}
}
