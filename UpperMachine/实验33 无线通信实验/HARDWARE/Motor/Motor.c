
#include "Motor.h"
/****
ENA  ..

IN1A PA0
IN2A PA1

ENB  ..
IN1B  PA2
IN2B PA3

��ע:
	��ͨ��� ��ߵ�ѹ6V   �ٶȱ仯  400 - 1000   ���㵽��
	�ŷ���� 

****/
uint16_t PrescalerValue = 1;

//��ʼ�������ʹ��IO��
void MotorInit(void)
{
	//ʹ�ܽ�EN ��ʼ��
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(MOTOR_EN_PORT_CLK ,ENABLE);

	GPIO_InitStructure.GPIO_Pin =  MOTOR_EN_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(MOTOR_EN_PORT ,&GPIO_InitStructure);
	//��0 �ر�
	GPIO_ResetBits(MOTOR_EN_PORT ,MOTOR_EN_PIN );
	//��ʱ��PWM��ʼ��
	TIM_PWM_Init();
	//��1 ��
	GPIO_SetBits(MOTOR_EN_PORT,MOTOR_EN_PIN);
}

/****
��ʱ��5PWM��ʼ��
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
	RCC_APB2PeriphClockCmd(	PWM_OUT_PORT_CLK|RCC_APB2Periph_AFIO,ENABLE);  //ʹ�ܻ�ʧ��APB2ʱ��
	
	//PWM_TIMER CH1-4
	GPIO_InitStructure.GPIO_Pin=PWM_OUT_PIN1 | PWM_OUT_PIN2|PWM_OUT_PIN3|PWM_OUT_PIN4;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(PWM_OUT_PORT,&GPIO_InitStructure);

	PrescalerValue = PWM_PSC;//��ƵΪ1MHz 
	
  /* Time base configuration */
	//������ʱ������
  	TIM_TimeBaseStructure.TIM_Period = PWM_ARR;   //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ PWMƵ�� 72000/1000   = 7.2KHZ  ???
  	TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;  // //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��  
  	TIM_TimeBaseStructure.TIM_ClockDivision = 0;////����ʱ�ӷָ�:TDTS = Tck_tim
  	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ

  	TIM_TimeBaseInit(PWM_TIMER , &TIM_TimeBaseStructure);////����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

  	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;//ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ1
  	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ�
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;


/* 
 * ����ͨ��1
 * PWM Mode configuration: Channel1
**/
//	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_Pulse = CCR1_Val;

  	TIM_OC1Init(PWM_TIMER , &TIM_OCInitStructure);

  	TIM_OC1PreloadConfig(PWM_TIMER , TIM_OCPreload_Enable);
	
/* 
 * ����ͨ��2
 * PWM Mode configuration: Channel2
**/
//	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  	TIM_OCInitStructure.TIM_Pulse = CCR2_Val;

  	TIM_OC2Init(PWM_TIMER , &TIM_OCInitStructure);

  	TIM_OC2PreloadConfig(PWM_TIMER , TIM_OCPreload_Enable);
	
/* 
 * ����ͨ��3
 * PWM Mode configuration: Channel3 
**/
//	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = CCR3_Val;

  	TIM_OC3Init(PWM_TIMER , &TIM_OCInitStructure);

  	TIM_OC3PreloadConfig(PWM_TIMER , TIM_OCPreload_Enable);

/* 
 * ����ͨ��4
 * PWM Mode configuration: Channel4
**/
// 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  	TIM_OCInitStructure.TIM_Pulse = CCR4_Val;

  	TIM_OC4Init(PWM_TIMER , &TIM_OCInitStructure);

  	TIM_OC4PreloadConfig(PWM_TIMER , TIM_OCPreload_Enable);

	TIM_ARRPreloadConfig(PWM_TIMER , ENABLE);

  /* TIM enable counter */
  	TIM_Cmd(PWM_TIMER , ENABLE);    //ʹ��pwm
}


