
#ifndef __MOTOR_H
#define _motor_h
#include "stm32f10x.h"

#define PWM_FREQ 			24// 24000000
/***驱动 用于DRV8834**/

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
#define PWM_MOTOR_A					GPIO_Pin_6
#define PWM_MOTOR_B					GPIO_Pin_7

#define DIR_MOTOR_A					GPIO_Pin_4
#define DIR_MOTOR_B					GPIO_Pin_5
#define DRV_NSLEEP_PIN			GPIO_Pin_3




// void TIM2_PWM(void);
// void TIM4_PWM(void);
void TIM_PWM_Init(void);
void MotorInit(void);

void MotorA_PWM_Update(s16 CCR_Value);
void MotorA_Forward(uint16_t CCR3_Value);
void MotorA_Backward(uint16_t CCR4_Value);
void MotorA_Brk(void);

void MotorB_PWM_Update(s16 CCR_Value);
void MotorB_Forward(uint16_t CCR3_Value);
void MotorB_Backward(uint16_t CCR4_Value);
void MotorB_Brk(void);


// void MotorDisable(void);
// void MotorEnable(void );

// void MotorAB(uint16_t CCR_Val);




#endif
