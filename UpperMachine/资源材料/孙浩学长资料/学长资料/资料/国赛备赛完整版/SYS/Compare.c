/*嵌入式家园stm32 时钟输入捕获代码库函数版1.0版本 不足之处希望同学们可以多多修改，使程序更
加完善。
作者 孙浩 2013.4.1 */
//定时器5时接PA0,PA1,PA2,PA3
//定时器2时接PA0,PA1,PA2,PA3
//定时器3时接PA6,PA7,PB0,PB1
//定时器4时接PB6,PB7,PB8,PB9

#include"Compare.h"
#include<stm32f10x.h>


void Input_Compare_Init( COMPARE_type type)
{
   TIM5_GPIO_INIT(type);
   TIM5_Cap_Init(type,0XFFFF,72-1);

}


void TIM5_GPIO_INIT(COMPARE_type type )
{
 	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);	//使能TIM5时钟
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //使能GPIOA时钟

	if(type==TIM5_1)
	{	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;    //PA0 清除之前设置  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA0 输入  
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOA,GPIO_Pin_0);			  //PA0 下拉
	}
	else if(type==TIM5_2)
	{	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1;    //PA1 清除之前设置  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA1 输入  
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOA,GPIO_Pin_1);			  //PA1 下拉
	}
	else if(type==TIM5_3)
	{	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2;    //PA2 清除之前设置  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA2 输入  
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOA,GPIO_Pin_2);			  //PA2 下拉
	}
	else if(type==TIM5_4)
	{	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_3;    //PA3 清除之前设置  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA3 输入  
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOA,GPIO_Pin_3);			  //PA3 下拉
	}

}




void TIM5_Cap_Init(COMPARE_type type,unsigned int arr,unsigned int psc)
{	 
	TIM_ICInitTypeDef  TIM5_ICInitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

	if(type==TIM5_1)
	{
	//初始化定时器5 TIM5	 
	TIM_TimeBaseStructure.TIM_Period = arr; //设定计数器自动重装值 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 	//预分频器   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
  
	//初始化TIM5输入捕获参数
	TIM5_ICInitStructure.TIM_Channel = TIM_Channel_1; //CC1S=01 	选择输入端 IC1映射到TI1上
  	TIM5_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//上升沿捕获
  	TIM5_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
  	TIM5_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //配置输入分频,不分频 
  	TIM5_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 配置输入滤波器 不滤波
  	TIM_ICInit(TIM5, &TIM5_ICInitStructure);
	TIM_ITConfig(TIM5,TIM_IT_Update|TIM_IT_CC1,ENABLE);//允许更新中断 ,允许CC1IE捕获中断	
	}
	else if(type==TIM5_2)
 	{
	//初始化定时器5 TIM5	 
	TIM_TimeBaseStructure.TIM_Period = arr; //设定计数器自动重装值 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 	//预分频器   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
  
	//初始化TIM5输入捕获参数
	TIM5_ICInitStructure.TIM_Channel = TIM_Channel_2; //CC1S=01 	选择输入端 IC1映射到TI1上
  	TIM5_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//上升沿捕获
  	TIM5_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
  	TIM5_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //配置输入分频,不分频 
  	TIM5_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 配置输入滤波器 不滤波
  	TIM_ICInit(TIM5, &TIM5_ICInitStructure);
	TIM_ITConfig(TIM5,TIM_IT_Update|TIM_IT_CC2,ENABLE);//允许更新中断 ,允许CC1IE捕获中断	
	}
	else if(type==TIM5_3)
 	{
	//初始化定时器5 TIM5	 
	TIM_TimeBaseStructure.TIM_Period = arr; //设定计数器自动重装值 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 	//预分频器   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
  
	//初始化TIM5输入捕获参数
	TIM5_ICInitStructure.TIM_Channel = TIM_Channel_3; //CC1S=01 	选择输入端 IC1映射到TI1上
  	TIM5_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//上升沿捕获
  	TIM5_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
  	TIM5_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //配置输入分频,不分频 
  	TIM5_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 配置输入滤波器 不滤波
  	TIM_ICInit(TIM5, &TIM5_ICInitStructure);
	TIM_ITConfig(TIM5,TIM_IT_Update|TIM_IT_CC3,ENABLE);//允许更新中断 ,允许CC1IE捕获中断	
	}
	else if(type==TIM5_4)
 	{
	//初始化定时器5 TIM5	 
	TIM_TimeBaseStructure.TIM_Period = arr; //设定计数器自动重装值 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 	//预分频器   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
  
	//初始化TIM5输入捕获参数
	TIM5_ICInitStructure.TIM_Channel = TIM_Channel_4; //CC1S=01 	选择输入端 IC1映射到TI1上
  	TIM5_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//上升沿捕获
  	TIM5_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
  	TIM5_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //配置输入分频,不分频 
  	TIM5_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 配置输入滤波器 不滤波
  	TIM_ICInit(TIM5, &TIM5_ICInitStructure);
	TIM_ITConfig(TIM5,TIM_IT_Update|TIM_IT_CC4,ENABLE);//允许更新中断 ,允许CC1IE捕获中断	
	}

 	TIM_Cmd(TIM5,ENABLE ); 	//使能定时器5
   
}



