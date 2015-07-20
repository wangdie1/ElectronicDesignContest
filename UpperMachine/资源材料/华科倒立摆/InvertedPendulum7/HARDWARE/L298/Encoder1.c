#include "Encoder1.h"
#include "Timebase.h"

volatile  int b1Is_First_Measurement ;
volatile s16 h1Previous_angle,h1Speed_Buffer[SPEED_BUFFER_SIZE],h1Rot_Speed;
static u8 b1Speed_Buffer_Index = 0;
static volatile u16 h1Encoder_Timer_Overflow=0;//溢出标志 用于测速
static volatile s32 h1Encoder_Revolutions_Num=0; //转数  用于测距
static volatile s32 Pre1Position=0,Now1Position=0;
static volatile s16 Speed1Normal=0;

void ENC1_Init(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	
	//Encoder uint connected to TIM2
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	//RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	RCC_APB1PeriphClockCmd(ENC1_TIMER_CLK,ENABLE);
	RCC_APB2PeriphClockCmd(ENC1_GPIO_CLK ,ENABLE);

	GPIO_StructInit(&GPIO_InitStructure);
	//GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Pin = ENC1_GPIO_PIN_A  | ENC1_GPIO_PIN_B ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(ENC1_GPIO_PORT ,&GPIO_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = ENC1_TIMER_IRQn ;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = TIMx_PRE_EMPTION_PRIORITY;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = TIMx_SUB_PRIORITY;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	TIM_DeInit(ENC1_TIMER);
	//TIM_TimeBaseInit(&TIM_TimeBaseStructure);

	TIM_TimeBaseStructure.TIM_Prescaler = 0x0;
	TIM_TimeBaseStructure.TIM_Period = (4*ENCODER_PPR)-1;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(ENC1_TIMER,&TIM_TimeBaseStructure);

	TIM_EncoderInterfaceConfig(ENC1_TIMER,TIM_EncoderMode_TI12,
	TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_ICFilter = ICx_FILTER;
	TIM_ICInit(ENC1_TIMER,&TIM_ICInitStructure);
 
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;//注意通道
	TIM_ICInit(ENC1_TIMER, &TIM_ICInitStructure);

	TIM_ClearFlag(ENC1_TIMER,TIM_FLAG_Update);
	TIM_ITConfig(ENC1_TIMER,TIM_IT_Update,ENABLE);

	TIM2->CNT = COUNTER_RESET;//!!此处注意修改

	//局部初始化
	ENC1_Clear_Speed_Buffer();
	h1Previous_angle=0;
  h1Rot_Speed=0;;
  b1Speed_Buffer_Index = 0;
  h1Encoder_Timer_Overflow=0;
  b1Is_First_Measurement = true;
  h1Encoder_Revolutions_Num=0; 
   
  TIM_Cmd(ENC1_TIMER,ENABLE);
}

/*******************************************************************************
* Function Name  : ENC_Get_Electrical_Angle
* Description    : Returns the absolute electrical Rotor angle 
* Input          : None
* Output         : None
* Return         : Rotor electrical angle: 0 -> 0 degrees, 
*                                          S16_MAX-> 180 degrees, 
*                                          S16_MIN-> -180 degrees                  
*******************************************************************************/
s16 ENC1_Get_Electrical_Angle(void)
{
  s32 temp;
  
  temp = (s32)(TIM_GetCounter(ENC1_TIMER)) * (s32)(U32_MAX / (4*ENCODER_PPR)); 
  return((s16)(temp/65536)); // s16 result
}


/*******************************************************************************
* Function Name  : ENC_Calc_Rot_Speed
* Description    : Compute return latest speed measurement 
* Input          : None
* Output         : s16
* Return         : Return the speed in 0.1 Hz resolution.                    
*******************************************************************************/
s16 ENC1_Calc_Rot_Speed(void)
{   
  s32 wDelta_angle;
  u16 hEnc_Timer_Overflow_sample_one, hEnc_Timer_Overflow_sample_two;
  u16 hCurrent_angle_sample_one, hCurrent_angle_sample_two;
  signed long long temp;
  s16 haux;
  
  if (!b1Is_First_Measurement)
  {
    // 1st reading of overflow counter    
    hEnc_Timer_Overflow_sample_one = h1Encoder_Timer_Overflow; 
    // 1st reading of encoder timer counter
    hCurrent_angle_sample_one = ENC1_TIMER->CNT;
    // 2nd reading of overflow counter
    hEnc_Timer_Overflow_sample_two = h1Encoder_Timer_Overflow;  
    // 2nd reading of encoder timer counter
    hCurrent_angle_sample_two = ENC1_TIMER->CNT;      

    // Reset hEncoder_Timer_Overflow and read the counter value for the next
    // measurement
    h1Encoder_Timer_Overflow = 0;
    haux = ENC1_TIMER->CNT;   
    
    if (h1Encoder_Timer_Overflow != 0) 
    {
      haux = ENC1_TIMER->CNT; 
      h1Encoder_Timer_Overflow = 0;            
    }
     
    if (hEnc_Timer_Overflow_sample_one != hEnc_Timer_Overflow_sample_two)
    { 
			//Compare sample 1 & 2 and check if an overflow has been generated right 
      //after the reading of encoder timer. If yes, copy sample 2 result in 
      //sample 1 for next process 
      hCurrent_angle_sample_one = hCurrent_angle_sample_two;
      hEnc_Timer_Overflow_sample_one = hEnc_Timer_Overflow_sample_two;
    }
    
    if ( (ENC1_TIMER->CR1 & TIM_CounterMode_Down) == TIM_CounterMode_Down)  
    {// encoder timer down-counting
      wDelta_angle = (s32)(hCurrent_angle_sample_one - h1Previous_angle - 
                    (hEnc_Timer_Overflow_sample_one) * (4*ENCODER_PPR));
    }
    else  
    {//encoder timer up-counting
      wDelta_angle = (s32)(hCurrent_angle_sample_one - h1Previous_angle + 
                    (hEnc_Timer_Overflow_sample_one) * (4*ENCODER_PPR));
    }
    
    // speed computation as delta angle * 1/(speed sempling time)
    temp = (signed long long)(wDelta_angle * SPEED_SAMPLING_FREQ);
    temp *= 60;  // RPM
    temp /= (4*ENCODER_PPR);
 		temp /=REDUCTION_RATIO;//除以减速波
        
  } //is first measurement, discard it
  else
  {
    b1Is_First_Measurement = false;
    temp = 0;
    h1Encoder_Timer_Overflow = 0;
    haux = ENC1_TIMER->CNT;       
    // Check if Encoder_Timer_Overflow is still zero. In case an overflow IT 
    // occured it resets overflow counter and wPWM_Counter_Angular_Velocity
    if (h1Encoder_Timer_Overflow != 0) 
    {
      haux = ENC_TIMER->CNT; 
      h1Encoder_Timer_Overflow = 0;            
    }
  }
  
  h1Previous_angle = haux;  
//  if(temp>=SPEED_MAX)
//  {
// 	 temp=Speed1Normal;
// 	}
// 	if(temp<=SPEED_MIN)
// 	{
// 		 temp=Speed1Normal;
// 	}
  return((s16) temp);
}
/*******************************************************************************
* Function Name  : ENC_Calc_Average_Speed
* Description    : Compute smoothed motor speed based on last SPEED_BUFFER_SIZE
                   informations and store it variable  
* Input          : None
* Output         : s16
* Return         : Return rotor speed in 0.1 Hz resolution. This routine 
                   will return the average mechanical speed of the motor.
*******************************************************************************/
s16 ENC1_Calc_Average_Speed(void)
{   
  s32 wtemp;
  u32 i;
  
  wtemp = ENC1_Calc_Rot_Speed();
        
/* Compute the average of the read speeds */  
  h1Speed_Buffer[b1Speed_Buffer_Index] = (s16)wtemp;
  b1Speed_Buffer_Index++;
  
  if (b1Speed_Buffer_Index == SPEED_BUFFER_SIZE) 
  {
    b1Speed_Buffer_Index = 0;
  }

  wtemp=0;

  for (i=0;i<SPEED_BUFFER_SIZE;i++)
  {
    wtemp += h1Speed_Buffer[i];
  }
  wtemp /= SPEED_BUFFER_SIZE;
  
  h1Rot_Speed = ((s16)(wtemp));
	Speed1Normal=h1Rot_Speed;
  return h1Rot_Speed;
}
/******************角位移******/
s32 ENC1_Get_AnglularPosition(void)
{
		s32 temp;
		temp = h1Encoder_Revolutions_Num*4*ENCODER_PPR+TIM_GetCounter(ENC1_TIMER);
		return (temp*3600/(REDUCTION_RATIO*4*ENCODER_PPR));//单位0.1度
// 	return  temp;
}

/**********线位移******/
s32 ENC1_Calc_Position(void)
{
		s32 temp;
		float ftemp;
		ftemp=(float)(TIM_GetCounter(ENC_TIMER))/(4*ENCODER_PPR );
		//temp = (s32)(TIM_GetCounter(ENCODER_TIMER ))+ 
		temp= h1Encoder_Revolutions_Num*LENGTH/REDUCTION_RATIO  + ftemp*LENGTH/REDUCTION_RATIO ;
	//	temp=(hEncoder_Revolutions_Num*(4*ENCODER_PPR )+(s32)(TIM_GetCounter(ENCODER_TIMER)))/(REDUCTION_RATIO *4*ENCODER_PPR);
		return  temp;
}

/*******************************************************************************
* Function Name  : ENC_Clear_Speed_Buffer
* Description    : Clear speed buffer used for average speed calculation  
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ENC1_Clear_Speed_Buffer(void)
{   
  u32 i;

  for (i=0;i<SPEED_BUFFER_SIZE;i++)
  {
    h1Speed_Buffer[i] = 0;
  }
  b1Is_First_Measurement = true;
}



void TIM2_IRQHandler(void)
{  
  /* Clear the interrupt pending flag */
  TIM_ClearFlag(ENC1_TIMER, TIM_FLAG_Update);
// 	bIs_First_Measurement = true;
  
  if (h1Encoder_Timer_Overflow != U16_MAX)  
  {
			h1Encoder_Timer_Overflow++;
	//		GPIOC->ODR ^= GPIO_Pin_9;
			//LEDToggle(0);
  }
	if(!((h1Encoder_Revolutions_Num == S32_MAX)|(h1Encoder_Revolutions_Num ==S32_MIN )))
	{
		if ( (ENC1_TIMER->CR1 & TIM_CounterMode_Down) == TIM_CounterMode_Down)  
    {// encoder timer down-counting
				h1Encoder_Revolutions_Num --;
    }
		else h1Encoder_Revolutions_Num ++;
	}
	else h1Encoder_Revolutions_Num = 0;
		
//  LEDToggle(LED4);
}

