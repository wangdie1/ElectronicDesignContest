#include "TimeBase.h"
#include "delay.h"
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


//定义LED
static volatile  u16 hTimebase_LED_Time = 0;


/*******************************************************************************
* Function Name  : TB_Init
* Description    : TimeBase peripheral initialization. The base time is set to 
*                  500usec and the related interrupt is enabled  
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
//void TB_Init(void)
//{
//	 //SystemFrequency /1000 1ms 中断一次  10000 100us
//	 //SystemFrequency /100000 10us中断一次
//	 //SystemFrequency /1000000 1us 中断一次
////	if(SysTick_Config(SystemCoreClock/1000000))	//  TIME_BASE_FREQ ：100000  10us中断一次
////	 {
////	 /*capture error*/
////	 	while(1);
////	 }
//	 //使能
//	 SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
//	 SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
//}

//定时器7的初始化程序
void TB_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE); //时钟使能
	
	//定时器TIM7初始化
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM7,TIM_IT_Update,ENABLE ); //使能指定的TIM7中断,允许更新中断

	//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;  //TIM7中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器
	
	TIM_Cmd(TIM7, ENABLE);  //使能TIMx					 
}


/*****通用定时****/
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

/***************位置环PID频率设置*******************/
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
/***************速度环频率***********************/
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


/*****************LCD刷新频率****×××××××*/
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

/******************ADC采样频率*********************/
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
/**********CAN总线发送频率***********/
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
// ***************位置采样****************************************************************/
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

/**********************速度采样时间设置******************************/
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

/*****************电流环PID 调节频率****×××××××*/
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


/***************电流取样时间设置********************///100us
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


/**************************************************************/
/*------------------------------------------------------------*/
//定义流水灯的采样时间

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


/*******************************************************************************
* Function Name  : SysTickHandler
* Description    : This function handles SysTick Handler.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM7_IRQHandler(void)
{

	if (TIM_GetITStatus(TIM7, TIM_IT_Update) != RESET)  //检查TIM7更新中断发生与否
	{
		TIM_ClearITPendingBit(TIM7, TIM_IT_Update  );  //清除TIM7更新中断标志 
		
		hSysTick_OverNum--;
		if(hTimebase_ADC_Time!=0)
		{
			hTimebase_ADC_Time--;
		}
		if (hTimebase_SpeedPID_Time != 0)  //速度环周期
		{
    	hTimebase_SpeedPID_Time --;
		}
		if(hTimebase_PositionPID_Time !=0)//位置环周期
		{
			hTimebase_PositionPID_Time --;
		}
		if(hTimebase_Delay_Time !=0)//通用延时
		{
			hTimebase_Delay_Time --;
		}
		if(hTimebase_Display_Time!=0)//LCD刷新
		{
			hTimebase_Display_Time--;
		}
		if(hTimebase_LED_Time!=0)//LED采样时间
		{
			hTimebase_LED_Time--;
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
		
}
 




