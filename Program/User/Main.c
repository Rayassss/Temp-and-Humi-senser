#include "STC8F.h"
#include "DHT11.h"
#include "Delay.h"
#include "Uart.h"
#include "DS1302.h"
#include "Lcd.h"
#include "GUI.h"
#include "Led.h"
#include "Key.h"
#include "stdio.h"
#include "string.h"
void main()
{
	char i = 1;
	char Temp[10];
	Uart1_Init();
//	DS_Init();
	lcd_initial();
	dsp_single_colour(WHITE);
//	Dsp_arc_area();
//	Draw_DHT11();
//	Draw_DS1302();
	memset(Temp,'1',sizeof(Temp));
//	sprintf(Temp,"%d",123);
	Display_Num(1,1,&Temp[0],BLACK,WHITE);
	while(1);
}


void UART1_Isr() interrupt 4
{
	
	
	//---免掉点下载，波特率默认57600bps--------
	static unsigned char uart_ser = 0;
	if(TI==1)   
	{
		TI=0;
	}
	RI = 0;
	if(SBUF == 0x7f)
	{
		uart_ser++;
		if(uart_ser == 10)
		{
			uart_ser = 0;
			IAP_CONTR |= 0x60;
		}
	}
	else
	{
		uart_ser = 0;
	}   
	//-----------------------------------------
}