#include "reg52.h"  
#include "intrins.h"

sbit HC138_A = P2^5;        
sbit HC138_B = P2^6;        
sbit HC138_C = P2^7;        

sbit SCLK = P1^7; 
sbit RST =  P1^3; 
sbit DSIO = P2^3;
unsigned char code READ_RTC_ADDR[7] = {0x81, 0x83, 0x85, 0x87, 0x89, 0x8b, 0x8d};
unsigned char code WRITE_RTC_ADDR[7] = {0x80, 0x82, 0x84, 0x86, 0x88, 0x8a, 0x8c};
unsigned char TIME[7] = {0x30, 0x50, 0x23, 0x17, 0x02, 0x06, 0x18};

unsigned char code SMG_NoDot[18] = 
    {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,
     0x80,0x90,0x88,0x80,0xc6,0xc0,0x86,0x8e,
     0xbf,0x7f};

void DelaySMG(unsigned int time)
{
        while(time--);
}

void Init74HC138(unsigned char n)
{
        switch(n)
        {
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
                case 8:
                        HC138_A = 0;
                        HC138_B = 0;
                        HC138_C = 0;
                        break;
        }
}
void Init()
{
	Init74HC138(5);
	P0 = 0x00;
	Init74HC138(4);
	P0 = 0xff;
}
void DispaySMG_Bit(unsigned char value, unsigned char pos)
{
        Init74HC138(6);
        P0 = (0x01 << pos);
        Init74HC138(7);
        P0 = value;
}

void DS1302_WriteByte(unsigned char addr, unsigned char dat)
{
        unsigned char n;
        RST = 0;
        _nop_();
        SCLK = 0;
        _nop_();
        RST = 1;
        _nop_();        

        for (n=0; n<8; n++)
        {
                DSIO = addr & 0x01;
                addr >>= 1;
                SCLK = 1;
                _nop_();
                SCLK = 0;
                _nop_();
        }
        for (n=0; n<8; n++)
        {
                DSIO = dat & 0x01;
                dat >>= 1;
                SCLK = 1;
                _nop_();
                SCLK = 0;
                _nop_();
        }                 
        RST = 0;
        _nop_();
}

unsigned char DS1302_ReadByte(unsigned char addr)
{
        unsigned char n,dat,tmp;
        RST = 0;
        _nop_();
        SCLK = 0;
        _nop_();
        RST = 1;
        _nop_();

        for(n=0; n<8; n++)
        {
                DSIO = addr & 0x01;
                addr >>= 1;
                SCLK = 1;
                _nop_();
                SCLK = 0;
                _nop_();
        }
        
        for(n=0; n<8; n++)
        {
                tmp = DSIO;
                dat = (dat>>1) | (tmp<<7);
                SCLK = 1;
                _nop_();
                SCLK = 0;
                _nop_();
        }

        RST = 0;
        _nop_();
        SCLK = 1;
        _nop_();
        DSIO = 0;
        _nop_();
        DSIO = 1;
        _nop_();
        return dat;        
}

void DS1302_Config()
{
        unsigned char n;
        DS1302_WriteByte(0x8E,0x00); 
        for (n=0; n<7; n++) 
        {
                DS1302_WriteByte(WRITE_RTC_ADDR[n],TIME[n]);        
        }
        DS1302_WriteByte(0x8E,0x80); 
}

void DS1302_ReadTime()
{
        unsigned char n;
        for (n=0; n<7; n++) 
        {
                TIME[n] = DS1302_ReadByte(READ_RTC_ADDR[n]);
        }                
}

void XMF_ShowRealTime()
{

        DispaySMG_Bit(SMG_NoDot[TIME[2]/16],0);        
        DelaySMG(500);
        DispaySMG_Bit(0xff,0);                        
        DispaySMG_Bit(SMG_NoDot[TIME[2]&0x0f],1);
        DelaySMG(500);
        DispaySMG_Bit(0xff,1);
        DispaySMG_Bit(SMG_NoDot[16],2);
        DelaySMG(500);
        DispaySMG_Bit(0xff,2);

        DispaySMG_Bit(SMG_NoDot[TIME[1]/16],3);
        DelaySMG(500);
        DispaySMG_Bit(0xff,3);
        DispaySMG_Bit(SMG_NoDot[TIME[1]&0x0f],4);
        DelaySMG(500);
        DispaySMG_Bit(0xff,4);
        DispaySMG_Bit(SMG_NoDot[16],5);
        DelaySMG(500);
        DispaySMG_Bit(0xff,5);

        DispaySMG_Bit(SMG_NoDot[TIME[0]/16],6);
        DelaySMG(500);
        DispaySMG_Bit(0xff,6);
        DispaySMG_Bit(SMG_NoDot[TIME[0]&0x0f],7);
        DelaySMG(500);
        DispaySMG_Bit(0xff,7);
}

main()
{
        Init();
		DS1302_Config();
        while(1)
        {
                DS1302_ReadTime();
                XMF_ShowRealTime();
        }
}