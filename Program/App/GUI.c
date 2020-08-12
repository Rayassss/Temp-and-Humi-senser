#include "Lcd.h"
#include "Font.h"
#include "GUI.h"
#include "Delay.h"
#include "DHT11.h"
#include "DS1302.h"
unsigned char code Table[] = "0123456789";
extern unsigned char TIME[7];
extern unsigned char RH_data_H,RH_data_L,T_data_H,T_data_L,checkdata;
void Draw_DHT11()
{
	unsigned char RH[2],T[2],str[5];
		Delay2000ms();
		DHT11_init();
		Delay100us();
	  str[0]=RH_data_H;
	  str[1]=RH_data_L;
	  str[2]=T_data_H;
	  str[3]=T_data_L;
	  str[4]=checkdata;
//	  SendData(str) ;  
//		RH[0] = Table[RH_data_H/10];
//		RH[1] = Table[RH_data_H%10];
//		Display_ASCII8X16(10,10,RH);
//		T[0] = Table[T_data_H/10];
//		T[1] = Table[T_data_H%10];
		Display_ASCII8X16(10,30,str);
}
void Draw_DS1302()
{
	unsigned char Sec[2],Min[2],Hour[2],Date[2],Mon[2],Day[2],Year[2];
	DS_ReadTime();
	Delay20ms();
	Sec[0] = Table[TIME[0]/10];
	Sec[1] = Table[TIME[1]%10];
	Display_ASCII8X16(10,30,Sec);
//	Min[0] = Table[TIME[0]/10];
//	Min[1] = Table[TIME[1]%10];
//	Display_ASCII8X16(10,40,Min);
//	Hour[0] = Table[TIME[0]/10];
//	Hour[1] = Table[TIME[1]%10];
//	Display_ASCII8X16(10,50,Hour);
//	Date[0] = Table[TIME[0]/10];
//	Date[1] = Table[TIME[1]%10];
//	Display_ASCII8X16(10,60,Date);
//	Mon[0] = Table[TIME[0]/10];
//	Mon[1] = Table[TIME[1]%10];
//	Display_ASCII8X16(10,70,Mon);
//	Day[0] = Table[TIME[0]/10];
//	Day[1] = Table[TIME[1]%10];
//	Display_ASCII8X16(10,80,Day);
//	Year[0] = Table[TIME[0]/10];
//	Year[1] = Table[TIME[1]%10];
//	Display_ASCII8X16(10,90,Year);
}