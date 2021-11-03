#ifndef IIC_H
#define IIC_H
#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"
 
#define write 0
#define read  1
 
//IIC总线地址接口定义
#define IIC_SCL PBout(7)
#define IIC_SDA_OUT PBout(6)
#define IIC_SDA_IN PBin(6)
 
#define IIC_INPUT_MODE_SET()  {GPIOB->CRL&=0xF0FFFFFF;GPIOB->CRL|=0x08000000;}
#define IIC_OUTPUT_MODE_SET() {GPIOB->CRL&=0xF0FFFFFF;GPIOB->CRL|=0x03000000;}
 
//函数声明
void IIC_Init(void);
void IIC_START(void);
void IIC_STOP(void);
u8 IIC_GetACK(void);
void IIC_SendAck(u8 ack);
void IIC_WriteOneByte(u8 data);
u8 IIC_ReadOneByte(void);
#endif