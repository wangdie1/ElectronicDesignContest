/*
	ZLG7290.c
	数码管显示与键盘管理芯片ZLG7290的标准80C51驱动程序C文件
	Copyright (c) 2005，广州周立功单片机发展有限公司
	All rights reserved.
	本程序仅供学习参考，不提供任何可靠性方面的担保；请勿用于商业目的
*/


#include "ZLG7290.h"
extern  unsigned char zlg_key;
extern unsigned char ZLK_KeyRead();

vu8 IsKeyPressed = 0;//按键按下标志

void EXTIX_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
 	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);	//关闭jtag
  RCC_APB2PeriphClockCmd(KEY_INT_PORT_CLK|RCC_APB2Periph_AFIO,ENABLE);
	GPIO_InitStructure.GPIO_Pin  = KEY_INT_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(KEY_INT_PORT, &GPIO_InitStructure);
	
	  //GPIOA.0	  中断线以及中断初始化配置
 	GPIO_EXTILineConfig(KEY_EXTI_PORT_SOURCE,KEY_EXTI_PIN_SOURCE);

		EXTI_InitStructure.EXTI_Line=KEY_EXTI_LINE;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);		//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
	
 	NVIC_InitStructure.NVIC_IRQChannel = KEY_EXTI_IRQn;			//使能按键所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//子优先级2 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
  
}



void EXTI0_IRQHandler(void)
{	
	if(KEY_INT==0)
	{
	
		zlg_key=ZLK_KeyRead();
		if((zlg_key!=0xff)&(zlg_key!=0x00))//避免二次中断
		IsKeyPressed = 1;
		
		while(!KEY_INT);
	}		
	EXTI_ClearITPendingBit(KEY_EXTI_LINE);
// 	EXTI->PR=1<<0;     //清除LINE0上的中断标志位	
}
/*
函数：ZLG7290_WriteReg()
功能：向ZLG7290的某个内部寄存器写入数据
参数：
	RegAddr：ZLG7290的内部寄存器地址
	dat：要写入的数据
返回：
	0：正常
	1：访问ZLG7290时出现异常
*/

u8 ZLG7290_WriteReg(u8 RegAddr, u8 dat)
{
	u8 b;
	b = I2C_Puts(ZLG7290_I2C_ADDR,RegAddr,1,&dat,1);
	return b;
}

/*
函数：ZLG7290_ReadReg()
功能：从ZLG7290的某个内部寄存器读出数据
参数：
	RegAddr：ZLG7290的内部寄存器地址
	*dat：保存读出的数据
返回：
	0：正常
	1：访问ZLG7290时出现异常
*/
u8 ZLG7290_ReadReg(u8 RegAddr, u8 *dat)
{
	u8 b;
	b = I2C_Gets(ZLG7290_I2C_ADDR,RegAddr,1,dat,1);
	return b;
}

/*
函数：ZLG7290_cmd()
功能：向ZLG7290发送控制命令
参数：
	cmd0：写入CmdBuf0寄存器的命令字（第1字节）
	cmd1：写入CmdBuf1寄存器的命令字（第2字节）
返回：
	0：正常
	1：访问ZLG7290时出现异常
*/
u8 ZLG7290_cmd(u8 cmd0, u8 cmd1)
{
	u8 b;
	u8 buf[2];
	buf[0] = cmd0;
	buf[1] = cmd1;
	b = I2C_Puts(ZLG7290_I2C_ADDR,ZLG7290_CmdBuf,1,buf,2);
	return b;
}

/*
函数：ZLG7290_SegOnOff()
功能：段寻址，单独点亮或熄灭数码管（或LED）中的某一段
参数：
	seg：取值0～63，表示数码管（或LED）的段号
	b：0表示熄灭，1表示点亮
返回：
	0：正常
	1：访问ZLG7290时出现异常
说明：
	在每一位数码管中，段号顺序按照“a,b,c,d,e,f,g,dp”进行
*/
u8 ZLG7290_SegOnOff(u8 seg, u8 b)
{
	u8 cmd;
	cmd = seg & 0x3F;
	if ( b ) cmd |= 0x80;
	return ZLG7290_cmd(0x01,cmd);
}

/*
函数：ZLG7290_Download()
功能：下载数据并译码
参数：
	addr：取值0～7，显示缓存DpRam0～DpRam7的编号
	dp：是否点亮该位的小数点，0－熄灭，1－点亮
	flash：控制该位是否闪烁，0－不闪烁，1－闪烁
	dat：取值0～31，表示要显示的数据
返回：
	0：正常
	1：访问ZLG7290时出现异常
说明：
	显示数据具体的译码方式请参见ZLG7290的数据手册
*/
u8 ZLG7290_Download(u8 addr, u8 dp, u8 flash, u8 dat)
{
	u8 cmd0;
	u8 cmd1;
	cmd0 = addr & 0x0F;
	cmd0 |= 0x60;
	cmd1 = dat & 0x1F;
	if ( dp ) cmd1 |= 0x80;
	if ( flash ) cmd1 |= 0x40;
	return ZLG7290_cmd(cmd0,cmd1);
}

