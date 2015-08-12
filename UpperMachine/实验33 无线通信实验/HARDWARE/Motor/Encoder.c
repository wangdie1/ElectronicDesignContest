#include "Encoder.h"
#include "Timebase.h"

//定义全局变量
volatile  int bIs_First_Measurement ;
volatile double hPrevious_angle,hSpeed_Buffer[SPEED_BUFFER_SIZE],hRot_Speed;
static u8 bSpeed_Buffer_Index = 0;
static volatile u16 hEncoder_Timer_Overflow=0;//溢出标志 用于测速
static volatile double hEncoder_Revolutions_Num=0; //转数  用于测距
static volatile double PrePosition=0,NowPosition=0;
static volatile double SpeedNormal=0;

//寄存器版本 -- 编码器初始化
void Encoder_Init(void)
{
	/* TIM3 clock source enable */ 
	RCC->APB1ENR|=1<<1;       //TIM3时钟使能
	/* Enable GPIOA, clock */
	RCC->APB2ENR|=1<<2;    //使能PORTA时钟

	/* Configure PA.06,07 as encoder input */
	GPIOA->CRL&=0XF0FFFFFF;//PA6
	GPIOA->CRL|=0X04000000;//浮空输入
	GPIOA->CRL&=0X0FFFFFFF;//PA7
	GPIOA->CRL|=0X40000000;//浮空输入

	/* Enable the TIM3 Update Interrupt */
	//这两个东东要同时设置才可以使用中断
	ENC_TIMER->DIER|=1<<0;   //允许更新中断				
	ENC_TIMER->DIER|=1<<6;   //允许触发中断

	/* Timer configuration in Encoder mode */ 
	ENC_TIMER->PSC = 0x0;//预分频器
	ENC_TIMER->ARR = 4*ENCODER_PPR-1;//ENCODER_TIM_PERIOD-1;//设定计数器自动重装值 
	ENC_TIMER->CR1 &=~(3<<8);// 选择时钟分频：不分频
	ENC_TIMER->CR1 &=~(3<<5);// 选择计数模式:边沿对齐模式
		
	ENC_TIMER->CCMR1 |= 1<<0; //CC1S='01' IC1FP1映射到TI1
	ENC_TIMER->CCMR1 |= 1<<8; //CC2S='01' IC2FP2映射到TI2
	ENC_TIMER->CCER &= ~(1<<1);	 //CC1P='0'	 IC1FP1不反相，IC1FP1=TI1
	ENC_TIMER->CCER &= ~(1<<5);	 //CC2P='0'	 IC2FP2不反相，IC2FP2=TI2
	ENC_TIMER->CCMR1 |= 3<<4; //	IC1F='1000' 输入捕获1滤波器
	ENC_TIMER->SMCR |= 3<<0;	 //SMS='011' 所有的输入均在上升沿和下降沿有效
	
	ENC_TIMER->CNT = COUNTER_RESET;
	
	//局部初始化
	ENC_Clear_Speed_Buffer();
	hPrevious_angle=0;
	hRot_Speed=0;;
	bSpeed_Buffer_Index = 0;
	hEncoder_Timer_Overflow=0;
	bIs_First_Measurement = true;
	hEncoder_Revolutions_Num=0;
	
	ENC_TIMER->CR1 |= 0x01;    //CEN=1，使能定时器
}



//获取编码器的计数

  u16 Encoder_Get_Counter(void)
{
	return ENC_TIMER->CNT;
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
//计算马达转子的位置电角度
double ENC_Get_Electrical_Angle(void)
{
  double temp;
  temp = (TIM_GetCounter(ENC_TIMER)) * (U32_MAX / (4*ENCODER_PPR)); 
  temp = ((double)(temp/U32_MAX))*360; // s16 result
  return temp; // s16 result
}

/*******************************************************************************
* Function Name  : ENC_Clear_Speed_Buffer
* Description    : Clear speed buffer used for average speed calculation  
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
//初始化马达速度缓存
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
//计算马达转动的平均电频率
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
//计算马达转动的电频率
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
  return((double) temp);
}


/**********线位移******/
double ENC_Calc_Position(void)
{
		double temp;
		float ftemp;
		ftemp=TIM_GetCounter(ENC_TIMER);
		temp=hEncoder_Revolutions_Num*(4*ENCODER_PPR )+ftemp;
		return  temp;
}

/******************角位移******/
double ENC_Get_AnglularPosition(void)
{
		double temp;
		temp = hEncoder_Revolutions_Num*4*ENCODER_PPR+TIM_GetCounter(ENC_TIMER);
		return (temp*ENC_ANGULAR_UNIT/(REDUCTION_RATIO*ENCODER_PPR));//单位0.1度
}



/******************编码器的总个数******/
double ENC_Get_TimerCounter(void)
{
		double temp;
		temp = hEncoder_Revolutions_Num*4*ENCODER_PPR+TIM_GetCounter(ENC_TIMER);
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
//定时器的中断服务程序

void TIM3_IRQHandler(void)
{  
	/* Clear the interrupt pending flag */
	TIM_ClearFlag(ENC_TIMER, TIM_FLAG_Update);//清楚中断标志位
	// 	bIs_First_Measurement = true;
	if (hEncoder_Timer_Overflow != U16_MAX)//如果没有溢出，圈数增加
	{
			hEncoder_Timer_Overflow++;
	}
	if(!((hEncoder_Revolutions_Num == INT32_MAX)|(hEncoder_Revolutions_Num ==INT32_MIN )))
	{
		if ( (ENC_TIMER->CR1 & TIM_CounterMode_Down) == TIM_CounterMode_Down)  
		{
			hEncoder_Revolutions_Num --;//反转
		}
		else
			hEncoder_Revolutions_Num ++;//正转
	}
	else hEncoder_Revolutions_Num = 0;
}

