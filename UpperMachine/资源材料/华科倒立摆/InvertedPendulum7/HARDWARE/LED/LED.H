#ifndef __LED_H
#define __LED_H	 
#include "stm32f10x.h"
//Mini STM32开发板
//LED驱动代码			 
//正点原子@ALIENTEK
//2012/2/27

//LED端口定义

#define LED0_GPIO_Port GPIOB
#define LED0_GPIO_CLK		RCC_APB2Periph_GPIOB
#define LED0_GPIO_Pin		GPIO_Pin_0

#define LED1_GPIO_Port GPIOD
#define LED1_GPIO_CLK		RCC_APB2Periph_GPIOD
#define LED1_GPIO_Pin		GPIO_Pin_2

#define LED2_GPIO_Port 	GPIOA
#define LED2_GPIO_Pin		GPIO_Pin_15
#define LED2_GPIO_CLK		RCC_APB2Periph_GPIOA
// #define LED0_GPIO_Port GPIOC
// #define LED0_GPIO_CLK		RCC_APB2Periph_GPIOC
// #define LED0_GPIO_Pin		GPIO_Pin_0
// #define LED1_GPIO_Port GPIOC
// #define LED1_GPIO_CLK		RCC_APB2Periph_GPIOC
// #define LED1_GPIO_Pin		GPIO_Pin_1

void LED_Init(void);//初始化
void LED0_Toggle(void);
void LED0_ON(void);
void LED0_OFF(void);
void LED1_Toggle(void);
void LED1_ON(void);
void LED1_OFF(void);
void LED2_Toggle(void);
void LED2_ON(void);
void LED2_OFF(void);
		 				    
#endif
