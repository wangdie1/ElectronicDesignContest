#ifndef __RED_H
#define __RED_H 
#include "sys.h"   
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//Mini STM32������
//����ң�ؽ��� ��������		   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2010/6/17 
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ����ԭ�� 2009-2019
//All rights reserved
////////////////////////////////////////////////////////////////////////////////// 	  
  
#define RDATA PAin(3)	 //�������������
//����ң��ʶ����(ID),ÿ��ң�����ĸ�ֵ��������һ��,��Ҳ��һ����.
//����ѡ�õ�ң����ʶ����Ϊ0
#define REMOTE_ID 	0 
#define IR_KEY1			48
#define IR_KEY2			24
#define IR_KEY3			122
#define IR_KEY4   	16
#define IR_KEY5			56
#define IR_KEY6			90
#define IR_KEY7			66
#define IR_KEY8			74
#define IR_KEY9			82
#define IR_KEY0			104
#define IR_VOL_UP   168
#define IR_VOL_DOWN 224
#define IR_NEXT 2
#define IR_PREV 34
#define IR_PLAY  194
#define IR_EQ			144
#define IR_CH_DOWN	162
#define IR_CH				98
#define IR_CH_UP		226
#define IR_100_UP		152
#define IR_200_UP		176

#define MODE_SELECT_MENU   			 			(u8) 0//ģʽѡ��˵�
#define POSITION_MEASURE_MENU         (u8) 1//λ�Ʋ����˵�
#define POSITION_CONTROL_MENU         (u8) 2//λ�ÿ���
#define WEIGHT_POSITION_MENU          (u8) 3//����λ��ת��
#define OTHERS_MODE_MENU           		(u8) 4//����

#define P_TORQUE_MENU          (u8) 5
#define I_TORQUE_MENU          (u8) 6
#define D_TORQUE_MENU          (u8) 7

#define P_FLUX_MENU            (u8) 8
#define I_FLUX_MENU            (u8) 9
#define D_FLUX_MENU            (u8) 10

#define POWER_STAGE_MENU       (u8) 11

#define CONTROL_MODE_MENU_6    (u8) 12
#define IQ_REF_MENU            (u8) 13
#define ID_REF_MENU            (u8) 14

#define FAULT_MENU             (u8) 15

#define WAIT_MENU              (u8) 16

extern u8 Remote_Cnt;    //��������,�˴ΰ��¼��Ĵ���
extern u8 Remote_Rdy;    //������յ����� 
extern u32 Remote_Odr;   //�����ݴ洦
void Remote_Init(void);    //���⴫��������ͷ���ų�ʼ��
u8 Remote_Process(void);   //������յ����ݴ���
u8 Pulse_Width_Check(void);//�������	  	
void IR_KEYS_Process(void);
#endif