u8  TIM5CH1_CAPTURE_STA=0;	//输入捕获状态		    				
u32	TIM5CH1_CAPTURE_VAL;	//输入捕获值

u8  TIM5CH2_CAPTURE_STA=0;	//输入捕获状态		    				
u32	TIM5CH2_CAPTURE_VAL;	//输入捕获值

u8  TIM5CH3_CAPTURE_STA=0;	//输入捕获状态		    				
u32	TIM5CH3_CAPTURE_VAL;	//输入捕获值

u8  TIM5CH4_CAPTURE_STA=0;	//输入捕获状态		    				
u32	TIM5CH4_CAPTURE_VAL;	//输入捕获值

 
//定时器5中断服务程序	 
void TIM5_IRQHandler(void)
{ 

 	if((TIM5CH1_CAPTURE_STA&0X80)==0)//还未成功捕获	
	{	  
		if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)
		 
		{	    
			if(TIM5CH1_CAPTURE_STA&0X40)//已经捕获到高电平了
			{
				if((TIM5CH1_CAPTURE_STA&0X3F)==0X3F)//高电平太长了
				{
					TIM5CH1_CAPTURE_STA|=0X80;//标记成功捕获了一次
					TIM5CH1_CAPTURE_VAL=0XFFFF;
				}else TIM5CH1_CAPTURE_STA++;
			}	 
		}

	if (TIM_GetITStatus(TIM5, TIM_IT_CC1) != RESET)//捕获1发生捕获事件
		{	
			if(TIM5CH1_CAPTURE_STA&0X40)		//捕获到一个下降沿 		
			{	  			
				TIM5CH1_CAPTURE_STA|=0X80;		//标记成功捕获到一次上升沿
				TIM5CH1_CAPTURE_VAL=TIM_GetCapture1(TIM5);
		   		TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Rising); //CC1P=0 设置为上升沿捕获
			}else  								//还未开始,第一次捕获上升沿
			{
				TIM5CH1_CAPTURE_STA=0;			//清空
				TIM5CH1_CAPTURE_VAL*=0;
	 			TIM_SetCounter(TIM5,0);
				TIM5CH1_CAPTURE_STA|=0X40;		//标记捕获到了上升沿
		   		TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Falling);		//CC1P=1 设置为下降沿捕获
			}		    
		}			     	    					   
 	} 

	if((TIM5CH2_CAPTURE_STA&0X80)==0)//还未成功捕获	
	{	  
		if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)
		 
		{	    
			if(TIM5CH2_CAPTURE_STA&0X40)//已经捕获到高电平了
			{
				if((TIM5CH2_CAPTURE_STA&0X3F)==0X3F)//高电平太长了
				{
					TIM5CH2_CAPTURE_STA|=0X80;//标记成功捕获了一次
					TIM5CH2_CAPTURE_VAL=0XFFFF;
				}else TIM5CH2_CAPTURE_STA++;
			}	 
		}

	if (TIM_GetITStatus(TIM5, TIM_IT_CC2) != RESET)//捕获1发生捕获事件
		{	
			if(TIM5CH2_CAPTURE_STA&0X40)		//捕获到一个下降沿 		
			{	  			
				TIM5CH2_CAPTURE_STA|=0X80;		//标记成功捕获到一次上升沿
				TIM5CH2_CAPTURE_VAL=TIM_GetCapture2(TIM5);
		   		TIM_OC2PolarityConfig(TIM5,TIM_ICPolarity_Rising); //CC1P=0 设置为上升沿捕获
			}else  								//还未开始,第一次捕获上升沿
			{
				TIM5CH2_CAPTURE_STA=0;			//清空
				TIM5CH2_CAPTURE_VAL*=0;
	 			TIM_SetCounter(TIM5,0);
				TIM5CH2_CAPTURE_STA|=0X40;		//标记捕获到了上升沿
		   		TIM_OC2PolarityConfig(TIM5,TIM_ICPolarity_Falling);		//CC1P=1 设置为下降沿捕获
			}		    
		}			     	    					   
 	} 

	if((TIM5CH3_CAPTURE_STA&0X80)==0)//还未成功捕获	
	{	  
		if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)
		 
		{	    
			if(TIM5CH3_CAPTURE_STA&0X40)//已经捕获到高电平了
			{
				if((TIM5CH3_CAPTURE_STA&0X3F)==0X3F)//高电平太长了
				{
					TIM5CH3_CAPTURE_STA|=0X80;//标记成功捕获了一次
					TIM5CH3_CAPTURE_VAL=0XFFFF;
				}else TIM5CH3_CAPTURE_STA++;
			}	 
		}

	if (TIM_GetITStatus(TIM5, TIM_IT_CC3) != RESET)//捕获1发生捕获事件
		{	
			if(TIM5CH3_CAPTURE_STA&0X40)		//捕获到一个下降沿 		
			{	  			
				TIM5CH3_CAPTURE_STA|=0X80;		//标记成功捕获到一次上升沿
				TIM5CH3_CAPTURE_VAL=TIM_GetCapture3(TIM5);
		   		TIM_OC3PolarityConfig(TIM5,TIM_ICPolarity_Rising); //CC1P=0 设置为上升沿捕获
			}else  								//还未开始,第一次捕获上升沿
			{
				TIM5CH3_CAPTURE_STA=0;			//清空
				TIM5CH3_CAPTURE_VAL*=0;
	 			TIM_SetCounter(TIM5,0);
				TIM5CH3_CAPTURE_STA|=0X40;		//标记捕获到了上升沿
		   		TIM_OC3PolarityConfig(TIM5,TIM_ICPolarity_Falling);		//CC1P=1 设置为下降沿捕获
			}		    
		}			     	    					   
 	} 

	if((TIM5CH4_CAPTURE_STA&0X80)==0)//还未成功捕获	
	{	  
		if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)
		 
		{	    
			if(TIM5CH4_CAPTURE_STA&0X40)//已经捕获到高电平了
			{
				if((TIM5CH4_CAPTURE_STA&0X3F)==0X3F)//高电平太长了
				{
					TIM5CH4_CAPTURE_STA|=0X80;//标记成功捕获了一次
					TIM5CH4_CAPTURE_VAL=0XFFFF;
				}else TIM5CH4_CAPTURE_STA++;
			}	 
		}

	if (TIM_GetITStatus(TIM5, TIM_IT_CC4) != RESET)//捕获1发生捕获事件
		{	
			if(TIM5CH4_CAPTURE_STA&0X40)		//捕获到一个下降沿 		
			{	  			
				TIM5CH4_CAPTURE_STA|=0X80;		//标记成功捕获到一次上升沿
				TIM5CH4_CAPTURE_VAL=TIM_GetCapture4(TIM5);
		   		TIM_OC4PolarityConfig(TIM5,TIM_ICPolarity_Rising); //CC1P=0 设置为上升沿捕获
			}else  								//还未开始,第一次捕获上升沿
			{
				TIM5CH4_CAPTURE_STA=0;			//清空
				TIM5CH4_CAPTURE_VAL*=0;
	 			TIM_SetCounter(TIM5,0);
				TIM5CH4_CAPTURE_STA|=0X40;		//标记捕获到了上升沿
		   		TIM_OC4PolarityConfig(TIM5,TIM_ICPolarity_Falling);		//CC1P=1 设置为下降沿捕获
			}		    
		}			     	    					   
 	}
 
    TIM_ClearITPendingBit(TIM5, TIM_IT_CC1|TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4|TIM_IT_Update); //清除中断标志位

}


