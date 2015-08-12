#ifndef __LED_H
#define __LED_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//LED驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/2
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////// 

//战舰系列
//#define   RCC_APB2Periph_LED   		RCC_APB2Periph_GPIOE

//#define   LED_GPIO_E                GPIOE
//#define   LED_GPIO_B                GPIOE

//#define   LED_GPIO_PIN_A 			GPIO_Pin_5
//#define   LED_GPIO_PIN_B  			GPIO_Pin_6


//#define LED0 PEout(5)// PB5
//#define LED1 PEout(6)// PE5	

//void LED_Init(void);				//初始化


//红龙系列



//贝一特单片机
#define   RCC_APB2Periph_LED   		RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOG
#define   LED_GPIO_E                GPIOD
#define   LED_GPIO_B                GPIOG

#define   LED_GPIO_PIN_A 			GPIO_Pin_13
#define   LED_GPIO_PIN_B  			GPIO_Pin_14

#define   LED0 PDout(13)			// PB5
#define   LED1 PGout(14)			// PE5	

void LED_Init(void);				//初始化

		 				    
#endif
