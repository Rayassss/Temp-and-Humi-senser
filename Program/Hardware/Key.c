#include "STC8F.h"
#include "Key.h"
#include "Delay.h"
#include "Led.h"
#include "Lcd.h"
#include "DS1302.h"
sbit Key1 = P2^4;
sbit Key2 = P2^5;
sbit Key3 = P5^4;
unsigned char counter1 = 0;
unsigned char counter2 = 0;
unsigned char counter3 = 0;
extern unsigned char TIME[7];
void Keyinit_1()
{
	if(!Key1)
	{
		Delayms(10);
		if (!Key1)
		{			
			counter1++;
			while(!Key1);
			if(counter1 == 8)
			{
				counter1 = 0;
			}
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
void Keyinit()//按一次k1调节秒，再按一次调节分钟，再按一次调节小时，再按一次调节日	//再按一次调节月，再按一次调节年，最后按一次确认数字，其中，Key2每次减一，Key3每次加一；					
{	
	unsigned char Temp_hour = 8;
	unsigned char Temp_min = 0;
	unsigned char Temp_sec = 0;
	unsigned char Temp_year = 20;
	unsigned char Temp_mouth = 6;
	unsigned char Temp_date = 15;
	if(counter1 == 1)
	{
		while(Key1)
		{
			if(Key2 == 0)
			{
				Delayms(10);
				if(Key2 == 0)
				{
					Temp_hour++;
					if(Temp_hour == 13)
					{
						Temp_hour = 8;
						TIME[2] = Temp_hour;
						DS_Init();
					}
					while(!Key2);					
				}			
			}
			if(Key3 == 0)
			{
				Delayms(10);
				if(Key3 == 0)
				{
					Temp_hour--;
					if(Temp_hour == 0)
					{
						Temp_hour = 8;
						TIME[2] = Temp_hour;
						DS_Init();
					}
					while(!Key3);
				}
			}
			break;
		}
		counter1 = 2;
	}
}
//void KeyRST()
//{
//	if(!RST)
//	{
//		Delayms(10);
//		if(!RST)
//		{
//			IAP_CONTR |= 0x20;
//			Ledinit();
//		}
//		else
//		{
//			Led = 1;
//		}
//	}
//}