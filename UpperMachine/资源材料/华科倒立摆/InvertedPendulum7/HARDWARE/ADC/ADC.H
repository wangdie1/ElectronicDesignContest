#ifndef _ADC_H
#define _ADC_H
#include "stm32f10x.h"        //这个头文件包括STM32F10x所有外围寄存器、位、内存映射的定义

#define  N   	5000	     //每通道采50次
#define  M  	3	     //为12个通道
extern vu16  AD_Value[N][M];   //用来存放ADC转换结果，也是DMA的目标地址
extern vu32  After_filter[M];    //用来存放求平均值之后的结果
void GPIO_Configuration(void);
void RCC_Configuration(void);
void ADC1_Configuration(void);
void DMA_Configuration(void);
void Init_ADC_Periph(void);
u16 GetVolt(u16 advalue)  ;
float GetVoltFloat(float ADvalue);
void filter(void);
void InitADC();
#endif