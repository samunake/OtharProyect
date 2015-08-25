#include "stm32f4xx.h"


/*********************************************************************************************************
 *
 * File                : RA8875.h
 * Hardware Environment:
 * Build Environment   : CooCox CoIDE  Version: 1.7.8
 * Version             : V1.0
 * By                  : Tomás Ariza Crespo
 *
 *
 *********************************************************************************************************/

/* Includes ------------------------------------------------------------------*/

/* Defines -------------------------------------------------------------------*/

/********************************************************************************************************/
uint8_t DMA_Access_Font(void);
uint8_t get_FontByte(uint8_t ascii);
void Print_String(char *c);
uint32_t Addr_Font(uint16_t ascii);
void External_Font(void);
void TextMode_Normal();
void showTypeFonts(void);

/*********************************************************************************************************/

void BackLight_Timer(void);
void BackLight_Init(void);

/*********************************************************************************************************/

void PLL_init(void);

void Chk_Busy(void);
void Chk_Busy_BTE(void);
void Chk_Busy_DIR_Access(void);
void Chk_DMA_Busy(void);

void Display_ON(void);
void Display_OFF(void);
void Normal_Mode_exitSleep(void);
void Sleep_Mode(void);
void Software_Reset(void);
void Start_Data(void);
void PCLK_inversion(void);
void PCLK_non_inversion(void);
void PCLK_width(uint8_t setx);
void Serial_ROM_select0(void);
void Serial_ROM_select1(void);
void Serial_ROM_Address_set_24bit(void);
void Serial_ROM_Address_set_32bit(void);
void Select_Serial_Waveform_mode0(void);
void Select_Serial_Waveform_mode3(void);
void SERIAL_ROM_Read_Cycle_4bus(void);
void SERIAL_ROM_Read_Cycle_5bus(void);
void SERIAL_ROM_Read_Cycle_6bus(void);
void SERIAL_ROM_Font_mode(void);
void SERIAL_ROM_DMA_mode(void);
void SERIAL_ROM_Single_mode(void);
void SERIAL_ROM_Dual_mode0(void);
void SERIAL_ROM_Dual_mode1(void);
void SROM_CLK_DIV(uint8_t CLK_DIV);
void Color_256(void);
void Color_65K(void);
void MPU_8bit_Interface(void);
void MPU_16bit_Interface(void);
uint8_t GPI_data(void);
void GPO_data(uint8_t setx);
void One_Layer(void);
void Two_Layers(void);
void HDIR_SEG0_SEGn(void);
void HDIR_SEGn_SEG0(void);
void VDIR_COM0_COMn(void);
void VDIR_COMn_COM0(void);
void CGROM_Font(void);
void CGRAM_Font(void);
void Internal_CGROM(void);
void External_CGROM(void);
void ISO8859_1(void);
void ISO8859_2(void);
void ISO8859_3(void);
void ISO8859_4(void);
void No_FullAlignment(void);
void FullAlignment(void);
void Font_with_BackgroundColor(void);
void Font_with_BackgroundTransparency(void);
void NoRotate_Font(void);
void Rotate90_Font(void);
void Horizontal_FontEnlarge_x1(void);
void Horizontal_FontEnlarge_x2(void);
void Horizontal_FontEnlarge_x3(void);
void Horizontal_FontEnlarge_x4(void);
void Vertical_FontEnlarge_x1(void);
void Vertical_FontEnlarge_x2(void);
void Vertical_FontEnlarge_x3(void);
void Vertical_FontEnlarge_x4(void);
void CGRAM_Select_Number(uint8_t setx);
void Scroll_Offset(uint16_t X, uint16_t Y);
void Line_distance(uint8_t setx);
void Font_Coordinate(uint16_t X, uint16_t Y);
void Font_size_16x16_8x16(void);
void Font_size_24x24_12x24(void);
void Font_size_32x32_16x32(void);
void Font_spacing_set(uint8_t setx); //uint8_t[5:0]
void GT_serial_ROM_select_GT21L16TW(void); //GT21L16T1W
void GT_serial_ROM_select_GT30L16U2W(void);
void GT_serial_ROM_select_GT30L24T3Y(void); //GT30H24T3Y
void GT_serial_ROM_select_GT30L24M1Z(void);
void GT_serial_ROM_select_GT30L32S4W(void); //GT30H32S4W
void Font_code_GB2312(void);
void Font_code_GB12345(void); //GB18030
void Font_code_BIG5(void);
void Font_code_UNICODE(void);
void Font_code_ASCII(void);
void Font_code_UNIJIS(void);
void Font_code_JIS0208(void);
void Font_code_LATIN(void);
void Font_Standard(void);
void Font_Arial(void);
void Font_Roman(void);
void Font_Bold(void); //for ASCII
void Active_Window(uint16_t XL, uint16_t XR, uint16_t YT, uint16_t YB);
void Scroll_Window(uint16_t XL, uint16_t XR, uint16_t YT, uint16_t YB);
void Graphic_Mode(void);
void Text_Mode(void);
void Text_Cursor_Disable(void);
void Text_Cursor_Enable(void);
void Text_Cursor_Blink_Disable(void);
void Text_Cursor_Blink_Enable(void);
void Memory_Write_LeftRight_TopDown(void);
void Memory_Write_RightLeft_TopDown(void);
void Memory_Write_DownTop_LeftRight(void);
void Memory_Write_TopDown_LeftRight(void);
void MemoryWrite_Cursor_autoIncrease(void);
void MemoryWrite_Cursor_NoautoIncrease(void);
void MemoryRead_Cursor_autoIncrease(void);
void MemoryRead_Cursor_NoautoIncrease(void);
void No_Graphic_Cursor(void);
void Graphic_Cursor(void);
void Graphic_Cursor_Set1(void);
void Graphic_Cursor_Set2(void);
void Graphic_Cursor_Set3(void);
void Graphic_Cursor_Set4(void);
void Graphic_Cursor_Set5(void);
void Graphic_Cursor_Set6(void);
void Graphic_Cursor_Set7(void);
void Graphic_Cursor_Set8(void);
void Write_To_Bank1and2(void);
void Write_To_CGRAM(void);
void Write_To_GraphicCursor(void);
void Write_To_Pattern(void);
void Write_To_Bank1(void);
void Write_To_Bank2(void);
void Text_Blink_Time(uint8_t setx);
void Memory_read_LeftRight_TopDown(void);
void Memory_read_RightLeft_TopDown(void);
void Memory_read_TopDown_LeftRight(void);
void Memory_read_DownTop_LeftRight(void);
void XY_Coordinate(uint16_t X, uint16_t Y);
void Memory_read_Coordinate(uint16_t X, uint16_t Y);
void Text_Cursor_Horizontal_Size(uint8_t setx);
void Text_Cursor_Vertical_Size(uint8_t setx);
void no_BTE_write(void);
void BTE_enable(void);
void BTE_contiguous_Data(void);
void BTE_rectangular_Data(void);
void BTE_ROP_Code(uint8_t setx);
void Layer1_Visible(void);
void Layer2_Visible(void);
void Transparent_Mode(void);
void Lighten_Overlay_Mode(void);
void Boolean_OR(void);
void Boolean_AND(void);
void Floating_window_mode(void);
void Floating_Window_transparent_with_BGTR_enable(void);
void Floating_Window_transparent_with_BGTR_disable(void);
void Layer1_2_scroll(void);
void Layer1_scroll(void);
void Layer2_scroll(void);
void Buffer_scroll(void);
void layer2_1_transparency(uint8_t setx);
void BTE_Source_Destination(uint16_t XL, uint16_t XR, uint16_t YT, uint16_t YB);
void Source_Layer1(void);
void Source_Layer2(void);
void Destination_Layer1(void);
void Destination_Layer2(void);
void BTE_Size_setting(uint16_t X, uint16_t Y);
void Background_color(uint16_t color);
void Foreground_color(uint16_t color);
void Text_Background_Color(uint8_t setR, uint8_t setG, uint8_t setB);
void Text_Foreground_Color(uint8_t setR, uint8_t setG, uint8_t setB);
void BTE_Background_color(uint8_t setR, uint8_t setG, uint8_t setB);
void BTE_Foreground_color(uint8_t setR, uint8_t setG, uint8_t setB);
void BTE_Background_red(uint8_t setx);
void BTE_Background_green(uint8_t setx);
void BTE_Background_blue(uint8_t setx);
void BTE_Foreground_red(uint8_t setx);
void BTE_Foreground_green(uint8_t setx);
void BTE_Foreground_blue(uint8_t setx);
void Pattern_Set_8x8(void);
void Pattern_Set_16x16(void);
void Pattern_Set_number(uint8_t setx);
void BackgroundColor_TransparentMode(uint8_t setR, uint8_t setG, uint8_t setB);
void Enable_TP(void);
void Disable_TP(void);
void Disable_Touch_WakeUp(void);
void Enable_Touch_WakeUp(void);
void TP_manual_mode(void);
void TP_auto_mode(void);
void TP_IDLE_mode(void);
void TP_event_mode(void);
void TP_latch_X(void);
void TP_latch_Y(void);
uint8_t ADC_X(void);
uint8_t ADC_Y(void);
uint8_t ADC_XY(void);
void Graphic_Cursor_Coordinate(uint16_t X, uint16_t Y);
void Graphic_Cursor_Color_0(uint8_t setx);
void Graphic_Cursor_Color_1(uint8_t setx);
void PWM1_enable(void);
void PWM1_disable(void);
void PWM1_disable_level_low(void);
void PWM1_disable_level_high(void);
void PWM1_fnuction_sel(void);
void PWM1_system_clk_out(void);
void PWM1_clock_ratio(uint8_t setx);
void PWM1_duty_cycle(uint8_t setx);
void PWM2_enable(void);
void PWM2_disable(void);
void PWM2_disable_level_low(void);
void PWM2_disable_level_high(void);
void PWM2_fnuction_sel(void);
void PWM2_system_clk_out(void);
void PWM2_clock_ratio(uint8_t setx);
void PWM2_duty_cycle(uint8_t setx);
void Stop_Memory_Clear(void);
void Memory_Clear(void);
void Clear_Full_Window(void);
void Clear_Active_Window(void);
void Draw_line(void);
void Draw_square(void);
void Draw_square_fill(void);
void Draw_circle(void);
void Draw_circle_fill(void);
void Draw_Triangle(void);
void Draw_Triangle_fill(void);
void Geometric_Coordinate(uint16_t X, uint16_t Y, uint16_t X1, uint16_t Y1);
void Circle_Coordinate_Radius(uint16_t X, uint16_t Y, uint16_t R);
void Draw_Ellipse(void);
void Draw_Ellipse_fill(void);
void Draw_Ellipse_Curve(void);
void Draw_Ellipse_Curve_Fill(void);
void Draw_Ellipse_Curve_part(uint8_t setx);
void Draw_Circle_Square(void);
void Draw_Circle_Square_fill(void);
void Ellipse_Coordinate_setting(uint16_t X, uint16_t Y, uint16_t ELL_A,
		uint16_t ELL_B);
