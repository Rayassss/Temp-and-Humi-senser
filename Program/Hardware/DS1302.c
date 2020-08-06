#include "STC8F.h"
#include "Delay.h"
#include "DS1302.h"
#include "intrins.h"
sbit SCLK = P4^5; 
sbit IO = P4^6;
sbit RST = P4^7;
unsigned char WRITE_RTC_ADDR[7] = {0x80,0x82,0x84,0x86,0x88,0x8A,0x8C};
unsigned char TIME[7] = {0x00,0x00,0x08,0x01,0x01,0x01,0x20};
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
void DS_Init()
{
	unsigned char n;
	DS_WriteByte(0x8E,0X00);		 //��ֹд���������ǹر�д��������
	for (n=0; n<7; n++)//д��7���ֽڵ�ʱ���źţ�����ʱ��������
	{
		DS_WriteByte(WRITE_RTC_ADDR[n],TIME[n]);	
	}
	DS_WriteByte(0x8E,0x80);		 //��д��������
}
void DS_ReadTime()
{
	unsigned char n;
	for (n=0; n<7; n++)//��ȡ7���ֽڵ�ʱ���źţ�����ʱ��������
	{
		TIME[n] = DS_ReadByte(READ_RTC_ADDR[n]);
	}
		
}