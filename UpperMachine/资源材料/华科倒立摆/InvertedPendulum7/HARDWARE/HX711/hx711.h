#ifndef __HX711_H
#define __HX711_H	 
#include "stm32f10x.h"
//Mini STM32������
//LED��������			 
//����ԭ��@ALIENTEK
//2012/2/27

//LED�˿ڶ���
#define ADDO GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5) 
#define ADSK_L GPIO_ResetBits(GPIOA,GPIO_Pin_4)
#define ADSK_H GPIO_SetBits(GPIOA,GPIO_Pin_4)
void HX711_INIT(void);//��ʼ��
u32 ReadHx711(void);
u32 ReadHx711_Average(void);
u32  weight_buffer_init();
		 				    
#endif
