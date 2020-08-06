#include "STC8F.h"
#include "Uart.h"
void Uart1_Init()//9600bps@24.000MHz
{
	SCON = 0x50;	
	AUXR |= 0x40;		
	AUXR &= 0xFE;		
	TMOD &= 0x0F;		
	TL1 = 0x8F;	
	TH1 = 0xFD;		
	ET1 = 0;		
	TR1 = 1;		
	EA = 1;
	ES = 1;

}
void Send_string(unsigned char *a)
{
	while(*a != '!')
	{
		SBUF = *a;
		a++;
		while(TI != 1);
		TI = 0;
	}
}