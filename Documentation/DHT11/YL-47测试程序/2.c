//****************************************************************//
//	   DHT21使用范例 
//单片机 AT89S52 或 STC89C52RC 
//功能   串口发送温湿度数据 晶振 11.0592M 波特率 9600 
//硬件   P2.0口为通讯口连接DHT11,DHT11的电源和地连接单片机的电源和地，单片机串口加MAX232连接电脑 
//公司  雁凌电子    
//****************************************************************//

#include <STC8.h>
#include <intrins.h>  \

//
typedef unsigned char  U8;       /* defined for unsigned 8-bits integer variable 	  无符号8位整型变量  */
typedef signed   char  S8;       /* defined for signed 8-bits integer variable		  有符号8位整型变量  */
typedef unsigned int   U16;      /* defined for unsigned 16-bits integer variable 	  无符号16位整型变量 */
typedef signed   int   S16;      /* defined for signed 16-bits integer variable 	  有符号16位整型变量 */
typedef unsigned long  U32;      /* defined for unsigned 32-bits integer variable 	  无符号32位整型变量 */
typedef signed   long  S32;      /* defined for signed 32-bits integer variable 	  有符号32位整型变量 */
typedef float          F32;      /* single precision floating point variable (32bits) 单精度浮点数（32位长度） */
typedef double         F64;      /* double precision floating point variable (64bits) 双精度浮点数（64位长度） */
//
#define uchar unsigned char
#define uint unsigned int
#define   Data_0_time    4

//----------------------------------------------//
//----------------IO口定义区--------------------//
//----------------------------------------------//
sbit  P2_0  = P4^0 ;

//----------------------------------------------//
//----------------定义区--------------------//
//----------------------------------------------//
U8  U8FLAG,k;
U8  U8count,U8temp;
U8  U8T_data_H,U8T_data_L,U8RH_data_H,U8RH_data_L,U8checkdata;
U8  U8T_data_H_temp,U8T_data_L_temp,U8RH_data_H_temp,U8RH_data_L_temp,U8checkdata_temp;
U8  U8comdata;
U8  outdata[5];  //定义发送的字节数	 
U8 str[5];
U16 U16temp1,U16temp2;
void SendData(U8 *a)
{
	U8 i;
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
/////////////////////////////////////////////
void Delayms(unsigned int xms)
{
	unsigned int i,j;
	for(i = xms; i > 0; i--)
		for(j = 110; j > 0; j--);
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
void Delay10us()		//@24.000MHz
{
	unsigned char i;

	i = 78;
	while (--i);
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
//////////////////////////////////////////////////////	
void COM()
{ 
   U8 i;    
    for(i=0;i<8;i++)	   
	   {
	    U8FLAG=2;	
			while((!P2_0)&&U8FLAG++);
			Delay10us();
			Delay10us();
			Delay10us();
			U8temp=0;
			if(P2_0)U8temp=1;
			U8FLAG=2;
			while((P2_0)&&U8FLAG++);	  
	   	if(U8FLAG==1)break;	   	 
		  U8comdata<<=1;
	   	U8comdata|=U8temp;  
		 }
}
void RH(void)
	{
     P2_0=0;
	   Delay18ms();
	   P2_0=1;
	   Delay10us();
	   Delay10us();
	   Delay10us();
	   Delay10us();
	   P2_0=1;
	   if(!P2_0)  
	   {
				U8FLAG=2;
				while((!P2_0)&&U8FLAG++);
				U8FLAG=2;
				while((P2_0)&&U8FLAG++);	 
				 COM();
				 U8RH_data_H_temp=U8comdata;
				 COM();
				 U8RH_data_L_temp=U8comdata;
				 COM();
				 U8T_data_H_temp=U8comdata;
				 COM();
				 U8T_data_L_temp=U8comdata;
				 COM();
				 U8checkdata_temp=U8comdata;
				 P2_0=1;
				 U8temp=(U8T_data_H_temp+U8T_data_L_temp+U8RH_data_H_temp+U8RH_data_L_temp);
				 if(U8temp==U8checkdata_temp)
				 {
						U8RH_data_H=U8RH_data_H_temp;
						U8RH_data_L=U8RH_data_L_temp;
						U8T_data_H=U8T_data_H_temp;
						U8T_data_L=U8T_data_L_temp;
						U8checkdata=U8checkdata_temp;
				 }
	   }

	}
void main()
{
	PCON &= 0x7F;		//波特率不倍速
	SCON = 0x50;		//8位数据,可变波特率
	AUXR |= 0x40;		//定时器1时钟为Fosc,即1T
	AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
	TMOD &= 0x0F;		//清除定时器1模式位
	TMOD |= 0x20;		//设定定时器1为8位自动重装方式
	TL1 = 0xB2;		//设定定时初值
	TH1 = 0xB2;		//设定定时器重装值
	ET1 = 0;	
	TR1 = 1;	     
	while(1)
	{  
		 Delay2000ms();
	   RH();
		 Delay100us();
	   str[0]=U8RH_data_H;
	   str[1]=U8RH_data_L;
	   str[2]=U8T_data_H;
	   str[3]=U8T_data_L;
	   str[4]=U8checkdata;
	   SendData(str) ;  
	}
}

void RSINTR() interrupt 4 
{
	static unsigned char uart_ser = 0;
	if(TI==1)   
	{
		TI=0;
	}
	RI = 0;
	if(SBUF == 0x7f)
	{
		uart_ser++;
		if(uart_ser == 10)
		{
			uart_ser = 0;
			IAP_CONTR |= 0x60;
		}
	}
	else
	{
		uart_ser = 0;
	}   
}
