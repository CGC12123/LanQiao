#include"reg52.h"

typedef unsigned int u16;
typedef unsigned char u8;

sfr P4 = 0xc0; // ����P4�ڵ�ַ

sbit R1 = P3^0;
sbit R2 = P3^1;
sbit R3 = P3^2;
sbit R4 = P3^3;

sbit C4 = P3^4;
sbit C3 = P3^5;
sbit C2 = P4^2;
sbit C1 = P4^4;

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

// smg��̬��ʾ
void Display_bit(u8 value, u8 pos)
{
	SeleteHC573(6);
	P0 = 0x01 << pos;
	SeleteHC573(7);
	P0 = value;			
}

void ScanKey_Multi() // 0Ϊ����
{
	u8 key_num;
	R1 = 0;
	R2 = R3 = R4 = 1;
	C1 = C2 = C3 = 1;
	if(C1 == 0)
	{
		delay_10us(100);
		while (C1 == 0);
		key_num = 0;
		Display_bit(smg_yang[key_num], 0);
	}
	else if(C2 == 0)
	{
		delay_10us(100);
		while (C2 == 0);
		key_num = 1;
		Display_bit(smg_yang[key_num], 0);
	}	
	else if(C3 == 0)
	{
		delay_10us(100);
		while (C3 == 0);
		key_num = 2;
		Display_bit(smg_yang[key_num], 0);
	}
	else if(C4 == 0)
	{
		delay_10us(100);
		while (C4 == 0);
		key_num = 3;
		Display_bit(smg_yang[key_num], 0);
	}

	R2 = 0;
	R1 = R3 = R4 = 1;
	C1 = C2 = C3 = 1;
	if(C1 == 0)
	{
		delay_10us(100);
		while (C1 == 0);
		key_num = 4;
		Display_bit(smg_yang[key_num], 0);
	}
	else if(C2 == 0)
	{
		delay_10us(100);
		while (C2 == 0);
		key_num = 5;
		Display_bit(smg_yang[key_num], 0);
	}	
	else if(C3 == 0)
	{
		delay_10us(100);
		while (C3 == 0);
		key_num = 6;
		Display_bit(smg_yang[key_num], 0);
	}
	else if(C4 == 0)
	{
		delay_10us(100);
		while (C4 == 0);
		key_num = 7;
		Display_bit(smg_yang[key_num], 0);
	}

	R3 = 0;
	R1 = R2 = R4 = 1;
	C1 = C2 = C3 = 1;
	if(C1 == 0)
	{
		delay_10us(100);
		while (C1 == 0);
		key_num = 8;
		Display_bit(smg_yang[key_num], 0);
	}
	else if(C2 == 0)
	{
		delay_10us(100);
		while (C2 == 0);
		key_num = 9;
		Display_bit(smg_yang[key_num], 0);
	}	
	else if(C3 == 0)
	{
		delay_10us(100);
		while (C3 == 0);
		key_num = 1;
		Display_bit(smg_yang[key_num], 0);
		key_num = 0;
		Display_bit(smg_yang[key_num], 1);
	}
	else if(C4 == 0)
	{
		delay_10us(100);
		while (C4 == 0);
		key_num = 1;
		Display_bit(smg_yang[key_num], 0);
		key_num = 1;
		Display_bit(smg_yang[key_num], 1);
	}

	R4 = 0;
	R1 = R2 = R3 = 1;
	C1 = C2 = C3 = 1;
	if(C1 == 0)
	{
		delay_10us(100);
		while (C1 == 0);
		key_num = 1;
		Display_bit(smg_yang[key_num], 0);
		key_num = 2;
		Display_bit(smg_yang[key_num], 1);
	}
	else if(C2 == 0)
	{
		delay_10us(100);
		while (C2 == 0);
		key_num = 1;
		Display_bit(smg_yang[key_num], 0);
		key_num = 3;
		Display_bit(smg_yang[key_num], 1);
	}	
	else if(C3 == 0)
	{
		delay_10us(100);
		while (C3 == 0);
		key_num = 1;
		Display_bit(smg_yang[key_num], 0);
		key_num = 4;
		Display_bit(smg_yang[key_num], 1);
	}
	else if(C4 == 0)
	{
		delay_10us(100);
		while (C4 == 0);
		key_num = 5;
		Display_bit(smg_yang[key_num], 0);
		key_num = 1;
		Display_bit(smg_yang[key_num], 1);
	}
}

void main()
{
	while(1)
	{
		ScanKey_Multi();
	}
}







