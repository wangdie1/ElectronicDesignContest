#include "init.h"

//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//函数初始化程序	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/2
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////// 






void Init(void)
{	    
	//基本功能初始化
	delay_init();	    	 							//延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);		//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	uart_init(115200);	 								//串口初始化为115200   
 	LED_Init();		  									//初始化与LED连接的硬件接口
	KEY_Init();											//按键初始化
	RTC_Init();		//内部时钟初始化
	BEEP_Init();
//	LCD_Init();											//初始化LCD 
	TB_Init(10-1,719); 									//采样频率初始化
	
	
	usmart_dev.init(72);		//初始化USMART
	MPU_Init();					//初始化MPU6050
	
	/*拓展功能初始
	
	*/
	//1.USMART初始化
//	usmart_dev.init(72);		//初始化USMART

	
	//2.电机模块初始化
//	MotorInit();
//	 Encoder_Init();
//	 Encoder1_Init();
//	 TIM_PWM_Init();
	
	//3.超声波模块初始化
//	UltrasonicWave_Configuration();
//	TIM4_Cap_Init(65535,72-1); 							 //以1Mhz的频率计数  1/1M = 1/1,000,000   f 72M/72 = 1M  ,T  1us  计数到65536
				   		 
 	
	//4.无线模块初始化
//	NRF24L01_Init();    		//初始化NRF24L01 

	//5.mpu6050模块
//	u8 MPU_Init(void); 

	//6.匿名上位机模块
	
	//红外接收传感器
//	Remote_Init();	
}
