#include "Lcd.h"
#include "Font.h"
#include "GUI.h"
#include "Delay.h"
#include "DHT11.h"
unsigned char code Table[] = "0123456789";
extern unsigned char RH_data_H,RH_data_L,T_data_H,T_data_L,checkdata;
void Draw_DHT11()
{
	unsigned char RH[2],T[2];
		Delay2000ms();
		DHT11_init();
		Delay100us();
//	  str[0]=RH_data_H;
//	  str[1]=RH_data_L;
//	  str[2]=T_data_H;
//	  str[3]=T_data_L;
//	  str[4]=checkdata;
//	  SendData(str) ;  
		dsp_single_colour(WHITE);
		RH[0] = Table[RH_data_H/10];
		RH[1] = Table[RH_data_H%10];
		Display_ASCII8X16(10,10,RH);
		T[0] = Table[T_data_H/10];
		T[1] = Table[T_data_H%10];
		Display_ASCII8X16(10,20,T);
}
void Draw_DS1302()
{
	
}