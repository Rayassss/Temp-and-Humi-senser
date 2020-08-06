#include "STC8F.h"
#include "Lcd.h"
#include "absacc.h"
#include "intrins.h"
#include "string.h"
#include "AsciiLib.h"



//uchar code Zk_ASCII8X16[];
void delay(unsigned int time)
{
 unsigned int i,j;
  for(i=0;i<time;i++)
   for(j=0;j<250;j++);
}

//向SPI总线传输一个8位数据
void  SPI_WriteData(unsigned char Data)
{
	unsigned char i=0;
	for(i=8;i>0;i--)
	{
		if(Data&0x80)	
		sda=1; //输出数据
		else sda=0;
		scl=0;
		scl=1;
		Data<<=1;
	}
}
//向液晶屏写一个8位指令
void  Lcd_WriteIndex(unsigned char Data)
{	
		cs=0;
		rs=0;
		SPI_WriteData(Data); 		
		cs=1;
}
//向液晶屏写一个8位数据
void  Lcd_WriteData(unsigned char Data)
{	
		unsigned char i=0;
		cs=0;
		rs=1;
		SPI_WriteData(Data); 	
		cs=1;
}
//向液晶屏写一个16位数据
void  Lcd_WriteData_16(unsigned int Data)
{
	unsigned char i=0;
	cs=0;
	rs=1;
	SPI_WriteData(Data>>8); 	//写入高8位数据
	SPI_WriteData(Data); 			//写入低8位数据
	cs=1;

}
//LCD复位时序
void Reset(void)
{
    reset=0;
    delay(100);
    reset=1;
    delay(100);
}
//////////////////////////////////////////////////////////////////////////////////////////////
//液晶屏初始化 for S6D02A1
void lcd_initial()
{
	Reset();//Reset before LCD Init.
		
	//LCD Init For 1.44Inch LCD Panel with ST7735R.
	Lcd_WriteIndex(0x11);//Sleep exit 
	delay (120);
		
	//ST7735R Frame Rate
	Lcd_WriteIndex(0xB1); 
	Lcd_WriteData(0x01); 
	Lcd_WriteData(0x2C); 
	Lcd_WriteData(0x2D); 

	Lcd_WriteIndex(0xB2); 
	Lcd_WriteData(0x01); 
	Lcd_WriteData(0x2C); 
	Lcd_WriteData(0x2D); 

	Lcd_WriteIndex(0xB3); 
	Lcd_WriteData(0x01); 
	Lcd_WriteData(0x2C); 
	Lcd_WriteData(0x2D); 
	Lcd_WriteData(0x01); 
	Lcd_WriteData(0x2C); 
	Lcd_WriteData(0x2D); 
	
	Lcd_WriteIndex(0xB4); //Column inversion 
	Lcd_WriteData(0x07); 
	
	//ST7735R Power Sequence
	Lcd_WriteIndex(0xC0); 
	Lcd_WriteData(0xA2); 
	Lcd_WriteData(0x02); 
	Lcd_WriteData(0x84); 
	Lcd_WriteIndex(0xC1); 
	Lcd_WriteData(0xC5); 

	Lcd_WriteIndex(0xC2); 
	Lcd_WriteData(0x0A); 
	Lcd_WriteData(0x00); 

	Lcd_WriteIndex(0xC3); 
	Lcd_WriteData(0x8A); 
	Lcd_WriteData(0x2A); 
	Lcd_WriteIndex(0xC4); 
	Lcd_WriteData(0x8A); 
	Lcd_WriteData(0xEE); 
	
	Lcd_WriteIndex(0xC5); //VCOM 
	Lcd_WriteData(0x0E); 
	
	Lcd_WriteIndex(0x36); //MX, MY, RGB mode 
	Lcd_WriteData(0xC0); 
	
	//ST7735R Gamma Sequence
	Lcd_WriteIndex(0xe0); 
	Lcd_WriteData(0x0f); 
	Lcd_WriteData(0x1a); 
	Lcd_WriteData(0x0f); 
	Lcd_WriteData(0x18); 
	Lcd_WriteData(0x2f); 
	Lcd_WriteData(0x28); 
	Lcd_WriteData(0x20); 
	Lcd_WriteData(0x22); 
	Lcd_WriteData(0x1f); 
	Lcd_WriteData(0x1b); 
	Lcd_WriteData(0x23); 
	Lcd_WriteData(0x37); 
	Lcd_WriteData(0x00); 	
	Lcd_WriteData(0x07); 
	Lcd_WriteData(0x02); 
	Lcd_WriteData(0x10); 

	Lcd_WriteIndex(0xe1); 
	Lcd_WriteData(0x0f); 
	Lcd_WriteData(0x1b); 
	Lcd_WriteData(0x0f); 
	Lcd_WriteData(0x17); 
	Lcd_WriteData(0x33); 
	Lcd_WriteData(0x2c); 
	Lcd_WriteData(0x29); 
	Lcd_WriteData(0x2e); 
	Lcd_WriteData(0x30); 
	Lcd_WriteData(0x30); 
	Lcd_WriteData(0x39); 
	Lcd_WriteData(0x3f); 
	Lcd_WriteData(0x00); 
	Lcd_WriteData(0x07); 
	Lcd_WriteData(0x03); 
	Lcd_WriteData(0x10);  
	
	Lcd_WriteIndex(0x2a);
	Lcd_WriteData(0x00);
	Lcd_WriteData(0x00+2);
	Lcd_WriteData(0x00);
	Lcd_WriteData(0x80+2);

	Lcd_WriteIndex(0x2b);
	Lcd_WriteData(0x00);
	Lcd_WriteData(0x00+3);
	Lcd_WriteData(0x00);
	Lcd_WriteData(0x80+3);
	
	Lcd_WriteIndex(0xF0); //Enable test command  
	Lcd_WriteData(0x01); 
	Lcd_WriteIndex(0xF6); //Disable ram power save mode 
	Lcd_WriteData(0x00); 
	
	Lcd_WriteIndex(0x3A); //65k mode 
	Lcd_WriteData(0x05); 
	
	
	Lcd_WriteIndex(0x29);//Display on

}
/*************************************************
函数名：LCD_Set_Region
功能：设置lcd显示区域，在此区域写点数据自动换行
入口参数：xy起点和终点
返回值：无
*************************************************/

