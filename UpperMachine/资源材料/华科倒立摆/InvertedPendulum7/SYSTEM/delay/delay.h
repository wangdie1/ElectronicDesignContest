#ifndef __DELAY_H
#define __DELAY_H 			   
#include "stm32f10x.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//Mini STM32开发板
//使用SysTick的普通计数模式对延迟进行管理
//包括delay_us,delay_ms
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2010/5/27
//版本：V1.2
//版权所有，盗版必究。
//Copyright(C) 正点原子 2009-2019
//All rights reserved
//********************************************************************************
//V1.2修改说明
//修正了中断中调用出现死循环的错误
//防止延时不准确,采用do while结构!
////////////////////////////////////////////////////////////////////////////////// 
// void delay_init(u8 SYSCLK);
//  #define delay_ms(x) { unsigned int _dcnt;\
// 	 _dcnt=(x*100); \
// 	 while(dcnt-->0)\
// 	 {\
// 		 delay_us(10)\
// 		}\
//      }
// #define delay_us(x) { unsigned int _dcnt; \
//       _dcnt=(x*8); \
//       while(_dcnt-- > 0) \
//       { continue; }\
// 			}
void delay_ms(u16 nms);
void delay_us(u32 nus);
void delay_init(u8 SYSCLK);
// void systick_delay_us(u32 nus);
// void systick_delay_ms(u16 nms);
// void delay(u32 nCount);
#endif





























