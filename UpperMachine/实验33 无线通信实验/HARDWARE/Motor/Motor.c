
#include "Motor.h"
/****
ENA  ..

IN1A PA0
IN2A PA1

ENB  ..
IN1B  PA2
IN2B PA3

±¸×¢:
	ÆÕÍ¨Âí´ï ×î¸ßµçÑ¹6V   ËÙ¶È±ä»¯  400 - 1000   ÖØÁãµ½´ó
	ËÅ·þµç»ú 

****/
uint16_t PrescalerValue = 1;

//³õÊ¼»¯µç»úµÄÊ¹ÄÜIO¿Ú
void MotorInit(void)
{
	//Ê¹ÄÜ½ÅEN ³õÊ¼»¯
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(MOTOR_EN_PORT_CLK ,ENABLE);

	GPIO_InitStructure.GPIO_Pin =  MOTOR_EN_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(MOTOR_EN_PORT ,&GPIO_InitStructure);
	//ÖÃ0 ¹Ø±Õ
	GPIO_ResetBits(MOTOR_EN_PORT ,MOTOR_EN_PIN );
	//¶¨Ê±Æ÷PWM³õÊ¼»¯
	TIM_PWM_Init();
	TIM5_PWM_Init();
	//ÖÃ1 ´ò¿ª
	GPIO_SetBits(MOTOR_EN_PORT,MOTOR_EN_PIN);
}

/****
¶¨Ê±Æ÷3PWM³õÊ¼»¯
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
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);  //Ê¹ÄÜ»òÊ§ÄÜAPB2Ê±ÖÓ
	
	//PWM_TIMER CH1-4
	GPIO_InitStructure.GPIO_Pin=PWM_OUT_PIN1 | PWM_OUT_PIN2;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(PWM_OUT_PORTA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin=PWM_OUT_PIN3|PWM_OUT_PIN4;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(PWM_OUT_PORTB,&GPIO_InitStructure);


	PrescalerValue = PWM_PSC;//·ÖÆµÎª1MHz 
	
  /* Time base configuration */
	//»ù±¾µÄÊ±ÖÓÅäÖÃ
  	TIM_TimeBaseStructure.TIM_Period = 1000;   //ÉèÖÃÔÚÏÂÒ»¸ö¸üÐÂÊÂ¼þ×°Èë»î¶¯µÄ×Ô¶¯ÖØ×°ÔØ¼Ä´æÆ÷ÖÜÆÚµÄÖµ PWMÆµÂÊ 72000/1000   = 7.2KHZ  ???
  	TIM_TimeBaseStructure.TIM_Prescaler = 2;  // //ÉèÖÃÓÃÀ´×÷ÎªTIMxÊ±ÖÓÆµÂÊ³ýÊýµÄÔ¤·ÖÆµÖµ  10KhzµÄ¼ÆÊýÆµÂÊ  
  	TIM_TimeBaseStructure.TIM_ClockDivision = 0;////ÉèÖÃÊ±ÖÓ·Ö¸î:TDTS = Tck_tim
  	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIMÏòÉÏ¼ÆÊýÄ£Ê½

  	TIM_TimeBaseInit(PWM_TIMER , &TIM_TimeBaseStructure);////¸ù¾ÝTIM_TimeBaseInitStructÖÐÖ¸¶¨µÄ²ÎÊý³õÊ¼»¯TIMxµÄÊ±¼ä»ùÊýµ¥Î»

  	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;//Ñ¡Ôñ¶¨Ê±Æ÷Ä£Ê½:TIMÂö³å¿í¶Èµ÷ÖÆÄ£Ê½1
  	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //±È½ÏÊä³öÊ¹Ä
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;


/* 
 * ÅäÖÃÍ¨µÀ1
 * PWM Mode configuration: Channel1
**/
//	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //±È½ÏÊä³öÊ¹ÄÜ
	TIM_OCInitStructure.TIM_Pulse = CCR1_Val;

  	TIM_OC1Init(PWM_TIMER , &TIM_OCInitStructure);

  	TIM_OC1PreloadConfig(PWM_TIMER , TIM_OCPreload_Enable);
	
