#include "Servo.h"

/**
引脚分配： PB7 PB9
**/


void ServoInit(void)
{
		Servo_TIM_PWM_Init();
}
/********
功能：配置PWM_TIMER 为PWM模式输出
计数频率为TIM_FREQ,PWM周期为PWM_PERIOD,初始占空比为0
********/
void Servo_TIM_PWM_Init(void)
{
		uint16_t CCR_Val = 1500;
		int PrescalerValue=1;
		GPIO_InitTypeDef 					GPIO_InitStructure;
		TIM_TimeBaseInitTypeDef 	TIM_TimeBaseStructure;
		TIM_OCInitTypeDef 				TIM_OCInitStructure;
	
	//TIM clock enable
	//根据TIM选择使能不同的时钟
		if((PWM_TIMER == TIM2) || (PWM_TIMER == TIM3)||(PWM_TIMER == TIM4) || 
		(PWM_TIMER == TIM5)||(PWM_TIMER == TIM6) || (PWM_TIMER == TIM7)) 
	{
		RCC_APB1PeriphClockCmd(PWM_TIMER_CLK, ENABLE);
	}
  if((PWM_TIMER != TIM1) && (PWM_TIMER != TIM8))
  {
		RCC_APB2PeriphClockCmd(PWM_TIMER_CLK, ENABLE);
  }
	
		//enable GPIO clocks 
		RCC_APB2PeriphClockCmd(	
							PWM_OUT_PORT_CLK |
							RCC_APB2Periph_AFIO,ENABLE);
	
	//配置相应的GPIO输出
		GPIO_InitStructure.GPIO_Pin=PWM_OUT_PIN1|PWM_OUT_PIN2|PWM_OUT_PIN3|PWM_OUT_PIN4;
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_Init(PWM_OUT_PORT,&GPIO_InitStructure);
	
	//配置TIMER 分频系数 计数周期 工作模式
		PrescalerValue= (uint16_t)(SystemCoreClock/TIM_FREQ-1);
	
		TIM_TimeBaseStructure.TIM_Period = PWM_PERIOD-1;
  	TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;
  	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	
		TIM_TimeBaseInit(PWM_TIMER , &TIM_TimeBaseStructure);
		
		//PWM模式配置 通道1
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  	TIM_OCInitStructure.TIM_Pulse = CCR_Val;
  	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;	
		TIM_OC1Init(PWM_TIMER , &TIM_OCInitStructure);
		TIM_OC1PreloadConfig(PWM_TIMER , TIM_OCPreload_Enable);
		//通道2
		TIM_OCInitStructure.TIM_Pulse = CCR_Val;
  	TIM_OC2Init(PWM_TIMER , &TIM_OCInitStructure);
  	TIM_OC2PreloadConfig(PWM_TIMER , TIM_OCPreload_Enable);
		//通道3
		TIM_OCInitStructure.TIM_Pulse = CCR_Val;
  	TIM_OC3Init(PWM_TIMER , &TIM_OCInitStructure);
  	TIM_OC3PreloadConfig(PWM_TIMER , TIM_OCPreload_Enable);
		//通道4
		TIM_OCInitStructure.TIM_Pulse = CCR_Val;
  	TIM_OC4Init(PWM_TIMER , &TIM_OCInitStructure);
  	TIM_OC4PreloadConfig(PWM_TIMER , TIM_OCPreload_Enable);
		
		TIM_ARRPreloadConfig(PWM_TIMER , ENABLE);
		/* TIM enable counter */
  	TIM_Cmd(PWM_TIMER , ENABLE);
}

/*******
设置水平电机角度位置 单位为0.18度
******/
void ServoH_PosSet(float Position)
{
	uint16_t CCR1_Val=0;
	CCR1_Val=1500+Position*100/18;
	TIM4->CCR2 =  CCR1_Val;
}

/*******
设置 垂直 电机角度位置 单位为0.18度
******/
void ServoV_PosSet(float Position)
{
	uint16_t CCR4_Val=0;
	CCR4_Val=1500+Position*100/18;
	TIM4->CCR4 =  CCR4_Val;
}

void ServoH_PWM_Set(uint16_t CCR_Val)
{
		TIM4->CCR2=CCR_Val;
}
void ServoV_PWM_Set(uint16_t CCR_Val)
{
		TIM4->CCR4=CCR_Val;
}

