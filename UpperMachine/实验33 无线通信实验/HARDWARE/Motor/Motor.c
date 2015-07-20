
#include "Motor.h"
/****
ENA  ..

IN1A PB8
IN2A PB9

ENB  ..
IN1B  PB7
IN2B PB6
****/
uint16_t PrescalerValue = 0;

void MotorInit()
{
	//使能脚EN 初始化
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(MOTOR_EN_PORT_CLK ,ENABLE);

	GPIO_InitStructure.GPIO_Pin =  MOTOR_EN_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(MOTOR_EN_PORT ,&GPIO_InitStructure);
	//置0 关闭
	GPIO_ResetBits(MOTOR_EN_PORT ,MOTOR_EN_PIN );
	//定时器PWM初始化
	TIM_PWM_Init();
	//置1 打开
	GPIO_SetBits(MOTOR_EN_PORT,MOTOR_EN_PIN);

}

/****
定时器4PWM初始化
****/

void TIM_PWM_Init(void)
{
	
	uint16_t CCR1_Val = 0;
	uint16_t CCR2_Val = 0;
	uint16_t CCR3_Val = 0;
	uint16_t CCR4_Val = 0;
	
	GPIO_InitTypeDef   					GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  		TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  					TIM_OCInitStructure;
	
	/* TIM clock enable */
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
	//TIM4 CH1-4: PB6-9
//	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin=PWM_OUT_PIN1|PWM_OUT_PIN2|PWM_OUT_PIN3|PWM_OUT_PIN4;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(PWM_OUT_PORT,&GPIO_InitStructure);

   /* Compute the prescaler value */
//   	PrescalerValue = (uint16_t) (SystemCoreClock /PWM_FREQ ) - 1;
	PrescalerValue = PWM_PSC;//分频为1MHz 
	
  /* Time base configuration */
  	TIM_TimeBaseStructure.TIM_Period = PWM_ARR;   //设置在下一个更新事件装入活动的自动重装载寄存器周期的值 PWM频率 72000/1000   = 7.2KHZ  ???
  	TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;  // //设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率  
  	TIM_TimeBaseStructure.TIM_ClockDivision = 0;////设置时钟分割:TDTS = Tck_tim
  	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式

  	TIM_TimeBaseInit(PWM_TIMER , &TIM_TimeBaseStructure);////根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

  /* PWM Mode configuration: Channel1 */
  	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;////选择定时器模式:TIM脉冲宽度调制模式1
  	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
  	TIM_OCInitStructure.TIM_Pulse = CCR1_Val;
  	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高

  	TIM_OC1Init(PWM_TIMER , &TIM_OCInitStructure); //根据T指定的参数初始化外设PWM_TIMER OC1

  	TIM_OC1PreloadConfig(PWM_TIMER , TIM_OCPreload_Enable); //使能TIM3在CCR2上的预装载寄存器

  /* PWM Mode configuration: Channel2 */
  //	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  	TIM_OCInitStructure.TIM_Pulse = CCR2_Val;

  	TIM_OC2Init(PWM_TIMER , &TIM_OCInitStructure);

  	TIM_OC2PreloadConfig(PWM_TIMER , TIM_OCPreload_Enable);

  /* PWM Mode configuration: Channel3 */
  //	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
		TIM_OCInitStructure.TIM_Pulse = CCR3_Val;

  	TIM_OC3Init(PWM_TIMER , &TIM_OCInitStructure);

  	TIM_OC3PreloadConfig(PWM_TIMER , TIM_OCPreload_Enable);

  /* PWM Mode configuration: Channel4 */
 // 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  	TIM_OCInitStructure.TIM_Pulse = CCR4_Val;

  	TIM_OC4Init(PWM_TIMER , &TIM_OCInitStructure);

  	TIM_OC4PreloadConfig(PWM_TIMER , TIM_OCPreload_Enable);

  	TIM_ARRPreloadConfig(PWM_TIMER , ENABLE);

  /* TIM enable counter */
  	TIM_Cmd(PWM_TIMER , ENABLE);
}




