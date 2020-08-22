#include "STC8F.h"
#include "Key.h"
#include "Delay.h"
#include "Led.h"
#include "Lcd.h"
#include "DS1302.h"
#include "GUI.h"
#include "stdio.h"
#include "string.h"
sbit Key1 = P2^4;//左
sbit Key2 = P2^5;
sbit Key3 = P5^4;//右
void Keyinit_1()
{

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
	unsigned char counter1 = 0;
	unsigned char counter2 = 0;
	unsigned char counter3 = 0;
	int Temp_hour = 8;
	int Temp_min = 0;
	int Temp_sec = 0;
	int Temp_year = 20;
	int Temp_month = 6;
	int Temp_date = 15;
	char Temp[5];
	unsigned char Writetime[7];
	bit flag;
	if(!Key1)
	{
		Delayms(10);
		if(!Key1)
		{			
			counter1 = 1;
			flag = 1;
		}
		while(!Key1);
	}
	while(flag)
	{
		if(counter1 == 1)
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
			if(!Key1)
			{
				Delayms(10);
				if(!Key1)
				{
					counter1 = 2;
				}
				while(!Key1);
			}
		}
		if(counter1 == 2)
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
						Display_ASCII8X16(50,2,Temp);		
						while(!Key2);
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
								Temp_min = 30;
							}
							Lcd_arc_clear(MIN);
							memset(Temp,' ',sizeof(Temp));
							sprintf(Temp,"%02d",Temp_min);
							Display_ASCII8X16(50,2,Temp);	
							while(!Key3);						
						}
				}
			
			if(!Key1)
			{
				Delayms(10);
				if(!Key1)
				{
					counter1 = 3;
				}
				while(!Key1);
			}
		}				
if(counter1 == 3)
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
				Display_ASCII8X16(102,2,Temp);	
				while(!Key2);
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
				Lcd_arc_clear(SEC);
				memset(Temp,' ',sizeof(Temp));
				sprintf(Temp,"%02d",Temp_sec);
				Display_ASCII8X16(102,2,Temp);	
				while(!Key3);						
				}
		}
		if(!Key1)
			{
				Delayms(10);
				if(!Key1)
				{
					counter1 = 4;
				}
				while(!Key1);
			}
}
if(counter1 == 4)
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
				sprintf(Temp,"20%02d",Temp_year);
				Display_ASCII8X16(1,40,Temp);
				while(!Key2);
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
				sprintf(Temp,"20%02d",Temp_year);
				Display_ASCII8X16(1,40,Temp);
				while(!Key3);
				}
		}
	if(!Key1)
			{
				Delayms(10);
				if(!Key1)
				{
					counter1 = 5;
				}
				while(!Key1);
			}

}
	
	if(counter1 == 5)
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
					while(!Key2);
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
						while(!Key3);
					}
			}
			if(Key1 == 0)
			{
				counter1 = 6;
			}
			while(!Key1);
	}
	if(counter1 == 6)
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
				while(!Key2);
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
						while(!Key3);
					}
			}
			if(!Key1)
			{
				Delayms(10);
				if(!Key1)
				{
					counter1 = 7;
				}
				while(!Key1);
			}
	}
	if(counter1 == 7)
	{
		Writetime[0] = Hex_to_BCD((unsigned char)Temp_sec);
		Writetime[1] = Hex_to_BCD((unsigned char)Temp_min);
		Writetime[2] = Hex_to_BCD((unsigned char)Temp_hour);
		Writetime[3] = Hex_to_BCD((unsigned char)Temp_date);
		Writetime[4] = Hex_to_BCD((unsigned char)Temp_month);
		Writetime[6] = Hex_to_BCD((unsigned char)Temp_year);
		DS_Init(Writetime);
		Lcd_half_clear();
		Draw_DS1302();
		counter1 = 0;
		flag = 0;
	}
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