#include "remote.h"
#include "delay.h"
#include "mytype.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//Mini STM32������
//����ң�ؽ��� ��������		   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2010/6/17 
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ����ԭ�� 2009-2019
//All rights reserved
////////////////////////////////////////////////////////////////////////////////// 	  

extern u8 bMenu_index;
extern SysStatus_t State;
					
u32 Remote_Odr=0;  	 //�����ݴ洦
u8  Remote_Cnt=0;    //��������,�˴ΰ��¼��Ĵ���
u8  Remote_Rdy=0;    //������յ�����    
//��ʼ������������ŵ�����
//�����ж�,��ӳ�� 




void Remote_Init(void)
{							 
	GPIO_InitTypeDef GPIO_InitStructure;	//GPIO
	NVIC_InitTypeDef NVIC_InitStructure;	//�ж�
	EXTI_InitTypeDef EXTI_InitStructure;	//�ⲿ�ж���
 		 
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE );	  
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU ;  //��������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);  
 
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource3);  	//ѡ��PA1���ڵ�GPIO�ܽ������ⲿ�ж���·EXIT1		
 
	EXTI_InitStructure.EXTI_Line = EXTI_Line3;	//�ⲿ��·EXIT1
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;			//�����ⲿ�ж�ģʽ:EXTI��·Ϊ�ж�����  EXTI_Mode_Event ;//���� EXTI��·Ϊ�¼����� 
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  //�ⲿ�жϴ�����ѡ��:����������·�½���Ϊ�ж�����
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;		//ʹ���ⲿ�ж���״̬
	EXTI_Init(&EXTI_InitStructure);		//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���	
 
	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn; //ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; //��ռ���ȼ�2��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; //�����ȼ�1��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&NVIC_InitStructure); //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
}   
//���������
//�����Ϊ5ms
//����ֵ:x,��������Ϊx*20us(x=1~250);
u8 Pulse_Width_Check(void)
{
    u8 t=0;	 
    while(RDATA)
    {	 
		t++;delay_us(20+2);			//�����ʱ+2����ʱ����ʱ����Ҫ		 
        if(t==250)return t; //��ʱ���
    }
    return t;
}			   
//����������  
/*-------------------------Э��--------------------------
��ʼ����9ms,������һ��4.5ms�ĸ�����,֪ͨ������ʼ����������
�����Ƿ���4��8λ��������,��һ������ң��ʶ����(REMOTE_ID),��һ��Ϊ
����(0),�ڶ���Ϊ����(255),�������������Ǽ�ֵ,��һ��Ϊ����
�ڶ���Ϊ����.�������40ms,ң���ٷ���һ��9ms��,2ms�ߵ�����,
��ʾ�����Ĵ���,����һ����֤��ֻ������һ��,������ֶ��,���
����Ϊ�ǳ������¸ü�.
---------------------------------------------------------*/		 
//�ⲿ�жϷ������	   
void EXTI3_IRQHandler(void)
{       
	  u8 res=0;
    u8 OK=0; 
    u8 RODATA=0; 
	  while(1)
    {        
        if(RDATA)//�и��������
        {
            res=Pulse_Width_Check();//��ô˴θ�������       
            if(res==250)break;//�������ź�
            if(res>=200&&res<250)OK=1; //���ǰ��λ(4.5ms)
            else if(res>=85&&res<200)  //����������һ(2ms)
            {  							    		 
                Remote_Rdy=1;//���ܵ�����
                Remote_Cnt++;//������������
							  delay_ms(20);
                break;
            }
            else if(res>=50&&res<85)RODATA=1;//1.5ms
            else if(res>=10&&res<50)RODATA=0;//500us
            if(OK)
            {
                Remote_Odr<<=1;
                Remote_Odr+=RODATA; 
                Remote_Cnt=0; //������������
            }   
        }			 						 
    } 	 	    
	EXTI->PR=1<<3;     //���LINE1�ϵ��жϱ�־λ    
}  
//����������
//������Ӧ�ļ�ֵ
u8 Remote_Process(void)
{               
    u8 t1,t2;   
    t1=Remote_Odr>>24; //�õ���ַ��
    t2=(Remote_Odr>>16)&0xff;//�õ���ַ���� 
    Remote_Rdy=0;//������ 		      
    if(t1==(u8)~t2&&t1==REMOTE_ID)//����ң��ʶ����(ID)����ַ 
    { 
        t1=Remote_Odr>>8;
        t2=Remote_Odr; 	
        if(t1==(u8)~t2)return t1; //�����ֵ  
    }     
    return 0;
}
void IR_KEYS_Process(void)
{
	u16 key;
	if(Remote_Rdy)
	{
		Remote_Rdy=0;
		key=Remote_Process();
		switch(bMenu_index)
		{
			case MODE_SELECT_MENU:
				switch(key)
				{
					case IR_KEY1:
						State= POSITION_MEASURE;
						bMenu_index=POSITION_MEASURE_MENU;
					break;
					case IR_KEY2:
						State= POSITION_CONTROL;
						bMenu_index=POSITION_CONTROL_MENU;
					break;
					case IR_KEY3:
						State= WEIGHT_POSITION;
						bMenu_index=WEIGHT_POSITION_MENU;
					break;
					case IR_KEY4:
						State=OTHER;
						bMenu_index=OTHERS_MODE_MENU;
						break;
					default:break;
				
				}
				break;
			case POSITION_MEASURE_MENU:
				break;
			case POSITION_CONTROL_MENU:
				break;
			case WEIGHT_POSITION_MENU:
				break;
			default:
				break;
		}
	}
	
}






