/******************电机失能************************/
 void MotorDisable(void)
 {
 	GPIO_ResetBits(MOTOR_EN_PORT ,MOTOR_EN_PIN );
 }
 
 
/******************电机使能************************/
 void MotorEnable(void )
 {
 	GPIO_SetBits(MOTOR_EN_PORT,MOTOR_EN_PIN );
 }

 

 /*********************电机A************************/

/****
电机A停止
****/
void MotorA_Brk(void)
{
// 		GPIO_ResetBits(MOTOR_EN_PORT ,MOTOR_EN_PIN );
		PWM_TIMER->CCR1 = 0;//占空比都设为0
		PWM_TIMER->CCR2 = 0;//!!!注意修改TIM
}
/****电极A前进*****/
void MotorA_Forward(uint16_t CCR2_Value)
{
    /* Set the Capture Compare Register value */
  	PWM_TIMER->CCR1 = 0 ;
 	PWM_TIMER->CCR2 = CCR2_Value;
}
/****电机A PWM修改****/
void MotorA_PWM_Update(s16 CCR_Value)
{
	if(CCR_Value >=0)
	{
		
		MotorA_Forward_PWM_Update(CCR_Value );
	}
	else
	{
		MotorA_Backward_PWM_Update(-CCR_Value );
	}
}
/****************A_前进PWM更新*******************/
void MotorA_Forward_PWM_Update(uint16_t CCR2_Value )
{
  /* Set the Capture Compare Register value */
		if(CCR2_Value<10)
		{
			CCR2_Value =0;
		}
  	    PWM_TIMER->CCR1 =0;
		PWM_TIMER->CCR2 =  CCR2_Value;
}
/******************电机A后退PWM更新**************************/
void MotorA_Backward_PWM_Update(uint16_t CCR1_Value)
{
	if(CCR1_Value<10)
		{
			CCR1_Value =0;
		}
	PWM_TIMER->CCR2 = 0;
	PWM_TIMER->CCR1 =  CCR1_Value;
	
}
/********************电机A后退**********************/
void MotorA_Backward(uint16_t CCR1_Value)
{	
	PWM_TIMER->CCR1 = CCR1_Value;
	PWM_TIMER->CCR2 =  0;
}




/**********************电机B*************************/

/****
电机B停止
****/
void MotorB_Brk(void)
{
// 		GPIO_ResetBits(MOTOR_EN_PORT ,MOTOR_EN_PIN );
		TIM4->CCR3 = 0;//占空比都设为0
		TIM4->CCR4 = 0;//!!!注意修改TIM
}
/****电极B前进*****/
void MotorB_Forward(uint16_t CCR4_Value)
{
		 /* Set the Capture Compare Register value */
  	TIM4->CCR3 = 0 ;
 		TIM4->CCR4 = CCR4_Value;
}
void MotorB_PWM_Update(s16 CCR_Value)
{
	if(CCR_Value >=0)
	{
		MotorB_Forward_PWM_Update(CCR_Value );
	}
	else
	{
		MotorB_Backward_PWM_Update(-CCR_Value );
	}
}
/****************B_前进PWM更新*******************/
void MotorB_Forward_PWM_Update(uint16_t CCR4_Value )
{
  /* Set the Capture Compare Register value */
  	TIM4->CCR3 =0;
		TIM4->CCR4 =  CCR4_Value;
}
/******************电机B后退PWM更新**************************/
void MotorB_Backward_PWM_Update(uint16_t CCR3_Value)
{
	TIM4->CCR4 = 0;
	TIM4->CCR3 =  CCR3_Value;
	
}
/********************电机B后退**********************/
void MotorB_Backward(uint16_t CCR3_Value)
{	
	TIM4->CCR3 = CCR3_Value;
	TIM4->CCR4 =  0;
}






