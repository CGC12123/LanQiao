#include "reg52.h"
#include "onewire.h"

typedef unsigned char u8;
typedef unsigned int u16;

unsigned char code SMG_NoDot[18]={0xc0,0xf9,
    0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,
    0x88,0x80,0xc6,0xc0,0x86,0x8e,0xbf,0x7f};
unsigned char code SMG_Dot[10]={0x40,0x79,
    0x24,0x30,0x19,0x12,0x02,0x78,0x00,0x10};
float temp_f;
unsigned int temp_i;

void delay(unsigned int t)
{
 	while(t--);
}
 
void Init_74HC138(unsigned char channel)
{
 	switch(channel)
	{
	 	case 4:P2 = (P2 & 0x1f) | 0x80;break;
		case 5:P2 = (P2 & 0x1f) | 0xa0;break;
		case 6:P2 = (P2 & 0x1f) | 0xc0;break;
		case 7:P2 = (P2 & 0x1f) | 0xe0;break;
		case 0:P2 = (P2 & 0x1f) | 0x00;break;
	}
		P2 = (P2 & 0x1f) | 0x00;
}

void  SMG_DisplayBit(unsigned char pos,unsigned char dat)
{
 	P0 = (0x01 << pos);
	Init_74HC138(6);
	P0 = dat;
	Init_74HC138(7);
}
 
void SMG_All(unsigned char dat)
{
 	P0 = 0xff;
	Init_74HC138(6);
	P0 = dat;
	Init_74HC138(7);
}
 
void Display_18b20()
{
     SMG_DisplayBit(4,SMG_NoDot[temp_i / 1000]);        
     delay(500);
     SMG_DisplayBit(4,0xff);    //ÏûÒþ
 
	 SMG_DisplayBit(5,SMG_Dot[(temp_i / 100) % 10]);
	 delay(200);
	 SMG_DisplayBit(5,0xff);
	 delay(200); 

	 SMG_DisplayBit(6,SMG_NoDot[(temp_i / 10) % 10]);
	 delay(200);
	 SMG_DisplayBit(6,0xff);
	 delay(200);

	 SMG_DisplayBit(7,SMG_NoDot[temp_i % 10]);
	 delay(200);
	 SMG_DisplayBit(7,0xff);
	 delay(200);

	

	 SMG_All(0xff);
	 delay(200);
}



void rd_18b20()
{
	u8 high, low;
	u16 temp;	
	init_ds18b20();
	Write_DS18B20(0xcc);
	Write_DS18B20(0x44);
	
	init_ds18b20();
    Write_DS18B20(0xcc);
	Write_DS18B20(0xbe);

	low = Read_DS18B20();
	high = Read_DS18B20();

	init_ds18b20();

	temp = (high << 8) | low;
	temp_f = temp * 0.0625;
	temp_i = temp_f * 100;
	Display_18b20();
}	

void Init_System()
{
 	P0 = 0xff;
	Init_74HC138(4);
	P0 = 0x00;
	Init_74HC138(5);
	SMG_All(0xff);
}

void main()
{
	Init_System();
	while(1)
	{
	 rd_18b20();
	}
}