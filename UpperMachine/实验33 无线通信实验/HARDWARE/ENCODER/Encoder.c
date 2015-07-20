#include "Encoder.h"
#include "Timebase.h"

//pa0 pa1

volatile  int bIs_First_Measurement ;
volatile double hPrevious_angle,hSpeed_Buffer[SPEED_BUFFER_SIZE],hRot_Speed;
static u8 bSpeed_Buffer_Index = 0;
static volatile u16 hEncoder_Timer_Overflow=0;//溢出标志 用于测速
static volatile double hEncoder_Revolutions_Num=0; //转数  用于测距
static volatile double PrePosition=0,NowPosition=0;
static volatile double SpeedNormal=0;



void ENC_Init(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	
	//Encoder uint connected to TIM2
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	//RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	RCC_APB1PeriphClockCmd(ENC_TIMER_CLK,ENABLE);
	RCC_APB2PeriphClockCmd(ENC_GPIO_CLK ,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE); 
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM3,ENABLE);
	
	GPIO_StructInit(&GPIO_InitStructure);
	//GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Pin = ENC_GPIO_PIN_A  | ENC_GPIO_PIN_B ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(ENC_GPIO_PORT ,&GPIO_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = ENC_TIMER_IRQn ;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = TIMx_PRE_EMPTION_PRIORITY;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = TIMx_SUB_PRIORITY;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	TIM_DeInit(ENC_TIMER);
	//TIM_TimeBaseInit(&TIM_TimeBaseStructure);

	TIM_TimeBaseStructure.TIM_Prescaler = 0x0;
	TIM_TimeBaseStructure.TIM_Period = (4*ENCODER_PPR)-1;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(ENC_TIMER,&TIM_TimeBaseStructure);

	TIM_EncoderInterfaceConfig(ENC_TIMER,TIM_EncoderMode_TI12,
	TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_ICFilter = ICx_FILTER;
	TIM_ICInit(ENC_TIMER,&TIM_ICInitStructure);
 
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;//注意通道
	TIM_ICInit(ENC_TIMER, &TIM_ICInitStructure);

	TIM_ClearFlag(ENC_TIMER,TIM_FLAG_Update);
	TIM_ITConfig(ENC_TIMER,TIM_IT_Update,ENABLE);

	TIM2->CNT = COUNTER_RESET;//!!此处注意修改

	//局部初始化
	ENC_Clear_Speed_Buffer();
	hPrevious_angle=0;
    hRot_Speed=0;;
    bSpeed_Buffer_Index = 0;
    hEncoder_Timer_Overflow=0;
    bIs_First_Measurement = true;
    hEncoder_Revolutions_Num=0; 
   
    TIM_Cmd(ENC_TIMER,ENABLE);
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

double ENC_Get_Electrical_Angle(void)
{
  double temp;
  
  temp = (double)(TIM_GetCounter(ENC_TIMER))  *  (double)(U32_MAX / (4*ENCODER_PPR)); //#define ENCODER_PPR (u16)   MAXON_RE25_CPR		//码盘线数
  
  return ((double)(temp/65536)); // s16 result
}


/*******************************************************************************
* Function Name  : ENC_Clear_Speed_Buffer
* Description    : Clear speed buffer used for average speed calculation  
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ENC_Clear_Speed_Buffer(void)
{   
  u32 i;

  for (i=0;i<SPEED_BUFFER_SIZE;i++)
  {
    hSpeed_Buffer[i] = 0;
  }
  bIs_First_Measurement = true;
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
double ENC_Calc_Average_Speed(void)
{   
  double wtemp;
  u32 i;
  
  wtemp = ENC_Calc_Rot_Speed();
        
/* Compute the average of the read speeds */  
  hSpeed_Buffer[bSpeed_Buffer_Index] = (double)wtemp;
  bSpeed_Buffer_Index++;
  
  if (bSpeed_Buffer_Index == SPEED_BUFFER_SIZE) 
  {
    bSpeed_Buffer_Index = 0;
  }

  wtemp=0;

  for (i=0;i<SPEED_BUFFER_SIZE;i++)
  {
    wtemp += hSpeed_Buffer[i];
  }
  wtemp /= SPEED_BUFFER_SIZE;
  
  hRot_Speed = ((double)(wtemp));
	SpeedNormal=hRot_Speed;
  return hRot_Speed;
}


