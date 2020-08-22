#include "Lcd.h"
#include "GUI.h"
#include "Delay.h"
#include "DHT11.h"
#include "DS1302.h"
#include "stdio.h"
#include "string.h"
unsigned char code Table[] = "0123456789";
extern unsigned char READTIME[7];
extern unsigned char RH_data_H,RH_data_L,T_data_H,T_data_L,checkdata;
void Draw_DHT11()
{
		unsigned char RH[2] = {0},T[2]= {0};
		RH_data_H = 0,RH_data_L = 0,T_data_H = 0,T_data_L = 0,checkdata = 0;
//		unsigned char str[5];
			DHT11_init();
			Delay2000ms();
//	  str[0]=RH_data_H;
//	  str[1]=RH_data_L;
//	  str[2]=T_data_H;
//	  str[3]=T_data_L;
//	  str[4]=checkdata;
//	  SendData(str) ;  
		RH[0] = '0' + (RH_data_H/10);
		RH[1] = '0' + (RH_data_H%10);
		Display_ASCII8X16(10,50,"%RH=");
 		Display_ASCII8X16(42,50,RH);
		T[0] = '0' + (T_data_H/10);
		T[1] = '0' + (T_data_H%10);
		Display_ASCII8X16(10,70,"Tmp=");
		Display_ASCII8X16(42,70,T);
}
void Draw_DS1302()
{
	unsigned char Temp[2] = {0x00};
	Delay2000ms();
	DS_ReadTime();
	Delay20ms();
	Temp[0] = Table[READTIME[2]/16];//显示时间
	Temp[1] = Table[READTIME[2]&0x0f];
	Display_ASCII8X16(1,2,Temp);
	Display_ASCII8X16(34,14,":");
	Temp[0] = 0x00;
	Temp[1] = 0x00;
	
	Temp[0] = Table[READTIME[1]/16];//显示分钟
	Temp[1] = Table[READTIME[1]&0x0f];
	Display_ASCII8X16(50,2,Temp);
	Display_ASCII8X16(80,14,":");
	Temp[0] = 0x00;
	Temp[1] = 0x00;	
	
	Temp[0] = Table[READTIME[0]/16];
	Temp[1] = Table[READTIME[0]&0x0f];
	Display_ASCII8X16(102,2,Temp);
	Temp[0] = 0x00;
	Temp[1] = 0x00;
	
	Temp[0] = Table[READTIME[6]/16];
	Temp[1] = Table[READTIME[6]%16];
	Display_ASCII8X16(1,40,"20");
	Display_ASCII8X16(18,40,Temp);
	Display_ASCII8X16(38,40,"/");
	Temp[0] = 0x00;
	Temp[1] = 0x00;
	
	Temp[0] = Table[READTIME[4]/16];
	Temp[1] = Table[READTIME[4]%16];
	Display_ASCII8X16(50,40,Temp);
	Display_ASCII8X16(74,40,"/");
	Temp[0] = 0x00;
	Temp[1] = 0x00;
	
	Temp[0] = Table[READTIME[3]/16];
	Temp[1] = Table[READTIME[3]%16];
	Display_ASCII8X16(90,40,Temp);
	Temp[0] = 0x00;
	Temp[1] = 0x00;
	
}