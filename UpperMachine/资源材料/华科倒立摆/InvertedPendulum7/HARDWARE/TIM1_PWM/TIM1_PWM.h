#ifndef _TIM1_PWM_H
#define _TIM1_PWM_H

#define TIM1_PWM_FREQ  10000 //单位HZ
#define TIM1_PWM_DUTY	 0//%初始化为
#define TIM1_PWM_Port				GPIOA
#define TIM1_PWM_CH1_Pin		GPIO_Pin_8
#define TIM1_PWM_CH2_Pin		GPIO_Pin_9
#define TIM1_PWM_CH3_Pin		GPIO_Pin_10
#define TIM1_PWM_CH4_Pin		GPIO_Pin_11

// #define 

void TIM1_PWM_Init(void);
void TIM1_PWM_ON(void);
void TIM1_PWM_OFF(void);
void TIM1_PWM_Update(float duty);
#endif