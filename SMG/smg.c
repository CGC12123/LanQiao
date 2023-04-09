#include"reg52.h"

typedef unsigned int u16;
typedef unsigned char u8;

#define LED P0

u8 smg_yang[11] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90, 0xff}; // 对应0-9, ff为消影用

void delay_10us(u16 ten_us)//延时函数，当传入Ten_us=1时，大约延时10us
{
	while(ten_us--);
}

void SeleteHC573(u8 channel) // 锁存器选择 用于使能对应锁存器启动对应外设
{
	switch(channel)
	{
		case 4:
			P2 = (P2 & 0x1f) | 0x80; // (P2 & 0x1f)选择高三位，或上0x80(1000 0000)对高三位进行判断 使高三为100
		break;
		case 5:
			P2 = (P2 & 0x1f) | 0xa0;
		break;
		case 6:
			P2 = (P2 & 0x1f) | 0xc0;
		break;
		case 7:
			P2 = (P2 & 0x1f) | 0xe0;
		break;
	}	
}

// 静态显示
void Display_bit(u8 value, u8 pos)
{
	SeleteHC573(6);
	P0 = 0x01 << pos;
	SeleteHC573(7);
	P0 = value;			
}

void Display_Dynamic()
{
	Display_bit(smg_yang[1], 0);
	delay_10us(500);	
	Display_bit(smg_yang[0], 1);
	delay_10us(500);
}

void main()
{
	while(1)
	{
		Display_Dynamic();
	}
}