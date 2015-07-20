#include "sys.h"
#include "usart.h"
#include "led.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK Mini STM32开发板
//串口1初始化		   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2010/5/27
//版本：V1.3
//版权所有，盗版必究。
//Copyright(C) 正点原子 2009-2019
//All rights reserved
//********************************************************************************
//V1.3修改说明 
//支持适应不同频率下的串口波特率设置.
//加入了对printf的支持
//增加了串口接收命令功能.
//修正了printf第一个字符丢失的bug
////////////////////////////////////////////////////////////////////////////////// 	  
volatile u8 IsUsartReceived=0;

//加入以下代码,支持printf函数,而不需要选择use MicroLIB
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
_sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while((COM_USART->SR&0X40)==0);//循环发送,直到发送完毕   
    COM_USART->DR = (u8) ch;      
	return ch;
}
#endif 

/*使用microLib的方法*/
 /* 
int fputc(int ch, FILE *f)
{
	USART_SendData(USART1, (uint8_t) ch);

	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) {}	
   
    return ch;
}
int GetKey (void)  { 

    while (!(USART1->SR & USART_FLAG_RXNE));

    return ((int)(USART1->DR & 0x1FF));
}
*/
 
u8 USART_RX_BUF[64]={0};     //接收缓冲,最大64个字节.
//接收状态
//bit7，接收完成标志
//bit6，接收到0x0d
//bit5~0，接收到的有效字节数目
u8 USART_RX_STA=0;       //接收状态标记
u8 usart_rx_buf_num=0;
volatile float x,y;
float delta_x=-20;
extern int delta_inc;

void InitUSART(u32 bound)
{
    //GPIO端口设置
		GPIO_InitTypeDef GPIO_InitStructure;
		USART_InitTypeDef USART_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;
	 
		if(COM_USART==USART1)//
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);
		else
		{
			RCC_APB2PeriphClockCmd(COM_USART_PORT_CLK|RCC_APB2Periph_AFIO,ENABLE);
			RCC_APB1PeriphClockCmd(COM_USART_CLK,ENABLE);
		}
		
     //USART_TX   
    GPIO_InitStructure.GPIO_Pin = COM_USART_TX_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(COM_USART_PORT, &GPIO_InitStructure);
   
    //USART_RX	
    GPIO_InitStructure.GPIO_Pin = COM_USART_RX_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(COM_USART_PORT, &GPIO_InitStructure);  

   //Usart NVIC 配置

    NVIC_InitStructure.NVIC_IRQChannel = COM_USART_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
		NVIC_Init(&NVIC_InitStructure);	//根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器USART1
  
   //USART 初始化设置
   
		USART_InitStructure.USART_BaudRate = bound;//波特率
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		USART_InitStructure.USART_StopBits = USART_StopBits_1;
		USART_InitStructure.USART_Parity = USART_Parity_No;
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    USART_Init(COM_USART, &USART_InitStructure);

    USART_ITConfig(COM_USART, USART_IT_RXNE, ENABLE);//开启中断
   
    USART_Cmd(COM_USART, ENABLE);                    //使能串口 

}
// void USART2_IRQHandler(void)
// {
// 	u8 Res;
// 	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
// 		{
// 		Res =USART_ReceiveData(USART2);//(USART2->DR);	//读取接收到的数据
// 		
// 		if((USART_RX_STA&0x80)==0)//接收未完成
// 			{
// 			if(USART_RX_STA&0x40)//接收到了0x0d
// 				{
// 				if(Res!=0x0a)USART_RX_STA=0;//接收错误,重新开始
// 				else USART_RX_STA|=0x80;	//接收完成了 
// 				}
// 			else //还没收到0X0D
// 				{	
// 				if(Res==0x0d)USART_RX_STA|=0x40;
// 				else
// 					{
// 					USART_RX_BUF[USART_RX_STA&0X3F]=Res ;
// 					USART_RX_STA++;
// 					if(USART_RX_STA>63)USART_RX_STA=0;//接收数据错误,重新开始接收	  
// 					}		 
// 				}
// 			}   		 
//      } 
// }
void USART1_IRQHandler(void)                	//串口1中断服务程序
	{
	u8 Res;
	u8 i;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
		{
// 			
			Res =USART_ReceiveData(USART1);//(USART1->DR);	//读取接收到的数据
			USART_RX_BUF[usart_rx_buf_num]=Res-'0';
			usart_rx_buf_num++;
// 			if((Res==';')&(usart_rx_buf_num==9))
				if(Res==';')
			{
			
				if(usart_rx_buf_num==9)
				{
					x=(USART_RX_BUF[0]*1000+USART_RX_BUF[1]*100+USART_RX_BUF[2]*10+(float)USART_RX_BUF[3])+delta_x;
					y=(USART_RX_BUF[4]*1000+USART_RX_BUF[5]*100+USART_RX_BUF[6]*10+(float)USART_RX_BUF[7]);
				  IsUsartReceived=1;
				}
					usart_rx_buf_num=0;
			}
			
// 			if(Res==';')//x
// 			{	
// 				LED0_Toggle();
// 			
// 					x=USART_RX_BUF[0]*1000+USART_RX_BUF[1]*100+USART_RX_BUF[2]
// 		
// 				usart_rx_buf_num=0;
// 				IsUsartReceived=1;
// 				
// 			}
// 			if(Res==',')
// 			{	
// 				LED0_Toggle();
// 				usart_rx_buf_num=0;
// 				IsUsartReceived=2;
// 			}
// 		if((USART_RX_STA&0x80)==0)//接收未完成
// 			{
// 				LED0_Toggle();
// 			if(USART_RX_STA&0x40)//接收到了0x0d
// 				{
// 						
// 						if(Res!=0x0a)USART_RX_STA=0;//接收错误,重新开始
// 						else USART_RX_STA|=0x80;	//接收完成了 
// 					
// 				}
// 			else //还没收到0X0D
// 				{	
// 						if(Res==0x0d)USART_RX_STA|=0x40;
// 						else
// 							{
// 							USART_RX_BUF[USART_RX_STA&0X3F]=Res ;
// 							USART_RX_STA++;
// 							if(USART_RX_STA>63)USART_RX_STA=0;//接收数据错误,重新开始接收	  
// 							}		 
// 				}
// 			}   		 
    }
		
} 
