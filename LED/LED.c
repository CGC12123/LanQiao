#include"reg52.h"

typedef unsigned int u16;
typedef unsigned char u8;

#define LED P0

sbit HC138_A = P2^5;
sbit HC138_B = P2^5;
sbit HC138_C = P2^7;


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

void LEDRunning()
{
	u8 i;
	// y4为0 使能锁存器
	HC138_A = 1;
	HC138_B = 0;
	HC138_C = 0;

	//LED = 0x00;
	//delay_10us(50000);
	//LED = 0xff;
	//delay_10us(50000);

	// 依次点亮
	for(i = 0; i <= 8; i++)
	{
		P0 = 0xff << i; // 左移后补位为0 左移几位就有几个灯亮 以实现依次点亮效果
		delay_10us(50000);
	}

	// 依次熄灭
	for(i = 0; i <= 8; i++)
	{
		P0 = ~(0xff << i); // 熄灭为亮的取反
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