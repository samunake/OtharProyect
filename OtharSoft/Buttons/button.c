//#include "car_pic.h"
#include "boton.h"
#include "button.h"
//#include "icon.h"

/*void print_BTEImage (uint16_t XL,uint16_t XR ,uint16_t YT ,uint16_t YB ){ //(0,200,120,360)

			//Set destiny point
			BTE_Source_Destination(XL,XR,YT,YB);
			//Set Image width and weight
			BTE_Size_setting(200,240);

			BTE_ROP_Code(0x78); //	set BTE color expansion
			BTE_enable();
			LCD_CmdWrite(0x02);//MRWC
			for(i=0;i<1500;i++)
			{
				LCD_DataWrite(gImage_rabbit[i]);
				Chk_Busy();
			}
		}
		*/
void print_pureImage (void){ /*(0,200,120,360)*/
	uint16_t i;
			//Active Window
			Active_Window(0,199,100,339);
			//Coordinates
			XY_Coordinate(0,100);
			Graphic_Mode();
				LCD_WriteCmd(0x02); //set CMD02 to  prepare data write
				for(i=0;i<48000;i++)
				{
				LCD_WriteData(image[i]);  //write black data
				Chk_Busy();
				}
		}