/*******************************************************************************
* Function Name  : ENC_Calc_Rot_Speed
* Description    : Compute return latest speed measurement 
* Input          : None
* Output         : double
* Return         : Return the speed in 0.1 Hz resolution.                    
*******************************************************************************/
double ENC_Calc_Rot_Speed(void)
{   
  double wDelta_angle;
  u16 hEnc_Timer_Overflow_sample_one, hEnc_Timer_Overflow_sample_two;
  u16 hCurrent_angle_sample_one, hCurrent_angle_sample_two;
  double temp;
  double haux;
  
  if (!bIs_First_Measurement)
  {
    // 1st reading of overflow counter    
    hEnc_Timer_Overflow_sample_one = hEncoder_Timer_Overflow; 
    // 1st reading of encoder timer counter
    hCurrent_angle_sample_one = ENC_TIMER->CNT;
    // 2nd reading of overflow counter
    hEnc_Timer_Overflow_sample_two = hEncoder_Timer_Overflow;  
    // 2nd reading of encoder timer counter
    hCurrent_angle_sample_two = ENC_TIMER->CNT;      

    // Reset hEncoder_Timer_Overflow and read the counter value for the next
    // measurement
    hEncoder_Timer_Overflow = 0;
    haux = ENC_TIMER->CNT;   
    
    if (hEncoder_Timer_Overflow != 0) 
    {
      haux = ENC_TIMER->CNT; 
      hEncoder_Timer_Overflow = 0;            
    }
     
    if (hEnc_Timer_Overflow_sample_one != hEnc_Timer_Overflow_sample_two)
    { 
			//Compare sample 1 & 2 and check if an overflow has been generated right 
      //after the reading of encoder timer. If yes, copy sample 2 result in 
      //sample 1 for next process 
      hCurrent_angle_sample_one = hCurrent_angle_sample_two;
      hEnc_Timer_Overflow_sample_one = hEnc_Timer_Overflow_sample_two;
    }
    
    if ( (ENC_TIMER->CR1 & TIM_CounterMode_Down) == TIM_CounterMode_Down)  
    {// encoder timer down-counting
      wDelta_angle = (double)(hCurrent_angle_sample_one - hPrevious_angle - 
                    (hEnc_Timer_Overflow_sample_one) * (4*ENCODER_PPR));
    }
    else  
    {//encoder timer up-counting
      wDelta_angle = (double)(hCurrent_angle_sample_one - hPrevious_angle + 
                    (hEnc_Timer_Overflow_sample_one) * (4*ENCODER_PPR));
    }
    
    // speed computation as delta angle * 1/(speed sempling time)
    temp = (double)(wDelta_angle * SPEED_SAMPLING_FREQ);
    temp *= ENC_SPEED_UNIT;  // RPM
    temp /= (4*ENCODER_PPR);
 		temp /=REDUCTION_RATIO;//除以减速波
        
  } //is first measurement, discard it
  else
  {
    bIs_First_Measurement = false;
    temp = 0;
    hEncoder_Timer_Overflow = 0;
    haux = ENC_TIMER->CNT;       
    // Check if Encoder_Timer_Overflow is still zero. In case an overflow IT 
    // occured it resets overflow counter and wPWM_Counter_Angular_Velocity
    if (hEncoder_Timer_Overflow != 0) 
    {
      haux = ENC_TIMER->CNT; 
      hEncoder_Timer_Overflow = 0;            
    }
  }
  
  hPrevious_angle = haux;  
//  if(temp>=SPEED_MAX)
//  {
// 	 temp=SpeedNormal;
// 	}
// 	if(temp<=SPEED_MIN)
// 	{
// 		 temp=SpeedNormal;
// 	}
  return((double) temp);
}
/**********线位移******/
double ENC_Calc_Position(void)
{
		double temp;
		float ftemp;
		ftemp=(float)(TIM_GetCounter(ENC_TIMER))/(4*ENCODER_PPR );
		//temp = (double)(TIM_GetCounter(ENCODER_TIMER ))+ 
		temp= hEncoder_Revolutions_Num*LENGTH/REDUCTION_RATIO  + ftemp*LENGTH/REDUCTION_RATIO ;
	//	temp=(hEncoder_Revolutions_Num*(4*ENCODER_PPR )+(double)(TIM_GetCounter(ENCODER_TIMER)))/(REDUCTION_RATIO *4*ENCODER_PPR);
		return  temp;
}
// double MY_Calc_Rot_Speed(void)
// {
// 	 double wDelta_angle;
// 	u16 hEnc_Timer_Overflow_sample_one, hEnc_Timer_Overflow_sample_two;
//   u16 hCurrent_angle_sample_one, hCurrent_angle_sample_two;
//   signed long long temp;
// 	
// }
/******************角位移******/
double ENC_Get_AnglularPosition(void)
{
		double temp;
		temp = hEncoder_Revolutions_Num*4*ENCODER_PPR+TIM_GetCounter(ENC_TIMER);
		return (temp*ENC_ANGULAR_UNIT/(REDUCTION_RATIO*ENCODER_PPR));//单位0.1度
// 	return  temp;
}


double ENC_Get_Speed(void)
{
	double temp;
	NowPosition=ENC_Get_AnglularPosition();
	temp=NowPosition-PrePosition;
	temp = (double)(temp * SPEED_SAMPLING_FREQ);
	temp *= 60;  // RPM
//   temp /= (4*ENCODER_PPR);
	temp /=REDUCTION_RATIO;//除以减速波
	PrePosition=NowPosition;
	return temp;
	
}

/******************计数器个数******/
double ENC_Get_TimerCounter(void)
{
		double temp;
		temp = hEncoder_Revolutions_Num;//*4*ENCODER_PPR+TIM_GetCounter(ENC_TIMER);
		return temp;
}
/*******************************************************************************
* Function Name  : TIM3_IRQHandler
* Description    : This function handles TIMx Update interrupt request.
                   Encoder unit connected to TIM2
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM3_IRQHandler(void)
{  
  /* Clear the interrupt pending flag */
  TIM_ClearFlag(ENC_TIMER, TIM_FLAG_Update);
// 	bIs_First_Measurement = true;
  
  if (hEncoder_Timer_Overflow != U16_MAX)  
  {
			hEncoder_Timer_Overflow++;
	//		GPIOC->ODR ^= GPIO_Pin_9;
			//LEDToggle(0);
  }
	if(!((hEncoder_Revolutions_Num == INT32_MAX)|(hEncoder_Revolutions_Num ==INT32_MIN )))
	{
		if ( (ENC_TIMER->CR1 & TIM_CounterMode_Down) == TIM_CounterMode_Down)  
    {// encoder timer down-counting
				hEncoder_Revolutions_Num --;
    }
		else hEncoder_Revolutions_Num ++;
	}
	else hEncoder_Revolutions_Num = 0;
		
//  LEDToggle(LED4);
}