/* 
 * ÅäÖÃÍ¨µÀ2
 * PWM Mode configuration: Channel2
**/
//	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  	TIM_OCInitStructure.TIM_Pulse = CCR2_Val;

  	TIM_OC2Init(PWM_TIMER , &TIM_OCInitStructure);

  	TIM_OC2PreloadConfig(PWM_TIMER , TIM_OCPreload_Enable);
	
/* 
 * ÅäÖÃÍ¨µÀ3
 * PWM Mode configuration: Channel3 
**/
//	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = CCR3_Val;

  	TIM_OC3Init(PWM_TIMER , &TIM_OCInitStructure);

  	TIM_OC3PreloadConfig(PWM_TIMER , TIM_OCPreload_Enable);

/* 
 * ÅäÖÃÍ¨µÀ4
 * PWM Mode configuration: Channel4
**/
// 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  	TIM_OCInitStructure.TIM_Pulse = CCR4_Val;

  	TIM_OC4Init(PWM_TIMER , &TIM_OCInitStructure);

  	TIM_OC4PreloadConfig(PWM_TIMER , TIM_OCPreload_Enable);

	TIM_ARRPreloadConfig(PWM_TIMER , ENABLE);

  /* TIM enable counter */
  	TIM_Cmd(PWM_TIMER , ENABLE);    //Ê¹ÄÜpwm
}


//lm298µÄÊ¹ÄÜ¿ÉÒÔÖ±½ÓÀ­¸ß¸ß£¬»òÕßIO¿ØÖÆ¡£

/******************µç»úÊ§ÄÜ************************/
 void MotorDisable(void)
 {
 	GPIO_ResetBits(MOTOR_EN_PORT ,MOTOR_EN_PIN );
 }
 
 
/******************µç»úÊ¹ÄÜ************************/
 void MotorEnable(void )
 {
 	GPIO_SetBits(MOTOR_EN_PORT,MOTOR_EN_PIN );
 }

 
 
 //³õÊ¼»¯¶¨Ê±Æ÷5µÄpwm²¨ÐÎ
 
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
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO,ENABLE);  //Ê¹ÄÜ»òÊ§ÄÜAPB2Ê±ÖÓ
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2|GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);


	PrescalerValue = PWM_PSC;//·ÖÆµÎª1MHz 
	
  /* Time base configuration */
	//»ù±¾µÄÊ±ÖÓÅäÖÃ
  	TIM_TimeBaseStructure.TIM_Period = 1000;   //ÉèÖÃÔÚÏÂÒ»¸ö¸üÐÂÊÂ¼þ×°Èë»î¶¯µÄ×Ô¶¯ÖØ×°ÔØ¼Ä´æÆ÷ÖÜÆÚµÄÖµ PWMÆµÂÊ 72000/1000   = 7.2KHZ  ???
  	TIM_TimeBaseStructure.TIM_Prescaler = 2;  // //ÉèÖÃÓÃÀ´×÷ÎªTIMxÊ±ÖÓÆµÂÊ³ýÊýµÄÔ¤·ÖÆµÖµ  10KhzµÄ¼ÆÊýÆµÂÊ  
  	TIM_TimeBaseStructure.TIM_ClockDivision = 0;////ÉèÖÃÊ±ÖÓ·Ö¸î:TDTS = Tck_tim
  	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIMÏòÉÏ¼ÆÊýÄ£Ê½

  	TIM_TimeBaseInit(TIM5 , &TIM_TimeBaseStructure);////¸ù¾ÝTIM_TimeBaseInitStructÖÐÖ¸¶¨µÄ²ÎÊý³õÊ¼»¯TIMxµÄÊ±¼ä»ùÊýµ¥Î»

  	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;//Ñ¡Ôñ¶¨Ê±Æ÷Ä£Ê½:TIMÂö³å¿í¶Èµ÷ÖÆÄ£Ê½1
  	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //±È½ÏÊä³öÊ¹Ä
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

