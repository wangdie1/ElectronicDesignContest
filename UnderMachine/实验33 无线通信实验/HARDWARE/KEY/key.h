#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//������������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/3
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////   	 


#define KEY0  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)//��ȡ����0

#define KEY1  GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_1)//��ȡ����1
#define KEY2  GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_2)//��ȡ����1
#define KEY3  GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_3)//��ȡ����1
#define KEY4  GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_4)//��ȡ����1
#define KEY5  GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_5)//��ȡ����1
#define KEY6  GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_6)//��ȡ����1
#define KEY7  GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_7)//��ȡ����1
//#define KEY8  GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_8)//��ȡ����1

#define WK_UP  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)//��ȡ�� WK_UP 




#define KEY0_PRES   10	//key0

#define WKUP_PRES   9   //wake_up

#define KEY8_PRES   8  //KEY8����
#define KEY7_PRES   7  //KEY7����
#define KEY6_PRES   6  //KEY6����
#define KEY5_PRES   5  //KEY5����
#define KEY4_PRES   4  //KEY4����
#define KEY3_PRES   3  //KEY3����
#define KEY2_PRES   2  //KEY2����
#define KEY1_PRES   1  //KEY1����


void KEY_Init(void);//IO��ʼ��
u8 KEY_Scan(u8);  	//����ɨ�躯��					    
#endif
