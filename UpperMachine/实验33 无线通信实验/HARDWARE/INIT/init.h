#ifndef __INIT_H
#define __INIT_H
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//������ʼ������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/2
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////// 
//�ر�ϵ��
#include "sys.h"
#include "led.h"
#include "rtc.h"
#include "key.h"
#include "delay.h"
#include "mytask.h"
#include "lcd.h"
#include "TimeBase.h"
#include "beep.h"


//����
#include "niming.h"
#include "usart.h"
#include "usmart.h"

#include "mytype.h"
#include "control_param.h"
#include "globals.h"

//���
//#include "Encoder1.h"
//#include "Encoder.h"
#include "Motor.h"
//#include "Control.h"


//����ͨ��	 
//#include "24l01.h"

//������
//#include "UltrasonicWave.h"
//#include "timer4_cap.h"

//���ⷢ����ճ���

//#include "remote.h"

//mpu6050ģ��
#include "mpu6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h" 

//ϵͳ��ʼ��
void Init(void);
void set_PID(u16 P,u16 I,u16 D);
void led_set(u16 sta);
#endif

