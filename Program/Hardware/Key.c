#include "STC8F.h"
#include "Key.h"
#include "Delay.h"
#include "Led.h"
#include "Lcd.h"
#include "DS1302.h"
#include "stdio.h"
#include "string.h"
sbit Key1 = P2^4;
sbit Key2 = P2^5;
sbit Key3 = P5^4;
unsigned char counter1 = 0;
unsigned char counter2 = 0;
unsigned char counter3 = 0;
int Temp_hour = 8;
int Temp_min = 0;
int Temp_sec = 0;
int Temp_year = 20;
int Temp_month = 6;
int Temp_date = 15;
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
void Keyinit()//��һ��k1�����룬�ٰ�һ�ε��ڷ��ӣ��ٰ�һ�ε���Сʱ���ٰ�һ�ε�����	//�ٰ�һ�ε����£��ٰ�һ�ε����꣬���һ��ȷ�����֣����У�Key2ÿ�μ�һ��Key3ÿ�μ�һ��					
{	
	char Temp[10];
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
					Lcd_arc_clear(HOUR);
					memset(Temp,' ',sizeof(Temp));
					sprintf(Temp,"%02d",Temp_hour);
					Display_ASCII8X16(1,2,Temp);
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
					Lcd_arc_clear(HOUR);
					memset(Temp,' ',sizeof(Temp));
					sprintf(Temp,"%02d",Temp_hour);
					Display_ASCII8X16(1,2,Temp);
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
					Lcd_arc_clear(MIN);
					memset(Temp,' ',sizeof(Temp));
					sprintf(Temp,"%02d",Temp_min);
					Display_ASCII8X16(50,2,Temp);				}
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
						Lcd_arc_clear(MIN);
						memset(Temp,' ',sizeof(Temp));
						sprintf(Temp,"%02d",Temp_min);
						Display_ASCII8X16(50,2,Temp);				}
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
					Lcd_arc_clear(SEC);
					memset(Temp,' ',sizeof(Temp));
					sprintf(Temp,"%02d",Temp_sec);
					Display_ASCII8X16(102,2,Temp);				}
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
					Lcd_arc_clear(SEC);
					memset(Temp,' ',sizeof(Temp));
					sprintf(Temp,"%02d",Temp_sec);
					Display_ASCII8X16(102,2,Temp);			}
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
					Lcd_arc_clear(YEAR);
					memset(Temp,' ',sizeof(Temp));
					sprintf(Temp,"%02d",Temp_year);
					Display_ASCII8X16(18,40,Temp);
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
					Lcd_arc_clear(YEAR);
					memset(Temp,' ',sizeof(Temp));
					sprintf(Temp,"%02d",Temp_year);
					Display_ASCII8X16(18,40,Temp);
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
						Temp_month++;
						if(Temp_month == 13)
						{
							Temp_month = 6;
						}
					Lcd_arc_clear(MONTH);
					memset(Temp,' ',sizeof(Temp));
					sprintf(Temp,"%02d",Temp_month);
					Display_ASCII8X16(50,40,Temp);
					}
				}
				if(Key3 == 0)
				{
						Delayms(10);
						if(Key3 == 0)
						{
							Temp_month--;
							if(Temp_month == (-1))
							{
								Temp_month = 6;
							}
						Lcd_arc_clear(MONTH);
						memset(Temp,' ',sizeof(Temp));
						sprintf(Temp,"%02d",Temp_month);
						Display_ASCII8X16(50,40,Temp);
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
					Lcd_arc_clear(DATE);
					memset(Temp,' ',sizeof(Temp));
					sprintf(Temp,"%02d",Temp_date);
					Display_ASCII8X16(90,40,Temp);
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
					Lcd_arc_clear(DATE);
					memset(Temp,' ',sizeof(Temp));
					sprintf(Temp,"%02d",Temp_date);
					Display_ASCII8X16(90,40,Temp);
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
			TIME[4] = (unsigned char)Temp_month;
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