#include "STC8F.h"
#include "DHT11.h"
#include "Delay.h"
#include "Uart.h"
#include "DS1302.h"
#include "Lcd.h"
#include "GUI.h"
#include "Led.h"
#include "Key.h"
#include "intrins.h"
unsigned char TIME[7] = {0x00,0x30,0x12,0x15,0x06,0x05,0x20};//sec,min,hour,date,month,day,year
extern unsigned char READTIME[7];
unsigned char i = 0;
void main()
{
	Uart1_Init();
	DS_ReadTime();
	if(((READTIME[0] & 0x80) >> 7) == 1)
	{
		DS_Init(TIME);
	}
	lcd_initial();
//	LCD_Clear(WHITE);
//	Delay2000ms();
//	Draw_DHT11();
//	LCD_Clear(WHITE);
//	Draw_DHT11();
//	Draw_DS1302();
	Timer5Init();
	while(1)
	{
		Keyinit();
	}
	
}
void UART1_Isr() interrupt 4
{
	//---免掉点下载，最低波特率默认57600bps--------
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
void TM2_Isr() interrupt 12 
{
	AUXINTIF &= ~T2IF;
	i++;
	if(i == 40)
	{
		LCD_Clear(WHITE);
		Draw_DS1302();
		Draw_DHT11();
		i = 0;
	}
}