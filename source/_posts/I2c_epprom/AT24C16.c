#include "at24c16.h"
 
/*
函数功能:  AT24C16写一个字节
函数参数:
      data:写入的字节数据
      addr:存放位置(0~2048)
*/
 
void AT24C16_WriteOneByte(u8 data,u8 addr)
{
	IIC_START();
	IIC_WriteOneByte(AT24C16_WRITE_ADDR); //发送设备地址
	IIC_GetACK(); //获取应答
	IIC_WriteOneByte(addr);  //发送存放数据的地址
	IIC_GetACK(); //获取应答
	IIC_WriteOneByte(data);  //发送实际要存放的数据
	IIC_GetACK(); //获取应答
	IIC_STOP();   //发送停止信号
	DelayMs(10);  //等待写完成
}
 
/*
函数功能: 指定位置读取指定数量的数据
函数参数:
    addr: 从哪里开始读取数据
    len : 读取多长的数据
    *p  : 存放数据的缓冲区
编写程序对AT24C16第100页的第3个字节进行读数据的时候，步骤如下：
1）发送起始信号；
2）发送器件地址0XA6（1010 0110，1010是固定地址，011是页地址的高三位，0表示写操作）；
3）发送操作地址0X43（0100 0011，0100是页地址的低四位，0011是页地址偏移量，即第100页内的第三个字节，
4）发送要写的数据，
5）发送终止信号。
（对于AT24C02,直接写设备地址和数据地址）
*/
void AT24C16_ReadData(u16 addr,u16 len,char *p)
{
	u16 i;
	u8 page_addr,page_addr_H,Devicce_Write_Addr,Devicce_Read_Addr;
	page_addr=addr>>4;
	page_addr_H=page_addr>>5;
	Devicce_Write_Addr=AT24C16_WRITE_ADDR + (page_addr_H<<1);
	Devicce_Read_Addr=AT24C16_READ_ADDR+(page_addr_H<<1);
//	printf("Devicce_Write_Addr = 0x%X \n Devicce_Read_Addr = 0x%X \n addr =0x%X \n",Devicce_Write_Addr,Devicce_Read_Addr,addr&0xFF);
	IIC_START();
	IIC_WriteOneByte(Devicce_Write_Addr); //发送设备地址(写)
	IIC_GetACK(); //获取应答
	IIC_WriteOneByte(addr&0xFF); //发送存放数据的地址(即将读取数据的地址)
	IIC_GetACK(); //获取应答
	IIC_START();
	IIC_WriteOneByte(Devicce_Read_Addr); //发送设备地址(读)
	IIC_GetACK(); //获取应答
 
	for(i=0;i<len;i++)
	{
			p[i]=IIC_ReadOneByte(); //接收数据
			IIC_SendAck(0);  //给从机发送应答
	}
	IIC_SendAck(1);  //给从机发送非应答
	IIC_STOP();      //停止信号
} 
 
 
/*
函数功能: 指定位置写入指定数量的数据
函数参数:
    addr: 从哪里开始写数据
    len : 写入多长的数据
    *p  : 存放数据的缓冲区
*/
void AT24C16_WriteData(u16 addr,u16 len,u8 *p)
{
   u8 page_remain=16-addr%16; //得到当前页剩余的字节数量
   if(page_remain>=len)
   {
      page_remain=len;
   }
   while(1)
   {
       AT24C16_PageWrite(addr,page_remain,p);
       if(page_remain==len)break;
       addr+=page_remain;
       p+=page_remain;
       len-=page_remain;
       if(len>=16)page_remain=16;
       else page_remain=len;
   }
}
 
/*
函数功能:  AT24C16页写函数
函数参数:
    addr: 从哪里开始写数据
    len : 写入多长的数据
    *p  : 存放数据的缓冲区
说明: AT24C16内部有一个页写缓冲器,页地址超出之后会复位到当前页的起始地址。
AT24C16页缓冲器大小:  16个字节
编写程序对AT24C16第100页的第3个字节进行写数据的时候，步骤如下：
1）发送起始信号；
2）发送器件地址0XA6（1010 0110，1010是固定地址，011是页地址的高三位，0表示写操作）；
3）发送操作地址0X43（0100 0011，0100是页地址的低四位，0011是页地址偏移量，即第100页内的第三个字节，
4）发送要写的数据，
5）发送终止信号。
（对于AT24C02,直接写设备地址和数据地址）
*/
void AT24C16_PageWrite(u16 addr,u16 len,u8 *p)
{
	u8 i;
	u8 page_addr,page_addr_H,Devicce_Write_Addr,Devicce_Read_Addr;
	page_addr=addr>>4;
	page_addr_H=page_addr>>5;
	Devicce_Write_Addr=AT24C16_WRITE_ADDR + (page_addr_H<<1);
	Devicce_Read_Addr=AT24C16_READ_ADDR+(page_addr_H<<1);
	printf("Devicce_Write_Addr = 0x%X \n Devicce_Read_Addr = 0x%X \n addr =0x%X \n",Devicce_Write_Addr,Devicce_Read_Addr,addr&0xFF);
	IIC_START();
	IIC_WriteOneByte(Devicce_Write_Addr); //发送设备地址
	IIC_GetACK(); //获取应答
	IIC_WriteOneByte(addr&0xFF);  //发送存放数据的地址
	IIC_GetACK(); //获取应答
	for(i=0;i<len;i++)
	{
		 IIC_WriteOneByte(p[i]);  //发送实际要存放的数据
		 IIC_GetACK(); //获取应答
	}
	IIC_STOP();   //发送停止信号
	DelayMs(10);  //等待写完成
}
 