  #ifndef __RED_H
#define __RED_H 
#include "sys.h"   
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������V3
//����ң�ؽ������� ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2015/1/15
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////

#define RDATA 	PBin(9)	 	//�������������

//����ң��ʶ����(ID),ÿ��ң�����ĸ�ֵ��������һ��,��Ҳ��һ����.
//����ѡ�õ�ң����ʶ����Ϊ0
#define REMOTE_ID 0      		   

//����ң�ض�ȡֵ
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
extern u8 RmtCnt;			//�������µĴ���

void Remote_Init(void);    	//���⴫��������ͷ���ų�ʼ��
u8 Remote_Scan(void);
u8 Remote_Read(u8 key);
#endif















