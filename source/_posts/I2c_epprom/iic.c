#include "iic.h"
#include "stdio.h"
/*
函数功能: IIC总线初始化
硬件连接:
        SCL-PB7
        SDA-PB6
*/
void IIC_Init(void)
{
	/*1. 开时钟*/
	RCC->APB2ENR|=1<<3; //PB
	RCC->APB2ENR|=1<<0; //开启AFIO时钟
	
	/*2. 配置模式*/
//	AFIO->MAPR |= 0x2<<24;//关闭JTAG-DP,启用SW-DP
	GPIOB->CRL&=0x00FFFFFF;
	GPIOB->CRL|=0x33000000;
	
	/*3. 上拉*/
	GPIOB->ODR|=0x1<<6;
	printf("IIC_Init OK!\n");
}
 
 
/*
函数功能: 起始信号
*/
void IIC_START(void)
{
        IIC_OUTPUT_MODE_SET(); //配置输出模式
	IIC_SDA_OUT = 1;       //拉高数据线
	IIC_SCL = 1;           //拉高时钟线
	DelayUs(2);            //延时
	IIC_SDA_OUT = 0;       //产生下降沿
	DelayUs(2);            //延时
	IIC_SCL = 0;           //拉低时钟线//告诉从机,通信开始(主机将要给从机发送数据)。
}

/*
函数功能: 停止信号
*/
void IIC_STOP(void)
{
        IIC_OUTPUT_MODE_SET(); 	//配置输出模式
	IIC_SDA_OUT = 0;        //拉低数据线
	IIC_SCL = 1;            //拉高时钟线
	DelayUs(2);             //延时
	IIC_SDA_OUT = 1;        //产生上升沿
	DelayUs(2);             //延时
}
 
/*
函数功能:  获取从机发给主机的应答
返回值  :  0表示获取成功,1表示获取失败
目的: 读取总线上一位数据的值。这一位数据的正确值0
*/
u8 IIC_GetACK(void)
{
    u8 cnt=0;
    IIC_INPUT_MODE_SET(); //输入模式
    IIC_SDA_OUT=1; //上拉
    IIC_SCL=0; //告诉从机主机需要数据
    DelayUs(2);
    IIC_SCL=1; //告诉从机主机正在读数据
    while(IIC_SDA_IN) //等待应答
    {
        cnt++;
        DelayUs(1);
        if(cnt>=250)//等待时间过长，产生停止信号，返回1，表示接收应答失败
	{
		IIC_STOP();
		//printf("N0 ACK\n");
		return 1;
	}
    }
    IIC_SCL=0; //告诉从机，主机准备发送数据
    return 0;
}
 
 
/*
函数功能: 主机给从机发送应答
函数参数: 1(非应答) 0(应答)
目的: 发送一位数据
*/
void IIC_SendAck(u8 ack)
{
	IIC_OUTPUT_MODE_SET(); 	//配置输出模式
	IIC_SCL = 0;              //拉低时钟线，告诉从机，主机将要发送数据
	if(ack) IIC_SDA_OUT = 1; 
	else IIC_SDA_OUT = 0;     //写应答信号
	DelayUs(2);               //延时
	IIC_SCL = 1;              //拉高时钟线
	DelayUs(2);               //延时
	IIC_SCL = 0;              //拉低时钟线
}
 
 
/*
函数功能:  发送一个字节数据
函数参数:  data将要发送数据
*/
void IIC_WriteOneByte(u8 data)
{
	u8 i;
	IIC_OUTPUT_MODE_SET();
	IIC_SCL = 0;	    //拉低时钟线, 数据准备发送
	DelayUs(2);		    //延时
	for(i=0;i<8;i++)    //从高位开始一位一位地传送
	{
		if(data&0x80)IIC_SDA_OUT=1;//送数据口
		else IIC_SDA_OUT=0;
		data<<=1;//移出数据的最高位
		IIC_SCL=1;//拉高时钟线,发送数据
		DelayUs(2);
		IIC_SCL=0;//拉低时钟线，数据发送完毕
		DelayUs(2);
	}
}
 
/*
函数功能:  读取一个字节数据
返回值  :  读取成功的数据
*/
u8 IIC_ReadOneByte(void)
{
    u8 data=0,i=0;
    IIC_INPUT_MODE_SET();//使能内部上拉,准备读取数据
    for(i=0;i<8;i++)
    {
        IIC_SCL=0;//置时钟线为低，准备接收数据位
        DelayUs(2);//时钟低电平周期大于4.7μs
        IIC_SCL=1;//置时钟线为高使数据线上数据有效，主机开始读数据，从机不能再改变数据了，即改变SDA的电平
        data<<=1;
        if(IIC_SDA_IN)data|=0x01;//读数据 
        DelayUs(2);
    }
    IIC_SCL=0;
    return data;
}
 