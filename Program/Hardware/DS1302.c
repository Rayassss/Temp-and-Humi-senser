#include "STC8F.h"
#include "Delay.h"
#include "DS1302.h"
#include "intrins.h"
sbit SCLK = P4^5; 
sbit IO = P4^6;
sbit RST = P4^7;
unsigned char READTIME[7];
unsigned char WRITE_RTC_ADDR[7] = {0x80,0x82,0x84,0x86,0x88,0x8A,0x8C};
unsigned char READ_RTC_ADDR[7] = {0x81,0x83,0x85,0x87,0x89,0x8B,0x8d};
void DS_WriteByte(unsigned char addr, unsigned char dat)
{
	unsigned char n;
	RST = 0;
	_nop_();
	SCLK = 0;
	_nop_();
	RST = 1;
	_nop_();
	for(n=0;n<8;n++)
	{
		IO = (addr & 0x01);
		addr >>= 1;
		SCLK = 1;
		_nop_();
		SCLK = 0;
		_nop_();
	}
	for(n=0;n<8;n++)
	{
		IO = (dat & 0x01);
		dat >>= 1;
		SCLK = 1;
		_nop_();
		SCLK = 0;
		_nop_();
	}
	RST = 0;
	_nop_();
}
unsigned char DS_ReadByte(unsigned char addr)
{
	unsigned char dat,Temp,i;
	RST = 0;
	_nop_();
	SCLK = 0;
	_nop_();
	RST = 1;
	_nop_();
	for(i=0;i<8;i++)
	{
		IO = (addr & 0x01);
		addr >>= 1;
		SCLK = 1;
		_nop_();
		SCLK = 0;
		_nop_();
	}
	_nop_();
	for(i=0;i<8;i++)
	{
		Temp = IO;
		dat = (dat>>1)|(Temp<<7);
		SCLK = 1;
		_nop_();
		SCLK = 0;
		_nop_();
	}
	RST = 0;
	_nop_();
	return dat;
}
void DS_Init(unsigned char Table[])
{
	unsigned char n;
	DS_WriteByte(0x8E,0X00);		 //禁止写保护，就是关闭写保护功能
	for (n=0; n<7; n++)//写入7个字节的时钟信号：sec,min,hour,date,month,day,year
	{
		DS_WriteByte(WRITE_RTC_ADDR[n],Table[n]);	
	}
	DS_WriteByte(0x8E,0x80);		 //打开写保护功能
}
void DS_ReadTime()
{
	unsigned char n;
	for (n=0; n<7; n++)//读取7个字节的时钟信号：分秒时日月周年
	{
		READTIME[n] = DS_ReadByte(READ_RTC_ADDR[n]);
	}
}