# include "STC15F2K60S2.h"
# include "ds1302.h"


typedef unsigned char u8;
typedef unsigned int u16;

sbit HC138_A = P2^5;
sbit HC138_B = P2^6;
sbit HC138_C = P2^7;

u8 code SMG_NoDot[18] = 
    {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x88,0x80,0xc6,0xc0,0x86,0x8e,0xbf,0x7f};

u8 code READ_RTC_ADDR[7] = {0x81, 0x83, 0x85, 0x87, 0x89, 0x8b, 0x8d};
u8 code WRITE_RTC_ADDR[7] = {0x80, 0x82, 0x84, 0x86, 0x88, 0x8a, 0x8c};

u8 time[7] = {0x30, 0x50, 0x23, 0x17, 0x02, 0x06, 0x18};

void delay(u8 t)
{
	while(t --);
}

void selete_hc138(u8 n)
{
	switch(n)
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

void system_init()
{
//	selete_hc138(5);
//	P0 = 0x00;
	selete_hc138(4);
	P0 = 0xff;
	selete_hc138(0);
	P0 = 0x00;	
}

void display_smg(u8 pos, u8 num)
{
	selete_hc138(6);
	P0 = (0x01 << pos);
	selete_hc138(7);
	P0 = num;
}

void ds1302_config()
{
	u8 n;
	Write_Ds1302_Byte(0x8e, 0x00); // 解除保护
	for(n = 0; n < 7; n ++)
	{
		Write_Ds1302_Byte(WRITE_RTC_ADDR[n], time[n]);
	}
	Write_Ds1302_Byte(0x8e, 0x80); // 保护
}

void rd_ds1302()
{
	u8 n;
	for(n = 0; n < 7; n ++)
	{
		time[n] = Read_Ds1302_Byte(READ_RTC_ADDR[n]);	
	}
}

void smg_test()
{
	display_smg(0, SMG_NoDot[0]);
	delay(200);
	display_smg(0, 0xff);
	delay(200);			
}

void SMG_All(unsigned char dat)
{
 	P0 = 0xff;
	selete_hc138(6);
	P0 = dat;
	selete_hc138(7);
}

void time_show()
{
	u8 i;
	for(i = 0; i < 9; i ++)
	{
		display_smg(0, SMG_NoDot[time[2] / 16]);
		delay(500);
		display_smg(0, 0xff);
		delay(500);

		display_smg(1, SMG_NoDot[time[2] % 16]);
		delay(500);
		display_smg(1, 0xff);
		delay(500);

		display_smg(2, SMG_NoDot[16]);
		delay(500);
		display_smg(2, 0xff);
		delay(500);

		display_smg(3, SMG_NoDot[time[1] / 16]);
		delay(500);
		display_smg(3, 0xff);
		delay(500);

		display_smg(4, SMG_NoDot[time[1] % 16]);
		delay(500);
		display_smg(4, 0xff);
		delay(500);

		display_smg(5, SMG_NoDot[16]);
		delay(500);
		display_smg(5, 0xff);
		delay(500);

		display_smg(6, SMG_NoDot[time[0] / 16]);
		delay(500);
		display_smg(6, 0xff);
		delay(500);

		display_smg(7, SMG_NoDot[time[0] % 16]);
		delay(500);
		display_smg(7, 0xff);
		delay(500);

		SMG_All(0xff);
		delay(5000);
	}
}



void main()
{
	system_init();
	ds1302_config();
	while(1)
	{
		// smg_test();
		rd_ds1302();
		time_show();	
	}							  
}