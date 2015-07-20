#ifndef	 _ENCODER1_H
#define _ENCODER1_H
#include "stm32f10x.h"
#include "stdbool.h"
#include  "Encoder.h"
// #include "TimeBase.h"
#include "encoder_param.h"


#define	ENC1_TIMER 							TIM2
#define ENC1_TIMER_IRQn					TIM2_IRQn
#define ENC1_TIMER_CLK					RCC_APB1Periph_TIM2
#define ENC1_GPIO_PORT					GPIOA
#define ENC1_GPIO_CLK						RCC_APB2Periph_GPIOA 
#define ENC1_GPIO_PIN_A					GPIO_Pin_0
#define ENC1_GPIO_PIN_B					GPIO_Pin_1

void ENC1_Init(void);

s16 ENC1_Get_Electrical_Angle(void);
void ENC1_Clear_Speed_Buffer(void);
s32 ENC1_Get_TimerCounter(void);
s16 ENC1_Calc_Average_Speed(void);
s16 ENC1_Get_Speed(void);
s16 ENC1_Calc_Rot_Speed(void);
void TIM2_IRQHandler(void);
s32 ENC1_Calc_Position(void);
s32 ENC1_Get_AnglularPosition(void);

#endif