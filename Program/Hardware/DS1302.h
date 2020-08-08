#ifndef _DS1302_H_
#define _DS1302_H_
void DS_WriteByte(unsigned char addr, unsigned char dat);
unsigned char DS_ReadByte(unsigned char addr);
void DS_Init();
void DS_ReadTime();
void go_DS1302();
#endif
