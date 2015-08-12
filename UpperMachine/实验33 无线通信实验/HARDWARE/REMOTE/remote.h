  #ifndef __RED_H
#define __RED_H 
#include "sys.h"   
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板V3
//红外遥控解码驱动 代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2015/1/15
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////

#define RDATA 	PBin(9)	 	//红外数据输入脚

//红外遥控识别码(ID),每款遥控器的该值基本都不一样,但也有一样的.
//我们选用的遥控器识别码为0
#define REMOTE_ID 0      		   

//红外遥控读取值
#define REMOTE0_PRES  0
#define REMOTE1_PRES  1
#define REMOTE2_PRES  2
#define REMOTE3_PRES  3
#define REMOTE4_PRES  4
#define REMOTE5_PRES  5
#define REMOTE6_PRES  6
#define REMOTE7_PRES  7
#define REMOTE8_PRES  8
#define REMOTE9_PRES  9

#define ERROR         11
#define POWER         12
#define UP        	  13
#define PLAY          14
#define ALIENTEK      15
#define RIGHT         16
#define LEFT          17
#define VOLH          18
#define DOWN          19
#define VOLL          20
#define DELETE        21







//
extern u8 RmtCnt;			//按键按下的次数

void Remote_Init(void);    	//红外传感器接收头引脚初始化
u8 Remote_Scan(void);
u8 Remote_Read(u8 key);
#endif















