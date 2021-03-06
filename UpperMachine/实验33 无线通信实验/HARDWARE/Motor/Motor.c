
#include "Motor.h"
/****
ENA  ..

IN1A PA0
IN2A PA1

ENB  ..
IN1B  PA2
IN2B PA3

备注:
	普通马达 最高电压6V   速度变化  400 - 1000   重零到大
	伺服电机 

****/
uint16_t PrescalerValue = 1;

//初始化电机的使能IO口
void MotorInit(void)
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
	TIM5_PWM_Init();
	//置1 打开
	GPIO_SetBits(MOTOR_EN_PORT,MOTOR_EN_PIN);
}

/****
定时器3PWM初始化
****/

void TIM_PWM_Init(void)
{
	
	uint16_t CCR1_Val = 0;
	uint16_t CCR2_Val = 0;
	uint16_t CCR3_Val = 0;
	uint16_t CCR4_Val = 0;
	
	GPIO_InitTypeDef   					GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  			TIM_TimeBaseStructure;
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
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);  //使能或失能APB2时钟
	
	//PWM_TIMER CH1-4
	GPIO_InitStructure.GPIO_Pin=PWM_OUT_PIN1 | PWM_OUT_PIN2;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(PWM_OUT_PORTA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin=PWM_OUT_PIN3|PWM_OUT_PIN4;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(PWM_OUT_PORTB,&GPIO_InitStructure);


	PrescalerValue = PWM_PSC;//分频为1MHz 
	
  /* Time base configuration */
	//基本的时钟配置
  	TIM_TimeBaseStructure.TIM_Period = 1000;   //设置在下一个更新事件装入活动的自动重装载寄存器周期的值 PWM频率 72000/1000   = 7.2KHZ  ???
  	TIM_TimeBaseStructure.TIM_Prescaler = 2;  // //设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率  
  	TIM_TimeBaseStructure.TIM_ClockDivision = 0;////设置时钟分割:TDTS = Tck_tim
  	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式

  	TIM_TimeBaseInit(PWM_TIMER , &TIM_TimeBaseStructure);////根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

  	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;//选择定时器模式:TIM脉冲宽度调制模式1
  	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使�
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;


/* 
 * 配置通道1
 * PWM Mode configuration: Channel1
**/
//	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_Pulse = CCR1_Val;

  	TIM_OC1Init(PWM_TIMER , &TIM_OCInitStructure);

  	TIM_OC1PreloadConfig(PWM_TIMER , TIM_OCPreload_Enable);
	
/* 
 * 配置通道2
 * PWM Mode configuration: Channel2
**/
//	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  	TIM_OCInitStructure.TIM_Pulse = CCR2_Val;

  	TIM_OC2Init(PWM_TIMER , &TIM_OCInitStructure);

  	TIM_OC2PreloadConfig(PWM_TIMER , TIM_OCPreload_Enable);
	
/* 
 * 配置通道3
 * PWM Mode configuration: Channel3 
**/
//	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = CCR3_Val;

  	TIM_OC3Init(PWM_TIMER , &TIM_OCInitStructure);

  	TIM_OC3PreloadConfig(PWM_TIMER , TIM_OCPreload_Enable);

/* 
 * 配置通道4
 * PWM Mode configuration: Channel4
**/
// 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  	TIM_OCInitStructure.TIM_Pulse = CCR4_Val;

  	TIM_OC4Init(PWM_TIMER , &TIM_OCInitStructure);

  	TIM_OC4PreloadConfig(PWM_TIMER , TIM_OCPreload_Enable);

	TIM_ARRPreloadConfig(PWM_TIMER , ENABLE);

  /* TIM enable counter */
  	TIM_Cmd(PWM_TIMER , ENABLE);    //使能pwm
}


//lm298的使能可以直接拉高高，或者IO控制。

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

 
 
 //初始化定时器5的pwm波形
 
void TIM5_PWM_Init(void)
{
	uint16_t CCR3_Val = 0;
	uint16_t CCR4_Val = 0;
	
	GPIO_InitTypeDef   					GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  			TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  					TIM_OCInitStructure;
	
	/* TIM clock enable */
	if((TIM5 == TIM2) || (TIM5 == TIM3)||(TIM5 == TIM4) || 
		(TIM5 == TIM5)||(TIM5 == TIM6) || (TIM5 == TIM7)) 
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
	}
    if((TIM5 != TIM1) && (TIM5 != TIM8))
    {
		RCC_APB2PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
    }
	//enable GPIO clocks 
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO,ENABLE);  //使能或失能APB2时钟
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2|GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);


	PrescalerValue = PWM_PSC;//分频为1MHz 
	
  /* Time base configuration */
	//基本的时钟配置
  	TIM_TimeBaseStructure.TIM_Period = 1000;   //设置在下一个更新事件装入活动的自动重装载寄存器周期的值 PWM频率 72000/1000   = 7.2KHZ  ???
  	TIM_TimeBaseStructure.TIM_Prescaler = 2;  // //设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率  
  	TIM_TimeBaseStructure.TIM_ClockDivision = 0;////设置时钟分割:TDTS = Tck_tim
  	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式

  	TIM_TimeBaseInit(TIM5 , &TIM_TimeBaseStructure);////根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

  	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;//选择定时器模式:TIM脉冲宽度调制模式1
  	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使�
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

