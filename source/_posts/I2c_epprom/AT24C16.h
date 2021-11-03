#ifndef AT24C16_H
#define AT24C16_H
#include <stdio.h>
#include "stm32f10x.h"
#include "iic.h"
 
#define AT24C16_WRITE_ADDR 0xA0
#define AT24C16_READ_ADDR  0xA1
 
void AT24C16_WriteOneByte(u8 data,u8 addr);
void AT24C16_ReadData(u16 addr,u16 len,char *p);
void AT24C16_WriteData(u16 addr,u16 len,u8 *p);
void AT24C16_PageWrite(u16 addr,u16 len,u8 *p);
 
#endif