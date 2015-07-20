#include<stm32f10x.h>
#include"car.h"
#include"delay.h"
#include"pwm.h"



void car_init(void)
{
   Dc_gpio_init();
   Dc_motor_init();

   forward(33);	
   pwm_init(TIM4_2);
   turn_straight();
  


}

void Dc_motor_init()
{
  TIM_OCInitTypeDef TIM_OCInitStruct;					    //PWM的初始化
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;			 //定时器初始化

  TIM_OCInitStruct .TIM_OCMode=TIM_OCMode_PWM2;					
  TIM_OCInitStruct .TIM_OutputState=TIM_OutputState_Enable;
  TIM_OCInitStruct .TIM_Pulse=0;						   //（pulse/preiod	）用来设置pwm占空比
  TIM_OCInitStruct .TIM_OCPolarity=TIM_OCPolarity_Low;
  TIM_OC3Init(TIM3,&TIM_OCInitStruct);
  TIM_ARRPreloadConfig( TIM3,ENABLE);
  TIM_OC3PreloadConfig( TIM3, TIM_OCPreload_Enable);

  TIM_TimeBaseInitStruct. TIM_Prescaler=0;				 //预分频和period一起设置pwm的周期
  TIM_TimeBaseInitStruct .TIM_CounterMode=TIM_CounterMode_Up;
  TIM_TimeBaseInitStruct .TIM_Period=7200;				     //重加载和预分频一起设置pwm周期
  TIM_TimeBaseInitStruct .TIM_ClockDivision=0;
							
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);
  TIM_Cmd(TIM3, ENABLE);


  TIM_OCInitStruct .TIM_OCMode=TIM_OCMode_PWM2;					
  TIM_OCInitStruct .TIM_OutputState=TIM_OutputState_Enable;
  TIM_OCInitStruct .TIM_Pulse=0;						   //（pulse/preiod	）用来设置pwm占空比
  TIM_OCInitStruct .TIM_OCPolarity=TIM_OCPolarity_Low;
  TIM_OC4Init(TIM3,&TIM_OCInitStruct);
  TIM_ARRPreloadConfig( TIM3,ENABLE);
  TIM_OC4PreloadConfig( TIM3, TIM_OCPreload_Enable);

  TIM_TimeBaseInitStruct. TIM_Prescaler=0;				 //预分频和period一起设置pwm的周期
  TIM_TimeBaseInitStruct .TIM_CounterMode=TIM_CounterMode_Up;
  TIM_TimeBaseInitStruct .TIM_Period=7200;				     //重加载和预分频一起设置pwm周期
  TIM_TimeBaseInitStruct .TIM_ClockDivision=0;
							
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);
  TIM_Cmd(TIM3, ENABLE);

}



void Dc_gpio_init()
{
          GPIO_InitTypeDef GPIO_InitStruct;
   		  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
          RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA, ENABLE);
 		  RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM3, ENABLE);
		 		 
		
		  GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0;
          GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
          GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;
          GPIO_Init(GPIOB, & GPIO_InitStruct);

		  GPIO_InitStruct.GPIO_Pin=GPIO_Pin_1;
          GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
          GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;
          GPIO_Init(GPIOB, & GPIO_InitStruct);
		
}




void forward(int percent)
{
int speed=0;
speed=(int)((percent*40)/100);
TIM_SetCompare3(TIM3,30*72);
TIM_SetCompare4(TIM3,(40+speed)*72 ); 
 
}

void backward(int  percent)
{
int speed=0;
speed=(int)((percent*40)/100);

TIM_SetCompare4(TIM3,30*72);
TIM_SetCompare3(TIM3,(40+speed)*72 );  


}

void turn_left_5()
{
   TIM_SetCompare2(TIM4,1500);

}
void turn_left_4()
{
   TIM_SetCompare2(TIM4,1360);
}
void turn_left_3()
{
    TIM_SetCompare2(TIM4,1340);
}
void turn_left_2()
{
 TIM_SetCompare2(TIM4,1180);
}
void turn_left_1()
{
   TIM_SetCompare2(TIM4,1130);
}

void turn_right_1()
{
  TIM_SetCompare2(TIM4,1050);
}

void turn_right_2()
{

  TIM_SetCompare2(TIM4,1000);
}
void turn_right_3()
{
TIM_SetCompare2(TIM4,820);
}
void turn_right_4()
{
TIM_SetCompare2(TIM4,790);
}
void turn_right_5()
{
TIM_SetCompare2(TIM4,600);
}

void turn_straight()
{
  TIM_SetCompare2(TIM4,1080);

}

 
void Pid_Init(my_pid *temp)
{

	temp-> differ=D;
	temp-> PreError=0;
	temp-> LastError=0;
	temp-> proportion=P;
	temp-> interal=I;
	temp->setpoint=60;	 

}

int get_inc(my_pid *pid,int nextpoint)
{
 
   int Ierror ;
   int inc=0;
   Ierror=pid->setpoint-nextpoint;
   inc=Ierror*pid->proportion-pid->LastError*pid->interal
       +pid->PreError*pid->differ;
	   if(inc>=10)inc=10;
	   else if (inc<=-8)inc=(-8);
   pid->PreError=pid->LastError;
   pid->LastError=Ierror;
   return inc;

}




