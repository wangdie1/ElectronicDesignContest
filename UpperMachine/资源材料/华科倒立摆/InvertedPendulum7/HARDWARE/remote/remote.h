#ifndef __RED_H
#define __RED_H 
#include "sys.h"   
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//Mini STM32开发板
//红外遥控接收 驱动代码		   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2010/6/17 
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 正点原子 2009-2019
//All rights reserved
////////////////////////////////////////////////////////////////////////////////// 	  
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
#define RDATA PAin(2)	 //红外数据输入脚
//红外遥控识别码(ID),每款遥控器的该值基本都不一样,但也有一样的.
//我们选用的遥控器识别码为0
#define REMOTE_ID 0      
extern volatile u8 ir_key;
extern u8 Remote_Cnt;    //按键次数,此次按下键的次数
extern u8 Remote_Rdy;    //红外接收到数据 
extern u32 Remote_Odr;   //命令暂存处
void Remote_Init(void);    //红外传感器接收头引脚初始化
u8 Remote_Process(void);   //红外接收到数据处理
u8 Pulse_Width_Check(void);//检查脉宽	  	
#endif















