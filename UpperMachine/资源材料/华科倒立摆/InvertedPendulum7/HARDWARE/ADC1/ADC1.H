#ifndef _ADC1_H
#define _ADC1_H
#define CHANNEL_NUM 2

#include "stm32f10x.h"
#define DR_ADDRESS ((uint32_t)0x4001244c)//ADC1 DR base
extern __IO uint16_t ADC_ConvertedValue;

void ADC1_Init(void);

#endif
