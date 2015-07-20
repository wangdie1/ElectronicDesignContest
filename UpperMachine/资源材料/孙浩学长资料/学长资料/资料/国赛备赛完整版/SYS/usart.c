/*Ƕ��ʽ��԰stm32����ͨ�Ŵ���⺯����1.0�汾 ����֮��ϣ��ͬѧ�ǿ��Զ���޸ģ�ʹ�����
�����ơ�
���� ��� 2013.4.1 */
/*
USART1   TX:PA9  RX:PA10
USART2	 TX:PA2  RX:PA3
USART3	 TX:PB10  RX:PB11
UART4	 TX:PC10  RX:C11
UART5	 TX:PC12  RX:PD2
*/

#include<stm32f10x.h>
#include"usart.h"
#include<stdio.h>

//����������һ�����ڿ���ʹ��printf��������Ϊprintf��������ʹ��һ������
//Use_Printf     ��ʾʹ��printf���
//Nonuse_Printf	 ��ʾ��ʹ��printf���
# define _usart1_  1    
# define _usart2_  0
# define _usart3_  0
# define _usart4_  0
# define _usart5_  0

//�����ж��յ�����
unsigned char Rec_Dat_U1=0;
unsigned char Rec_Dat_U2=0;
unsigned char Rec_Dat_U3=0;
unsigned char Rec_Dat_U4=0;
unsigned char Rec_Dat_U5=0;


void Usart_Init(usart_type x)
{

   switch(x)
    {
  	case (usart1) :usart1_init();   break;
	  case (usart2) :usart2_init();   break;
	  case (usart3) :usart3_init();   break;
	  case (uart4 ) :uart4_init( );   break;
  	case (uart5 ) :uart5_init( );   break;
    }
   	//NVIC_Configuration();

}


void usart1_init()
{
  USART_InitTypeDef USART_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO|RCC_APB2Periph_USART1,  ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin =GPIO_Pin_10 ;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity =  USART_Parity_No ;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
   
  USART_Init(USART1, &USART_InitStructure);
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
  USART_Cmd(USART1, ENABLE);

}

void usart2_init()
{
  USART_InitTypeDef USART_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO,  ENABLE);
  RCC_APB1PeriphClockCmd( RCC_APB1Periph_USART2,  ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin =GPIO_Pin_3 ;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  USART_InitStructure.USART_BaudRate = 9600;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity =  USART_Parity_No ;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
   
  USART_Init(USART2, &USART_InitStructure);
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
  USART_Cmd(USART2, ENABLE);
}

void usart3_init()
{

  USART_InitTypeDef USART_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,  ENABLE);
  RCC_APB1PeriphClockCmd( RCC_APB1Periph_USART3,  ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  
  GPIO_InitStructure.GPIO_Pin =GPIO_Pin_11 ;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  USART_InitStructure.USART_BaudRate = 9600;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity =  USART_Parity_No ;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
   
  USART_Init(USART3, &USART_InitStructure);
  USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
  USART_Cmd(USART3, ENABLE);
}

void uart4_init()
{
  USART_InitTypeDef USART_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO,  ENABLE);
  RCC_APB1PeriphClockCmd( RCC_APB1Periph_UART4,  ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  
  GPIO_InitStructure.GPIO_Pin =GPIO_Pin_11 ;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  USART_InitStructure.USART_BaudRate = 9600;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity =  USART_Parity_No ;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
   
  USART_Init(UART4, &USART_InitStructure);
  USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);
  USART_Cmd(UART4, ENABLE);

}

void uart5_init()
{
  USART_InitTypeDef USART_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO,  ENABLE);
  RCC_APB1PeriphClockCmd( RCC_APB1Periph_UART5,  ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  
  GPIO_InitStructure.GPIO_Pin =GPIO_Pin_2 ;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

  USART_InitStructure.USART_BaudRate = 9600;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity =  USART_Parity_No ;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
   
  USART_Init(UART5, &USART_InitStructure);
  USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);
  USART_Cmd(UART5, ENABLE);

}


int fputc(int ch,FILE*f)	
{

#if _usart1_
   	   USART_SendData( USART1,(unsigned char) ch);
	   while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
#elif _usart2_
	   USART_SendData( USART2,(unsigned char) ch);
	   while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
#elif _usart3_
	   USART_SendData( USART3,(unsigned char) ch);
	   while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
#elif _uart4_
	   USART_SendData( UART4,(unsigned char) ch);
	   while(USART_GetFlagStatus(UART4, USART_FLAG_TXE) == RESET);
#elif _uart5_
	   USART_SendData( UART5,(unsigned char) ch);
	   while(USART_GetFlagStatus(UART5, USART_FLAG_TXE) == RESET);
#endif
       return ch;

}






void usart_sent_char(USART_TypeDef* USARTx,char ch )
{
      
	   USART_SendData( USARTx,(unsigned char) ch);
	   while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);
	   USART_ClearFlag(USARTx, USART_FLAG_TXE);
} 


void usart_sent_string(USART_TypeDef* USARTx,char *ch)
{
  while(*ch!='\0')
  {
  usart_sent_char( USARTx,*ch );
   ch++;
  
  }
}


void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  /*����������Ӧ���ȼ�����ռʽ���ȼ�����GROUP3��3λ����ռʽ���ȼ�1λ����Ӧʽ���ȼ�*/  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  /*��Ӧ���ȼ��������������ȼ�ֻ�ܵȴ��������ȼ����꣬
  ��������������ͬʱ��Ӧ��������Ӧ�����ȼ��� */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

      

  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);


  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
   

  NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
   

  NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);  
    

}


void USART1_IRQHandler(void)
{ 
  
  if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
   {
    Rec_Dat_U1= USART_ReceiveData(USART1);

   }
  	  
}


void USART2_IRQHandler(void)
{ 
  
  if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
   {
    Rec_Dat_U2= USART_ReceiveData(USART2);
   }
  	  
}


void USART3_IRQHandler(void)
{ 
  
  if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
   {
    Rec_Dat_U3= USART_ReceiveData(USART3);
   

   }
  	  
}


void UART4_IRQHandler(void)
{ 
  
  if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)
   {
    Rec_Dat_U4= USART_ReceiveData(UART4);
   }
  	  
}


void UART5_IRQHandler(void)
{ 
  
  if(USART_GetITStatus(UART5, USART_IT_RXNE) != RESET)
   {
    Rec_Dat_U5= USART_ReceiveData(UART5);
   }
  	  
}


