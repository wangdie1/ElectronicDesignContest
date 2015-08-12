#include "Encoder1.h"
#include "Timebase.h"

volatile  int b1Is_First_Measurement ;
volatile double h1Previous_angle,h1Speed_Buffer[SPEED_BUFFER_SIZE],h1Rot_Speed;
static u8 b1Speed_Buffer_Index = 0;
static volatile u16 h1Encoder_Timer_Overflow=0;//溢出标志 用于测速
static volatile s32 h1Encoder_Revolutions_Num=0; //转数  用于测距
static volatile double Pre1Position=0,Now1Position=0;
static volatile double Speed1Normal=0;

//编码器的初始化
void Encoder1_Init(void)
{	 
	/* TIM3 clock source enable */ 
	RCC->APB1ENR|=1<<2;       //TIM4使能
	/* Enable GPIOA, clock */
	RCC->APB2ENR|=1<<3;       // 使能GBIOB
	
	
	/* Configure PB.00,01 as encoder input2 */
	ENC1_GPIO_PORT->CRL&=0XF0FFFFFF;//PB6
	ENC1_GPIO_PORT->CRL|=0X04000000;//浮空输入
	ENC1_GPIO_PORT->CRL&=0X0FFFFFFF;//PB7
	ENC1_GPIO_PORT->CRL|=0X40000000;//浮空输入
	
	/* Enable the TIM3 Update Interrupt */
	ENC1_TIMER->DIER|=1<<0;   //允许更新中断		
	ENC1_TIMER->DIER|=1<<6;   //允许触发中断
	//MY_NVIC_Init(1,3,TIM4_IRQChannel,2);

	/* Timer configuration in Encoder mode */ 
	ENC1_TIMER->PSC = 0x0;//预分频器
	ENC1_TIMER->ARR = 4*ENCODER1_PPR-1; //设定计数器计数重转值
	ENC1_TIMER->CR1 &=~(3<<8);// 选着时钟分频:不分频
	ENC1_TIMER->CR1 &=~(3<<5);//选着计数模式:边沿对齐模式
		
	ENC1_TIMER->CCMR1 |= 1<<0; //CC1s = "01"
	ENC1_TIMER->CCMR1 |= 1<<8; //cc2s = "01"
	ENC1_TIMER->CCER &= ~(1<<1);	 //cc1p = "0"
	ENC1_TIMER->CCER &= ~(1<<5);	 //cc2p = "0"
	ENC1_TIMER->CCMR1 |= 3<<4; //	IC1F='1000' 
	ENC1_TIMER->SMCR |= 1<<0;	 //Ic1f = "100"
	
  	ENC1_TIMER->CNT = COUNTER_RESET;

	
	ENC1_Clear_Speed_Buffer();
	h1Previous_angle=0;
	h1Rot_Speed=0;;
	b1Speed_Buffer_Index = 0;
	h1Encoder_Timer_Overflow=0;
	b1Is_First_Measurement = true;
	h1Encoder_Revolutions_Num=0; 
	
	ENC1_TIMER->CR1 |= 0x01;    //
}


//返回编码器的计数值
u16 Encoder1_Get_Counter(void)
{
	return ENC1_TIMER->CNT;
}

/*******************************************************************************
* Function Name  : ENC_Get_Electrical_Angle
* Description    : Returns the absolute electrical Rotor angle 
* Input          : None
* Output         : None
* Return         : Rotor electrical angle: 0 -> 0 degrees, 
*                                          S16_MAX-> 180 degrees, 
*                                          S16_MIN-> -180 degrees                  
// *******************************************************************************/
//直接放回编码器转过的角度
 double ENC1_Get_Electrical_Angle(void)
 {
	double temp;
	temp = (TIM_GetCounter(ENC1_TIMER)) * (U32_MAX / (4*ENCODER1_PPR)); 
	return((double)(temp/U32_MAX)*360); // double r 
 }

 double ENC1_Get_Speed(void)
{
	double temp;
	double sum;
	double speed;
	int i;
	Now1Position=Encoder1_Get_Counter(); 	//
	temp=Now1Position-Pre1Position;  		//
	
	//速度有正负
//	if( Now1Position - Pre1Position > 400 )
//		temp = Now1Position - 800 + Pre1Position;
//	else if( Now1Position - Pre1Position  <  -400)
//		temp = Now1Position + 800 - Pre1Position;
	
	
	if( Now1Position - Pre1Position > 400 )
		temp = 800  - Now1Position + Pre1Position;
	else if( Now1Position - Pre1Position  <  -400)
		temp = Now1Position + 800 - Pre1Position;
	
	for(i = 0;i<21;i++)
	{
		h1Speed_Buffer[i] = h1Speed_Buffer[i+1];
		sum+=h1Speed_Buffer[i];
	}
	
	h1Speed_Buffer[i] = temp;
	sum+=h1Speed_Buffer[i];
	speed = sum/21;
	return speed;
}




