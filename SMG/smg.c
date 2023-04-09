#include"reg52.h"

typedef unsigned int u16;
typedef unsigned char u8;

#define LED P0

u8 smg_yang[11] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90, 0xff}; // ��Ӧ0-9, ffΪ��Ӱ��

void delay_10us(u16 ten_us)//��ʱ������������Ten_us=1ʱ����Լ��ʱ10us
{
	while(ten_us--);
}

void SeleteHC573(u8 channel) // ������ѡ�� ����ʹ�ܶ�Ӧ������������Ӧ����
{
	switch(channel)
	{
		case 4:
			P2 = (P2 & 0x1f) | 0x80; // (P2 & 0x1f)ѡ�����λ������0x80(1000 0000)�Ը���λ�����ж� ʹ����Ϊ100
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

// ��̬��ʾ
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