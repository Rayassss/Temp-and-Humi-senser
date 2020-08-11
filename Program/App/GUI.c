#include "Lcd.h"
#include "Font.h"
#include "GUI.h"
void General_Display_Font(unsigned char x, unsigned int  y, unsigned int dcolor,unsigned int bgcolor,
	unsigned char *str,unsigned char Num,unsigned char Length,unsigned char Height)
{
	unsigned char *Temp_Str;
	unsigned char i,j,k,m;									//������ʱ����
	Num++;
	Temp_Str = str;
	for (k=0;k<Num;k++) 		  								//64��ʾ�Խ��ֿ��еĸ�����ѭ����ѯ����	���������ȷ�� ȡ���ڴ���ĺ��ָ���	  
	{
		Address_set((k*Length) + x,y,(k*Length) + x + Length - 1, y + Height - 1);	 // ����Ϊ������ʾ
		for(i=0;i<((Length * Height) / 8);i++)
		{								    //32���ֽ� ÿ���ֽڶ�Ҫһ����һ���㴦�� �����Ǵ�����32X8��
			str = Temp_Str;
			str += k * ((Length * Height) / 8) + i;
			m = *str;
			for(j=0;j<8;j++) 									//��ʾһ���ֽ�  һ���ֽ�8λ Ҳ����8����
			{
					if((m&0x80)==0x80) 							//�ж��Ƿ���Ҫд��� 	 ����� ��������ɫ
						Lcd_Write_Data(dcolor);				
					else 											//������� Ϊ����ɫ  ����ɫ
						Lcd_Write_Data(bgcolor);
					m <<= 1;										    //����һλ  �ж���һ��
			}
		}
	}
}
//����
//color�Ǳ�����ɫ��
//˵����ʹ�ñ�����ɫ���TFTģ����Ļ��ȫ����ʾ���ݡ�
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
//����
//(x��y)�ǵ������
//color �ǵ����ɫ��
//˵������ָ������ɫ��ָ��������λ���ϻ���һ���㡣
void Draw_Frame()
{
	GUI_box(0,0,159,2,Black);
	GUI_box(0,0,2,127,Black);
	GUI_box(0,125,159,127,Black);
	GUI_box(157,0,159,127,Black);//��ʾ�߿�
}	
void GUI_Point(unsigned char x, unsigned int y, unsigned int color)
{  
	Address_set(x,y,x,y);
	Lcd_Write_Data(color);
}
//��8��(Bresenham�㷨)		  
//(rx,ry,a,b):����
//color:��ɫ
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
//��ָ��λ�û�һ��ָ����С��Բ
//(rx,ry):Բ��
//r    :�뾶
//color:��ɫ
//mode :0,�����;1,���
void GUI_arc(unsigned int rx,unsigned int ry,unsigned int r,unsigned int color,unsigned char mode)
{
	int a,b,c;
	int di;	  
	a=0;b=r;	  
	di=3-(r<<1);	//�ж��¸���λ�õı�־
	while(a<=b)
	{
		if(mode)
		for(c=a;c<=b;c++)
		gui_circle8(rx,ry,a,c,color);//��ʵ��Բ
 		else gui_circle8(rx,ry,a,b,color);			//������Բ
		a++;
		//ʹ��Bresenham�㷨��Բ     
		if(di<0)di +=4*a+6;	  
		else
		{
			di+=10+4*(a-b);   
			b--;
		} 							  
	}
}
//����RPG����ʱ���˵�С���⣬��Ҫ���������������ɫ��ת��
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
//��ʵ�ľ���
//(sx,sy)���ϽǶ�������, 
//(ex,ey)���½Ƕ�������, color��ɫ
//����: ��
//˵������ָ��λ���ϻ���ʵ�ľ��Ρ�
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
//��ʾӢ�Ļ������ַ�
//����֧�� �ַ�������ͺ�����ʾ ��Ҫ���ɨ�跽ʽ��
//x  y  Ҫ��ʾ�ַ��ĳ�ʼ����
//value ��ʾ�ַ�����
//dcolor ��ʾ���ַ���ɫ  bgcolor��ʾ�ַ��ı�����ɫ
//mode   0 �ַ�������ʾ  1 �ַ�������ʾ
void GUI_sprintf_char(unsigned char x,unsigned int y,unsigned char value,unsigned int dcolor,unsigned int bgcolor,unsigned char mode)	
{  
	unsigned char i,j;
	unsigned char *temp=Asc_5_8_;    //temp��*temp�ĵ�ַ  ����temp����zifu���׵�ַ       
	temp+=(value-32)*8;   //ȷ��Ҫ��ʾ��ֵ
				           //��ascii��  ǰ32��asciiû�д���zifu���� ����Ҫ��32
	                       //ÿ���ַ���16���ֽ���ʾ �����ڳ���16  ���Ƕ�Ӧ����ʾλ���׵�ַ
	  if(mode==0)Address_set(x,y,x+4,y+7);    //��������		   
	  if(mode==1)Address_set(x,y,x+4,y+7); //��������   		    
		for(j=0;j<8;j++)
		{
			for(i=0;i<5;i++)		    //�Ⱥ�ɨ
			{
			 	if((*temp&(1<<(7-i)))!=0)		   //��1 ���� Ȼ���Ӧλ�������� 				
				  Lcd_Write_Data(dcolor);		   //��ʾ�ַ���ɫ
				 
				else				
				  Lcd_Write_Data(bgcolor);		   //��ʾ������ɫ		
			}
			temp++;								   //��һ�ֽ�
		}
}
//��ʾ�����ַ��� ������ʾ
//x1 y1 ��ʾ�ĳ�ʼλ��
//*str Ҫ��ʾ������
//dcolor ��ʾ�ַ�����ɫ
//bgcolor ��ʾ�ַ��ı�����ɫ  
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
//��ʾ��ͬ���ֺţ�Font_Sizeѡ�������ֺţ�FONT_HUGE�Ǵ��24*62��FONT_MEDIUM���к�16*32
//void Display_Num(unsigned char Font_Size,unsigned char x,unsigned int  y,unsigned char *str,unsigned int dcolor,unsigned int bgcolor)
//{
//	unsigned char Temp_Count = 0;
//	while(*str)
//	{
//		unsigned int i,Num;
//		unsigned char j,m;									//������ʱ����
//		Num = *str;
//		if(Num == '.')
//			Num = 10;
//		else
//			Num = Num - 48;  //ASCIIת����
////		if(Font_Size == FONT_HUGE)
////		{
////			Address_set(x+Temp_Count*23,y,x + Temp_Count*23 + 23, y + 62 - 1);
////			for(i=0;i<186;i++)
////			{								    //32���ֽ� ÿ���ֽڶ�Ҫһ����һ���㴦�� �����Ǵ�����32X8��
////				m = Hugenumber_24_62_[Num * 186 + i];							//��ȡ��Ӧ�ֽ�����
////				for(j=0;j<8;j++) 									//��ʾһ���ֽ�  һ���ֽ�8λ Ҳ����8����
////				{
////					if((m&0x80)==0x80) 							//�ж��Ƿ���Ҫд��� 	 ����� ��������ɫ
////						Lcd_Write_Data(dcolor);				
////					else									//������� Ϊ����ɫ  ����ɫ
////						Lcd_Write_Data(bgcolor);
////					m<<=1;										    //����һλ  �ж���һ��
////				}
////			}
////		}
//	  if(Font_Size == FONT_MEDIUM)
//		{
//			Address_set(x+Temp_Count*15,y,x + Temp_Count*15 + 15, y + 32 - 1);	 // ����Ϊ������ʾ
//			for(i=0;i<64;i++)
//			{								    //32���ֽ� ÿ���ֽڶ�Ҫһ����һ���㴦�� �����Ǵ�����32X8��
//				m = Number_16_32_[Num * 64 + i];							//��ȡ��Ӧ�ֽ�����
//				for(j=0;j<8;j++) 									//��ʾһ���ֽ�  һ���ֽ�8λ Ҳ����8����
//				{
//					if((m&0x80)==0x80) 							//�ж��Ƿ���Ҫд��� 	 ����� ��������ɫ
//						Lcd_Write_Data(dcolor);			
//					else									//������� Ϊ����ɫ  ����ɫ
//						Lcd_Write_Data(bgcolor);
//					m<<=1;										    //����һλ  �ж���һ��
//				}
//			}
//		}
//		Temp_Count++;
//		str++;
//	}
//}
//8*16�ĺ����ֺ�
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
//8*16��ASCII
void GUI_sprintf_Asc_8_16(unsigned char x,unsigned int y,unsigned char value,unsigned int dcolor,unsigned int bgcolor,unsigned char mode)	
{  
	unsigned char i,j;
	unsigned char *temp=Asc_8_16_;    //temp��*temp�ĵ�ַ  ����temp����zifu���׵�ַ       
	temp+=(value-32)*16;   //ȷ��Ҫ��ʾ��ֵ
				           //��ascii��  ǰ32��asciiû�д���zifu���� ����Ҫ��32
	                       //ÿ���ַ���16���ֽ���ʾ �����ڳ���16  ���Ƕ�Ӧ����ʾλ���׵�ַ
	  if(mode==0)Address_set(x,y,x+7,y+15);    //��������		   
	  if(mode==1)Address_set(x,y,x+7,y+15); //��������   		    
		for(j=0;j<16;j++)
		{
			for(i=0;i<8;i++)		    //�Ⱥ�ɨ
			{ 		     
			 	if((*temp&(1<<(7-i)))!=0)		   //��1 ���� Ȼ���Ӧλ�������� 				
				  Lcd_Write_Data(dcolor);		   //��ʾ�ַ���ɫ
				 
				else				
				  Lcd_Write_Data(bgcolor);		   //��ʾ������ɫ		
			}
			temp++;								   //��һ�ֽ�
		}
}
