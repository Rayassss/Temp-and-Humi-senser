#include "STC8F.h"
#include "Delay.h"
#include "DHT11.h"
sbit DATA = P4^0;
unsigned char Byte_temp;
unsigned char RH_data_H,RH_data_L,T_data_H,T_data_L,checkdata;

void Readbyte()
{
	unsigned char i,bit_temp,flag;
	for(i=0; i<8; i++)	   
	{
		flag = 2;	
		while((!DATA) && flag++);
		Delay30us();
		bit_temp = 0;
		if(DATA)bit_temp = 1;
		flag = 2;
		while((DATA) && flag++);	  
		if(flag == 1)break;	   	 
		Byte_temp <<= 1;
		Byte_temp |= bit_temp;  
	}	
}
void DHT11_init()
{
	unsigned char RH_data_H_temp,RH_data_L_temp,T_data_H_temp,T_data_L_temp,checkdata_temp;
	unsigned char flag;
	DATA = 0;
	Delay18ms();
	DATA = 1;
	Delay40us();
	DATA = 1;
	if(!DATA)
	{
		flag = 2;
		while((!DATA) && (flag++));
		flag = 2;
		while((DATA) && (flag++));
		Readbyte();
		RH_data_H_temp = Byte_temp;
		Readbyte();
		RH_data_L_temp = Byte_temp;
		Readbyte();
		T_data_H_temp = Byte_temp;
		Readbyte();
		T_data_L_temp = Byte_temp;
		Readbyte();
		checkdata_temp = Byte_temp;
		DATA = 1;
		if((T_data_H_temp+T_data_L_temp+RH_data_H_temp+RH_data_L_temp) == checkdata_temp)
		{
			RH_data_H = RH_data_H_temp;
			RH_data_L = RH_data_L_temp;
			T_data_H  = T_data_H_temp;
			T_data_L  = T_data_L_temp;
			checkdata = checkdata_temp;			
		}
	}
}
void SendData(unsigned char *a)
{
	unsigned char outdata[5];
	unsigned char i;
	outdata[0] = a[0]; 
	outdata[1] = a[1];
	outdata[2] = a[2];
	outdata[3] = a[3];
	outdata[4] = a[4];
	ES = 0;
	for(i=0; i<5; i++)
	{
		SBUF = outdata[i];
		while(!TI);
		TI = 0;
	}
	ES = 1;	
}












