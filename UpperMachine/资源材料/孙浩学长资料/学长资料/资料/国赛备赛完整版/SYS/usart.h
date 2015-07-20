//嵌入式家园stm32串口通信代码库函数版1.0版本 希望同学们可以多多修改，是程序更加完善。
//作者 孙浩 2013.4.1
/*
USART1   TX:PA9  RX:PA10
USART2	 TX:PA2  RX:PA3
USART3	 TX:PB10  RX:PB11
UART4	 TX:PC10  RX:C11
UART5	 TX:PC12  RX:PD2
*/
#ifndef   __USART_H
#define   __USART_H

#include<stm32f10x.h>
#define Use_Printf 1
#define Nonuse_Printf  0
typedef enum {usart1,usart2,usart3,uart4,uart5}usart_type;

void Usart_Init(usart_type x);
u16 usart_receive_char(USART_TypeDef* USARTx);
void usart_receive_string(USART_TypeDef* USARTx,u8 *ch,int len);
void usart1_init(void);
void usart2_init(void);
void usart3_init(void);
void uart4_init(void);
void uart5_init(void);
void usart_sent_char(USART_TypeDef* USARTx,char ch );
void usart_sent_string(USART_TypeDef* USARTx,char *ch);
void NVIC_Configuration(void);

#endif
