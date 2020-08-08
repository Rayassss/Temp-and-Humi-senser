#ifndef _LCD_H_
#define _LCD_H_
#define RED  		0xf800
#define GREEN		0x07e0
#define BLUE 		0x001f
#define WHITE		0xffff
#define BLACK		0x0000 
#define YELLOW  0xFFE0
#define GRAY0   0xEF7D   
#define GRAY1   0x8410      	
#define GRAY2   0x4208 
sbit bl        =P4^4;//接模块BL引脚，背光可以采用IO控制或者PWM控制，也可以直接接到高电平常亮
sbit scl       =P1^1;//接模块CLK引脚,接裸屏Pin9_SCL
sbit sda       =P1^2;//接模块DIN/MOSI引脚，接裸屏Pin8_SDA
sbit rs        =P1^3;//接模块D/C引脚，接裸屏Pin7_A0
sbit cs        =P1^0;//接模块CE引脚，接裸屏Pin12_CS
sbit reset     =P1^4;//接模块RST引脚，接裸屏Pin6_RES
void delay(unsigned int time);
void  SPI_WriteData(unsigned char Data);
void  Lcd_WriteIndex(unsigned char Data);
void  Lcd_WriteData(unsigned char Data);
void  Lcd_WriteData_16(unsigned int Data);
void Reset(void);
void lcd_initial();
void Lcd_SetRegion(unsigned int x_start,unsigned int y_start,unsigned int x_end,unsigned int y_end,unsigned char mode);//mode是横竖屏模式，1为横屏，2为竖屏
void PutPixel(unsigned int x_start,unsigned int y_start,unsigned int color);
void dsp_single_colour(int color);
void Display_ASCII8X16(unsigned int x0,unsigned int y0,unsigned char *s);
void LCD_Clear(unsigned int Color);
void Display_Desc();
void go_Lcd();


#endif
