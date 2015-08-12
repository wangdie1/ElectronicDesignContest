// TB6560的代码: 
#include "init.h"
#include "sys.h"  
#include "usart.h" 
#include "delay.h"
#include "tb6560.h"
#include "led.h"

/*
备注:
1.减速伺服电机
2.42步进电机
3.57步进电机
*/

#define DRVDEV    8   //驱动器的细分数 
#define STEPDEG   1.8 //步进电机的步角 

void Step_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;

	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//100MHz

	GPIO_Init(GPIOG, &GPIO_InitStructure);//	
}

//步进电机运转多少角度 
//stepx:步进电机编号,0/1; 
//deg:角度 
//lr :左转或者右转 
void Step_Run_by_PWM(float deg,u8 lr,int delay) 
{    
	float clkf; 
	u16 nclk;    
	clkf=(deg*DRVDEV)/STEPDEG; //  (角度*细分数)/步进电机的步角
	nclk=clkf;//取整数部分 
 
	STEP_DIR=lr; 
	
	
	//方式1  接pwm
	//开启pwm
	TIM_Cmd(TIM3, ENABLE);
	//设置pwm的转动的角度
	TB_SetTB6560_Time(nclk);
}

	
void Step_Run_By_dalay(float deg,u8 lr,int delay) 
{    
	float clkf; 
	u16 nclk;    
	clkf=(deg*DRVDEV)/STEPDEG; //  (角度*细分数)/步进电机的步角
	nclk=clkf;//取整数部分 
 
	STEP_DIR=lr; 
	
	//延时时间和细分数有关
	if(delay == 0)
		delay = 800/DRVDEV;
	else if(delay == 1)
		delay = 800;
	else if(delay == 2)
		delay = 400;
 
	//方法一 ：改变脉冲时，使用延时程序
	while(nclk--) 
	{ 
//		STEP_CLK=0; //产生一个脉冲,频率5Khz 
//		delay_us(400); 
//		STEP_CLK=1; 
//		delay_us(400);	
		
		//整部，半步脉冲
//		STEP_CLK=0; //产生一个脉冲,频率5Khz 
//		delay_us(delay); 
//		STEP_CLK=1; 
//		delay_us(delay);	
	} 
}


//} 
//步进电机运转多少个1.8度 

//dx:1.8度的个数  --多少个1.8度
//lr :0:左转，1:右转
void Step_Run_18(u16 dx,u8 lr) 
{    
	Step_Run(dx*1.8,lr,0);          
}


//步进电机左转
//dx:1.8度的个数
void Step_Run_Left(u16 dx)
{
	Step_Run_18(dx,0); 
}

//步进电机右转



   	  
//通用定时器3中断初始化
//这里时钟选择为APB1的2倍，而APB1为36M
//arr：自动重装值。
//psc：时钟预分频数
//这里使用的是定时器3!
void TIM3_Int_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //时钟使能

	TIM_TimeBaseStructure.TIM_Period = 100-1; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到5000为500ms
	TIM_TimeBaseStructure.TIM_Prescaler =720-1; //设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //使能指定的TIM3中断,允许更新中断

	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

	TIM_Cmd(TIM3, ENABLE);  //使能TIMx外设						 
}


//定时器3中断服务程序
//void TIM3_IRQHandler(void)   //TIM3中断
//{
//	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
//	{
//		TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //清除TIMx的中断待处理位:TIM 中断源 
//		LED0 = !LED0;
//	}
//}




//TIM3 PWM部分初始化 
//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
void TIM3_PWM_Init(u16 arr,u16 psc)
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//使能定时器3时钟
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  | RCC_APB2Periph_AFIO, ENABLE);  //使能GPIO外设和AFIO复用功能模块时钟
	
	
	//GPIO_PinAFConfig(GPIOF,GPIO_PinSource9,GPIO_AF_TIM14); //GPIOF9复用为定时器14
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE); //Timer3部分重映射  TIM3_CH2->PB5    
 
   //设置该引脚为复用输出功能,输出TIM3 CH2的PWM脉冲波形	GPIOB.5
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; //TIM_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIO
 
   //初始化TIM3
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	
	//初始化TIM3 Channel2 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM3 OC2

	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM3在CCR2上的预装载寄存器
 
	TIM_Cmd(TIM3, ENABLE);  //使能TIM3
}





//dx:1.8度的个数
void Step_Run_Right(u16 dx)
{
	Step_Run_18(dx,1); 
}

