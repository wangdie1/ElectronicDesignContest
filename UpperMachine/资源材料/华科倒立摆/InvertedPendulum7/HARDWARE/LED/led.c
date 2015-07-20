#include "stm32f10x.h"
#include "led.h"

//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//Mini STM32������
//LED��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/5/27
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ����ԭ�� 2009-2019
//All rights reserved											  
////////////////////////////////////////////////////////////////////////////////// 	   

//��ʼ��PA8��PD2Ϊ�����.��ʹ���������ڵ�ʱ��		    
//LED IO��ʼ��
void LED_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(LED0_GPIO_CLK, ENABLE);	 //ʹ��PA�˿�ʱ��
	
 GPIO_InitStructure.GPIO_Pin = LED0_GPIO_Pin;				 //LED0-->PA.8 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 GPIO_Init(LED0_GPIO_Port, &GPIO_InitStructure);
 GPIO_SetBits(LED0_GPIO_Port,LED0_GPIO_Pin);						 //PA.8 �����


 RCC_APB2PeriphClockCmd(LED1_GPIO_CLK, ENABLE);   //ʹ��PD�˿�ʱ��

 GPIO_InitStructure.GPIO_Pin = LED1_GPIO_Pin;	    		 //LED1-->PD.2 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
 GPIO_Init(LED1_GPIO_Port, &GPIO_InitStructure);	
 GPIO_SetBits(LED1_GPIO_Port,LED1_GPIO_Pin); 						 //PD.2 ����� 
	
	RCC_APB2PeriphClockCmd(LED2_GPIO_CLK, ENABLE);   //ʹ��PD�˿�ʱ��

 GPIO_InitStructure.GPIO_Pin = LED2_GPIO_Pin;	    		 //LED1-->PD.2 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
 GPIO_Init(LED2_GPIO_Port, &GPIO_InitStructure);	
 GPIO_SetBits(LED2_GPIO_Port,LED2_GPIO_Pin); 	
}
void LED0_Toggle()
{
	LED0_GPIO_Port->ODR ^=LED0_GPIO_Pin;//�˴�ע���޸�
}
void LED0_ON()
{
	GPIO_ResetBits(LED0_GPIO_Port,LED0_GPIO_Pin);
}
void LED0_OFF()
{
	GPIO_SetBits(LED0_GPIO_Port,LED0_GPIO_Pin);
}

void LED1_Toggle()
{
	LED1_GPIO_Port->ODR ^=LED1_GPIO_Pin;
}
void LED1_ON()
{
	GPIO_ResetBits(LED1_GPIO_Port,LED1_GPIO_Pin);
}
void LED1_OFF()
{
	GPIO_SetBits(LED1_GPIO_Port,LED1_GPIO_Pin);
}
 
void LED2_Toggle()
{
	LED2_GPIO_Port->ODR ^=LED2_GPIO_Pin;
}
void LED2_ON()
{
	GPIO_ResetBits(LED2_GPIO_Port,LED2_GPIO_Pin);
}
void LED2_OFF()
{
	GPIO_SetBits(LED2_GPIO_Port,LED2_GPIO_Pin);
}
