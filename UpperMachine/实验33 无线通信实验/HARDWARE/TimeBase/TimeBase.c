#include "TimeBase.h"
//#include "delay.h"
//#include "led.h"
#ifdef TB_TEST
static volatile u16 hTimebase_PositionTest_Time = 0;
static volatile u16 hTimebase_SpeedTest_Time =0;
#endif

#ifdef TB_CURRENT_PID
static volatile u16 hTimebase_CurrentPID_Time =0;
static volatile u16 hTimebase_CurrentTest_Time=0; 
#endif

#ifdef TB_CAN_SEND
static volatile  u16 hTimebase_CAN_Send_Time=0;
#endif

static volatile u16 hTimebase_PositionPID_Time = 0;
static volatile u16 hTimebase_SpeedPID_Time = 0;

static volatile u16 hTimebase_Enc_Time = 0;
static volatile  u16 hTimebase_Delay_Time = 0;
static volatile  u16 hTimebase_Display_Time =0;

static volatile u16 hTimebase_TB6560_Time = 0;

static volatile u16 hTimebase_ADC_Time = 0;

static volatile u16 hTimebase_Main_Time = 0;

static volatile u16 hTimebase_Uart_Time = 0;

volatile u32 hSysTick_OverNum=0;

static volatile u16 hTimebase_Key_Time = 0;


//����LED
static volatile  u16 hTimebase_LED_Time = 0;

static volatile  u16 hTimebase_MPU6050_Time = 0;
/*******************************************************************************
* Function Name  : TB_Init
* Description    : TimeBase peripheral initialization. The base time is set to 
*                  500usec and the related interrupt is enabled  
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
//��ʱ��7�ĳ�ʼ������
void TB_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE); //ʱ��ʹ��
	
	//��ʱ��TIM7��ʼ��
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM7,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM7�ж�,��������ж�

	//�ж����ȼ�NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;  //TIM7�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���
	
	TIM_Cmd(TIM7, ENABLE);  //ʹ��TIMx					 
}


/*****ͨ����ʱ����****/
void TB_SetDelay_Time(u16 hDelay)   //hDelay * 100us 
{
	hTimebase_Delay_Time  = hDelay ;
}
bool TB_Delay_IsElapsed(void )
{
	if(hTimebase_Delay_Time ==0)
	{
		return  (true );
	}
	else
		return  false ;
}


/*****ͨ��������Ƶ��****/
void TB_SetMain_Time(u16 hDelay)
{
	hTimebase_Main_Time  = hDelay ;
}
bool TB_Main_isElapsed()
{
	if(hTimebase_Main_Time ==0)
	{
		return  (true );
	}
	else
		return  false ;
}

/*****���ڷ���Ƶ��***/
void TB_SetUart_Time(u16 hDelay)   //һ��Ϊ300ms���ҷ���һ��
{
	hTimebase_Uart_Time  = hDelay ;
}
bool TB_Uart_isElapsed(void)
{
	if(hTimebase_Uart_Time ==0)
	{
		return  (true );
	}
	else
		return  false ;
}


////���ñ���Ķ�ȡƵ��
//void TB_SetEnc_Time(u16 hDelay)
//{
//	hTimebase_Enc_Time = hDelay;
//}

//bool TB_Enc_IsElapsed(void)
//{
//	if(hTimebase_Enc_Time ==0)
//	{
//		return  (true );
//	}
//	else
//		return  false ;
//}


////pwm�Ĳ������
//void TB_SetTB6560_Time(u16 hDelay)      //���Ծ�ȷ�������ת���ĽǶ�
//{
//	hTimebase_TB6560_Time = hDelay;
//}

//bool TB_TB6560_IsElapsed(void)
//{
//	if(hTimebase_TB6560_Time ==0)
//	{
//		return  (true );
//	}
//	else
//		return  false ;
//}

/***************λ�û�PIDƵ������*******************/
//void TB_SetPositionPIDDelay_Time(u16 hDelay)//10ms
//{
//	hTimebase_PositionPID_Time = hDelay;
//}
//bool TB_PositionPIDDelay_IsElapsed(void)
//{
//	if(hTimebase_PositionPID_Time==0)
//	{
//		return (true);
//	}
//	else
//	{
//		return  (false );
//	}
//}
///***************�ٶȻ�Ƶ��***********************/
//void TB_SetSpeedPIDDelay_Time(u16 hDelay )
//{
//	hTimebase_SpeedPID_Time=  hDelay;
//}
//bool TB_SpeedPIDDelay_IsElapsed(void)
//{
//	if(hTimebase_SpeedPID_Time == 0)
//	{
//		return true;
//	}
//	else
//	{
//		return false;
//	}
//}