/*******************************************************************************
* Function Name  : ENC_Calc_Rot_Speed
* Description    : Compute return latest speed measurement 
* Input          : None
* Output         : double
* Return         : Return the speed in 0.1 Hz resolution.                    
*******************************************************************************/
double ENC1_Calc_Rot_Speed(void)
{   
  double wDelta_angle;
  u16 hEnc_Timer_Overflow_sample_one, hEnc_Timer_Overflow_sample_two;
  u16 hCurrent_angle_sample_one, hCurrent_angle_sample_two;
  signed long long temp;
  double haux;
  
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
      wDelta_angle = (double)(hCurrent_angle_sample_one - h1Previous_angle - 
                    (hEnc_Timer_Overflow_sample_one) * (4*ENCODER1_PPR));
    }
    else  
    {//encoder timer up-counting
      wDelta_angle = (double)(hCurrent_angle_sample_one - h1Previous_angle + 
                    (hEnc_Timer_Overflow_sample_one) * (4*ENCODER1_PPR));
    }
    
    // speed computation as delta angle * 1/(speed sempling time)
    temp = (signed long long)(wDelta_angle * SPEED_SAMPLING_FREQ);
    temp *= ENC1_SPPED_UNIT;  // RPM
    temp /= (4*ENCODER1_PPR);
 		temp /=REDUCTION1_RATIO;//除以减速波
        
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
      haux = ENC1_TIMER->CNT; 
      h1Encoder_Timer_Overflow = 0;            
    }
  }
  
  h1Previous_angle = haux;  
  return((double) temp);
}
/*******************************************************************************
* Function Name  : ENC_Calc_Average_Speed
* Description    : Compute smoothed motor speed based on last SPEED_BUFFER_SIZE
                   informations and store it variable  
* Input          : None
* Output         : double
* Return         : Return rotor speed in 0.1 Hz resolution. This routine 
                   will return the average mechanical speed of the motor.
*******************************************************************************/
double ENC1_Calc_Average_Speed(void)
{   
  double wtemp;
  u32 i;
  wtemp = ENC1_Calc_Rot_Speed();
        
/* Compute the average of the read speeds */  
  h1Speed_Buffer[b1Speed_Buffer_Index] = (double)wtemp;
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
  
  h1Rot_Speed = ((double)(wtemp));
	Speed1Normal=h1Rot_Speed;
  return h1Rot_Speed;
}
/******************角位移******/
double ENC1_Get_AnglularPosition(void)
{
	double temp;
	temp = h1Encoder_Revolutions_Num*4*ENCODER1_PPR+TIM_GetCounter(ENC1_TIMER); //圈数+
	return (temp*ENC1_ANFULAR_UNIT/(REDUCTION1_RATIO*ENCODER1_PPR));//单位0.01度
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



void TIM4_IRQHandler(void)
{  
  /* Clear the interrupt pending flag */
  TIM_ClearFlag(ENC1_TIMER, TIM_FLAG_Update);  //清除中断标志位
// 	bIs_First_Measurement = true;
  
	if (h1Encoder_Timer_Overflow != U16_MAX)  
	{
		h1Encoder_Timer_Overflow++;
	}
	if(!((h1Encoder_Revolutions_Num == INT32_MAX)|(h1Encoder_Revolutions_Num ==S32_MIN )))
	{
		if ( (ENC1_TIMER->CR1 & TIM_CounterMode_Down) == TIM_CounterMode_Down)  
		{
			h1Encoder_Revolutions_Num --;
		}
		else
			h1Encoder_Revolutions_Num ++;
	}
	else
		h1Encoder_Revolutions_Num = 0;
}

