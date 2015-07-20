#ifndef __USART_H
#define __USART_H
#include "stdio.h"
#include "stm32f10x.h"
#define COM_USART1//选择使用的串口号

#ifdef 	COM_USART2

#define COM_USART		USART2
#define COM_USART_IRQn	USART2_IRQn
#define COM_USART_CLK	RCC_APB1Periph_USART2
#define COM_USART_TX_PIN	GPIO_Pin_2
#define COM_USART_RX_PIN	GPIO_Pin_3
#define COM_USART_PORT		GPIOA
#define COM_USART_PORT_CLK	RCC_APB2Periph_GPIOA

#endif

#ifdef 	COM_USART1

#define COM_USART		USART1
#define COM_USART_IRQn	USART1_IRQn
#define COM_USART_CLK	RCC_APB2Periph_USART1
#define COM_USART_TX_PIN	GPIO_Pin_9
#define COM_USART_RX_PIN	GPIO_Pin_10
#define COM_USART_PORT		GPIOA
#define COM_USART_PORT_CLK	RCC_APB2Periph_GPIOA

#endif

#ifdef COM_USART3

#define COM_USART					USART3
#define COM_USART_IRQn		USART3_IRQn
#define COM_USART_CLK			RCC_APB1Periph_USART3
#define COM_USART_TX_PIN	GPIO_Pin_10
#define COM_USART_RX_PIN	GPIO_Pin_11
#define COM_USART_PORT		GPIOB
#define COM_USART_PORT_CLK	RCC_APB2Periph_GPIOB

#endif
extern volatile float x,y;
extern volatile u8 IsUsartReceived;
extern u8 USART_RX_BUF[64];     //接收缓冲,最大63个字节.末字节为换行符 
extern u8 USART_RX_STA;         //接收状态标记	

void InitUSART(u32 bound);

#endif
