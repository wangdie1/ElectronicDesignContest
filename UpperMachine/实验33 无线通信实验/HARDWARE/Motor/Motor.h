#ifndef __MOTOR_H
#define __MOTOR_H
#include "sys.h"

#define PWM_FREQ 			24         // 24000000
#define PWM_PSC              2         //时钟预分频数
#define PWM_ARR              1000      //自动重装值
/***
!!!!!移植时注意修改PWM_Update函数
**/


/****
设置pwm的定时器
***/
#define PWM_TIMER						TIM4
#define PWM_TIMER_CLK					RCC_APB1Periph_TIM4


#define	PWM_OUT_PORT					GPIOB
#define PWM_OUT_PORT_CLK				RCC_APB2Periph_GPIOB

/****
IN1A PB8
IN2A PB9

IN1B  PB7
IN2B PB6
****/
#define PWM_OUT_PIN1					GPIO_Pin_8
#define PWM_OUT_PIN2					GPIO_Pin_9
#define PWM_OUT_PIN3					GPIO_Pin_6
#define PWM_OUT_PIN4					GPIO_Pin_7


/*****
EN1 EN2   --PB5
*****/
#define MOTOR_EN_PORT					GPIOB
#define	MOTOR_EN_PIN					GPIO_Pin_5
#define MOTOR_EN_PORT_CLK				RCC_APB2Periph_GPIOB



void TIM_PWM_Init(void);

void MotorA_Forward_PWM_Update(uint16_t CCR3_Value );
void MotorA_Backward_PWM_Update(uint16_t CCR4_Value);
void MotorA_PWM_Update(s16 CCR_Value);
void MotorA_Forward(uint16_t CCR3_Value);
void MotorA_Backward(uint16_t CCR4_Value);
void MotorA_Brk(void);

void MotorB_Forward_PWM_Update(uint16_t CCR3_Value );
void MotorB_Backward_PWM_Update(uint16_t CCR4_Value);
void MotorB_PWM_Update(s16 CCR_Value);
void MotorB_Forward(uint16_t CCR3_Value);
void MotorB_Backward(uint16_t CCR4_Value);
void MotorB_Brk(void);

void MotorInit(void);

void MotorDisable(void);
void MotorEnable(void );


#endif
