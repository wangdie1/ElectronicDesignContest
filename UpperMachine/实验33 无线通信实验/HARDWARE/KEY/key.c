#include "stm32f10x.h"
#include "key.h"
#include "sys.h" 
#include "delay.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//按键驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/3
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////  
								    
//按键初始化函数
void KEY_Init(void) //IO初始化
{ 
	//战舰
// 	GPIO_InitTypeDef GPIO_InitStructure;
// 
// 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOE,ENABLE);//使能PORTA,PORTE时钟

//	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;//KEY0-KEY2
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
// 	GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化GPIOE2,3,4

//	//初始化 WK_UP-->GPIOA.0	  下拉输入
//	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA0设置成输入，默认下拉	  
//	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.0
	
	
	//贝一特
	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOE,ENABLE);//使能PORTA,PORTE时钟

	//初始化C13     --E
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //PC13设置成输入，默认下拉
 	GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIOE2,3,4
	
	//初始化C2-C5   --A,B,C,D
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //PC13设置成输入，默认下拉
 	GPIO_Init(GPIOG, &GPIO_InitStructure);//初始化GPIOE2,3,4
	
	//初始化D12-D15  --上下 + -
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //PC13设置成输入，默认下拉
 	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOE2,3,4
	

	//初始化 WK_UP-->GPIOA.0	  下拉输入
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //PE0设置成输入，默认下拉	  
	GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化GPIOA.0
	
	
	

}
//按键处理函数
//返回按键值
//mode:0,不支持连续按;1,支持连续按;
//0，没有任何按键按下
//1，KEY0按下
//2，KEY1按下
//3，KEY2按下 
//4，KEY3按下 WK_UP
//注意此函数有响应优先级,KEY0>KEY1>KEY2>KEY3!!
//u8 KEY_Scan(u8 mode)
//{	 
//	static u8 key_up=1;//按键按松开标志
//	if(mode)key_up=1;  //支持连按		  
//	if(key_up&&(KEY0==0||KEY1==0||KEY2==0||WK_UP==1))
//	{
//		delay_ms(10);//去抖动 
//		key_up=0;
//		if(KEY0==0)return KEY0_PRES;
//		else if(KEY1==0)return KEY1_PRES;
//		else if(KEY2==0)return KEY2_PRES;
//		else if(WK_UP==1)return WKUP_PRES;
//	}else if(KEY0==1&&KEY1==1&&KEY2==1&&WK_UP==0)key_up=1; 	    
// 	return 0;// 无按键按下
//}


u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//按键按松开标志
	if(mode)key_up=1;  //支持连按		  
	if(key_up&&(KEYA==0||KEYB==0||KEYC==0||KEYD==0|| KEYE==0  ||KEYADD==0||KEYDCS==0||KEYCF==0||KEYCC==0||WK_UP == 0))
	{
		delay_ms(10);//去抖动 
		key_up=0;
		//功能按键
		if(KEYA==0)
			return KEYA_PRES;
		else if(KEYB==0)
			return KEYB_PRES;
		else if(KEYC==0)
			return KEYC_PRES;
		else if(KEYD==0)
			return KEYD_PRES;
		else if(KEYE==0)
			return KEYE_PRES;
		//添加减少
		else if(KEYADD==0)
			return KEYADD_PRES;
		else if(KEYDCS==0)
			return KEYDCS_PRES;
		//确定取消
		else if(KEYCF==0)
			return KEYCF_PRES;
		else if(KEYCC==0)
			return KEYCC_PRES;
		else if(WK_UP == 0)
			return WKUP_PRES;	
	}
	else if(KEYA==1&&KEYB==1&&KEYC==1&&KEYD==1&&KEYE==1&&KEYADD==1&&KEYDCS==1&&KEYCF==1&&KEYCC==1&&WK_UP ==1)
       key_up=1; 	    
 	return 0;// 无按键按下
}
