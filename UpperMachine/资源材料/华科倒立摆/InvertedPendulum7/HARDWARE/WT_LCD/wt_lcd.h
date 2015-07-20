/*
*****************************************************************************
** �ļ����� �� lcd.h
** ����˵�� �� stm32ϵ��оƬӲ�� �������
** ʹ��˵�� �� 
** ��    �� ��xiong57785@163.com    ��    �ڣ�2012��07-12
** ��    �� ��                 		��    �ڣ� 
*****************************************************************************/
#ifndef __WT_LCD_H__
#define __WT_LCD_H__

#include "stm32f10x.h"


#define	 SID    		GPIO_Pin_1   
#define  SCLK   		GPIO_Pin_2
#define  RCC_GPIO_LCD	RCC_APB2Periph_GPIOB
#define  GPIO_LCD_PORT	GPIOB
#define  GPIO_LCD_ALL	SID | SCLK

#define READ_STATE		0xfc
#define READ_DATA		0xfe
#define WRITE_COM		0xf8
#define WRITE_DATA		0xfa
#define LCD_CLEAN  0X01



//=========�ⲿ�ӿڱ���============//


//========�ⲿ�ӿں���=============//
extern void LCD_Init(void);
extern void LCD_StrShow(u8 x,u8 y,char *str);
void LCD_Clean();
void LCD_Clrscreen(void);
void PhotoDisplay(unsigned char * photo);
#endif
/*****************************************************************************
**                            End Of File
*****************************************************************************/
