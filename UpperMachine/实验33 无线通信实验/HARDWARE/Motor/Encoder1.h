#ifndef	 _ENCODER1_H
#define _ENCODER1_H
#include "stm32f10x.h"
#include "stdbool.h"
#include  "Encoder.h"
// #include "TimeBase.h"
#include "encoder_param.h"

#define ENCODER1_PPR (u16) 	1000//码盘线数
#define REDUCTION1_RATIO 1//减速比 
#define RADIOUS1	36//单位mm
#define LENGTH1 1980 //单位mm

#define	ENC1_TIMER 							TIM2
#define ENC1_TIMER_IRQn					TIM2_IRQn
#define ENC1_TIMER_CLK					RCC_APB1Periph_TIM2
#define ENC1_GPIO_PORT					GPIOA
#define ENC1_GPIO_CLK						RCC_APB2Periph_GPIOA 
#define ENC1_GPIO_PIN_A					GPIO_Pin_0
#define ENC1_GPIO_PIN_B					GPIO_Pin_1

#define ENC1_ANFULAR_UNIT       90//1度
#define ENC1_SPPED_UNIT					600//RPM/10

void ENC1_Init(void);

// double ENC1_Get_Electrical_Angle(void);
void	 ENC1_Clear_Speed_Buffer(void);
double ENC1_Get_TimerCounter(void);
double ENC1_Calc_Average_Speed(void);
double ENC1_Get_Speed(void);
double ENC1_Calc_Rot_Speed(void);
void TIM2_IRQHandler(void);
double ENC1_Get_AnglularPosition(void);

#endif