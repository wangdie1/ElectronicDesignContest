#ifndef __voice_H
#define __voice_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//VOICE��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/2
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 
#define voice1 PAout(1)
#define voice2 PAout(2)	
#define voice3 PAout(3)
#define voice4 PAout(4)
#define voice5 PAout(5)


void set_Voice(u8 i);
void Voice_Init(void);//��ʼ��

		 				    
#endif
