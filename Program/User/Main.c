#include "STC8F.h"
#include "DHT11.h"
#include "Delay.h"
#include "Uart.h"
#include "DS1302.h"
#include "Lcd.h"
#include "GUI.h"
#include "Key.h"

void main()
{
	Uart1_Init();
	DS_Init();
	bl = 0;
	Delay2000ms()	;
	bl = 1;
	lcd_initial();
	dsp_single_colour(WHITE);
	Draw_DHT11();
	Draw_DS1302();
	while(1);
}


void UART1_Isr() interrupt 4
{
	//---��������أ�������Ĭ��57600bps--------
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