

#ifndef _TIM1_CAP_H
#define _TIM1_CAP_H
#include "stm32f10x.h"
extern vu8 capnum;
extern __IO int IC1ReadValue , IC2ReadValue , IC3ReadValue,IC4ReadValue ;
extern volatile u32 time_over_num;

void TIM1_CapInit(void);
#endif