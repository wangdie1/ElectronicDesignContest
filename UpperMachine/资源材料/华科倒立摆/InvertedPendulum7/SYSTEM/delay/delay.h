#ifndef __DELAY_H
#define __DELAY_H 			   
#include "stm32f10x.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//Mini STM32������
//ʹ��SysTick����ͨ����ģʽ���ӳٽ��й���
//����delay_us,delay_ms
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2010/5/27
//�汾��V1.2
//��Ȩ���У�����ؾ���
//Copyright(C) ����ԭ�� 2009-2019
//All rights reserved
//********************************************************************************
//V1.2�޸�˵��
//�������ж��е��ó�����ѭ���Ĵ���
//��ֹ��ʱ��׼ȷ,����do while�ṹ!
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





























