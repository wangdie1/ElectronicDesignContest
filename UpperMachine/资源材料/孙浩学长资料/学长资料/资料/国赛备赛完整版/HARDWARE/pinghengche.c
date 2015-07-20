#include"pinghengche.h"
#include"delay.h"
#include"pwm.h"
#include<stm32f10x.h>
static PID sPID;
static PID *sptr = &sPID;
//PID��ʼ��//
void IncPIDInit(void) 
{ 
sptr->SumError = 0; 
sptr->LastError = 0; //Error[-1] 
sptr->PrevError = 0; //Error[-2] 
sptr->Proportion = 4.2; //Proportional Const 
sptr->Integral = 1.8; //Integral Const 
sptr->Derivative = 1.7; //Derivative Const 
sptr->SetPoint = 2553; 
}

//����ʽPID���㲿��//
float IncPIDCalc(int NextPoint) 
{ 
register float iError, iIncpid;//��ǰ��� 
iError = sptr->SetPoint - NextPoint; //��������
iIncpid = sptr->Proportion * iError  //E[K]��
- sptr->Integral * sptr->LastError   //E[K-1]��
+ sptr->Derivative * sptr->PrevError;//E[K-2]�� 
//�洢�������´μ���
sptr->PrevError = sptr->LastError; 
sptr->LastError = iError; 
//��������ֵ
// if((iError>0)&(iIncpid>iError))
// 		iIncpid=iError;
// if((iError<0)&(iIncpid<iError))
// 		iIncpid=iError;
return(iIncpid); 
}

void PH_car_init(void)
{
   PH_gpio_init();
   PH_motor_init();
	 IncPIDInit();
}

void PH_motor_init()
{
  TIM_OCInitTypeDef TIM_OCInitStruct;					    //PWM�ĳ�ʼ��
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;			 //��ʱ����ʼ��

  TIM_OCInitStruct .TIM_OCMode=TIM_OCMode_PWM2;					
  TIM_OCInitStruct .TIM_OutputState=TIM_OutputState_Enable;
  TIM_OCInitStruct .TIM_Pulse=0;						   //��pulse/preiod	����������pwmռ�ձ�
  TIM_OCInitStruct .TIM_OCPolarity=TIM_OCPolarity_Low;
  TIM_OC3Init(TIM3,&TIM_OCInitStruct);
  TIM_ARRPreloadConfig( TIM3,ENABLE);
  TIM_OC3PreloadConfig( TIM3, TIM_OCPreload_Enable);

  TIM_TimeBaseInitStruct. TIM_Prescaler=999;				 //Ԥ��Ƶ��periodһ������pwm������
  TIM_TimeBaseInitStruct .TIM_CounterMode=TIM_CounterMode_Up;
  TIM_TimeBaseInitStruct .TIM_Period=240;				     //�ؼ��غ�Ԥ��Ƶһ������pwm����
  TIM_TimeBaseInitStruct .TIM_ClockDivision=0;
							
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);
  TIM_Cmd(TIM3, ENABLE);


  TIM_OCInitStruct .TIM_OCMode=TIM_OCMode_PWM2;					
  TIM_OCInitStruct .TIM_OutputState=TIM_OutputState_Enable;
  TIM_OCInitStruct .TIM_Pulse=0;						   //��pulse/preiod	����������pwmռ�ձ�
  TIM_OCInitStruct .TIM_OCPolarity=TIM_OCPolarity_Low;
  TIM_OC4Init(TIM3,&TIM_OCInitStruct);
  TIM_ARRPreloadConfig( TIM3,ENABLE);
  TIM_OC4PreloadConfig( TIM3, TIM_OCPreload_Enable);

  TIM_TimeBaseInitStruct. TIM_Prescaler=999;				 //Ԥ��Ƶ��periodһ������pwm������
  TIM_TimeBaseInitStruct .TIM_CounterMode=TIM_CounterMode_Up;
  TIM_TimeBaseInitStruct .TIM_Period=240;				     //�ؼ��غ�Ԥ��Ƶһ������pwm����
  TIM_TimeBaseInitStruct .TIM_ClockDivision=0;
							
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);
  TIM_Cmd(TIM3, ENABLE);

}

