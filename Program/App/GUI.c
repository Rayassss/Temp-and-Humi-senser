#include "Lcd.h"
#include "GUI.h"
#include "Delay.h"
#include "DHT11.h"
#include "DS1302.h"
#include "stdio.h"
#include "string.h"
unsigned char code Table[] = "0123456789";
extern unsigned char TIME[7];
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
	unsigned char Sec[2] = {0},Min[2] = {0},Hour[2] = {0},Date[2] = {0},Mon[2] = {0},Day[2] = {0},Year[2] = {0};
	DS_ReadTime();
	Delay20ms();
	Sec[0] = Table[TIME[0]/16];
	Sec[1] = Table[TIME[0]&0x0f];
	Display_ASCII8X16(46,5,Sec);
	
	Min[0] = Table[TIME[1]/16];
	Min[1] = Table[TIME[1]&0x0f];
	Display_ASCII8X16(24,5,Min);
	Display_ASCII8X16(40,5,":");
	
	Hour[0] = Table[TIME[2]/16];
	Hour[1] = Table[TIME[2]&0x0f];
	Display_ASCII8X16(2,5,Hour);
	Display_ASCII8X16(18,5,":");
	
	Date[0] = Table[TIME[3]/16];
	Date[1] = Table[TIME[3]%16];
	Display_ASCII8X16(67,20,Date);
	
	Mon[0] = Table[TIME[4]/16];
	Mon[1] = Table[TIME[4]%16];
	Display_ASCII8X16(50,20,Mon);
	
//	Day[0] = Table[TIME[5]/16];
//	Day[1] = Table[TIME[5]%16];
//	Display_ASCII8X16(10,80,Day);
	
	Year[0] = Table[TIME[6]/16];
	Year[1] = Table[TIME[6]%16];
	Display_ASCII8X16(19,20,Year);
	Display_ASCII8X16(2,20,"20");

}