//�����Ķ�ȡƵ��
void TB_SetKey_Time(u16 hDelay )
{
	hTimebase_Key_Time=  hDelay;
}
bool TB_Key_IsElapsed(void)
{
	if(hTimebase_Key_Time == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}




///*****************LCDˢ��Ƶ��****��������������*/
void TB_SetDisplayDelay_Time(u16 hDelay)
{
	hTimebase_Display_Time =hDelay;
}
bool TB_DisplayDelay_IsElapsed(void)
{
	if(hTimebase_Display_Time == 0)
	{
		return true;
	}
	else return false;
}

///******************ADC����Ƶ��*********************/
//void TB_SetADC_Time(u16 hDelay)
//{
//	hTimebase_ADC_Time = hDelay;
//}
//bool TB_ADC_Delay_IsElapsed(void)
//{
//	if(hTimebase_ADC_Time==0)
//	{
//		return true;
//	}
//	else 
//		return false;
//}

//#ifdef TB_CAN_SEND
///**********CAN���߷���Ƶ��***********/
//void TB_SetCAN_SendDelay_Time(u16 hDelay)
//{
//	hTimebase_CAN_Send_Time  = hDelay ;	
//}
//bool  TB_CAN_SendDelay_IsElapsed(void )
//{
//	if (hTimebase_CAN_Send_Time == 0)
//	{
//		return (true);
//	}
//	else 
//	{
//		return (false);
//	}
//}
//#endif

//#ifdef TB_TEST
//// ***************λ�ò���****************************************************************/
//void TB_Set_PositionDelay_Time(u16 hDelay)
//{
//	hTimebase_PositionTest_Time =hDelay;

//}
//bool TB_PositionDelay_IsElapsed(void)
//{
// if (hTimebase_PositionTest_Time == 0)
// {
//   return (true);
// }
// else 
// {
//   return (false);
// }
//}

///**********************�ٶȲ���ʱ������******************************/
//void TB_SetSpeedDelay_Time(u16 hDelay )
//{
//	hTimebase_SpeedTest_Time=  hDelay;
//}
//bool TB_SpeedDelay_IsElapsed(void)
//{
//	if(hTimebase_SpeedTest_Time == 0)
//	{
//		return true;
//	}
//	else
//	{
//		return false;
//	}
//}
//#endif


//#ifdef TB_CURRENT_PID

///*****************������PID ����Ƶ��****��������������*/
//void TB_SetCurrentPIDDelay_Time(u16 hDelay)
//{
//	hTimebase_CurrentPID_Time =hDelay;
//}
//bool TB_CurrentPIDDelay_IsElapsed(void)
//{
//	if(hTimebase_CurrentPID_Time == 0)
//	{
//		return true;
//	}
//	else return false;
//}


///***************����ȡ��ʱ������********************///100us
//void TB_SetCurrentDelay_Time(u16 hDelay )
//{
//	hTimebase_CurrentTest_Time=  hDelay;
//}

//bool TB_CurrentDelay_IsElapsed(void)
//{
//	if(hTimebase_CurrentTest_Time == 0)
//	{
//		return true;
//	}
//	else
//	{
//		return false;
//	}
//}
//#endif


/**************************************************************/
/*------------------------------------------------------------*/
//������ˮ�ƵĲ���ʱ��

void TB_SetLed_Time(u32 hDelay)
{
	hTimebase_LED_Time =hDelay;
}
bool TB_SetLed_IsElapsed(void)
{
	if(hTimebase_LED_Time == 0)
	{
		return true;
	}
	else
		return false;
}
/*------------------------------------------------------------*/
/**************************************************************/


/**************************************************************/
/*------------------------------------------------------------*/
//����MPU6050�Ĳ���ʱ��

void TB_SetMPU6050_Time(u32 hDelay)
{
	hTimebase_MPU6050_Time =hDelay;
}
bool TB_SetMPU6050_IsElapsed(void)
{
	if(hTimebase_MPU6050_Time == 0)
	{
		return true;
	}
	else
		return false;
}
/*------------------------------------------------------------*/
/**************************************************************/


/*******************************************************************************
* Function Name  : SysTickHandler
* Description    : This function handles SysTick Handler.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM7_IRQHandler(void)
{

	if (TIM_GetITStatus(TIM7, TIM_IT_Update) != RESET)  //���TIM7�����жϷ������
	{
		TIM_ClearITPendingBit(TIM7, TIM_IT_Update  );  //���TIM7�����жϱ�־ 

		
		//�����Ķ�ȡƵ��
		if(hTimebase_Key_Time!=0)
		{
			hTimebase_Key_Time--;
		}
		
		if(hTimebase_Delay_Time !=0)//ͨ����ʱ
		{
			hTimebase_Delay_Time --;
		}
		
//		hSysTick_OverNum--;
//		if(hTimebase_ADC_Time!=0)
//		{
//			hTimebase_ADC_Time--;
//		}
//		if (hTimebase_SpeedPID_Time != 0)  //�ٶȻ�����
//		{
//    	hTimebase_SpeedPID_Time --;
//		}
//		if(hTimebase_PositionPID_Time !=0)//λ�û�����
//		{
//			hTimebase_PositionPID_Time --;
//		}
		
		if(hTimebase_Display_Time!=0)//LCDˢ��
		{
			hTimebase_Display_Time--;
		}
		if(hTimebase_Main_Time!=0)//LED����ʱ��
		{
			hTimebase_Main_Time--;
		}

//		if(hTimebase_Enc_Time!=0)
//		{
//			hTimebase_Enc_Time--;
//		}
		
//		if(hTimebase_TB6560_Time!=0) //�������
//		{
//			hTimebase_TB6560_Time--;
//		}
//		else                         //�����������,�ر�ʹ��
//		{
//			TIM_Cmd(TIM3, DISABLE);	
//		}
		
	
	
		
		//���幦�ܵĲ���Ƶ��
//		#ifdef TB_TEST
//			if (hTimebase_SpeedTest_Time != 0)  
//		{
//			hTimebase_SpeedTest_Time --;
//		}
//			if (hTimebase_PositionTest_Time != 0)  
//		{
//			hTimebase_PositionTest_Time --;
//		}
//		#endif
//		
//	
//		#ifdef TB_CURRENT_PID
//			if (hTimebase_CurrentTest_Time != 0)  
//		{
//			hTimebase_CurrentTest_Time --;
//		}
//		if(hTimebase_CurrentPID_Time != 0)
//		{
//			hTimebase_CurrentPID_Time--;
//		}
//		#endif
//		
//		#ifdef TB_CAN_SEND
//		if(hTimebase_CAN_Send_Time !=0)
//		{
//			hTimebase_CAN_Send_Time--;
//		}
//		#endif
	}
		
}
 