void PH_gpio_init()
{
          GPIO_InitTypeDef GPIO_InitStruct;
   		  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
        RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOE, ENABLE);
				RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM3, ENABLE);
		 		 
		
		  GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0;
          GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
          GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;
          GPIO_Init(GPIOB, & GPIO_InitStruct);

		  GPIO_InitStruct.GPIO_Pin=GPIO_Pin_1;
          GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
          GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;
          GPIO_Init(GPIOB, & GPIO_InitStruct);
			
			GPIO_InitStruct.GPIO_Pin=GPIO_Pin_10;
          GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
          GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
          GPIO_Init(GPIOE, & GPIO_InitStruct);
	
			GPIO_InitStruct.GPIO_Pin=GPIO_Pin_11;
          GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
          GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
          GPIO_Init(GPIOE, & GPIO_InitStruct);
					
			GPIO_InitStruct.GPIO_Pin=GPIO_Pin_12;
          GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
          GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
          GPIO_Init(GPIOE, & GPIO_InitStruct);
			
			GPIO_InitStruct.GPIO_Pin=GPIO_Pin_13;
          GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
          GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
          GPIO_Init(GPIOE, & GPIO_InitStruct);
}
void PH_forward100(int percent)//12
{
GPIO_SetBits(GPIOE,GPIO_Pin_10);
GPIO_ResetBits(GPIOE,GPIO_Pin_11);
GPIO_SetBits(GPIOE,GPIO_Pin_12);
GPIO_ResetBits(GPIOE,GPIO_Pin_13);

TIM_SetCompare3(TIM3,(percent-1)*24/10);
TIM_SetCompare4(TIM3,percent*24/10); 
 
}
void PH_backward100(int  percent)
{
GPIO_ResetBits(GPIOE,GPIO_Pin_10);
GPIO_SetBits(GPIOE,GPIO_Pin_11);
GPIO_ResetBits(GPIOE,GPIO_Pin_12);//GPIO_ResetBits(GPIOB,GPIO_Pin_12)
GPIO_SetBits(GPIOE,GPIO_Pin_13);	
TIM_SetCompare3(TIM3,(percent-1)*24/10);
TIM_SetCompare4(TIM3,percent*24/10);  
}


void PH_forward90(int percent)//15
{
GPIO_SetBits(GPIOE,GPIO_Pin_10);
GPIO_ResetBits(GPIOE,GPIO_Pin_11);
GPIO_SetBits(GPIOE,GPIO_Pin_12);
GPIO_ResetBits(GPIOE,GPIO_Pin_13);

TIM_SetCompare3(TIM3,(percent-1)*24/10);
TIM_SetCompare4(TIM3,percent*24/10); 
 
}
void PH_backward90(int  percent)
{
GPIO_ResetBits(GPIOE,GPIO_Pin_10);
GPIO_SetBits(GPIOE,GPIO_Pin_11);
GPIO_ResetBits(GPIOE,GPIO_Pin_12);//GPIO_ResetBits(GPIOB,GPIO_Pin_12)
GPIO_SetBits(GPIOE,GPIO_Pin_13);	
TIM_SetCompare3(TIM3,(percent-1)*24/10);
TIM_SetCompare4(TIM3,percent*24/10);  
}


void PH_forward80(int percent)//20
{
GPIO_SetBits(GPIOE,GPIO_Pin_10);
GPIO_ResetBits(GPIOE,GPIO_Pin_11);
GPIO_SetBits(GPIOE,GPIO_Pin_12);
GPIO_ResetBits(GPIOE,GPIO_Pin_13);

TIM_SetCompare3(TIM3,(percent-2)*24/10);
TIM_SetCompare4(TIM3,percent*24/10); 
 
}

void PH_backward80(int  percent)
{
GPIO_ResetBits(GPIOE,GPIO_Pin_10);
GPIO_SetBits(GPIOE,GPIO_Pin_11);
GPIO_ResetBits(GPIOE,GPIO_Pin_12);//GPIO_ResetBits(GPIOB,GPIO_Pin_12)
GPIO_SetBits(GPIOE,GPIO_Pin_13);	
TIM_SetCompare3(TIM3,(percent-2)*24/10);
TIM_SetCompare4(TIM3,percent*24/10);  
}



