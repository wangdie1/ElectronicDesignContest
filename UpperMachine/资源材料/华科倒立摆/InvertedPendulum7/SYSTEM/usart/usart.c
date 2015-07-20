#include "sys.h"
#include "usart.h"
#include "led.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK Mini STM32������
//����1��ʼ��		   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2010/5/27
//�汾��V1.3
//��Ȩ���У�����ؾ���
//Copyright(C) ����ԭ�� 2009-2019
//All rights reserved
//********************************************************************************
//V1.3�޸�˵�� 
//֧����Ӧ��ͬƵ���µĴ��ڲ���������.
//�����˶�printf��֧��
//�����˴��ڽ��������.
//������printf��һ���ַ���ʧ��bug
////////////////////////////////////////////////////////////////////////////////// 	  
volatile u8 IsUsartReceived=0;

//�������´���,֧��printf����,������Ҫѡ��use MicroLIB
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
_sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{      
	while((COM_USART->SR&0X40)==0);//ѭ������,ֱ���������   
    COM_USART->DR = (u8) ch;      
	return ch;
}
#endif 

/*ʹ��microLib�ķ���*/
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
 
u8 USART_RX_BUF[64]={0};     //���ջ���,���64���ֽ�.
//����״̬
//bit7��������ɱ�־
//bit6�����յ�0x0d
//bit5~0�����յ�����Ч�ֽ���Ŀ
u8 USART_RX_STA=0;       //����״̬���
u8 usart_rx_buf_num=0;
volatile float x,y;
float delta_x=-20;
extern int delta_inc;

void InitUSART(u32 bound)
{
    //GPIO�˿�����
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

   //Usart NVIC ����

    NVIC_InitStructure.NVIC_IRQChannel = COM_USART_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
		NVIC_Init(&NVIC_InitStructure);	//����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���USART1
  
   //USART ��ʼ������
   
		USART_InitStructure.USART_BaudRate = bound;//������
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		USART_InitStructure.USART_StopBits = USART_StopBits_1;
		USART_InitStructure.USART_Parity = USART_Parity_No;
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    USART_Init(COM_USART, &USART_InitStructure);

    USART_ITConfig(COM_USART, USART_IT_RXNE, ENABLE);//�����ж�
   
    USART_Cmd(COM_USART, ENABLE);                    //ʹ�ܴ��� 

}
// void USART2_IRQHandler(void)
// {
// 	u8 Res;
// 	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
// 		{
// 		Res =USART_ReceiveData(USART2);//(USART2->DR);	//��ȡ���յ�������
// 		
// 		if((USART_RX_STA&0x80)==0)//����δ���
// 			{
// 			if(USART_RX_STA&0x40)//���յ���0x0d
// 				{
// 				if(Res!=0x0a)USART_RX_STA=0;//���մ���,���¿�ʼ
// 				else USART_RX_STA|=0x80;	//��������� 
// 				}
// 			else //��û�յ�0X0D
// 				{	
// 				if(Res==0x0d)USART_RX_STA|=0x40;
// 				else
// 					{
// 					USART_RX_BUF[USART_RX_STA&0X3F]=Res ;
// 					USART_RX_STA++;
// 					if(USART_RX_STA>63)USART_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
// 					}		 
// 				}
// 			}   		 
//      } 
// }
void USART1_IRQHandler(void)                	//����1�жϷ������
	{
	u8 Res;
	u8 i;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
		{
// 			
			Res =USART_ReceiveData(USART1);//(USART1->DR);	//��ȡ���յ�������
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
// 		if((USART_RX_STA&0x80)==0)//����δ���
// 			{
// 				LED0_Toggle();
// 			if(USART_RX_STA&0x40)//���յ���0x0d
// 				{
// 						
// 						if(Res!=0x0a)USART_RX_STA=0;//���մ���,���¿�ʼ
// 						else USART_RX_STA|=0x80;	//��������� 
// 					
// 				}
// 			else //��û�յ�0X0D
// 				{	
// 						if(Res==0x0d)USART_RX_STA|=0x40;
// 						else
// 							{
// 							USART_RX_BUF[USART_RX_STA&0X3F]=Res ;
// 							USART_RX_STA++;
// 							if(USART_RX_STA>63)USART_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
// 							}		 
// 				}
// 			}   		 
    }
		
} 
