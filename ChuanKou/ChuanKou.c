#include"reg52.h"

sfr AUXR = 0x8e;

typedef unsigned int u16;
typedef unsigned char u8;

void InitUart()
{
	TMOD |= 0X20;
	TH1 = 0XFD;
	TL1 = 0XFD;
	TR1 = 1;

	SCON = 0X50;
	AUXR = 0x00;

	EA = 1;
	ES = 1;
}

u8 date;
void ServiceUart() interrupt 4
{
	if(RI == 1)
	{
		RI = 0;
		date = SBUF;
	}
}

void Send(u8 dat)
{
	SBUF = dat;
	while(TI == 0);
	TI = 0;	
}

void main()
{
	InitUart();
	Send(0xa5);
	while(1);
}