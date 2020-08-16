#include "STC8F.h"
#include "Lcd.h"
#include "absacc.h"
#include "intrins.h"
#include "string.h"
#include "AsciiLib.h"
#include "Delay.h"
#include "Font.h"
//sbit bl        =P4^4;//接模块BL引脚，背光可以采用IO控制或者PWM控制，也可以直接接到高电平常亮
sbit scl       =P1^1;//接模块CLK引脚,接裸屏Pin9_SCL
sbit sda       =P1^2;//接模块DIN/MOSI引脚，接裸屏Pin8_SDA
sbit rs        =P1^3;//接模块D/C引脚，接裸屏Pin7_A0
sbit cs        =P1^0;//接模块CE引脚，接裸屏Pin12_CS
sbit reset     =P1^4;//接模块RST引脚，接裸屏Pin6_RES
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
	if(mode == 2)
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
	else if(mode == 1)
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
	Lcd_SetRegion(x_start,y_start,x_start+1,y_start+1,2);
	Lcd_WriteData_16(color);
}
void dsp_single_colour(int color)
{
 	unsigned char i,j;
	Lcd_SetRegion(0,0,128-1,160-1,2);
 	for (i=0;i<160;i++)
    	for (j=0;j<128;j++)
        	Lcd_WriteData_16(color);
}
void Dsp_arc_area()
{
	unsigned char i,j;
	Lcd_SetRegion(0,0,80,18,2);
	for (i=0;i<18;i++)
    	for (j=0;j<80;j++)
        	Lcd_WriteData_16(WHITE);
}
//显示一个英文字符
void Display_ASCII8X16(unsigned int x0,unsigned int y0,unsigned char *s)
{
	int i,j,k,x,y,xx;
	unsigned char qm;
	long int ulOffset;
	char  ywbuf[32],temp[2];
	for(i = 0; i<strlen((unsigned char*)s);i++)
	{
		if(((unsigned char)(*(s+i))) >= 161)
		{
			temp[0] = *(s+i);
			temp[1] = '\0';
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
	Lcd_SetRegion(0,0,127,159,2);
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
    Display_ASCII8X16(10,10,"Dreamix is so so beautiful");
}
void go_Lcd()
{
		lcd_initial();
		bl=1;
		dsp_single_colour(WHITE);//白色
		Display_Desc();         //版本
}
//void Lcd_showchar(unsigned char x,unsigned char y,int bgcolor,int Fontcolor)
//{
//	int i = 0,j = 0;
//	unsigned char Temp = 0;
//	Lcd_SetRegion(x,y,x + 79,y + 127,1);
//	for(i=0; i<80*16; i++)
//	{
//		Temp = Font_A[i];
//		for(j=0; j<8; j++)
//		{
//			if(Temp & 0x80)
//			{
//				Lcd_WriteData_16(Fontcolor);
//			}
//			else
//			{
//				Lcd_WriteData_16(bgcolor);
//			}
//			Temp <<= 1;
//		}
//	}
//}
//void GUI_sprintf_Asc_8_16(unsigned char x,unsigned int y,unsigned char value,unsigned int dcolor,unsigned int bgcolor,unsigned char mode)	
//{  
//	unsigned char i,j;
//	unsigned char *temp=Asc_8_16_;    //temp是*temp的地址  这里temp就是zifu的首地址       
//	temp+=(value-32)*16;   //确定要显示的值
//				           //用ascii表  前32个ascii没有存入zifu库里 所以要减32
//	                       //每个字符用16个字节显示 所以在乘以16  就是对应的显示位的首地址
//	  if(mode==0)Lcd_SetRegion(x,y,x+7,y+15,1);    //设置区域		   
//	  if(mode==1)Lcd_SetRegion(x,y,x+7,y+15,1); //设置区域   		    
//		for(j=0;j<16;j++)
//		{
//			for(i=0;i<8;i++)		    //先横扫
//			{ 		     
//			 	if((*temp&(1<<(7-i)))!=0)		   //将1 左移 然后对应位进行相与 				
//				  Lcd_Write_Data(dcolor);		   //显示字符颜色
//				 
//				else				
//				  Lcd_Write_Data(bgcolor);		   //显示背景颜色		
//			}
//			temp++;								   //下一字节
//		}
//}
