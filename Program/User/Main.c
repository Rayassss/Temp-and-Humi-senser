#include "STC8F.h"
#include "DHT11.h"
#include "Delay.h"
#include "Uart.h"
#include "DS1302.h"
#include "Lcd.h"
//unsigned char str[5];
//extern unsigned char RH_data_H,RH_data_L,T_data_H,T_data_L,checkdata;
extern unsigned char TIME[7];
void main()
{
//	unsigned char i;
//	while(1)
//	{
//		Delay2000ms();
//		DHT11_init();
//		Delay100us();
//	  str[0]=RH_data_H;
//	  str[1]=RH_data_L;
//	  str[2]=T_data_H;
//	  str[3]=T_data_L;
//	  str[4]=checkdata;
//	  SendData(str) ;  		
//	}
//	DS_Init();

//	while(1)
//	{
//		Delay2000ms();
//		DS_ReadTime();
//		ES = 0;
//		for(i=0; i<7; i++)
//		{
//			SBUF = TIME[i];
//			while(!TI);
//			TI = 0;
//		}
//		ES = 1;
//		Delay2000ms();

//	}
		Uart1_Init();
		lcd_initial();
		bl=1;
		while(1)
		{
			dsp_single_colour(RED);//红色
			dsp_single_colour(GREEN);//绿色	
			dsp_single_colour(BLUE);//蓝色
			Delayms(500);
			dsp_single_colour(WHITE);//白色
			Display_Desc();         //版本
			Delayms(500);
    }
		
		LCD_Clear(WHITE);
		Display_Desc();
}

void UART1_Isr() interrupt 4
{
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
}