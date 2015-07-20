/*Ƕ��ʽ��԰stm32 PWM�������⺯����1.0�汾 ����֮��ϣ��ͬѧ�ǿ��Զ���޸ģ�ʹ�����
�����ơ�
���� ��� 2013.4.1 */

//��ʱ��2/5ʱ��PA0,PA1,PA2,PA3
//��ʱ��3ʱ��PA6,PA7,PB0,PB1
//��ʱ��4ʱ��PB6,PB7,PB8,PB9
#include<stm32f10x.h>
#include"pwm.h"

//ʹ���ĸ���ʱ������1
#define tim2 0
#define tim3 1
#define tim4 0
//��������ʱ������
#define TIME2_CYCLE_MS 5
#define TIME3_CYCLE_MS 5
#define TIME4_CYCLE_MS 5

//��������pwm���ڣ�Ԥ��Ƶ100��ǰ�ᣩ
#define CYCLE_MS(X)  (720*X)   


void pwm_config(TIMtype type)
{
  TIM_OCInitTypeDef TIM_OCInitStruct;					        //PWM�ĳ�ʼ��
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;			    //��ʱ����ʼ��

  #if  tim2
  TIM_TimeBaseInitStruct. TIM_Prescaler=99;				        //Ԥ��Ƶ��periodһ������pwm������
  TIM_TimeBaseInitStruct .TIM_CounterMode=TIM_CounterMode_Up;
  TIM_TimeBaseInitStruct .TIM_Period=CYCLE_MS(TIME2_CYCLE_MS)-1;//�ؼ��غ�Ԥ��Ƶһ������pwm����
  TIM_TimeBaseInitStruct .TIM_ClockDivision=0;
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
  TIM_Cmd(TIM2, ENABLE);
  #endif
  #if tim3
  TIM_TimeBaseInitStruct. TIM_Prescaler=99;				     //Ԥ��Ƶ��periodһ������pwm������
  TIM_TimeBaseInitStruct .TIM_CounterMode=TIM_CounterMode_Up;
  TIM_TimeBaseInitStruct .TIM_Period=CYCLE_MS(TIME3_CYCLE_MS)-1; //�ؼ��غ�Ԥ��Ƶһ������pwm����
  TIM_TimeBaseInitStruct .TIM_ClockDivision=0;
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);
  TIM_Cmd(TIM3, ENABLE);
  #endif
  #if	tim4
  TIM_TimeBaseInitStruct. TIM_Prescaler=99;				     //Ԥ��Ƶ��periodһ������pwm������
  TIM_TimeBaseInitStruct .TIM_CounterMode=TIM_CounterMode_Up;
  TIM_TimeBaseInitStruct .TIM_Period=CYCLE_MS(TIME4_CYCLE_MS)-1;//�ؼ��غ�Ԥ��Ƶһ������pwm����
  TIM_TimeBaseInitStruct .TIM_ClockDivision=0;
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStruct);
  TIM_Cmd(TIM4, ENABLE);
  #endif



  if(type==TIM2_1)
  {
  TIM_OCInitStruct .TIM_OCMode=TIM_OCMode_PWM2;					
  TIM_OCInitStruct .TIM_OutputState=TIM_OutputState_Enable;
  TIM_OCInitStruct .TIM_Pulse=0;						   //��pulse/preiod	����������pwmռ�ձ�
  TIM_OCInitStruct .TIM_OCPolarity=TIM_OCPolarity_Low;
  TIM_OC1Init(TIM2,&TIM_OCInitStruct);
  TIM_ARRPreloadConfig( TIM2,ENABLE);
  TIM_OC1PreloadConfig( TIM2, TIM_OCPreload_Enable); 
  }
  else if(type==TIM2_2)
  {
  TIM_OCInitStruct .TIM_OCMode=TIM_OCMode_PWM2;					
  TIM_OCInitStruct .TIM_OutputState=TIM_OutputState_Enable;
  TIM_OCInitStruct .TIM_Pulse=0;						   //��pulse/preiod	����������pwmռ�ձ�
  TIM_OCInitStruct .TIM_OCPolarity=TIM_OCPolarity_Low;
  TIM_OC2Init(TIM2,&TIM_OCInitStruct);
  TIM_ARRPreloadConfig( TIM2,ENABLE);
  TIM_OC2PreloadConfig( TIM2, TIM_OCPreload_Enable); 
  }
 else if(type==TIM2_3)
  {
  TIM_OCInitStruct .TIM_OCMode=TIM_OCMode_PWM2;					
  TIM_OCInitStruct .TIM_OutputState=TIM_OutputState_Enable;
  TIM_OCInitStruct .TIM_Pulse=0;						   //��pulse/preiod	����������pwmռ�ձ�
  TIM_OCInitStruct .TIM_OCPolarity=TIM_OCPolarity_Low;
  TIM_OC3Init(TIM2,&TIM_OCInitStruct);
  TIM_ARRPreloadConfig( TIM2,ENABLE);
  TIM_OC3PreloadConfig( TIM2, TIM_OCPreload_Enable);
  }
   else if(type==TIM2_4)
  {
  TIM_OCInitStruct .TIM_OCMode=TIM_OCMode_PWM2;					
  TIM_OCInitStruct .TIM_OutputState=TIM_OutputState_Enable;
  TIM_OCInitStruct .TIM_Pulse=0;						   //��pulse/preiod	����������pwmռ�ձ�
  TIM_OCInitStruct .TIM_OCPolarity=TIM_OCPolarity_Low;
  TIM_OC4Init(TIM2,&TIM_OCInitStruct);
  TIM_ARRPreloadConfig( TIM2,ENABLE);
  TIM_OC4PreloadConfig( TIM2, TIM_OCPreload_Enable);
  }
   else if(type==TIM3_1)
  {
  TIM_OCInitStruct .TIM_OCMode=TIM_OCMode_PWM2;					
  TIM_OCInitStruct .TIM_OutputState=TIM_OutputState_Enable;
  TIM_OCInitStruct .TIM_Pulse=0;						   //��pulse/preiod	����������pwmռ�ձ�
  TIM_OCInitStruct .TIM_OCPolarity=TIM_OCPolarity_Low;
  TIM_OC1Init(TIM3,&TIM_OCInitStruct);
  TIM_ARRPreloadConfig( TIM3,ENABLE);
  TIM_OC1PreloadConfig( TIM3, TIM_OCPreload_Enable);
  }
   else if(type==TIM3_2)
  {
  TIM_OCInitStruct .TIM_OCMode=TIM_OCMode_PWM2;					
  TIM_OCInitStruct .TIM_OutputState=TIM_OutputState_Enable;
  TIM_OCInitStruct .TIM_Pulse=0;						   //��pulse/preiod	����������pwmռ�ձ�
  TIM_OCInitStruct .TIM_OCPolarity=TIM_OCPolarity_Low;
  TIM_OC2Init(TIM3,&TIM_OCInitStruct);
  TIM_ARRPreloadConfig( TIM3,ENABLE);
  TIM_OC2PreloadConfig( TIM3, TIM_OCPreload_Enable);
  }
   else if(type==TIM3_3)
  {
  TIM_OCInitStruct .TIM_OCMode=TIM_OCMode_PWM2;					
  TIM_OCInitStruct .TIM_OutputState=TIM_OutputState_Enable;
  TIM_OCInitStruct .TIM_Pulse=0;						   //��pulse/preiod	����������pwmռ�ձ�
  TIM_OCInitStruct .TIM_OCPolarity=TIM_OCPolarity_Low;
  TIM_OC3Init(TIM3,&TIM_OCInitStruct);
  TIM_ARRPreloadConfig( TIM3,ENABLE);
  TIM_OC3PreloadConfig( TIM3, TIM_OCPreload_Enable);
  }
   else if(type==TIM3_4)
  {
  TIM_OCInitStruct .TIM_OCMode=TIM_OCMode_PWM2;					
  TIM_OCInitStruct .TIM_OutputState=TIM_OutputState_Enable;
  TIM_OCInitStruct .TIM_Pulse=0;						   //��pulse/preiod	����������pwmռ�ձ�
  TIM_OCInitStruct .TIM_OCPolarity=TIM_OCPolarity_Low;
  TIM_OC4Init(TIM3,&TIM_OCInitStruct);
  TIM_ARRPreloadConfig( TIM3,ENABLE);
  TIM_OC4PreloadConfig( TIM3, TIM_OCPreload_Enable);
  }
   else if(type==TIM4_1)
  {
  TIM_OCInitStruct .TIM_OCMode=TIM_OCMode_PWM2;					
  TIM_OCInitStruct .TIM_OutputState=TIM_OutputState_Enable;
  TIM_OCInitStruct .TIM_Pulse=0;						   //��pulse/preiod	����������pwmռ�ձ�
  TIM_OCInitStruct .TIM_OCPolarity=TIM_OCPolarity_Low;
  TIM_OC1Init(TIM4,&TIM_OCInitStruct);
  TIM_ARRPreloadConfig( TIM4,ENABLE);
  TIM_OC1PreloadConfig( TIM4, TIM_OCPreload_Enable);
  }
   else if(type==TIM4_2)
  {
  TIM_OCInitStruct .TIM_OCMode=TIM_OCMode_PWM2;					
  TIM_OCInitStruct .TIM_OutputState=TIM_OutputState_Enable;
  TIM_OCInitStruct .TIM_Pulse=0;						   //��pulse/preiod	����������pwmռ�ձ�
  TIM_OCInitStruct .TIM_OCPolarity=TIM_OCPolarity_Low;
  TIM_OC2Init(TIM4,&TIM_OCInitStruct);
  TIM_ARRPreloadConfig( TIM4,ENABLE);
  TIM_OC2PreloadConfig( TIM4, TIM_OCPreload_Enable);
  }
   else if(type==TIM4_3)
  {
  TIM_OCInitStruct .TIM_OCMode=TIM_OCMode_PWM2;					
  TIM_OCInitStruct .TIM_OutputState=TIM_OutputState_Enable;
  TIM_OCInitStruct .TIM_Pulse=0;						   //��pulse/preiod	����������pwmռ�ձ�
  TIM_OCInitStruct .TIM_OCPolarity=TIM_OCPolarity_Low;
  TIM_OC3Init(TIM4,&TIM_OCInitStruct);
  TIM_ARRPreloadConfig( TIM4,ENABLE);
  TIM_OC3PreloadConfig( TIM4, TIM_OCPreload_Enable);
  }
   else if(type==TIM4_4)
  {
  TIM_OCInitStruct .TIM_OCMode=TIM_OCMode_PWM2;					
  TIM_OCInitStruct .TIM_OutputState=TIM_OutputState_Enable;
  TIM_OCInitStruct .TIM_Pulse=0;						   //��pulse/preiod	����������pwmռ�ձ�
  TIM_OCInitStruct .TIM_OCPolarity=TIM_OCPolarity_Low;
  TIM_OC4Init(TIM4,&TIM_OCInitStruct);
  TIM_ARRPreloadConfig( TIM4,ENABLE);
  TIM_OC4PreloadConfig( TIM4, TIM_OCPreload_Enable);
  }



}