/* 
 * 配置通道3
 * PWM Mode configuration: Channel3 
**/
//	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = CCR3_Val;

  	TIM_OC3Init(TIM5 , &TIM_OCInitStructure);

  	TIM_OC3PreloadConfig(TIM5 , TIM_OCPreload_Enable);

/* 
 * 配置通道4
 * PWM Mode configuration: Channel4
**/
// 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  	TIM_OCInitStructure.TIM_Pulse = CCR4_Val;

  	TIM_OC4Init(TIM5 , &TIM_OCInitStructure);

  	TIM_OC4PreloadConfig(TIM5 , TIM_OCPreload_Enable);

	TIM_ARRPreloadConfig(TIM5 , ENABLE);

  /* TIM enable counter */
  	TIM_Cmd(TIM5 , ENABLE);    //使能pwm
}

 /*********************电机A************************/

/****
电机A停止
****/
//void MotorA_Brk(void)
//{
//// 	GPIO_ResetBits(MOTOR_EN_PORT ,MOTOR_EN_PIN );
//	PWM_TIMER->CCR1 = 0;//占空比都设为0
//	PWM_TIMER->CCR2 = 0;//!!!注意修改TIM
//}
///*******************电极A前�***********************/
//void MotorA_Forward(uint16_t CCR2_Value)
//{
//    /* Set the Capture Compare Register value */
//	if(CCR2_Value >  PWM_ARR)
//		CCR2_Value  =  PWM_ARR - 1; // CCR的值必须小于或等于ARR的值
//  	PWM_TIMER->CCR1 = 0 ;
// 	PWM_TIMER->CCR2 = CCR2_Value;
//}

///********************电机A后退**********************/
//void MotorA_Backward(uint16_t CCR1_Value)
//{	
//	if(CCR1_Value >  PWM_ARR)
//		CCR1_Value  =  PWM_ARR - 1; // CCR的值必须小于或等于ARR的值
//	PWM_TIMER->CCR1 = CCR1_Value;
//	PWM_TIMER->CCR2 =  0;
//}
///****电机A PWM修改****/
//void MotorA_PWM_Update(s16 CCR_Value)
//{
//	if(CCR_Value >=0)
//	{
//		
//		MotorA_Forward_PWM_Update(CCR_Value );
//	}
//	else
//	{
//		MotorA_Backward_PWM_Update(-CCR_Value );
//	}
//}
///****************A_前进PWM更新*******************/
//void MotorA_Forward_PWM_Update(uint16_t CCR2_Value )
//{
//  /* Set the Capture Compare Register value */
//	if(CCR2_Value<10)
//	{
//		CCR2_Value =0;
//	}
//	PWM_TIMER->CCR1 =0;
//	PWM_TIMER->CCR2 =  CCR2_Value;
//}
///******************电机A后退PWM更新**************************/
//void MotorA_Backward_PWM_Update(uint16_t CCR1_Value)
//{
//	if(CCR1_Value<10)
//	{
//		CCR1_Value =0;
//	}
//	PWM_TIMER->CCR2 = 0;
//	PWM_TIMER->CCR1 =  CCR1_Value;
//	
//}




///**********************电机B*************************/

///****
//电机B停止
//****/
//void MotorB_Brk(void)
//{
//// 		GPIO_ResetBits(MOTOR_EN_PORT ,MOTOR_EN_PIN );
//	PWM_TIMER->CCR3 = 0;//占空比都设为0
//	PWM_TIMER->CCR4 = 0;//!!!注意修改TIM
//}
///****电极B前进*****/
//void MotorB_Forward(uint16_t CCR4_Value)
//{
//		 /* Set the Capture Compare Register value */
//	if(CCR4_Value >  PWM_ARR)
//		CCR4_Value  =  PWM_ARR - 1; // CCR的值必须小于或等于ARR的值
//  	PWM_TIMER->CCR3 = 0 ;
// 	PWM_TIMER->CCR4 = CCR4_Value;
//}