/* 
 * ÅäÖÃÍ¨µÀ3
 * PWM Mode configuration: Channel3 
**/
//	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = CCR3_Val;

  	TIM_OC3Init(TIM5 , &TIM_OCInitStructure);

  	TIM_OC3PreloadConfig(TIM5 , TIM_OCPreload_Enable);

/* 
 * ÅäÖÃÍ¨µÀ4
 * PWM Mode configuration: Channel4
**/
// 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  	TIM_OCInitStructure.TIM_Pulse = CCR4_Val;

  	TIM_OC4Init(TIM5 , &TIM_OCInitStructure);

  	TIM_OC4PreloadConfig(TIM5 , TIM_OCPreload_Enable);

	TIM_ARRPreloadConfig(TIM5 , ENABLE);

  /* TIM enable counter */
  	TIM_Cmd(TIM5 , ENABLE);    //Ê¹ÄÜpwm
}

 /*********************µç»úA************************/

/****
µç»úAÍ£Ö¹
****/
//void MotorA_Brk(void)
//{
//// 	GPIO_ResetBits(MOTOR_EN_PORT ,MOTOR_EN_PIN );
//	PWM_TIMER->CCR1 = 0;//Õ¼¿Õ±È¶¼ÉèÎª0
//	PWM_TIMER->CCR2 = 0;//!!!×¢ÒâÐÞ¸ÄTIM
//}
///*******************µç¼«AÇ°½***********************/
//void MotorA_Forward(uint16_t CCR2_Value)
//{
//    /* Set the Capture Compare Register value */
//	if(CCR2_Value >  PWM_ARR)
//		CCR2_Value  =  PWM_ARR - 1; // CCRµÄÖµ±ØÐëÐ¡ÓÚ»òµÈÓÚARRµÄÖµ
//  	PWM_TIMER->CCR1 = 0 ;
// 	PWM_TIMER->CCR2 = CCR2_Value;
//}

///********************µç»úAºóÍË**********************/
//void MotorA_Backward(uint16_t CCR1_Value)
//{	
//	if(CCR1_Value >  PWM_ARR)
//		CCR1_Value  =  PWM_ARR - 1; // CCRµÄÖµ±ØÐëÐ¡ÓÚ»òµÈÓÚARRµÄÖµ
//	PWM_TIMER->CCR1 = CCR1_Value;
//	PWM_TIMER->CCR2 =  0;
//}
///****µç»úA PWMÐÞ¸Ä****/
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
///****************A_Ç°½øPWM¸üÐÂ*******************/
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
///******************µç»úAºóÍËPWM¸üÐÂ**************************/
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




///**********************µç»úB*************************/

///****
//µç»úBÍ£Ö¹
//****/
//void MotorB_Brk(void)
//{
//// 		GPIO_ResetBits(MOTOR_EN_PORT ,MOTOR_EN_PIN );
//	PWM_TIMER->CCR3 = 0;//Õ¼¿Õ±È¶¼ÉèÎª0
//	PWM_TIMER->CCR4 = 0;//!!!×¢ÒâÐÞ¸ÄTIM
//}
///****µç¼«BÇ°½ø*****/
//void MotorB_Forward(uint16_t CCR4_Value)
//{
//		 /* Set the Capture Compare Register value */
//	if(CCR4_Value >  PWM_ARR)
//		CCR4_Value  =  PWM_ARR - 1; // CCRµÄÖµ±ØÐëÐ¡ÓÚ»òµÈÓÚARRµÄÖµ
//  	PWM_TIMER->CCR3 = 0 ;
// 	PWM_TIMER->CCR4 = CCR4_Value;
//}

///********************µç»úBºóÍË**********************/
//void MotorB_Backward(uint16_t CCR3_Value)
//{	
//	if(CCR3_Value >  PWM_ARR)
//		CCR3_Value  =  PWM_ARR - 1; // CCRµÄÖµ±ØÐëÐ¡ÓÚ»òµÈÓÚARRµÄÖµ
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
///****************B_Ç°½øPWM¸üÐÂ*******************/
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


