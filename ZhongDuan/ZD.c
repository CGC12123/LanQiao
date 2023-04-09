#include"reg52.h"

typedef unsigned int u16;
typedef unsigned char u8;

sbit L1 = P0^7;

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

void init_int0()
{
	IT0 = 1;
	EX0 = 1;
	EA = 1;
}

void init_timer0() // ʵ������
{
	TMOD |= 0X01;
	TH0 = (65535 - 50000) / 256;
	TL0 = (65535 - 50000) % 256;

	ET0 = 1;
	EA = 1;
	TR0 = 1;

}

void serviceINT0() interrupt 0
{
		
}

u8 count = 0;
void serviceTIMER0() interrupt 1
{
	TH0 = (65535 - 50000) / 256; // �����趨��ʱʱ��
	TL0 = (65535 - 50000) % 256;

	count ++;
	if(count == 10)
	{
		L1 = ~L1;
		count = 0;	
	}
}

void main()
{
	SeleteHC573(4);
	InitTimer0();
	while(1)
	{			
	}
}