//全屏填充函数
void Lcd_SetRegion(unsigned int x_start,unsigned int y_start,unsigned int x_end,unsigned int y_end,unsigned char mode)//mode是横竖屏模式，1为横屏，2为竖屏
{	
	if(mode == 1)
	{
	Lcd_WriteIndex(0x2a);
	Lcd_WriteData(0x02);
	Lcd_WriteData(x_start+2);
	Lcd_WriteData(0x02);
	Lcd_WriteData(x_end+2);

	Lcd_WriteIndex(0x2b);
	Lcd_WriteData(0x01);
	Lcd_WriteData(y_start+1);
	Lcd_WriteData(0x01);
	Lcd_WriteData(y_end+1);
	}
	else if(mode==2)
	{
	Lcd_WriteIndex(0x2a);
	Lcd_WriteData(0x02);
	Lcd_WriteData(x_start+2);
	Lcd_WriteData(0x02);
	Lcd_WriteData(x_end+2);

	Lcd_WriteIndex(0x2b);
	Lcd_WriteData(0x01);
	Lcd_WriteData(y_start+1);
	Lcd_WriteData(0x01);
	Lcd_WriteData(y_end+1);	
	}
		//#endif
	Lcd_WriteIndex(0x2c);
}


void PutPixel(unsigned int x_start,unsigned int y_start,unsigned int color)
{
	Lcd_SetRegion(x_start,y_start,x_start+1,y_start+1,1);
	Lcd_WriteData_16(color);
	
}



void dsp_single_colour(int color)
{
 	unsigned char i,j;
	Lcd_SetRegion(0,0,128-1,160-1,1);
 	for (i=0;i<160;i++)
    	for (j=0;j<128;j++)
        	Lcd_WriteData_16(color);
}
//显示一个英文字符
void Display_ASCII8X16(unsigned int x0,unsigned int y0,unsigned char *s)
{
	int i,j,k,x,y,xx;
	
	unsigned char qm;
	
	long int ulOffset;
	
	char  ywbuf[32],temp[2];

	for(i = 0; i<strlen((char*)s);i++)
	{
		if(((unsigned char)(*(s+i))) >= 161)
		{
			temp[0] = *(s+i);
			temp[1] = '\0';
			return;
		}
		
		else
		{
			qm = *(s+i);

			ulOffset = (long int)(qm) * 16;
			
      for (j = 0; j < 16; j ++)
      {
				ywbuf[j]=Zk_ASCII8X16[ulOffset+j];
      }
             
      for(y = 0;y < 16;y++)
      {
	        for(x=0;x<8;x++) 
	        {
             k=x % 8;
                	
				  	if(ywbuf[y]&(0x80 >> k))
				   	{
				  		xx=x0+x+i*8;
				    	PutPixel(xx,y+y0,RED);
				  	}
							
			   	}
      }

		}
	}     	
}
void LCD_Clear(unsigned int Color)
{
	unsigned char i,j;
	Lcd_SetRegion(0,0,127,159,1);
	for (i=0;i<160;i++)
	{
    	for (j=0;j<128;j++)
		{
        	Lcd_WriteData_16(Color);
		}
	}
}
void Display_Desc()
{ 
    Display_ASCII8X16(10,10,"Welcome");
    Display_ASCII8X16(10,26,"Zhongjy");
    Display_ASCII8X16(10,42,"Dots:128*160");
    Display_ASCII8X16(10,58,"IC: ST7735");
    Display_ASCII8X16(10,74,"VA:6 o'clock");
    Display_ASCII8X16(10,90,"2015.10.26");
}



