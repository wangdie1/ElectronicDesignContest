#ifndef _PPM_H
#define _PPM_H

#include "stm32f10x.h"

#define PWM_TIMER							TIM4
#define PWM_TIMER_CLK					RCC_APB1Periph_TIM4

//配置为1MHZ 及1us
#define TIM_FREQ							1000000//单位Hz 表示定时器的计数频率
//配置为20ms
#define PWM_PERIOD						21200//单位为（1/TIM_FREQ） 表示 PWM周期
                                   
#define	PWM_OUT_PORT					GPIOB
#define PWM_OUT_PORT_CLK			RCC_APB2Periph_GPIOB
#define PWM_OUT_PIN1					GPIO_Pin_8
#define PWM_OUT_PIN2					GPIO_Pin_9
#define PWM_OUT_PIN3					GPIO_Pin_6
#define PWM_OUT_PIN4					GPIO_Pin_7
void PPM_Init(void);
void PPM_TIM_PWM_Init(void);
void PPM_H_PosSet(float Position);
void PPM_H_PWM_Set(uint16_t CCR_Val);
void PPM_V_PWM_Set(uint16_t CCR_Val);
void PPM_V_PosSet(float Position);
#endif
