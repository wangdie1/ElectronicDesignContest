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




#define KEYA GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_3)// ����A
#define KEYB GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_5)// ����B
#define KEYC GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_2)// ����C
#define KEYD GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_4)// ����D
#define KEYE GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13)// ����E

#define KEYADD GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_9)// ��Ӱ���
#define KEYDCS GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_11)// ���ٰ���

#define KEYCF GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)// ȷ�ϰ���
#define KEYCC GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_10)// ȡ������

#define WK_UP  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)//wk

//����ѡ���
#define KEYA_PRES	1	//  ����A����
#define KEYB_PRES	2	//  ����B����
#define KEYC_PRES	3	//  ����C����
#define KEYD_PRES	4	//  ����D����
#define KEYE_PRES	5	//  ����E����
//ȷ��ȡ������
#define KEYCF_PRES	6	//  ȷ�ϼ�����
#define KEYCC_PRES	7	//  ȡ��/���ؼ�����
//�Ӽ�����
#define KEYADD_PRES 8  //  �����Ӱ���
#define KEYDCS_PRES 9  //  ����������

#define WKUP_PRES   10  //������һ��˵��� 

void KEY_Init(void);//IO��ʼ��
u8 KEY_Scan(u8);  	//����ɨ�躯��					    
#endif