void PH_forward70(int percent)//27
{
GPIO_SetBits(GPIOE,GPIO_Pin_10);
GPIO_ResetBits(GPIOE,GPIO_Pin_11);
GPIO_SetBits(GPIOE,GPIO_Pin_12);
GPIO_ResetBits(GPIOE,GPIO_Pin_13);

TIM_SetCompare3(TIM3,(percent-1)*24/10);
TIM_SetCompare4(TIM3,percent*24/10); 
 
}

void PH_backward70(int  percent)
{
GPIO_ResetBits(GPIOE,GPIO_Pin_10);
GPIO_SetBits(GPIOE,GPIO_Pin_11);
GPIO_ResetBits(GPIOE,GPIO_Pin_12);//GPIO_ResetBits(GPIOB,GPIO_Pin_12)
GPIO_SetBits(GPIOE,GPIO_Pin_13);	
TIM_SetCompare3(TIM3,(percent-1)*24/10);
TIM_SetCompare4(TIM3,percent*24/10);  
}

void PH_forward60(int percent)//38
{
GPIO_SetBits(GPIOE,GPIO_Pin_10);
GPIO_ResetBits(GPIOE,GPIO_Pin_11);
GPIO_SetBits(GPIOE,GPIO_Pin_12);
GPIO_ResetBits(GPIOE,GPIO_Pin_13);

TIM_SetCompare3(TIM3,(percent-1)*24/10);
TIM_SetCompare4(TIM3,percent*24/10); 
 
}

void PH_backward60(int  percent)//38
{
GPIO_ResetBits(GPIOE,GPIO_Pin_10);
GPIO_SetBits(GPIOE,GPIO_Pin_11);
GPIO_ResetBits(GPIOE,GPIO_Pin_12);//GPIO_ResetBits(GPIOB,GPIO_Pin_12)
GPIO_SetBits(GPIOE,GPIO_Pin_13);	
TIM_SetCompare3(TIM3,(percent-1)*24/10);
TIM_SetCompare4(TIM3,percent*24/10);  
}

void PH_forward50(int percent)//61
{
GPIO_SetBits(GPIOE,GPIO_Pin_10);
GPIO_ResetBits(GPIOE,GPIO_Pin_11);
GPIO_SetBits(GPIOE,GPIO_Pin_12);
GPIO_ResetBits(GPIOE,GPIO_Pin_13);

TIM_SetCompare3(TIM3,124);
TIM_SetCompare4(TIM3,percent*24/10); 
 
}

void PH_backward50(int  percent)
{
GPIO_ResetBits(GPIOE,GPIO_Pin_10);
GPIO_SetBits(GPIOE,GPIO_Pin_11);
GPIO_ResetBits(GPIOE,GPIO_Pin_12);//GPIO_ResetBits(GPIOB,GPIO_Pin_12)
GPIO_SetBits(GPIOE,GPIO_Pin_13);	
TIM_SetCompare3(TIM3,124);
TIM_SetCompare4(TIM3,percent*24/10);  
}

void PH_forward40(int percent)
{
GPIO_SetBits(GPIOE,GPIO_Pin_10);
GPIO_ResetBits(GPIOE,GPIO_Pin_11);
GPIO_SetBits(GPIOE,GPIO_Pin_12);
GPIO_ResetBits(GPIOE,GPIO_Pin_13);

TIM_SetCompare3(TIM3,(percent+1)*24/10);//��
TIM_SetCompare4(TIM3,percent*24/10); //��
 
}

void PH_backward40(int  percent)//127
{
GPIO_ResetBits(GPIOE,GPIO_Pin_10);
GPIO_SetBits(GPIOE,GPIO_Pin_11);
GPIO_ResetBits(GPIOE,GPIO_Pin_12);//GPIO_ResetBits(GPIOB,GPIO_Pin_12)
GPIO_SetBits(GPIOE,GPIO_Pin_13);	
TIM_SetCompare3(TIM3,(percent+1)*24/10);
TIM_SetCompare4(TIM3,percent*24/10);  
}
void PH_stop(void)
{
GPIO_SetBits(GPIOE,GPIO_Pin_10);
GPIO_ResetBits(GPIOE,GPIO_Pin_11);
GPIO_SetBits(GPIOE,GPIO_Pin_12);
GPIO_ResetBits(GPIOE,GPIO_Pin_13);

TIM_SetCompare3(TIM3,0);
TIM_SetCompare4(TIM3,0); 
 
}
