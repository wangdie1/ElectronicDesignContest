#ifndef __LED_H
#define __LED_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//LED��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/2
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////// 

//ս��ϵ��
//#define   RCC_APB2Periph_LED   		RCC_APB2Periph_GPIOE

//#define   LED_GPIO_E                GPIOE
//#define   LED_GPIO_B                GPIOE

//#define   LED_GPIO_PIN_A 			GPIO_Pin_5
//#define   LED_GPIO_PIN_B  			GPIO_Pin_6


//#define LED0 PEout(5)// PB5
//#define LED1 PEout(6)// PE5	

//void LED_Init(void);				//��ʼ��


//����ϵ��



//��һ�ص�Ƭ��
#define   RCC_APB2Periph_LED   		RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOG
#define   LED_GPIO_E                GPIOD
#define   LED_GPIO_B                GPIOG

#define   LED_GPIO_PIN_A 			GPIO_Pin_13
#define   LED_GPIO_PIN_B  			GPIO_Pin_14

#define   LED0 PDout(13)			// PB5
#define   LED1 PGout(14)			// PE5	

void LED_Init(void);				//��ʼ��

		 				    
#endif
