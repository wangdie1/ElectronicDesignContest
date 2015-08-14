#include "stm32f10x.h"
#include "key.h"
#include "sys.h" 
#include "delay.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//������������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/3
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////  
								    
//������ʼ������
void KEY_Init(void) //IO��ʼ��
{ 
	//ս��
// 	GPIO_InitTypeDef GPIO_InitStructure;
// 
// 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOE,ENABLE);//ʹ��PORTA,PORTEʱ��

//	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;//KEY0-KEY2
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
// 	GPIO_Init(GPIOE, &GPIO_InitStructure);//��ʼ��GPIOE2,3,4

//	//��ʼ�� WK_UP-->GPIOA.0	  ��������
//	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA0���ó����룬Ĭ������	  
//	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.0
	
	
	//��һ��
	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOE,ENABLE);//ʹ��PORTA,PORTEʱ��

	//��ʼ��C13     --E
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //PC13���ó����룬Ĭ������
 	GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIOE2,3,4
	
	//��ʼ��C2-C5   --A,B,C,D
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //PC13���ó����룬Ĭ������
 	GPIO_Init(GPIOG, &GPIO_InitStructure);//��ʼ��GPIOE2,3,4
	
	//��ʼ��D12-D15  --���� + -
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //PC13���ó����룬Ĭ������
 	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOE2,3,4
	

	//��ʼ�� WK_UP-->GPIOA.0	  ��������
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //PE0���ó����룬Ĭ������	  
	GPIO_Init(GPIOE, &GPIO_InitStructure);//��ʼ��GPIOA.0
	
	
	

}
//����������
//���ذ���ֵ
//mode:0,��֧��������;1,֧��������;
//0��û���κΰ�������
//1��KEY0����
//2��KEY1����
//3��KEY2���� 
//4��KEY3���� WK_UP
//ע��˺�������Ӧ���ȼ�,KEY0>KEY1>KEY2>KEY3!!
//u8 KEY_Scan(u8 mode)
//{	 
//	static u8 key_up=1;//�������ɿ���־
//	if(mode)key_up=1;  //֧������		  
//	if(key_up&&(KEY0==0||KEY1==0||KEY2==0||WK_UP==1))
//	{
//		delay_ms(10);//ȥ���� 
//		key_up=0;
//		if(KEY0==0)return KEY0_PRES;
//		else if(KEY1==0)return KEY1_PRES;
//		else if(KEY2==0)return KEY2_PRES;
//		else if(WK_UP==1)return WKUP_PRES;
//	}else if(KEY0==1&&KEY1==1&&KEY2==1&&WK_UP==0)key_up=1; 	    
// 	return 0;// �ް�������
//}


u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//�������ɿ���־
	if(mode)key_up=1;  //֧������		  
	if(key_up&&(KEYA==0||KEYB==0||KEYC==0||KEYD==0|| KEYE==0  ||KEYADD==0||KEYDCS==0||KEYCF==0||KEYCC==0||WK_UP == 0))
	{
		delay_ms(10);//ȥ���� 
		key_up=0;
		//���ܰ���
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
		//��Ӽ���
		else if(KEYADD==0)
			return KEYADD_PRES;
		else if(KEYDCS==0)
			return KEYDCS_PRES;
		//ȷ��ȡ��
		else if(KEYCF==0)
			return KEYCF_PRES;
		else if(KEYCC==0)
			return KEYCC_PRES;
		else if(WK_UP == 0)
			return WKUP_PRES;	
	}
	else if(KEYA==1&&KEYB==1&&KEYC==1&&KEYD==1&&KEYE==1&&KEYADD==1&&KEYDCS==1&&KEYCF==1&&KEYCC==1&&WK_UP ==1)
       key_up=1; 	    
 	return 0;// �ް�������
}