void pwm_gpio_init(TIMtype type)
{
   GPIO_InitTypeDef GPIO_InitStruct;
   RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);
 
		if( type==TIM2_1)	   	
		{ 
		  RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM2, ENABLE);
		  GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0;
          GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
          GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;
          GPIO_Init(GPIOA, & GPIO_InitStruct);
		}
		else if(type==TIM2_2)
		{ 
		  RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM2, ENABLE);
		  GPIO_InitStruct.GPIO_Pin=GPIO_Pin_1;
          GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
          GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;
          GPIO_Init(GPIOA, & GPIO_InitStruct);
		}
	    else	if(type==TIM2_3)
		{ 
		 RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM2, ENABLE);
		 GPIO_InitStruct.GPIO_Pin=GPIO_Pin_2;
         GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
         GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;
         GPIO_Init(GPIOA, & GPIO_InitStruct);
		}
			else	if(type==TIM2_4)
		{  
		  RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM2, ENABLE);
		  GPIO_InitStruct.GPIO_Pin=GPIO_Pin_3;
          GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
          GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;
          GPIO_Init(GPIOA, & GPIO_InitStruct);
		}
			else	if( type==TIM3_1)
		{ 
		  RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM3, ENABLE);
		  GPIO_InitStruct.GPIO_Pin=GPIO_Pin_6;
          GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
          GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;
          GPIO_Init(GPIOA, & GPIO_InitStruct);
		}
			else	if( type==TIM3_2)
		{ 
		  RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM3, ENABLE);
		  GPIO_InitStruct.GPIO_Pin=GPIO_Pin_7;
          GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
          GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;
          GPIO_Init(GPIOA, & GPIO_InitStruct);
		}	else	if(type==TIM3_3)
		{ 
		  RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM3, ENABLE);
		  GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0;
          GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
          GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;
          GPIO_Init(GPIOB, & GPIO_InitStruct);
		}
			else	if(type==TIM3_4)
		{ 
		  RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM3, ENABLE);
		  GPIO_InitStruct.GPIO_Pin=GPIO_Pin_1;
          GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
          GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;
          GPIO_Init(GPIOB, & GPIO_InitStruct);
		}	else	if(type==TIM4_1)
		{ 
		  RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM4, ENABLE);
		  GPIO_InitStruct.GPIO_Pin=GPIO_Pin_6;
          GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
          GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;
          GPIO_Init(GPIOB, & GPIO_InitStruct);
		}	else	if( type==TIM4_2)
		{ 
		  RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM4, ENABLE);
		  GPIO_InitStruct.GPIO_Pin=GPIO_Pin_7;
          GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
          GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;
          GPIO_Init(GPIOB, & GPIO_InitStruct);
		}
			else	if( type==TIM4_3)
		{ 
		  RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM4, ENABLE);
		  GPIO_InitStruct.GPIO_Pin=GPIO_Pin_8;
          GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
          GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;
          GPIO_Init(GPIOB, & GPIO_InitStruct);
		}
			else	if( type==TIM4_4)
		{ 
		  RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM4, ENABLE);
		  GPIO_InitStruct.GPIO_Pin=GPIO_Pin_9;
          GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
          GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;
          GPIO_Init(GPIOB, & GPIO_InitStruct);
		}

}