///********************电机B后退**********************/
//void MotorB_Backward(uint16_t CCR3_Value)
//{	
//	if(CCR3_Value >  PWM_ARR)
//		CCR3_Value  =  PWM_ARR - 1; // CCR的值必须小于或等于ARR的值
//	PWM_TIMER->CCR3 = CCR3_Value;
//	PWM_TIMER->CCR4 =  0;
//}

//void MotorB_PWM_Update(s16 CCR_Value)
//{
//	if(CCR_Value >= 0)
//	{
////		CCR_Value += 20;
//		MotorB_Forward_PWM_Update(CCR_Value );
//	}
//	else
//	{
////		CCR_Value-=20;
//		MotorB_Backward_PWM_Update(-CCR_Value );
//	}
//}
///****************B_前进PWM更新*******************/
//void MotorB_Forward_PWM_Update(uint16_t CCR4_Value )
//{
//  /* Set the Capture Compare Register value */
//  	if(CCR4_Value<10)
//	{
//		CCR4_Value =0;
//	}
//	PWM_TIMER->CCR3 =0;
//	PWM_TIMER->CCR4 =  CCR4_Value;
//}


///******************电机B后退PWM更新**************************/
//void MotorB_Backward_PWM_Update(uint16_t CCR3_Value)
//{
//	if(CCR3_Value<10)
//	{
//		CCR3_Value =0;
//	}
//	PWM_TIMER->CCR4 = 0;
//	PWM_TIMER->CCR3 =  CCR3_Value;
//	
//}



//由于轴流风机只能正转，所以只需要使用一个pwm即可，四个pwm最多可支持四个   --四路风扇设定
/***风扇停止1***/
void FanA_Brk(void)
{
// 		GPIO_ResetBits(MOTOR_EN_PORT ,MOTOR_EN_PIN );
	PWM_TIMER->CCR1 = 0;//占空比都设为0
}
/****风扇正转***/

void FanA_Forward(uint16_t CCR1_Value)
{
		 /* Set the Capture Compare Register value */
	if(CCR1_Value >  PWM_ARR)
		CCR1_Value  =  PWM_ARR - 1; // CCR的值必须小于或等于ARR的值
	PWM_TIMER->CCR1 =  CCR1_Value;
}


//定义四个风机,前后左右四个  
//前推AB   A向吹
void FanAB_Forward(uint16_t CCR1_Value)
{
	if(CCR1_Value >  PWM_ARR)
		CCR1_Value  =  PWM_ARR - 1; // CCR的值必须小于或等于ARR的值
  	PWM_TIMER->CCR2 = 0 ;
 	PWM_TIMER->CCR1 = CCR1_Value;
}

//后退AB   	B向吹
void FanAB_Backward(uint16_t CCR2_Value)
{
	if(CCR2_Value >  PWM_ARR)
		CCR2_Value  =  PWM_ARR - 1; // CCR的值必须小于或等于ARR的值
  	PWM_TIMER->CCR1 = 0 ;
 	PWM_TIMER->CCR2 = CCR2_Value;
}

//前推CD   C向吹
void FanCD_Forward(uint16_t CCR3_Value)
{
	if(CCR3_Value >  PWM_ARR)
		CCR3_Value  =  PWM_ARR - 1; // CCR的值必须小于或等于ARR的值
  	TIM5->CCR4 = 0 ;
 	TIM5->CCR3 = CCR3_Value;
}

//后退CD  D向吹
void FanCD_Backward(uint16_t CCR4_Value)
{
	if(CCR4_Value >  PWM_ARR)
		CCR4_Value  =  PWM_ARR - 1; // CCR的值必须小于或等于ARR的值
  	TIM5->CCR3 = 0 ;
 	TIM5->CCR4 = CCR4_Value;
}

//AB项停止
void FanAB_Brk()
{
	PWM_TIMER->CCR1= 0;
 	PWM_TIMER->CCR2= 0;
}

//CD项停
void FanCD_Brk()
{
	TIM5->CCR3= 0;
 	TIM5->CCR4= 0;
}

//四项停
void FanABCD_Brk()
{
	PWM_TIMER->CCR1= 0;
 	PWM_TIMER->CCR2= 0;
	TIM5->CCR3= 0;
 	TIM5->CCR4= 0;
}

//AB项PWM的风机修改
void MotorAB_PWM_Update(s16 CCR_Value)
{
	if(CCR_Value >=0)
	{
		
		FanAB_Forward(CCR_Value );
	}
	else
	{
		FanAB_Backward(-CCR_Value );
	}
}

//CD项PWM的风机修改
void MotorCD_PWM_Update(s16 CCR_Value)
{
	if(CCR_Value >=0)
	{
		
		FanCD_Forward(CCR_Value );
	}
	else
	{
		FanCD_Backward(-CCR_Value );
	}
}
