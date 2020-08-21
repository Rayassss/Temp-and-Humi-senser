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
#define HOUR 1
#define MIN 2
#define SEC 3
#define YEAR 4
#define MONTH 5
#define DATE 6
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
void Lcd_showchar(unsigned char x,unsigned char y,int bgcolor,int Fontcolor);
void Display_Num(unsigned char x,unsigned char y,unsigned char *str);
void Lcd_arc_clear(unsigned char index);
#endif
