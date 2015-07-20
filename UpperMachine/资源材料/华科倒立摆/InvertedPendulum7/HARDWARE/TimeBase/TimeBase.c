#include "TimeBase.h"
#include "led.h"
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

static volatile  u16 hTimebase_Delay_Time = 0;
static volatile  u16 hTimebase_Display_Time =0;

static volatile u16 hTimebase_ADC_Time = 0;

volatile u32 hSysTick_OverNum=0;




/*******************************************************************************
* Function Name  : TB_Init
* Description    : TimeBase peripheral initialization. The base time is set to 
*                  500usec and the related interrupt is enabled  
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TB_Init(void)
{
	 //SystemFrequency /1000 1ms �ж�һ��  10000 100us
	 //SystemFrequency /100000 10us�ж�һ��
	 //SystemFrequency /1000000 1us �ж�һ��
	 if(SysTick_Config(SystemCoreClock/TIME_BASE_FREQ))	 //10us
	 {
	 /*capture error*/
	 	while(1);
	 }
	 //ʹ��
	 SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
// 	 SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk;
	 SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
}


/*****ͨ�ö�ʱ****/
void TB_SetDelay_Time(u16 hDelay)
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

/***************λ�û�PIDƵ������*******************/
void TB_SetPositionPIDDelay_Time(u16 hDelay)//10ms
{
	hTimebase_PositionPID_Time = hDelay;
}
bool TB_PositionPIDDelay_IsElapsed(void)
{
	if(hTimebase_PositionPID_Time==0)
	{
		return (true);
	}
	else
	{
		return  (false );
	}
}
/***************�ٶȻ�Ƶ��***********************/
void TB_SetSpeedPIDDelay_Time(u16 hDelay )
{
	hTimebase_SpeedPID_Time=  hDelay;
}

bool TB_SpeedPIDDelay_IsElapsed(void)
{
	if(hTimebase_SpeedPID_Time == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}


/*****************LCDˢ��Ƶ��****��������������*/
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

/******************ADC����Ƶ��*********************/
void TB_SetADC_Time(u16 hDelay)
{
	hTimebase_ADC_Time = hDelay;
}
bool TB_ADC_Delay_IsElapsed(void)
{
	if(hTimebase_ADC_Time==0)
	{
		return true;
	}
	else 
		return false;
}

#ifdef TB_CAN_SEND
/**********CAN���߷���Ƶ��***********/
void TB_SetCAN_SendDelay_Time(u16 hDelay)
{
	hTimebase_CAN_Send_Time  = hDelay ;	
}
bool  TB_CAN_SendDelay_IsElapsed(void )
{
	if (hTimebase_CAN_Send_Time == 0)
	{
		return (true);
	}
	else 
	{
		return (false);
	}
}
#endif

#ifdef TB_TEST
// ***************λ�ò���****************************************************************/
void TB_Set_PositionDelay_Time(u16 hDelay)
{
	hTimebase_PositionTest_Time =hDelay;

}
bool TB_PositionDelay_IsElapsed(void)
{
 if (hTimebase_PositionTest_Time == 0)
 {
   return (true);
 }
 else 
 {
   return (false);
 }
}

/**********************�ٶȲ���ʱ������******************************/
void TB_SetSpeedDelay_Time(u16 hDelay )
{
	hTimebase_SpeedTest_Time=  hDelay;
}
bool TB_SpeedDelay_IsElapsed(void)
{
	if(hTimebase_SpeedTest_Time == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
#endif




#ifdef TB_CURRENT_PID

/*****************������PID ����Ƶ��****��������������*/
void TB_SetCurrentPIDDelay_Time(u16 hDelay)
{
	hTimebase_CurrentPID_Time =hDelay;
}
bool TB_CurrentPIDDelay_IsElapsed(void)
{
	if(hTimebase_CurrentPID_Time == 0)
	{
		return true;
	}
	else return false;
}

/***************����ȡ��ʱ������********************///100us
void TB_SetCurrentDelay_Time(u16 hDelay )
{
	hTimebase_CurrentTest_Time=  hDelay;
}
bool TB_CurrentDelay_IsElapsed(void)
{
	if(hTimebase_CurrentTest_Time == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
#endif



/*******************************************************************************
* Function Name  : SysTickHandler
* Description    : This function handles SysTick Handler.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SysTick_Handler(void)
{
	//GPIOC->ODR ^= GPIO_Pin_9;
// 		LED2_Toggle();
		hSysTick_OverNum--;
		if(hTimebase_ADC_Time!=0)
		{
			hTimebase_ADC_Time--;
		}
		if (hTimebase_SpeedPID_Time != 0)  //�ٶȻ�����
  	{
    	hTimebase_SpeedPID_Time --;
  	}
		if(hTimebase_PositionPID_Time !=0)//λ�û�����
		{
			hTimebase_PositionPID_Time --;
		}
		if(hTimebase_Delay_Time !=0)//ͨ����ʱ
		{
			hTimebase_Delay_Time --;
		}
		if(hTimebase_Display_Time!=0)//LCDˢ��
		{
			hTimebase_Display_Time--;
		}
	
	#ifdef TB_TEST
		if (hTimebase_SpeedTest_Time != 0)  
  	{
    	hTimebase_SpeedTest_Time --;
  	}
		if (hTimebase_PositionTest_Time != 0)  
  	{
    	hTimebase_PositionTest_Time --;
  	}
	#endif
	
	#ifdef TB_CURRENT_PID
		if (hTimebase_CurrentTest_Time != 0)  
  	{
    	hTimebase_CurrentTest_Time --;
  	}
		if(hTimebase_CurrentPID_Time != 0)
		{
			hTimebase_CurrentPID_Time--;
		}
	#endif
	#ifdef TB_CAN_SEND
		if(hTimebase_CAN_Send_Time !=0)
		{
			hTimebase_CAN_Send_Time--;
		}
	#endif
	
}
 




