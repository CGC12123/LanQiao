#include"reg52.h"

typedef unsigned int u16;
typedef unsigned char u8;

#define LED P0

sbit HC138_A = P2^5;
sbit HC138_B = P2^5;
sbit HC138_C = P2^7;


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

void LEDRunning()
{
	u8 i;
	// y4Ϊ0 ʹ��������
	HC138_A = 1;
	HC138_B = 0;
	HC138_C = 0;

	//LED = 0x00;
	//delay_10us(50000);
	//LED = 0xff;
	//delay_10us(50000);

	// ���ε���
	for(i = 0; i <= 8; i++)
	{
		P0 = 0xff << i; // ���ƺ�λΪ0 ���Ƽ�λ���м������� ��ʵ�����ε���Ч��
		delay_10us(50000);
	}

	// ����Ϩ��
	for(i = 0; i <= 8; i++)
	{
		P0 = ~(0xff << i); // Ϩ��Ϊ����ȡ��
		delay_10us(50000);
	}
		
}

void main()
{
	while(1)
	{
		//LEDRunning();

		//P2 = 0x80;
		SeleteHC573(4);
		P0 = 0xf0;
		delay_10us(100000);
		P0 = 0x0f;
		delay_10us(100000);
	}
}