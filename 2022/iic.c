#include "iic.h"

#define DELAY_TIME 5

//I2C总线内部延时函数
void IIC_Delay(unsigned char i)
{
    do{_nop_();}
    while(i--);        
}

//I2C总线启动信号
void IIC_Start(void)
{
    SDA_IIC = 1;
    SCL_IIC = 1;
    IIC_Delay(DELAY_TIME);
    SDA_IIC = 0;
    IIC_Delay(DELAY_TIME);
    SCL_IIC = 0;	
}

//I2C总线停止信号
void IIC_Stop(void)
{
    SDA_IIC = 0;
    SCL_IIC = 1;
    IIC_Delay(DELAY_TIME);
    SDA_IIC = 1;
    IIC_Delay(DELAY_TIME);
}

//发送应答或非应答信号
void IIC_SendAck(bit ackbit)
{
    SCL_IIC = 0;
    SDA_IIC = ackbit;  					
    IIC_Delay(DELAY_TIME);
    SCL_IIC = 1;
    IIC_Delay(DELAY_TIME);
    SCL_IIC = 0; 
    SDA_IIC = 1;
    IIC_Delay(DELAY_TIME);
}

//等待应答
bit IIC_WaitAck(void)
{
    bit ackbit;
	
    SCL_IIC = 1;
    IIC_Delay(DELAY_TIME);
    ackbit = SDA_IIC;
    SCL_IIC = 0;
    IIC_Delay(DELAY_TIME);
    return ackbit;
}

//I2C总线发送一个字节数据
void IIC_SendByte(unsigned char byt)
{
    unsigned char i;

    for(i=0; i<8; i++)
    {
        SCL_IIC  = 0;
        IIC_Delay(DELAY_TIME);
        if(byt & 0x80) SDA_IIC  = 1;
        else SDA_IIC  = 0;
        IIC_Delay(DELAY_TIME);
        SCL_IIC = 1;
        byt <<= 1;
        IIC_Delay(DELAY_TIME);
    }
    SCL_IIC  = 0;  
}

//I2C总线接收一个字节数据
unsigned char IIC_RecByte(void)
{
    unsigned char i, da;
    for(i=0; i<8; i++)
    {   
    	SCL_IIC = 1;
	IIC_Delay(DELAY_TIME);
	da <<= 1;
	if(SDA_IIC) da |= 1;
	SCL_IIC = 0;
	IIC_Delay(DELAY_TIME);
    }
    return da;    
}


unsigned int Ad_Read(unsigned char addr)
{
	unsigned int temp;
	IIC_Start();
	IIC_SendByte(0x90);
	IIC_WaitAck();
	IIC_SendByte(addr);
	IIC_WaitAck();

	IIC_Start();
	IIC_SendByte(0x91);
	IIC_WaitAck();

	temp = IIC_RecByte();
	IIC_SendAck(1);
	IIC_Stop();

	return temp;
}


unsigned char ad_read(unsigned char addr)		/////////////
{
	unsigned char temp;
	IIC_Start();

	IIC_SendByte(0x90);
	IIC_WaitAck();
	
	IIC_SendByte(addr);
	IIC_WaitAck();
	
	IIC_Start();
	IIC_SendByte(0x91);
	IIC_WaitAck();
	
	temp = IIC_RecByte();
	IIC_SendAck(1);

	IIC_Stop();					   
	return temp;
}

void Da_Write(unsigned char dat)
{
	IIC_Start();
	IIC_SendByte(0x90);
	IIC_WaitAck();

	IIC_SendByte(0x41);//使能
	IIC_WaitAck();

	IIC_SendByte(dat);
	IIC_WaitAck();
	
	IIC_Stop();
}

void da_write(unsigned char dat)   //////////////////////
{
	IIC_Start();
	IIC_SendByte(0x90);
	IIC_WaitAck();	

	IIC_SendByte(0x41);//使能
	IIC_WaitAck();

	IIC_SendByte(dat);
	IIC_WaitAck();
	
	IIC_Stop();
}


void EEPROM_Write(unsigned char * string, unsigned char addr, unsigned char num)
{
	IIC_Start();
	IIC_SendByte(0xA0);
	IIC_WaitAck();
	
	IIC_SendByte(addr);
	IIC_WaitAck();
	
	while(num --)
	{
		IIC_SendByte(*string ++); 
		IIC_WaitAck();
		IIC_Delay(200);	
	}	
	IIC_Stop();
}

void eeprom_write(unsigned char * str, unsigned char addr, unsigned char num)  ///////////////////
{
	IIC_Start();
	IIC_SendByte(0xA0);
	IIC_WaitAck();

	IIC_SendByte(addr);
	IIC_WaitAck();

	while(num --)
	{
		IIC_SendByte(*string ++); 
		IIC_WaitAck();
		IIC_Delay(200);	 
	}
	IIC_Stop();
}

void EEPROM_Read(unsigned char* string, unsigned char addr, unsigned char num)
{
	IIC_Start();
	IIC_SendByte(0xA0);
	IIC_WaitAck();
	
	IIC_SendByte(addr);
	IIC_WaitAck();
	
	IIC_Start();
	IIC_SendByte(0xA1);
	IIC_WaitAck();	

	while(num --)
	{
		*string ++ = IIC_RecByte();
		if(num)
		{
			IIC_SendAck(0);	
		}
		else
		{
			IIC_SendAck(1);
		}
	}
	IIC_Stop();
}

void eeprom_read(unsigned char * str, unsigned char addr, unsigned char num) ////////////////////////
{
	IIC_Start();

	IIC_SendByte(0xA0);
	IIC_WaitAck();

	IIC_SendByte(addr);
	IIC_WaitAck();

	IIC_SendByte(0xA1);
	IIC_WaitAck();

	while(num --)
	{
		*str ++ = IIC_RecByte();
		if(num)
		{
			IIC_SendAck(0);	
		}
		else
		{
			IIC_SendAck(1);	
		}
	}
	IIC_Stop();
}