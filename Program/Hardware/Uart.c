#include "STC8F.h"
#include "Uart.h"
void Uart1_Init()//57600bps@24.000MHz
{
	PCON |= 0x80;		//使能波特率倍速位SMOD
	SCON = 0x50;		//8位数据,可变波特率
	AUXR |= 0x40;		//定时器1时钟为Fosc,即1T
	AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
	TMOD &= 0x0F;		//清除定时器1模式位
	TMOD |= 0x20;		//设定定时器1为8位自动重装方式
	TL1 = 0xE6;		//设定定时初值
	TH1 = 0xE6;		//设定定时器重装值
	ET1 = 0;		//禁止定时器1中断
	TR1 = 1;		//启动定时器1
	EA = 1;
	ES = 1;
}
void Timer5Init()		//25毫秒@24.000MHz
{
	AUXR &= 0xFB;		//定时器时钟12T模式
	T2L = 0xB0;		//设置定时初值
	T2H = 0x3C;		//设置定时初值
	AUXR |= 0x10;		//定时器2开始计时
	IE2 = ET2; 
	EA = 1;
}
