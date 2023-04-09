#include"reg52.h"

typedef unsigned int u16;
typedef unsigned char u8;

sbit HC138_A = P2^5;
sbit HC138_B = P2^5;
sbit HC138_C = P2^7;

#define LED P0

void delay_10us(u16 ten_us)//��ʱ������������Ten_us=1ʱ����Լ��ʱ10us
{
	while(ten_us--);
}

// ��ֹ�ҽ�
void Init()
{
	HC138_A = 1;
   	HC138_B = 0;
	HC138_C = 1;

	P0 = 0x00;
	P2 &= 0x1f;
}

void FMQRunning()
{
	// y4Ϊ0 ʹ��������
	HC138_A = 1;
	HC138_B = 0;
	HC138_C = 1;

	P0 = 0x10; // �̵�����ӦλΪ1
	delay_10us(50000);
	P0 = 0x10; // �̵�����ӦλΪ1	
	delay_10us(50000);
	

}

void main()
{
	Init();
	while(1)
	{
		//FMQRunning();
	}
}