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
			counter1 = 1;
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
void Keyinit()//按一次k1调节秒，再按一次调节分钟，再按一次调节小时，再按一次调节日	//再按一次调节月，再按一次调节年，最后按一次确认数字，其中，Key2每次减一，Key3每次加一；					
{	
	char Temp_hour = 8;
	char Temp_min = 0;
	char Temp_sec = 0;
	char Temp_year = 20;
	char Temp_mouth = 6;
	char Temp_date = 15;
	Keyinit_1();
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
					if(Temp_hour == 25)
					{
						Temp_hour = 8;			
					}
					Dsp_arc_area();
					Display_ASCII8X16(2,5,&Temp_hour);
					while(!Key2);					
				}			
			}
			if(Key3 == 0)
			{
				Delayms(10);
				if(Key3 == 0)
				{
					Temp_hour--;
					if(Temp_hour == (-1))
					{
						Temp_hour = 8;
					}
					Dsp_arc_area();
					Display_ASCII8X16(2,5,&Temp_hour);
					while(!Key3);
				}
			}
		}
		while(!Key1);
		counter1 = 2;
	}
	if(counter1 == 2)
	{
		while(Key1)
		{
			if(Key2 == 0)
			{
				Delayms(10);
				if(Key2 ==0)
				{
					Temp_min++;
					if(Temp_min == 61)
					{
						Temp_min = 30;
					}
					Dsp_arc_area();
					Display_ASCII8X16(24,5,&Temp_min);
				}
			}
			if(Key3 == 0)
			{
					Delayms(10);
					if(Key3 == 0)
					{
						Temp_min--;
						if(Temp_min == (-1))
						{
							Temp_min = 0;
						}
						Dsp_arc_area();
						Display_ASCII8X16(24,5,&Temp_min);
					}
			}
		}
		while(!Key1);
		counter1 = 3;
	}
	if(counter1 == 3)
	{
		while(Key1)
		{
			if(Key2 == 0)
			{
				Delayms(10);
				if(Key2 ==0)
				{
					Temp_sec++;
					if(Temp_sec == 61)
					{
						Temp_sec = 30;
					}
					Dsp_arc_area();
					Display_ASCII8X16(46,5,&Temp_sec);
				}
			}
			if(Key3 == 0)
			{
					Delayms(10);
					if(Key3 == 0)
					{
						Temp_sec--;
						if(Temp_sec == (-1))
						{
							Temp_sec = 0;
						}
						Dsp_arc_area();
						Display_ASCII8X16(46,5,&Temp_sec);
					}
			}
		}
		while(!Key1);
		counter1 = 4;
	}
	if(counter1 == 4)
	{
		while(Key1)
		{
			if(Key2 == 0)
			{
				Delayms(10);
				if(Key2 ==0)
				{
					Temp_year++;
					if(Temp_year == 100)
					{
						Temp_year = 20;
					}
					Dsp_arc_area();
					Display_ASCII8X16(50,20,&Temp_year);
				}
			}
			if(Key3 == 0)
			{
					Delayms(10);
					if(Key3 == 0)
					{
						Temp_year--;
						if(Temp_year == (-1))
						{
							Temp_year = 20;
						}
						Dsp_arc_area();
						Display_ASCII8X16(50,20,&Temp_year);
					}
			}
		}
		while(!Key1);
		counter1 = 5;
	}
		
		if(counter1 == 5)
		{
			while(Key1)
			{
				if(Key2 == 0)
				{
					Delayms(10);
					if(Key2 ==0)
					{
						Temp_mouth++;
						if(Temp_mouth == 13)
						{
							Temp_mouth = 6;
						}
						Dsp_arc_area();
						Display_ASCII8X16(50,20,&Temp_mouth);
					}
				}
				if(Key3 == 0)
				{
						Delayms(10);
						if(Key3 == 0)
						{
							Temp_mouth--;
							if(Temp_mouth == (-1))
							{
								Temp_mouth = 6;
							}
							Dsp_arc_area();
							Display_ASCII8X16(50,20,&Temp_mouth);
						}
				}
			}
			while(!Key1);
			counter1 = 6;
		}
		if(counter1 == 6)
		{
			while(Key1)
			{
				if(Key2 == 0)
				{
					Delayms(10);
					if(Key2 ==0)
					{
						Temp_date++;
						if(Temp_date == 32)
						{
							Temp_date = 15;
						}
						Dsp_arc_area();
						Display_ASCII8X16(67,20,&Temp_date);
					}
				}
				if(Key3 == 0)
				{
						Delayms(10);
						if(Key3 == 0)
						{
							Temp_date--;
							if(Temp_date == (-1))
							{
								Temp_date = 15;
							}
							Dsp_arc_area();
							Display_ASCII8X16(67,20,&Temp_date);
						}
				}
			}
			while(!Key1);
			counter1 = 7;
		}
		if(counter1 == 7)
		{
			TIME[0] = (unsigned char)Temp_sec;
			TIME[1] = (unsigned char)Temp_min;
			TIME[2] = (unsigned char)Temp_hour;
			TIME[3] = (unsigned char)Temp_date;
			TIME[4] = (unsigned char)Temp_mouth;
			TIME[6] = (unsigned char)Temp_year;
			DS_Init();
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