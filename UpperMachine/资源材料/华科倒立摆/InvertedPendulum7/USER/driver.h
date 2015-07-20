#ifndef _driver_h
#define _driver_h

//系统必须
#include "delay.h"
#include "sys.h"
#include "Timebase.h"
#include "app.h"
#include "math.h"
#include "MyType.H"
#include "mytask.h"
#include "gpio.h"
//人际接口
#include "LED.H"
#include "LCD.H"
#include "remote.h"
#include "ZLG_Key.h"
#include "ZLG7290.h"
#include "I2C.h"
#include "usart.h"
// #include "wt_lcd.h"//串口LCD
//#include "wt_display.h"



//电机控制
#include "control.h"
#include "Motor.h"
#include "Encoder.h"
#include "Encoder1.h"
// #include "servo.h"//模拟舵机
// #include "TIM1_PWM.H"

//其他
//#include "ADC1.h"//单通道ADC1
//#include "ADC.H" //多通道连续模式
//#include "TIM1_Cap.h"//TIM1捕获模式
// #include "TIM1_PWM.h"//TIM1PWM输出模式
// #include "st168.h" //红外对管黑线检测
// #include "laba.h"  //TIM1输出PWM，喇叭驱动
// #include "24l01.h" //无线通信
// #include "HX711.H"  //称重模块驱动
// #include "switch.h"  //行程开关
#include "DS18B20.h"
#include "math.h"
#include "extikey.h"


#endif
