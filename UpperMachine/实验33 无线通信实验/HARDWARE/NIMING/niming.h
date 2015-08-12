#ifndef __Niming_H
#define __Niming_H
#include "sys.h"

/////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//LED��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/5/2
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////
//�����������λ������
//����ʹ�õĹ�����
//1.����ʾ��������
//2.����λ����������

//������λ���Ĵ�����������
void usart1_send_char(u8 c);

void usart1_niming_report(u8 fun,u8*data,u8 len);
//���ͼ��ٶȴ��������ݺ�����������
void mpu6050_send_data(short aacx,short aacy,short aacz,short gyrox,short gyroy,short gyroz);
//������̬���ݸ���λ��
void usart1_report_imu(short aacx,short aacy,short aacz,short gyrox,short gyroy,short gyroz,short roll,short pitch,short yaw);

//��pwm1,pwm2,enc1,enc2��ֵ���͸�������λ��
void usart1_report_Pwm(short pwm1,short pwm2,short enc1,short enc2);

//��pid���͸���λ��
void usart1_report_Pid(short pid_p,short pid_i,short pid_d);
void usart1_niming_report_pid(u8 fun,u8*data,u8 len);

//��λ���޸���λ����ֵ   δ���

void Data_Receive(void);

void usart_report_enc(short enc1);
#endif
