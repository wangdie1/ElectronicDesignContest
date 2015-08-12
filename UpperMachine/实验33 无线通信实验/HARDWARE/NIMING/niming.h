#ifndef __Niming_H
#define __Niming_H
#include "sys.h"

/////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F407开发板
//LED驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2014/5/2
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////
//匿名四轴的上位机程序
//可以使用的功能有
//1.虚拟示波器功能
//2.向上位机传送数据

//匿名上位机的串口驱动程序
void usart1_send_char(u8 c);

void usart1_niming_report(u8 fun,u8*data,u8 len);
//发送加速度传感器数据和陀螺仪数据
void mpu6050_send_data(short aacx,short aacy,short aacz,short gyrox,short gyroy,short gyroz);
//发送姿态数据给上位机
void usart1_report_imu(short aacx,short aacy,short aacz,short gyrox,short gyroy,short gyroz,short roll,short pitch,short yaw);

//把pwm1,pwm2,enc1,enc2的值发送给匿名上位机
void usart1_report_Pwm(short pwm1,short pwm2,short enc1,short enc2);

//把pid发送给上位机
void usart1_report_Pid(short pid_p,short pid_i,short pid_d);
void usart1_niming_report_pid(u8 fun,u8*data,u8 len);

//下位机修改上位机的值   未完成

void Data_Receive(void);

void usart_report_enc(short enc1);
#endif
