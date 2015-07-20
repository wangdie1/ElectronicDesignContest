#ifndef __HX711_H
#define __HX711_H	 
#include "stm32f10x.h"
//Mini STM32开发板
//LED驱动代码			 
//正点原子@ALIENTEK
//2012/2/27

//LED端口定义
#define ADDO GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5) 
#define ADSK_L GPIO_ResetBits(GPIOA,GPIO_Pin_4)
#define ADSK_H GPIO_SetBits(GPIOA,GPIO_Pin_4)
void HX711_INIT(void);//初始化
u32 ReadHx711(void);
u32 ReadHx711_Average(void);
u32  weight_buffer_init();
		 				    
#endif
