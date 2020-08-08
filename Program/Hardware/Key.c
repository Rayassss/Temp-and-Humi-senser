#include "STC8F.h"
#include "Key.h"
#include "Delay.h"
#include "Led.h"
sbit Key1 = P2^5;
sbit Key2 = P2^4;
sbit RST = P5^4;
void Keyinit_1()
{
	if(!Key1)
	{
		Delayms(10);
		if (!Key1)
		{			
			
			while(!Key1);
		}
	}
}
void Keyinit_2()
{
	if(!Key2)
	{
		Delayms(10);
		if (!Key2)
		{
		
			while(!Key2);
		}
	}
}
void KeyRST()
{
	if(!RST)
	{
		Delayms(10);
		if(!RST)
		{
			IAP_CONTR |= 0x10;
			Ledinit();
			while(!RST);
		}
	}
}