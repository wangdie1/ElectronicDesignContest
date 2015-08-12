#include "Encoder.h"
#include "Timebase.h"

//����ȫ�ֱ���
volatile  int bIs_First_Measurement ;
volatile double hPrevious_angle,hSpeed_Buffer[SPEED_BUFFER_SIZE],hRot_Speed;
static u8 bSpeed_Buffer_Index = 0;
static volatile u16 hEncoder_Timer_Overflow=0;//�����־ ���ڲ���
static volatile double hEncoder_Revolutions_Num=0; //ת��  ���ڲ��
static volatile double PrePosition=0,NowPosition=0;
static volatile double SpeedNormal=0;

//�Ĵ����汾 -- ��������ʼ��
void Encoder_Init(void)
{
	/* TIM3 clock source enable */ 
	RCC->APB1ENR|=1<<1;       //TIM3ʱ��ʹ��
	/* Enable GPIOA, clock */
	RCC->APB2ENR|=1<<2;    //ʹ��PORTAʱ��

	/* Configure PA.06,07 as encoder input */
	GPIOA->CRL&=0XF0FFFFFF;//PA6
	GPIOA->CRL|=0X04000000;//��������
	GPIOA->CRL&=0X0FFFFFFF;//PA7
	GPIOA->CRL|=0X40000000;//��������

	/* Enable the TIM3 Update Interrupt */
	//����������Ҫͬʱ���òſ���ʹ���ж�
	ENC_TIMER->DIER|=1<<0;   //��������ж�				
	ENC_TIMER->DIER|=1<<6;   //�������ж�

	/* Timer configuration in Encoder mode */ 
	ENC_TIMER->PSC = 0x0;//Ԥ��Ƶ��
	ENC_TIMER->ARR = 4*ENCODER_PPR-1;//ENCODER_TIM_PERIOD-1;//�趨�������Զ���װֵ 
	ENC_TIMER->CR1 &=~(3<<8);// ѡ��ʱ�ӷ�Ƶ������Ƶ
	ENC_TIMER->CR1 &=~(3<<5);// ѡ�����ģʽ:���ض���ģʽ
		
	ENC_TIMER->CCMR1 |= 1<<0; //CC1S='01' IC1FP1ӳ�䵽TI1
	ENC_TIMER->CCMR1 |= 1<<8; //CC2S='01' IC2FP2ӳ�䵽TI2
	ENC_TIMER->CCER &= ~(1<<1);	 //CC1P='0'	 IC1FP1�����࣬IC1FP1=TI1
	ENC_TIMER->CCER &= ~(1<<5);	 //CC2P='0'	 IC2FP2�����࣬IC2FP2=TI2
	ENC_TIMER->CCMR1 |= 3<<4; //	IC1F='1000' ���벶��1�˲���
	ENC_TIMER->SMCR |= 3<<0;	 //SMS='011' ���е�������������غ��½�����Ч
	
	ENC_TIMER->CNT = COUNTER_RESET;
	
	//�ֲ���ʼ��
	ENC_Clear_Speed_Buffer();
	hPrevious_angle=0;
	hRot_Speed=0;;
	bSpeed_Buffer_Index = 0;
	hEncoder_Timer_Overflow=0;
	bIs_First_Measurement = true;
	hEncoder_Revolutions_Num=0;
	
	ENC_TIMER->CR1 |= 0x01;    //CEN=1��ʹ�ܶ�ʱ��
}



//��ȡ�������ļ���

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
//�������ת�ӵ�λ�õ�Ƕ�
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
//��ʼ������ٶȻ���
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
//�������ת����ƽ����Ƶ��
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
//�������ת���ĵ�Ƶ��
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
 		temp /=REDUCTION_RATIO;//���Լ��ٲ�
        
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


/**********��λ��******/
double ENC_Calc_Position(void)
{
		double temp;
		float ftemp;
		ftemp=TIM_GetCounter(ENC_TIMER);
		temp=hEncoder_Revolutions_Num*(4*ENCODER_PPR )+ftemp;
		return  temp;
}

/******************��λ��******/
double ENC_Get_AnglularPosition(void)
{
		double temp;
		temp = hEncoder_Revolutions_Num*4*ENCODER_PPR+TIM_GetCounter(ENC_TIMER);
		return (temp*ENC_ANGULAR_UNIT/(REDUCTION_RATIO*ENCODER_PPR));//��λ0.1��
}



/******************���������ܸ���******/
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
//��ʱ�����жϷ������

void TIM3_IRQHandler(void)
{  
	/* Clear the interrupt pending flag */
	TIM_ClearFlag(ENC_TIMER, TIM_FLAG_Update);//����жϱ�־λ
	// 	bIs_First_Measurement = true;
	if (hEncoder_Timer_Overflow != U16_MAX)//���û�������Ȧ������
	{
			hEncoder_Timer_Overflow++;
	}
	if(!((hEncoder_Revolutions_Num == INT32_MAX)|(hEncoder_Revolutions_Num ==INT32_MIN )))
	{
		if ( (ENC_TIMER->CR1 & TIM_CounterMode_Down) == TIM_CounterMode_Down)  
		{
			hEncoder_Revolutions_Num --;//��ת
		}
		else
			hEncoder_Revolutions_Num ++;//��ת
	}
	else hEncoder_Revolutions_Num = 0;
}

