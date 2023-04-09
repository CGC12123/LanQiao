#include"reg52.h"

typedef unsigned int u16;
typedef unsigned char u8;

sbit HC138_A = P2^5;
sbit HC138_B = P2^5;
sbit HC138_C = P2^7;

#define LED P0

void delay_10us(u16 ten_us)//延时函数，当传入Ten_us=1时，大约延时10us
{
	while(ten_us--);
}

// 防止乱叫
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
	// y4为0 使能锁存器
	HC138_A = 1;
	HC138_B = 0;
	HC138_C = 1;

	P0 = 0x10; // 继电器对应位为1
	delay_10us(50000);
	P0 = 0x10; // 继电器对应位为1	
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