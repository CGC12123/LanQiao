#include "STC15F2K60S2.h"
#include "onewire.h"
#include "ds1302.h"
#include "iic.h"

typedef unsigned char u8;
typedef unsigned int u16;

u8 code num_nodot[18] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x88,0x80,0xc6,0xc0,0x86,0x8e,0xbf,0x7f};
u8 code num_dot[10] = {0x40,0x79,0x24,0x30,0x19,0x12,0x02,0x78,0x00,0x10};

u8 code READ_RTC_ADDR[7] = {0x81, 0x83, 0x85, 0x87, 0x89, 0x8b, 0x8d};
u8 code WRITE_RTC_ADDR[7] = {0x80, 0x82, 0x84, 0x86, 0x88, 0x8a, 0x8c};

u8 time[] = {0x50, 0x59, 0x20, 0x05, 0x03, 0x05, 0x23};

sbit HC138_A = P2^5;
sbit HC138_B = P2^6;
sbit HC138_C = P2^7;

sbit r1 = P3^0;
sbit r2 = P3^1;
sbit r3 = P3^2;
sbit r4 = P3^3;

sbit c1 = P4^4;
sbit c2 = P4^2;
sbit c3 = P3^5;
sbit c4 = P3^4;

float temp_f;
u16 temp_i;
u8 param = 23;
u8 key = 0;
u8 jdq = 0;
bit mode = 0;
u8 dat;

unsigned char date[2];

void delay(u8 time)
{
	while(time --);
}

void selete_hc138(u8 num)
{
	switch (num)
	{
		case 0:
			HC138_A = 0;
			HC138_B = 0;
			HC138_C = 0;
			break;
		case 4:
			HC138_A = 0;
			HC138_B = 0;
			HC138_C = 1;
			break;
		case 5:
			HC138_A = 1;
			HC138_B = 0;
			HC138_C = 1;
			break;
		case 6:
			HC138_A = 0;
			HC138_B = 1;
			HC138_C = 1;
			break;
		case 7:
			HC138_A = 1;
			HC138_B = 1;
			HC138_C = 1;	
			break;
	}
}

void fmq_display(u8 pos,u8 num)
{
	selete_hc138(6);
	P0 = (0X01 << pos) ;
	selete_hc138(7);
	P0 = num;
}
	
void ds1302_init();

void system_init()
{
	selete_hc138(0);
	P0 = 0x00;
	selete_hc138(4);
	P0 = 0xff;
	
	ds1302_init();		
}

void rd_tempture()
{
	u16 temp;
	u8 high, low;
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
	temp_i = temp_f * 10;
}

void temp_display()
{
	rd_tempture();

	fmq_display(0, 0xc1); // U
	delay(200);
	fmq_display(0, 0xff);

	fmq_display(1, num_nodot[1]);
	delay(200);
	fmq_display(1, 0xff);

	fmq_display(5, num_nodot[temp_i / 100]);
	delay(200);
	fmq_display(5, 0xff);

	fmq_display(6, num_dot[temp_i / 10 % 10]);
	delay(200);
	fmq_display(6, 0xff);
		
	fmq_display(7, num_nodot[temp_i % 10]);
	delay(200);
	fmq_display(7, 0xff);

}

void ds1302_init()
{
	u8 i;
 	Write_Ds1302_Byte(0x8e, 0x00);
	for(i = 0; i < 7; i++)
	{
		Write_Ds1302_Byte(WRITE_RTC_ADDR[i], time[i]);	
	}
	Write_Ds1302_Byte(0x8e, 0x80);
}

void rd_ds1302()
{
	u8 i;
	for(i = 0; i < 7; i ++)
	{
		time[i] = Read_Ds1302_Byte(READ_RTC_ADDR[i]);		
	}
}

void ds1302_display_1()	// Ê±·Ö
{
	rd_ds1302();

	fmq_display(0, 0xc1); // U
	delay(200);
	fmq_display(0, 0xff);

	fmq_display(1, num_nodot[2]);
	delay(200);
	fmq_display(1, 0xff);

	fmq_display(3, num_nodot[time[2] / 16]);
	delay(200);
	fmq_display(3, 0xff);

	fmq_display(4, num_nodot[time[2] % 16]);
	delay(200);
	fmq_display(4, 0xff);

	fmq_display(5, 0xbf);
	delay(200);
	fmq_display(5, 0xff);

	fmq_display(6, num_nodot[time[1] / 16]);
	delay(200);
	fmq_display(6, 0xff);

	fmq_display(7, num_nodot[time[1] % 16]);
	delay(200);
	fmq_display(7, 0xff);
}

