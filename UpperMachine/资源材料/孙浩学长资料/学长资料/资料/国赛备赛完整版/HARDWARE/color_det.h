#ifndef __COLOR_DET_H
#define __COLOR_DET_H

#include<stm32f10x.h>
#include"Compare.h"
#include"delay.h"

void Color_Pin_Init(void);
void Color_measure(int R_fac,int G_fac,int B_fac);
void White_bal(void);

#endif

