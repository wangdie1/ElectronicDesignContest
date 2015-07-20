
#ifndef __MOTOR_H
#define _motor_h
#include "stm32f10x.h"

#define PWM_FREQ 			24// 24000000

/***
!!!!!移植时注意修改PWM_Update函数
**/
// #define MOTOR_EN_PORT					GPIOB
// #define MOTOR_EN_PIN					GPIO_Pin_15
// #define MOTOR_EN_PORT_CLK			RCC_APB2Periph_GPIOB

#define PWM_TIMER							TIM4
#define PWM_TIMER_CLK					RCC_APB1Periph_TIM4


#define	PWM_OUT_PORT					GPIOB
#define PWM_OUT_PORT_CLK			RCC_APB2Periph_GPIOB
#define PWM_OUT_PIN1					GPIO_Pin_8
#define PWM_OUT_PIN2					GPIO_Pin_9
#define PWM_OUT_PIN3					GPIO_Pin_6
#define PWM_OUT_PIN4					GPIO_Pin_7

#define MOTOR_EN_PORT				GPIOB
#define	MOTOR_EN_PIN				GPIO_Pin_5
#define MOTOR_EN_PORT_CLK		RCC_APB2Periph_GPIOB





// void TIM2_PWM(void);
// void TIM4_PWM(void);
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
// void MotorDisable(void);
// void MotorEnable(void );

// void MotorAB(uint16_t CCR_Val);




#endif