//lm298��ʹ�ܿ���ֱ�����߸ߣ�����IO���ơ�

/******************���ʧ��************************/
 void MotorDisable(void)
 {
 	GPIO_ResetBits(MOTOR_EN_PORT ,MOTOR_EN_PIN );
 }
 
 
/******************���ʹ��************************/
 void MotorEnable(void )
 {
 	GPIO_SetBits(MOTOR_EN_PORT,MOTOR_EN_PIN );
 }

 

 /*********************���A************************/

/****
���Aֹͣ
****/
//void MotorA_Brk(void)
//{
//// 	GPIO_ResetBits(MOTOR_EN_PORT ,MOTOR_EN_PIN );
//	PWM_TIMER->CCR1 = 0;//ռ�ձȶ���Ϊ0
//	PWM_TIMER->CCR2 = 0;//!!!ע���޸�TIM
//}
///*******************�缫Aǰ�***********************/
//void MotorA_Forward(uint16_t CCR2_Value)
//{
//    /* Set the Capture Compare Register value */
//	if(CCR2_Value >  PWM_ARR)
//		CCR2_Value  =  PWM_ARR - 1; // CCR��ֵ����С�ڻ����ARR��ֵ
//  	PWM_TIMER->CCR1 = 0 ;
// 	PWM_TIMER->CCR2 = CCR2_Value;
//}

///********************���A����**********************/
//void MotorA_Backward(uint16_t CCR1_Value)
//{	
//	if(CCR1_Value >  PWM_ARR)
//		CCR1_Value  =  PWM_ARR - 1; // CCR��ֵ����С�ڻ����ARR��ֵ
//	PWM_TIMER->CCR1 = CCR1_Value;
//	PWM_TIMER->CCR2 =  0;
//}
///****���A PWM�޸�****/
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
///****************A_ǰ��PWM����*******************/
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
///******************���A����PWM����**************************/
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




///**********************���B*************************/

///****
//���Bֹͣ
//****/
//void MotorB_Brk(void)
//{
//// 		GPIO_ResetBits(MOTOR_EN_PORT ,MOTOR_EN_PIN );
//	PWM_TIMER->CCR3 = 0;//ռ�ձȶ���Ϊ0
//	PWM_TIMER->CCR4 = 0;//!!!ע���޸�TIM
//}
///****�缫Bǰ��*****/
//void MotorB_Forward(uint16_t CCR4_Value)
//{
//		 /* Set the Capture Compare Register value */
//	if(CCR4_Value >  PWM_ARR)
//		CCR4_Value  =  PWM_ARR - 1; // CCR��ֵ����С�ڻ����ARR��ֵ
//  	PWM_TIMER->CCR3 = 0 ;
// 	PWM_TIMER->CCR4 = CCR4_Value;
//}

///********************���B����**********************/
//void MotorB_Backward(uint16_t CCR3_Value)
//{	
//	if(CCR3_Value >  PWM_ARR)
//		CCR3_Value  =  PWM_ARR - 1; // CCR��ֵ����С�ڻ����ARR��ֵ
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
///****************B_ǰ��PWM����*******************/
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


///******************���B����PWM����**************************/
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



//�����������ֻ����ת������ֻ��Ҫʹ��һ��pwm���ɣ��ĸ�pwm����֧���ĸ�
/***����ֹͣ1***/
void FanA_Brk(void)
{
// 		GPIO_ResetBits(MOTOR_EN_PORT ,MOTOR_EN_PIN );
	PWM_TIMER->CCR1 = 0;//ռ�ձȶ���Ϊ0
}
/****������ת***/

void FanA_Forward(uint16_t CCR1_Value)
{
		 /* Set the Capture Compare Register value */
	if(CCR1_Value >  PWM_ARR)
		CCR1_Value  =  PWM_ARR - 1; // CCR��ֵ����С�ڻ����ARR��ֵ
	PWM_TIMER->CCR1 =  CCR1_Value;
}







