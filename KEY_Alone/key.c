#include "reg52.h"

typedef unsigned int u16;
typedef unsigned char u8;

sbit S7 = P3^0;
sbit S6 = P3^1;
sbit S5 = P3^2;
sbit S4 = P3^3;

sbit L1 = P0^0;
sbit L2 = P0^1;
sbit L3 = P0^2;
sbit L4 = P0^3;
sbit L5 = P0^4;
sbit L6 = P0^5;

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

void ScanKeys_alone()
{
	if(S7 == 0)
	{
		delay_10us(100);
		if(S7 == 0)
		{
			L1 = 0;
			while(S7 == 0); // �ȴ������ɿ�
			L1 = 1;
		}
	}	
	if(S6 == 0)
	{
		delay_10us(100);
		if(S6 == 0)
		{
			L1 = 0;
			while(S6 == 0); // �ȴ������ɿ�
			L1 = 1;
		}
	}
	if(S5 == 0)
	{
		delay_10us(100);
		if(S5 == 0)
		{
			L1 = 0;
			while(S5 == 0); // �ȴ������ɿ�
			L1 = 1;
		}
	}
	if(S4 == 0)
	{
		delay_10us(100);
		if(S4 == 0)
		{
			L1 = 0;
			while(S4 == 0); // �ȴ������ɿ�
			L1 = 1;
		}
	}
}



void main()
{
	SeleteHC573(4);
	while(1)
	{
	 	ScanKeys_alone();
	}
}