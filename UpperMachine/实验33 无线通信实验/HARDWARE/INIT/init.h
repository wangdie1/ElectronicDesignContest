#ifndef __INIT_H
#define __INIT_H
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//函数初始化程序	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/2
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////// 
//必备系列
#include "sys.h"
#include "led.h"
#include "rtc.h"
#include "key.h"
#include "delay.h"
#include "mytask.h"
#include "lcd.h"
#include "TimeBase.h"
#include "beep.h"


//串口
#include "niming.h"
#include "usart.h"
#include "usmart.h"

#include "mytype.h"
#include "control_param.h"
#include "globals.h"

//电机
//#include "Encoder1.h"
//#include "Encoder.h"
#include "Motor.h"
//#include "Control.h"


//无线通信	 
//#include "24l01.h"

//超声波
//#include "UltrasonicWave.h"
//#include "timer4_cap.h"

//红外发射接收程序

//#include "remote.h"

//mpu6050模块
#include "mpu6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h" 

//系统初始化
void Init(void);
void set_PID(u16 P,u16 I,u16 D);
void led_set(u16 sta);
#endif