int Get_H_Pulse(COMPARE_type type)
{
int temp=0;
        switch(type)
		{
	 	    case(0):
			{
				if(TIM5CH1_CAPTURE_STA&0X80)//成功捕获到了一次上升沿
				{
					temp=TIM5CH1_CAPTURE_STA&0X3F;
					temp*=65536;//溢出时间总和
					temp+=TIM5CH1_CAPTURE_VAL;//得到总的高电平时间
					//printf("HIGH:%d us\r\n",temp);//打印总的高点平时间
					TIM5CH1_CAPTURE_STA=0;//开启下一次捕获
				}
				return temp;
			}
			 case(1):
			{
				if(TIM5CH2_CAPTURE_STA&0X80)//成功捕获到了一次上升沿
				{
					temp=TIM5CH2_CAPTURE_STA&0X3F;
					temp*=65536;//溢出时间总和
					temp+=TIM5CH2_CAPTURE_VAL;//得到总的高电平时间
					//printf("HIGH:%d us\r\n",temp);//打印总的高点平时间
					TIM5CH2_CAPTURE_STA=0;//开启下一次捕获
				}
				return temp;
			}
			 case(2):
			{
				if(TIM5CH3_CAPTURE_STA&0X80)//成功捕获到了一次上升沿
				{
					temp=TIM5CH3_CAPTURE_STA&0X3F;
					temp*=65536;//溢出时间总和
					temp+=TIM5CH3_CAPTURE_VAL;//得到总的高电平时间
					//printf("HIGH:%d us\r\n",temp);//打印总的高点平时间
					TIM5CH3_CAPTURE_STA=0;//开启下一次捕获
				}
				return temp;
			}
			 case(3):
			{
				if(TIM5CH4_CAPTURE_STA&0X80)//成功捕获到了一次上升沿
				{
					temp=TIM5CH4_CAPTURE_STA&0X3F;
					temp*=65536;//溢出时间总和
					temp+=TIM5CH4_CAPTURE_VAL;//得到总的高电平时间
					//printf("HIGH:%d us\r\n",temp);//打印总的高点平时间
					TIM5CH4_CAPTURE_STA=0;//开启下一次捕获
				}
				return temp;
			}
			
		}
	 return -1;
}