///******************µç»úBºóÍËPWM¸üÐÂ**************************/
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



//ÓÉÓÚÖáÁ÷·ç»úÖ»ÄÜÕý×ª£¬ËùÒÔÖ»ÐèÒªÊ¹ÓÃÒ»¸öpwm¼´¿É£¬ËÄ¸öpwm×î¶à¿ÉÖ§³ÖËÄ¸ö   --ËÄÂ··çÉÈÉè¶¨
/***·çÉÈÍ£Ö¹1***/
void FanA_Brk(void)
{
// 		GPIO_ResetBits(MOTOR_EN_PORT ,MOTOR_EN_PIN );
	PWM_TIMER->CCR1 = 0;//Õ¼¿Õ±È¶¼ÉèÎª0
}
/****·çÉÈÕý×ª***/

void FanA_Forward(uint16_t CCR1_Value)
{
		 /* Set the Capture Compare Register value */
	if(CCR1_Value >  PWM_ARR)
		CCR1_Value  =  PWM_ARR - 1; // CCRµÄÖµ±ØÐëÐ¡ÓÚ»òµÈÓÚARRµÄÖµ
	PWM_TIMER->CCR1 =  CCR1_Value;
}


//¶¨ÒåËÄ¸ö·ç»ú,Ç°ºó×óÓÒËÄ¸ö  
//Ç°ÍÆAB   AÏò´µ
void FanAB_Forward(uint16_t CCR1_Value)
{
	if(CCR1_Value >  PWM_ARR)
		CCR1_Value  =  PWM_ARR - 1; // CCRµÄÖµ±ØÐëÐ¡ÓÚ»òµÈÓÚARRµÄÖµ
  	PWM_TIMER->CCR2 = 0 ;
 	PWM_TIMER->CCR1 = CCR1_Value;
}

//ºóÍËAB   	BÏò´µ
void FanAB_Backward(uint16_t CCR2_Value)
{
	if(CCR2_Value >  PWM_ARR)
		CCR2_Value  =  PWM_ARR - 1; // CCRµÄÖµ±ØÐëÐ¡ÓÚ»òµÈÓÚARRµÄÖµ
  	PWM_TIMER->CCR1 = 0 ;
 	PWM_TIMER->CCR2 = CCR2_Value;
}

//Ç°ÍÆCD   CÏò´µ
void FanCD_Forward(uint16_t CCR3_Value)
{
	if(CCR3_Value >  PWM_ARR)
		CCR3_Value  =  PWM_ARR - 1; // CCRµÄÖµ±ØÐëÐ¡ÓÚ»òµÈÓÚARRµÄÖµ
  	TIM5->CCR4 = 0 ;
 	TIM5->CCR3 = CCR3_Value;
}

//ºóÍËCD  DÏò´µ
void FanCD_Backward(uint16_t CCR4_Value)
{
	if(CCR4_Value >  PWM_ARR)
		CCR4_Value  =  PWM_ARR - 1; // CCRµÄÖµ±ØÐëÐ¡ÓÚ»òµÈÓÚARRµÄÖµ
  	TIM5->CCR3 = 0 ;
 	TIM5->CCR4 = CCR4_Value;
}

//ABÏîÍ£Ö¹
void FanAB_Brk()
{
	PWM_TIMER->CCR1= 0;
 	PWM_TIMER->CCR2= 0;
}

//CDÏîÍ£
void FanCD_Brk()
{
	TIM5->CCR3= 0;
 	TIM5->CCR4= 0;
}

//ËÄÏîÍ£
void FanABCD_Brk()
{
	PWM_TIMER->CCR1= 0;
 	PWM_TIMER->CCR2= 0;
	TIM5->CCR3= 0;
 	TIM5->CCR4= 0;
}

//ABÏîPWMµÄ·ç»úÐÞ¸Ä
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

//CDÏîPWMµÄ·ç»úÐÞ¸Ä
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
