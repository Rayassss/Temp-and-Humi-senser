#include "Lcd.h"
#include "Font.h"
#include "GUI.h"
void General_Display_Font(unsigned char x, unsigned int  y, unsigned int dcolor,unsigned int bgcolor,
	unsigned char *str,unsigned char Num,unsigned char Length,unsigned char Height)
{
	unsigned char *Temp_Str;
	unsigned char i,j,k,m;									//定义临时变量
	Num++;
	Temp_Str = str;
	for (k=0;k<Num;k++) 		  								//64表示自建字库中的个数，循环查询内码	这个数并不确定 取决于存如的汉字个数	  
	{
		Address_set((k*Length) + x,y,(k*Length) + x + Length - 1, y + Height - 1);	 // 设置为纵向显示
		for(i=0;i<((Length * Height) / 8);i++)
		{								    //32个字节 每个字节都要一个点一个点处理 所以是处理了32X8次
			str = Temp_Str;
			str += k * ((Length * Height) / 8) + i;
			m = *str;
			for(j=0;j<8;j++) 									//显示一个字节  一个字节8位 也就是8个点
			{
					if((m&0x80)==0x80) 							//判断是否是要写入点 	 如果是 给字体颜色
						Lcd_Write_Data(dcolor);				
					else 											//如果不是 为背景色  给颜色
						Lcd_Write_Data(bgcolor);
					m <<= 1;										    //左移一位  判断下一点
			}
		}
	}
}
//清屏
//color是背景颜色。
//说明：使用背景颜色清除TFT模块屏幕的全部显示内容。
void GUI_Clear(unsigned int color)
{
	 unsigned int i;
	 unsigned int j;
	 Address_set(0,0,159,127);
   for(i=0;i<128;i++)
	 {
	    for (j=0;j<160;j++)
	   	{
        	 Lcd_Write_Data(color);
	    }
	  }
}
//画点
//(x，y)是点的坐标
//color 是点的颜色。
//说明：用指定的颜色在指定的坐标位置上画出一个点。
void Draw_Frame()
{
	GUI_box(0,0,159,2,Black);
	GUI_box(0,0,2,127,Black);
	GUI_box(0,125,159,127,Black);
	GUI_box(157,0,159,127,Black);//显示边框
}	
void GUI_Point(unsigned char x, unsigned int y, unsigned int color)
{  
	Address_set(x,y,x,y);
	Lcd_Write_Data(color);
}
//画8点(Bresenham算法)		  
//(rx,ry,a,b):参数
//color:颜色
void gui_circle8(unsigned int rx,unsigned int ry,int a,int b,unsigned int color)
{
	GUI_Point(rx+a,ry-b,color);              
	GUI_Point(rx+b,ry-a,color);                       
	GUI_Point(rx+b,ry+a,color);                           
	GUI_Point(rx+a,ry+b,color);             
	GUI_Point(rx-a,ry+b,color);                  
	GUI_Point(rx-b,ry+a,color);               
	GUI_Point(rx-b,ry-a,color);                      
	GUI_Point(rx-a,ry-b,color);                  
}
//在指定位置画一个指定大小的圆
//(rx,ry):圆心
//r    :半径
//color:颜色
//mode :0,不填充;1,填充
void GUI_arc(unsigned int rx,unsigned int ry,unsigned int r,unsigned int color,unsigned char mode)
{
	int a,b,c;
	int di;	  
	a=0;b=r;	  
	di=3-(r<<1);	//判断下个点位置的标志
	while(a<=b)
	{
		if(mode)
		for(c=a;c<=b;c++)
		gui_circle8(rx,ry,a,c,color);//画实心圆
 		else gui_circle8(rx,ry,a,b,color);			//画空心圆
		a++;
		//使用Bresenham算法画圆     
		if(di<0)di +=4*a+6;	  
		else
		{
			di+=10+4*(a-b);   
			b--;
		} 							  
	}
}
//由于RPG解析时出了点小问题，需要用这个函数进行颜色的转换
unsigned int TranColor(unsigned int color)
{
	unsigned int Result;
	unsigned int Temp_Red,Temp_Blue,Temp_Green;
	Temp_Red = color >> 11;
	Temp_Blue = color & 0x001f;
	Temp_Green = (color & 0x07ff) >> 5;
	Result = Temp_Red;
	Result |= Temp_Green << 5;
	Result |= Temp_Blue << 11;
	return Result;
}
//画实心矩形
//(sx,sy)左上角顶点坐标, 
//(ex,ey)右下角顶点坐标, color颜色
//返回: 无
//说明：在指定位置上画出实心矩形。
void GUI_box(unsigned char sx,unsigned int sy,unsigned char ex,unsigned int ey,unsigned int color)
{ 
	unsigned int temp,temp1,m,n;   
	Address_set(sx,sy,ex,ey); 
  n=ex-sx+1;
	m=ey-sy+1;
	for(temp=0;temp<n;temp++)
	{	 	
		for(temp1=0;temp1<m;temp1++)
	 	{	
			Lcd_Write_Data(color);
		}
	}
}
//显示英文或数字字符
//函数支持 字符的纵向和横向显示 （要配合扫描方式）
//x  y  要显示字符的初始坐标
//value 显示字符数据
//dcolor 显示的字符颜色  bgcolor显示字符的背景颜色
//mode   0 字符纵向显示  1 字符横向显示
void GUI_sprintf_char(unsigned char x,unsigned int y,unsigned char value,unsigned int dcolor,unsigned int bgcolor,unsigned char mode)	
{  
	unsigned char i,j;
	unsigned char *temp=Asc_5_8_;    //temp是*temp的地址  这里temp就是zifu的首地址       
	temp+=(value-32)*8;   //确定要显示的值
				           //用ascii表  前32个ascii没有存入zifu库里 所以要减32
	                       //每个字符用16个字节显示 所以在乘以16  就是对应的显示位的首地址
	  if(mode==0)Address_set(x,y,x+4,y+7);    //设置区域		   
	  if(mode==1)Address_set(x,y,x+4,y+7); //设置区域   		    
		for(j=0;j<8;j++)
		{
			for(i=0;i<5;i++)		    //先横扫
			{
			 	if((*temp&(1<<(7-i)))!=0)		   //将1 左移 然后对应位进行相与 				
				  Lcd_Write_Data(dcolor);		   //显示字符颜色
				 
				else				
				  Lcd_Write_Data(bgcolor);		   //显示背景颜色		
			}
			temp++;								   //下一字节
		}
}
//显示汉字字符串 纵向显示
//x1 y1 显示的初始位置
//*str 要显示的数据
//dcolor 显示字符的颜色
//bgcolor 显示字符的背景颜色  
void GUI_sprintf_hzstr16x(unsigned char x1,unsigned int y1,unsigned char *str,unsigned int dcolor,unsigned int bgcolor)	  
{  
	unsigned char l=0;
	while(*str)
	{
			GUI_box(x1+l*6-1,y1,x1+l*6-1,y1+7,bgcolor);
			GUI_sprintf_char(x1+l*6,y1,*str,dcolor,bgcolor,0);
			l+=1;
			str++;
	}
}
//显示不同的字号，Font_Size选择两种字号，FONT_HUGE是大号24*62，FONT_MEDIUM是中号16*32
//void Display_Num(unsigned char Font_Size,unsigned char x,unsigned int  y,unsigned char *str,unsigned int dcolor,unsigned int bgcolor)
//{
//	unsigned char Temp_Count = 0;
//	while(*str)
//	{
//		unsigned int i,Num;
//		unsigned char j,m;									//定义临时变量
//		Num = *str;
//		if(Num == '.')
//			Num = 10;
//		else
//			Num = Num - 48;  //ASCII转数字
////		if(Font_Size == FONT_HUGE)
////		{
////			Address_set(x+Temp_Count*23,y,x + Temp_Count*23 + 23, y + 62 - 1);
////			for(i=0;i<186;i++)
////			{								    //32个字节 每个字节都要一个点一个点处理 所以是处理了32X8次
////				m = Hugenumber_24_62_[Num * 186 + i];							//读取对应字节数据
////				for(j=0;j<8;j++) 									//显示一个字节  一个字节8位 也就是8个点
////				{
////					if((m&0x80)==0x80) 							//判断是否是要写入点 	 如果是 给字体颜色
////						Lcd_Write_Data(dcolor);				
////					else									//如果不是 为背景色  给颜色
////						Lcd_Write_Data(bgcolor);
////					m<<=1;										    //左移一位  判断下一点
////				}
////			}
////		}
//	  if(Font_Size == FONT_MEDIUM)
//		{
//			Address_set(x+Temp_Count*15,y,x + Temp_Count*15 + 15, y + 32 - 1);	 // 设置为纵向显示
//			for(i=0;i<64;i++)
//			{								    //32个字节 每个字节都要一个点一个点处理 所以是处理了32X8次
//				m = Number_16_32_[Num * 64 + i];							//读取对应字节数据
//				for(j=0;j<8;j++) 									//显示一个字节  一个字节8位 也就是8个点
//				{
//					if((m&0x80)==0x80) 							//判断是否是要写入点 	 如果是 给字体颜色
//						Lcd_Write_Data(dcolor);			
//					else									//如果不是 为背景色  给颜色
//						Lcd_Write_Data(bgcolor);
//					m<<=1;										    //左移一位  判断下一点
//				}
//			}
//		}
//		Temp_Count++;
//		str++;
//	}
//}
//8*16的汉字字号
void GUI_sprintf_hzstr8x(unsigned char x1,unsigned int y1,unsigned char *str,unsigned int dcolor,unsigned int bgcolor)	  
{  
	unsigned char l=0;
	while(*str)
	{
			GUI_sprintf_Asc_8_16(x1+l*8,y1,*str,dcolor,bgcolor,0);
			l+=1;
			str++;
	}	
}
//8*16的ASCII
void GUI_sprintf_Asc_8_16(unsigned char x,unsigned int y,unsigned char value,unsigned int dcolor,unsigned int bgcolor,unsigned char mode)	
{  
	unsigned char i,j;
	unsigned char *temp=Asc_8_16_;    //temp是*temp的地址  这里temp就是zifu的首地址       
	temp+=(value-32)*16;   //确定要显示的值
				           //用ascii表  前32个ascii没有存入zifu库里 所以要减32
	                       //每个字符用16个字节显示 所以在乘以16  就是对应的显示位的首地址
	  if(mode==0)Address_set(x,y,x+7,y+15);    //设置区域		   
	  if(mode==1)Address_set(x,y,x+7,y+15); //设置区域   		    
		for(j=0;j<16;j++)
		{
			for(i=0;i<8;i++)		    //先横扫
			{ 		     
			 	if((*temp&(1<<(7-i)))!=0)		   //将1 左移 然后对应位进行相与 				
				  Lcd_Write_Data(dcolor);		   //显示字符颜色
				 
				else				
				  Lcd_Write_Data(bgcolor);		   //显示背景颜色		
			}
			temp++;								   //下一字节
		}
}
