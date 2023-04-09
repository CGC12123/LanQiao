#ifndef _IIC_H
#define _IIC_H

#include "STC15F2K60S2.h"
#include "intrins.h"

sbit SDA_IIC = P2^1;
sbit SCL_IIC = P2^0;

void IIC_Start(void); 
void IIC_Stop(void);  
bit IIC_WaitAck(void);  
void IIC_SendAck(bit ackbit); 
void IIC_SendByte(unsigned char byt); 
unsigned char IIC_RecByte(void); 
unsigned int Ad_Read(unsigned char addr);
void Da_Write(unsigned char dat);
void EEPROM_Write(unsigned char * string, unsigned char addr, unsigned char num);
void EEPROM_Read(unsigned char* string, unsigned char addr, unsigned char num);


#endif