void pwm_init(TIMtype type)
{
   if(type==TIM2_1||type==TIM2_2||type==TIM2_3||type==TIM2_4)
   {
   
   pwm_gpio_init(type);
   pwm_config(type);
   }
   else if(type==TIM3_1||type==TIM3_2||type==TIM3_3||type==TIM3_4)
   {
   
   pwm_gpio_init(type);
   pwm_config(type);
   }
    else if(type==TIM4_1||type==TIM4_2||type==TIM4_3||type==TIM4_4)
   {
 
   pwm_gpio_init(type);
   pwm_config(type);
   }

}

void set_pwm_percent(TIMtype type,int percent) 
{
 if( type==TIM2_1)
 TIM_SetCompare1(TIM2,(percent*CYCLE_MS(TIME2_CYCLE_MS)/100)-1 );

 else if( type==TIM2_2)
  TIM_SetCompare2(TIM2,(percent*CYCLE_MS(TIME2_CYCLE_MS)/100)-1 );

 else if( type==TIM2_3)
 TIM_SetCompare3(TIM2,(percent*CYCLE_MS(TIME2_CYCLE_MS)/100)-1 );

 else if( type==TIM2_4)
 TIM_SetCompare4(TIM2,(percent*CYCLE_MS(TIME2_CYCLE_MS)/100)-1 );

 else if( type==TIM3_1)
  TIM_SetCompare1(TIM3,(percent*CYCLE_MS(TIME3_CYCLE_MS)/100)-1 );

 else if( type==TIM3_2)
 TIM_SetCompare2(TIM3,(percent*CYCLE_MS(TIME3_CYCLE_MS)/100)-1 );

 else if( type==TIM3_3)
 TIM_SetCompare3(TIM3,(percent*CYCLE_MS(TIME3_CYCLE_MS)/100)-1 );

 else if( type==TIM3_4)
 TIM_SetCompare4(TIM3,(percent*CYCLE_MS(TIME3_CYCLE_MS)/100)-1 );

 else if( type==TIM4_1)
 TIM_SetCompare1(TIM4,(percent*CYCLE_MS(TIME4_CYCLE_MS)/100)-1 );

 else if( type==TIM4_2)
  TIM_SetCompare2(TIM4,(percent*CYCLE_MS(TIME4_CYCLE_MS)/100)-1 );

 else if( type==TIM4_3)
 TIM_SetCompare3(TIM4,(percent*CYCLE_MS(TIME4_CYCLE_MS)/100)-1 );

 else if( type==TIM4_4)
 TIM_SetCompare4(TIM4,(percent*CYCLE_MS(TIME4_CYCLE_MS)/100)-1 );


}

