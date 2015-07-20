#ifndef _SERVO_H
#define _SERVO_H

#include "stm32f10x.h"

#define PWM_TIMER							TIM4
#define PWM_TIMER_CLK					RCC_APB1Periph_TIM4

//����Ϊ1MHZ ��1us
#define TIM_FREQ							1000000//��λHz ��ʾ��ʱ���ļ���Ƶ��
//����Ϊ20ms
#define PWM_PERIOD						20000//��λΪ��1/TIM_FREQ�� ��ʾ PWM����
                                   
#define	PWM_OUT_PORT					GPIOB
#define PWM_OUT_PORT_CLK			RCC_APB2Periph_GPIOB
#define PWM_OUT_PIN1					GPIO_Pin_8
#define PWM_OUT_PIN2					GPIO_Pin_9
#define PWM_OUT_PIN3					GPIO_Pin_6
#define PWM_OUT_PIN4					GPIO_Pin_7
void ServoInit(void);
void Servo_TIM_PWM_Init(void);
void ServoH_PosSet(float Position);
void ServoH_PWM_Set(uint16_t CCR_Val);
void ServoV_PWM_Set(uint16_t CCR_Val);
void ServoV_PosSet(float Position);
#endif
