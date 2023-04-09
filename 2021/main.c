#include "STC15F2K60S2.h"
#include "onewire.h"
#include "absacc.h"
#include "iic.h"

typedef unsigned char u8;
typedef unsigned int u16;

// 以下为矩阵键盘定义
sbit R1 = P3^0;
sbit R2 = P3^1;
sbit R3 = P3^2;
sbit R4 = P3^3;

sbit C4 = P3^4;
sbit C3 = P3^5;
sbit C2 = P4^2;
sbit C1 = P4^4;


u8 smg_nodot[] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82 , 0xF8, 0x80, 0x90, 0xff, 0xc6, 0x8c, 0x88}; // c p a  0110 0011
u8 smg_dot[] = {0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x02, 0x78, 0x00, 0x10, 0xff};

u16 temp = 0;
u8 key_mutil = 0;
u8 param_tem = 25;
u8 paper = 1;
bit mode = 0;
float Vdac;

void display_temp();

void delay(u8 time)
{
	while(time --);
}

void Delay_OneWire_(u8 time)
{
	while(time --)
	{
		display_temp();	
	}
}

void selete_hc138(u8 num)
{
	switch(num)
	{
		case 4:
			P2 = (P2 & 0x1f) | 0x80; // 0001 1111
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

void display_smg_bit(u8 pos, u8 num)
{
	selete_hc138(7);
	P0 = 0xff;
	selete_hc138(6);
	P0 = 0x01 << pos;
	selete_hc138(7);
	P0 = num;
}

void rd_ds18b20()
{
	u8 LSB, MSB;
	
	init_ds18b20();
	Write_DS18B20(0xcc);
	Write_DS18B20(0x44);

	//Delay_OneWire_(1000);

	init_ds18b20();
	Write_DS18B20(0xcc);
	Write_DS18B20(0xbe);

	LSB = Read_DS18B20(); // 低八位
	MSB = Read_DS18B20(); // 高八位

	temp = MSB;
	temp = (temp << 8) | LSB;

	//if(temp & 0xf800 == 0x0000) // 判断高五位（符号位）此处为判断正数
	//{
		temp >>= 4;
		//temp *= 100; // 放大100倍
		//temp = temp + (LSB & 0x0f) * 6.25; // 得到原温度的100倍	
		temp = temp *0.0625;
		temp = temp * 10;													 	
	//}
}

void display_smg_all(unsigned char dat)
{
	XBYTE[0xc000] = 0xff;							 
	XBYTE[0xe000] = dat;	
}


void scan_key()
{
	R1 = 0;
	R2 = R3 = R4 = 1;
	C1 = C2 = C3 = 1;
	if(C1 == 0)
	{
		delay(500);
		while(C1 == 0);
		key_mutil = 7; 
	}
	if(C2 == 0)
	{
		delay(500);
		while(C2 == 0);
		key_mutil = 11; 
	}
	if(C3 == 0)
	{
		delay(500);
		while(C3 == 0);
		key_mutil = 15; 
	}
	if(C4 == 0)
	{
		delay(500);
		while(C4 == 0);
		key_mutil = 19; 
	}

	R2 = 0;
	R1 = R3 = R4 = 1;
	C1 = C2 = C3 = 1;
	if(C1 == 0)
	{
		delay(500);
		while(C1 == 0);
		key_mutil = 6; 
	}
	if(C2 == 0)
	{
		delay(500);
		while(C2 == 0);
		key_mutil = 10; 
	}
	if(C3 == 0)
	{
		delay(500);
		while(C3 == 0);
		key_mutil = 14; 
	}
	if(C4 == 0)
	{
		delay(500);
		while(C4 == 0);
		key_mutil = 18; 
	}

	R3 = 0;
	R1 = R2 = R4 = 1;
	C1 = C2 = C3 = 1;
	if(C1 == 0)
	{
		delay(500);
		while(C1 == 0);
		key_mutil = 5; 
	}
	if(C2 == 0)
	{
		delay(500);
		while(C2 == 0);
		key_mutil = 9; 
	}
	if(C3 == 0)
	{
		delay(500);
		while(C3 == 0);
		key_mutil = 13; 
	}
	if(C4 == 0)
	{
		delay(500);
		while(C4 == 0);
		key_mutil = 17; 
	}

	R4 = 0;
	R1 = R2 = R3 = 1;
	C1 = C2 = C3 = 1;
	if(C1 == 0)
	{
		delay(500);
		while(C1 == 0);
		key_mutil = 4; 
	}
	if(C2 == 0)
	{
		delay(500);
		while(C2 == 0);
		key_mutil = 8; 
	}
	if(C3 == 0)
	{
		delay(500);
		while(C3 == 0);
		key_mutil = 12; 
	}
	if(C4 == 0)
	{
		delay(500);
		while(C4 == 0);
		key_mutil = 16; 
	}								
}

void display_temp() // 温度显示页面
{
//	display_smg_bit(7, smg_nodot[temp % 10]);
//	delay(50);
//	display_smg_bit(6, smg_nodot[temp % 100 / 10]);
//	delay(50);
//	display_smg_bit(5, smg_dot[temp % 1000 / 100]);
//	delay(50);
//	display_smg_bit(4, smg_nodot[temp / 1000]);
	display_smg_bit(7, smg_nodot[temp % 10]);
	delay(200);
	display_smg_bit(7, 0xff);
	delay(200);
	display_smg_bit(6, smg_dot[temp /10 % 10 ]);
	delay(5200);
	display_smg_bit(6, 0xff);
	delay(200);
	display_smg_bit(5, smg_nodot[temp / 100]);
	delay(200);
	display_smg_bit(5, 0xff);
	delay(200);

	display_smg_bit(4, 0xff);
	delay(200);	
	display_smg_bit(3, 0xff);
	delay(200);
	display_smg_bit(2, 0xff);
	delay(200);
	display_smg_bit(1, 0xff);
	delay(200);
	display_smg_bit(0, smg_nodot[11]); // c
	delay(200);

	//display_smg_all(0xff); // 消影	
}

void param_set()
{
	if (key_mutil == 8)
	{
		param_tem --;
		key_mutil = 0;
	}
	else if(key_mutil == 9)
	{
		param_tem ++;
		key_mutil = 0; 		
	}
}

void display_param() // 参数显示页面
{
	display_smg_bit(7, smg_nodot[param_tem % 10]);
	delay(50);
	display_smg_bit(6, smg_nodot[param_tem / 10]);
	delay(50);
	display_smg_bit(5, 0xff);
	delay(50);
	display_smg_bit(4, 0xff);
	delay(50);
	display_smg_bit(3, 0xff);
	delay(50);
	display_smg_bit(2, 0xff);
	delay(50);
	display_smg_bit(1, 0xff);
	delay(50);
	display_smg_bit(0, smg_nodot[12]); // p
	delay(50);		
}

void dac_pcf8591(u8 dat)
{
	IIC_Start();
	IIC_SendByte(0x90);
	IIC_WaitAck();

	IIC_SendByte(0x40);  // DAC输出模式  允许DAC   ADC 通道 0
	IIC_WaitAck();

	IIC_SendByte(dat);
	IIC_WaitAck();
	IIC_Stop();
}

void dac_change_mode()
{
	if (key_mutil == 5)
	{	
		mode = !mode;
		key_mutil = 0;
	}
	if (mode == 0) // 模式1
	{
		if(temp < param_tem * 100)
			Vdac = 0.0;
		else
			Vdac = 5.0;	
	}
	else if(mode == 1) // 模式2
	{
		if(temp < 20 * 100)
			Vdac = 1.0;
		else if(temp > 40 * 100)
			Vdac = 4.0;
		else
			Vdac = 0.15 * temp / 100 - 2;
	}
	dac_pcf8591((u8)(Vdac * 51));
}

void display_dac()
{
	u8 x = (u8) Vdac * 100;
	display_smg_bit(0, smg_nodot[13]);
	delay(50);
	display_smg_bit(1, 0xff);
	delay(50);
	display_smg_bit(2, 0xff);
	delay(50);
	display_smg_bit(3, 0xff);
	delay(50);
	display_smg_bit(4, 0xff);
	delay(50);
	display_smg_bit(5, 0xff);
	delay(50);
	display_smg_bit(6, smg_dot[x / 100 % 10]);
	delay(50);
	display_smg_bit(7, smg_nodot[x / 10 % 10]);
	delay(50);
	display_smg_bit(8, smg_nodot[x % 10, 0]);
	delay(50);
}

void main()
{
	//XBYTE[8000] = 0xff; // 关灯
	
	selete_hc138(4);
	P0 = 0xff;
	
//	display_smg_bit(0, 0xc6);
//	delay(100);
//	display_smg_bit(1, 0x88);
//	delay(100);
	while(1)
	{		
		
		rd_ds18b20();
		display_temp();		

//		scan_key();
//		
//		if (key_mutil == 4)
//		{
//			paper ++;
//			key_mutil = 0;
//			if (paper == 4)
//				paper = 1;
//		}
//
//		//paper
//		if (paper == 1)
//		{	
//			rd_ds18b20();
//			display_temp();
//			selete_hc138(4);
//			P0 = ~(0x40);
//		}
//		else if(paper == 2)
//		{
//			display_param();
//			param_set();
//			selete_hc138(4);
//			P0 = ~(0x20);	
//		}
//		else if(paper == 3)
//		{
//			rd_ds18b20();
//			dac_change_mode();
//			display_dac();	
//		}			
	}
	
}









