#include "Delay.h"
#include "intrins.h"
void Delayms(unsigned int xms)
{
	unsigned int i,j;
	for(i = xms; i > 0; i--)
		for(j = 55; j > 0; j--);
}
void Delay30us()		//@24.000MHz
{
	unsigned char i;

	i = 238;
	while (--i);
}


void Delay80us()		//@24.000MHz
{
	unsigned char i, j;

	_nop_();
	_nop_();
	i = 3;
	j = 123;
	do
	{
		while (--j);
	} while (--i);
}

void Delay100us()		//@24.000MHz
{
	unsigned char i, j;

	i = 4;
	j = 27;
	do
	{
		while (--j);
	} while (--i);
}

void Delay1us()		//@24.000MHz
{
	unsigned char i;

	i = 6;
	while (--i);
}


void Delay40us()		//@24.000MHz
{
	unsigned char i, j;

	_nop_();
	i = 2;
	j = 60;
	do
	{
		while (--j);
	} while (--i);
}


void Delay50us()		//@24.000MHz
{
	unsigned char i, j;

	_nop_();
	i = 2;
	j = 140;
	do
	{
		while (--j);
	} while (--i);
}

void Delay18ms()		//@24.000MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 3;
	j = 50;
	k = 4;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void Delay20ms()		//@24.000MHz
{
	unsigned char i, j, k;

	_nop_();
	i = 3;
	j = 112;
	k = 91;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void Delay2000ms()		//@24.000MHz
{
	unsigned char i, j, k;

	i = 244;
	j = 130;
	k = 4;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}
void Delay100ms()		//@24.000MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 13;
	j = 45;
	k = 214;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}
void Delay1000ms()		//@24.000MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 122;
	j = 193;
	k = 128;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}