void ds1302_display_2() // ·ÖÃë
{
	rd_ds1302();

	fmq_display(0, 0xc1); // U
	delay(500);
	fmq_display(0, 0xff);

	fmq_display(1, num_nodot[2]);
	delay(500);
	fmq_display(1, 0xff);

	fmq_display(3, num_nodot[time[1] / 16]);
	delay(500);
	fmq_display(3, 0xff);

	fmq_display(4, num_nodot[time[1] % 16]);
	delay(500);
	fmq_display(4, 0xff);

	fmq_display(5, 0xbf);
	delay(500);
	fmq_display(5, 0xff);

	fmq_display(6, num_nodot[time[0] / 16]);
	delay(5000);
	fmq_display(6, 0xff);

	fmq_display(7, num_nodot[time[0] % 16]);
	delay(5000);
	fmq_display(7, 0xff);
}

void key_scan()
{
	c3 = c4 = r4 = 1;
	r3 = 0;
	if(c3 == 0)
	{
		delay(100);
		while(c3 == 0);
		key = 13;
		mode = !mode;
	}
	if(c4 == 0)
	{
		delay(100);
		while(c4 == 0);
		key = 17;
	}
	
	c3 = c4 = r3 = 1;
	r4 = 0;
	if(c3 == 0)
	{
		delay(100);
		while(c3 == 0);
		key = 12;
	}
	if(c4 == 0)
	{
		delay(100);
		while(c4 == 0);
		key = 16;
	}	
}

void set_param()
{
	key_scan();
	if (key == 16)	
	{
		if(param < 90)	
			param ++;
		key = 0;
	}
	if (key == 17)	
	{
		if(param > 10)
			param --;
		key = 0;
	}
}

void param_display()
{
	set_param();
	
	fmq_display(0, 0xc1); // U
	delay(500);
	fmq_display(0, 0xff);
	
	fmq_display(1, num_nodot[3]);
	delay(500);
	fmq_display(1, 0xff);
	
	fmq_display(6, num_nodot[param / 10]);
	delay(500);
	fmq_display(6, 0xff);
	
	fmq_display(7, num_nodot[param % 10]);
	delay(500);
	fmq_display(7, 0xff);		
}

void jdq_display()
{
	u8 temp1 = 0;
	if(mode == 0)
	{
		selete_hc138(4);
		P0 = 0xfd;
		delay(200);
		if ((temp_i / 10) >= param)
		{
			selete_hc138(5);
			P0 = 0x10;
		}
		else
		{
			selete_hc138(5);
			P0 = 0x00;	
		}
	}
	else
	{
		selete_hc138(4);
		P0 = 0xff;
		selete_hc138(5);
		P0 = 0x00;
		rd_ds1302();
		if(time[0] == 0 && time[1] == 0)
		{
			selete_hc138(5);
			P0 = 0x10;
			selete_hc138(4);
			P0 = 0xfe;
			delay(200);
			temp1 = 1;	
		}
		if(temp1 == 1 && (time[0] % 16) >= 5)
		{
			selete_hc138(5);
			P0 = 0x00;
			temp1 = 0;	
		}		
	}
	selete_hc138(4);
	P0 = 0xff;
}

u8 paper = 1;
void display_all()
{
	key_scan();
	
	if(key == 12)
	{
		paper ++;
		if(paper == 4)
			paper = 1;
		key = 0;
	}

	if(paper == 1)
	{
		temp_display();
	}

	if(paper == 2)
	{
		ds1302_display_1();
		c3 = c4 = r4 = 1;
		r3 = 0;
		if(c4 == 0)
		{
			delay(100);
			while(c4 == 0)
			{
				ds1302_display_2();
			}
		}
	}

	if(paper == 3)
	{
		param_display();
	}

	jdq_display();		
}

void dac_display(u16 dat)
{
	dat = Ad_Read(0x03);
	fmq_display(0, num_dot[dat / 100]);
	delay(500);
	fmq_display(0, 0xff);
	fmq_display(1, num_nodot[dat / 10 % 10]);	
	delay(500);
	fmq_display(1, 0xff);
	fmq_display(2, num_nodot[dat % 10]);	
	delay(500);
	fmq_display(2, 0xff);
}

void eeprom_display()
{
	EEPROM_Read(date, 0x01, 2);
	fmq_display(0, num_nodot[date[0]]);	
	delay(500);
	fmq_display(1, num_nodot[date[1]]);	
	delay(500);		
}
u8 temp[] = {1, 2};

void main()
{
	system_init();
	while(1)
	{
		
		//display_all();
		//dac_display();
		//EEPROM_Write(temp, 0x01, 2);
		u16 dac = 0;
		dac = Ad_Read(0x03);
		dac_display(dac / 51);
		Da_Write((5- dac) * 51);
	}
}