void Circle_Square_Coordinate_setting(uint16_t X0, uint16_t Y0, uint16_t X1,
		uint16_t Y1, uint16_t ELL_A, uint16_t ELL_B);
void Draw_Triangle_3point_Coordinate(uint16_t P1_X, uint16_t P1_Y,
		uint16_t P2_X, uint16_t P2_Y, uint16_t P3_X, uint16_t P3_Y);
void DMA_Start_address_setting(uint32_t set_address);
void DMA_Continuous_mode_size_setting(uint32_t set_size);
void DMA_block_mode_size_setting(uint16_t BWR, uint16_t BHR, uint16_t SPWR);
void DMA_Continuous_mode(void);
void DMA_Block_mode(void);
void DMA_Start_enable(void);
void Key_Scan_Enable(void);
void Key_Scan_setting(uint8_t setx);
void Long_Key_Scan_enable(void);
void Key_Scan_Wakeup_Function_Enable(void);
void Long_Key_Timing_Adjustment(uint8_t setx);
void Floating_window_start_point(uint16_t X, uint16_t Y);
void Floating_window_size(uint16_t width_X, uint16_t high_Y);
void Floating_window_display_point(uint16_t X, uint16_t Y);
void Serial_ROM_direct_access_mode_enable(void);
void Serial_ROM_direct_access_mode_disable(void);
void DMA_Address_32bits(uint32_t set_address);
void DAM_Address_24bits(uint32_t set_address);
uint8_t DAM_Read_Data_buffer(void);
void KEYSCAN_Interrupt_Enable(void);
void KEYSCAN_Interrupt_Disable(void);
void DMA_Interrupt_Enable(void);
void DMA_Interrupt_Disable(void);
void Touch_Panel_Interrupt_Enable(void);
void Touch_Panel_Interrupt_Disable(void);
void BTE_Interrupt_Enable(void);
void BTE_Interrupt_Disable(void);
void Font_BTE_read_write_Interrupt_Enable(void);
void Font_BTE_read_write_Interrupt_Disable(void);
void Clear_keyscan_interrupt(void);
uint8_t Keyscan_Status(void);
void Clear_DMA_interrupt(void);
uint8_t DMA_Status(void);
void clear_TP_interrupt(void);
uint8_t Touch_Status(void);
void Clear_BTE_interrupt(void);
uint8_t BTE_Status(void);
void Clear_Font_BTE_read_write_Interrupt(void);
uint8_t Font_BTE_read_write_Status(void);
