#include<stm32f10x.h>
#include"bianma.h"
#include"delay.h"
//设置DIO为输入模式
void DIO_IN(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;       //上拉输入 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}
//设置DIO为输出模式
void DIO_OUT(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}
//SPI初始化
void SPI_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE);		     //开启总线时钟

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_Out_PP;    //推挽输出 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //输出的最大频率为50HZ
	GPIO_Init(GPIOA, &GPIO_InitStructure);	

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;       //上拉输入 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	CS(1);
	CLK(0);
	DIO(1);

}
//发送纯指令函数
void send_com(unsigned int com)
{
	unsigned int i;
	CS(1);
	delay_us(10);
	DIO_OUT();
	delay_us(10);
	CS(0);
	CLK(0);
	delay_us(50);
	for(i=8;i>0;i--)
	{
		if(com&(0x01<<(i-1)))
			DIO(1);
		else
			DIO(0);
		CLK(1);
		delay_us(10);
		CLK(0);
		delay_us(10);
	}
	CS(1);
}
//带数据指令操作函数
void send_datacom(unsigned int data,unsigned int com)
{
	unsigned int i,j;
	CS(1);
	delay_us(10);
	DIO_OUT();
	delay_us(10);
	CS(0);
	CLK(0);
	delay_us(50);
	for(i=8;i>0;i--)
	{
		if(com&(0x01<<(i-1)))
			DIO(1);
		else
			DIO(0);
		CLK(1);
		delay_us(10);
		CLK(0);
		if(i==0)
		delay_us(40);
		else
		delay_us(10);
	}
	for(j=8;j>0;j--)
	{
		if(data&(0x01<<(j-1)))
			DIO(1);
		else
			DIO(0);
		CLK(1);
		delay_us(10);
		CLK(0);
		delay_us(10);
	}
	delay_us(20);
	CS(1);		
}
//接受数据函数
unsigned int receive(unsigned int com)
{
	unsigned int i,j,rebuf;
	rebuf=0;
	CS(1);
	delay_us(10);
	DIO_OUT();
	delay_us(10);
	CS(0);
	CLK(0);
	delay_us(50);
	for(i=8;i>0;i--)
	{
		if(com&(0x01<<(i-1)))
			DIO(1);
		else
			DIO(0);
		CLK(1);
		delay_us(10);
		CLK(0);
		if(i==1)
		delay_us(30);
		else
		delay_us(10);
	}
	DIO_IN();
	for(j=8;j>0;j--)
	{
		CLK(1);
		delay_us(10);
		rebuf=rebuf<<1;
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2))
		rebuf|=1;
		else
		rebuf|=0;
		delay_us(10);
		CLK(0);
		delay_us(10);
	}
	DIO_OUT();
	delay_us(10);
	CS(1);
	return rebuf;
}

unsigned int  getkeycode(unsigned int dat)
{
	unsigned int key;
	switch(dat)
	{
		case 0x07: key = 0x01;break;
		case 0x0f: key = 0x02;break;
		case 0x17: key = 0x03;break;
		case 0x1f: key = 0x04;break;
		case 0x27: key = 0x05;break;
		case 0x2f: key = 0x06;break;
		case 0x37: key = 0x07;break;
		case 0x3f: key = 0x08;break;
		case 0x06: key = 0x09;break;
		case 0x0e: key = 0x0a;break;
		case 0x16: key = 0x0b;break;
		case 0x1e: key = 0x0c;break;
		case 0x26: key = 0x0d;break;
		case 0x2e: key = 0x0e;break;
		case 0x36: key = 0x0f;break;
		case 0x3e: key = 0x10;break;
		case 0x05: key = 0x11;break;
		case 0x0d: key = 0x12;break;
		case 0x15: key = 0x13;break;
		case 0x1d: key = 0x14;break;
		case 0x25: key = 0x15;break;
		case 0x2d: key = 0x16;break;
		case 0x35: key = 0x17;break;
		case 0x3d: key = 0x18;break;
		default:   key = 0xff;break;
	}
	return key;
}

//键盘驱动
// unsigned int Key=0xff;
// unsigned int dat=0;
// 	if(!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3))
// 	{			
// 		Key=receive(0x15);
// 		delay_us(10);
// 		if(!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3))
// 		{
// 			delay_us(10);
// 			while(!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3));	
// 			delay_us(10);
// 			dat=getkeycode(Key);
// 			printf("按键键值%d\r\n",dat);
// 		}
// 	}
//键盘驱动	
//}
// }	
/*编码键盘数码管*/
//while(1)
//{	
//	send_com(0xbf);
//	send_com(0xa4);
//	send_datacom(0x07,0x98);
//	send_datacom(0x01,0x80);
//	//delay_us(5);
//	send_datacom(0x02,0x81);
//	//delay_us(5);
//	send_datacom(0x03,0x82);
//	//delay_us(5);
//	send_datacom(0x04,0x83);
//	//delay_us(5);
//	send_datacom(0x05,0x84);
//	//delay_us(5);
//	send_datacom(0x06,0x85);
//	//delay_us(5);
//	send_datacom(0x07,0x86);
//	//delay_us(5);
//	send_datacom(0x08,0x87);
//	//delay_us(5);


/*编码键盘数码管*/


