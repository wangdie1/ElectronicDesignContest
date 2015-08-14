#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
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




#define KEYA GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_3)// 按键A
#define KEYB GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_5)// 按键B
#define KEYC GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_2)// 按键C
#define KEYD GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_4)// 按键D
#define KEYE GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13)// 按键E

#define KEYADD GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_9)// 添加按键
#define KEYDCS GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_11)// 减少按键

#define KEYCF GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)// 确认按键
#define KEYCC GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_10)// 取消按键

#define WK_UP  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)//wk

//功能选项按键
#define KEYA_PRES	1	//  按键A按下
#define KEYB_PRES	2	//  按键B按下
#define KEYC_PRES	3	//  按键C按下
#define KEYD_PRES	4	//  按键D按下
#define KEYE_PRES	5	//  按键E按下
//确认取消按键
#define KEYCF_PRES	6	//  确认键按下
#define KEYCC_PRES	7	//  取消/返回键按下
//加减按键
#define KEYADD_PRES 8  //  按键加按下
#define KEYDCS_PRES 9  //  按键减按下

#define WKUP_PRES   10  //返回上一层菜单键 

void KEY_Init(void);//IO初始化
u8 KEY_Scan(u8);  	//按键扫描函数					    
#endif
