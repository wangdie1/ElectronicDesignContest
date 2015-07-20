// TB6560的代码: 

#include "sys.h"  
#include "usart.h" 
#include "delay.h"
#include "tb6560.h"


//步进电机运转多少角度 
//stepx:步进电机编号,0/1; 
//deg:角度 
//lr :左转或者右转 
#define DRVDEV    8   //驱动器的细分数 
#define STEPDEG   1.8 //步进电机的步角 

void Step_Init(void)
{
 
	GPIO_InitTypeDef  GPIO_InitStructure;

	//RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);//
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//
	//GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;//100MHz
	//GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//
	GPIO_Init(GPIOG, &GPIO_InitStructure);//
	
}

void Step_Run(float deg,u8 lr) 
{    
	float clkf; 
	u16 nclk;    
	clkf=(deg*DRVDEV)/STEPDEG; //  (角度*细分数)/步进电机的步角
	nclk=clkf;//取整数部分 
 
	STEP_DIR=lr; 
 
	while(nclk--) 
	{ 
//		STEP_CLK=0; //产生一个脉冲,频率5Khz 
//		delay_us(400); 
//		STEP_CLK=1; 
//		delay_us(400);	
		
		//整部，半步脉冲
		STEP_CLK=0; //产生一个脉冲,频率5Khz 
		delay_us(800); 
		STEP_CLK=1; 
		delay_us(800);	
	} 

} 
//步进电机运转多少个1.8度 

//dx:1.8度的个数  --多少个1.8度
//lr :0:左转，1:右转
void Step_Run_18(u16 dx,u8 lr) 
{    
	Step_Run(dx*1.8,lr);          
}


//步进电机左转
//dx:1.8度的个数
void Step_Run_Left(u16 dx)
{
	Step_Run_18(dx,0); 
}

//步进电机右转
//dx:1.8度的个数
void Step_Run_Right(u16 dx)
{
	Step_Run_18(dx,1); 
}


 
 
