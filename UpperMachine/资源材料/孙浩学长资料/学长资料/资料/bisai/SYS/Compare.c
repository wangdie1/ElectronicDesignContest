/*Ƕ��ʽ��԰stm32 ʱ�����벶�����⺯����1.0�汾 ����֮��ϣ��ͬѧ�ǿ��Զ���޸ģ�ʹ�����
�����ơ�
���� ��� 2013.4.1 */
//��ʱ��5ʱ��PA0,PA1,PA2,PA3
//��ʱ��2ʱ��PA0,PA1,PA2,PA3
//��ʱ��3ʱ��PA6,PA7,PB0,PB1
//��ʱ��4ʱ��PB6,PB7,PB8,PB9

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

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);	//ʹ��TIM5ʱ��
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //ʹ��GPIOAʱ��

	if(type==TIM5_1)
	{	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;    //PA0 ���֮ǰ����  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA0 ����  
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOA,GPIO_Pin_0);			  //PA0 ����
	}
	else if(type==TIM5_2)
	{	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1;    //PA1 ���֮ǰ����  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA1 ����  
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOA,GPIO_Pin_1);			  //PA1 ����
	}
	else if(type==TIM5_3)
	{	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2;    //PA2 ���֮ǰ����  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA2 ����  
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOA,GPIO_Pin_2);			  //PA2 ����
	}
	else if(type==TIM5_4)
	{	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_3;    //PA3 ���֮ǰ����  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA3 ����  
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOA,GPIO_Pin_3);			  //PA3 ����
	}

}




void TIM5_Cap_Init(COMPARE_type type,unsigned int arr,unsigned int psc)
{	 
	TIM_ICInitTypeDef  TIM5_ICInitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

	if(type==TIM5_1)
	{
	//��ʼ����ʱ��5 TIM5	 
	TIM_TimeBaseStructure.TIM_Period = arr; //�趨�������Զ���װֵ 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 	//Ԥ��Ƶ��   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
  
	//��ʼ��TIM5���벶�����
	TIM5_ICInitStructure.TIM_Channel = TIM_Channel_1; //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
  	TIM5_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
  	TIM5_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
  	TIM5_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //���������Ƶ,����Ƶ 
  	TIM5_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 ���������˲��� ���˲�
  	TIM_ICInit(TIM5, &TIM5_ICInitStructure);
	TIM_ITConfig(TIM5,TIM_IT_Update|TIM_IT_CC1,ENABLE);//��������ж� ,����CC1IE�����ж�	
	}
	else if(type==TIM5_2)
 	{
	//��ʼ����ʱ��5 TIM5	 
	TIM_TimeBaseStructure.TIM_Period = arr; //�趨�������Զ���װֵ 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 	//Ԥ��Ƶ��   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
  
	//��ʼ��TIM5���벶�����
	TIM5_ICInitStructure.TIM_Channel = TIM_Channel_2; //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
  	TIM5_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
  	TIM5_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
  	TIM5_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //���������Ƶ,����Ƶ 
  	TIM5_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 ���������˲��� ���˲�
  	TIM_ICInit(TIM5, &TIM5_ICInitStructure);
	TIM_ITConfig(TIM5,TIM_IT_Update|TIM_IT_CC2,ENABLE);//��������ж� ,����CC1IE�����ж�	
	}
	else if(type==TIM5_3)
 	{
	//��ʼ����ʱ��5 TIM5	 
	TIM_TimeBaseStructure.TIM_Period = arr; //�趨�������Զ���װֵ 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 	//Ԥ��Ƶ��   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
  
	//��ʼ��TIM5���벶�����
	TIM5_ICInitStructure.TIM_Channel = TIM_Channel_3; //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
  	TIM5_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
  	TIM5_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
  	TIM5_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //���������Ƶ,����Ƶ 
  	TIM5_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 ���������˲��� ���˲�
  	TIM_ICInit(TIM5, &TIM5_ICInitStructure);
	TIM_ITConfig(TIM5,TIM_IT_Update|TIM_IT_CC3,ENABLE);//��������ж� ,����CC1IE�����ж�	
	}
	else if(type==TIM5_4)
 	{
	//��ʼ����ʱ��5 TIM5	 
	TIM_TimeBaseStructure.TIM_Period = arr; //�趨�������Զ���װֵ 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 	//Ԥ��Ƶ��   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
  
	//��ʼ��TIM5���벶�����
	TIM5_ICInitStructure.TIM_Channel = TIM_Channel_4; //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
  	TIM5_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
  	TIM5_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
  	TIM5_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //���������Ƶ,����Ƶ 
  	TIM5_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 ���������˲��� ���˲�
  	TIM_ICInit(TIM5, &TIM5_ICInitStructure);
	TIM_ITConfig(TIM5,TIM_IT_Update|TIM_IT_CC4,ENABLE);//��������ж� ,����CC1IE�����ж�	
	}

 	TIM_Cmd(TIM5,ENABLE ); 	//ʹ�ܶ�ʱ��5
   
}



u8  TIM5CH1_CAPTURE_STA=0;	//���벶��״̬		    				
u32	TIM5CH1_CAPTURE_VAL;	//���벶��ֵ

u8  TIM5CH2_CAPTURE_STA=0;	//���벶��״̬		    				
u32	TIM5CH2_CAPTURE_VAL;	//���벶��ֵ

u8  TIM5CH3_CAPTURE_STA=0;	//���벶��״̬		    				
u32	TIM5CH3_CAPTURE_VAL;	//���벶��ֵ

u8  TIM5CH4_CAPTURE_STA=0;	//���벶��״̬		    				
u32	TIM5CH4_CAPTURE_VAL;	//���벶��ֵ

 
//��ʱ��5�жϷ������	 
void TIM5_IRQHandler(void)
{ 

 	if((TIM5CH1_CAPTURE_STA&0X80)==0)//��δ�ɹ�����	
	{	  
		if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)
		 
		{	    
			if(TIM5CH1_CAPTURE_STA&0X40)//�Ѿ����񵽸ߵ�ƽ��
			{
				if((TIM5CH1_CAPTURE_STA&0X3F)==0X3F)//�ߵ�ƽ̫����
				{
					TIM5CH1_CAPTURE_STA|=0X80;//��ǳɹ�������һ��
					TIM5CH1_CAPTURE_VAL=0XFFFF;
				}else TIM5CH1_CAPTURE_STA++;
			}	 
		}

	if (TIM_GetITStatus(TIM5, TIM_IT_CC1) != RESET)//����1���������¼�
		{	
			if(TIM5CH1_CAPTURE_STA&0X40)		//����һ���½��� 		
			{	  			
				TIM5CH1_CAPTURE_STA|=0X80;		//��ǳɹ�����һ��������
				TIM5CH1_CAPTURE_VAL=TIM_GetCapture1(TIM5);
		   		TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Rising); //CC1P=0 ����Ϊ�����ز���
			}else  								//��δ��ʼ,��һ�β���������
			{
				TIM5CH1_CAPTURE_STA=0;			//���
				TIM5CH1_CAPTURE_VAL*=0;
	 			TIM_SetCounter(TIM5,0);
				TIM5CH1_CAPTURE_STA|=0X40;		//��ǲ�����������
		   		TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Falling);		//CC1P=1 ����Ϊ�½��ز���
			}		    
		}			     	    					   
 	} 

	if((TIM5CH2_CAPTURE_STA&0X80)==0)//��δ�ɹ�����	
	{	  
		if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)
		 
		{	    
			if(TIM5CH2_CAPTURE_STA&0X40)//�Ѿ����񵽸ߵ�ƽ��
			{
				if((TIM5CH2_CAPTURE_STA&0X3F)==0X3F)//�ߵ�ƽ̫����
				{
					TIM5CH2_CAPTURE_STA|=0X80;//��ǳɹ�������һ��
					TIM5CH2_CAPTURE_VAL=0XFFFF;
				}else TIM5CH2_CAPTURE_STA++;
			}	 
		}

	if (TIM_GetITStatus(TIM5, TIM_IT_CC2) != RESET)//����1���������¼�
		{	
			if(TIM5CH2_CAPTURE_STA&0X40)		//����һ���½��� 		
			{	  			
				TIM5CH2_CAPTURE_STA|=0X80;		//��ǳɹ�����һ��������
				TIM5CH2_CAPTURE_VAL=TIM_GetCapture2(TIM5);
		   		TIM_OC2PolarityConfig(TIM5,TIM_ICPolarity_Rising); //CC1P=0 ����Ϊ�����ز���
			}else  								//��δ��ʼ,��һ�β���������
			{
				TIM5CH2_CAPTURE_STA=0;			//���
				TIM5CH2_CAPTURE_VAL*=0;
	 			TIM_SetCounter(TIM5,0);
				TIM5CH2_CAPTURE_STA|=0X40;		//��ǲ�����������
		   		TIM_OC2PolarityConfig(TIM5,TIM_ICPolarity_Falling);		//CC1P=1 ����Ϊ�½��ز���
			}		    
		}			     	    					   
 	} 

	if((TIM5CH3_CAPTURE_STA&0X80)==0)//��δ�ɹ�����	
	{	  
		if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)
		 
		{	    
			if(TIM5CH3_CAPTURE_STA&0X40)//�Ѿ����񵽸ߵ�ƽ��
			{
				if((TIM5CH3_CAPTURE_STA&0X3F)==0X3F)//�ߵ�ƽ̫����
				{
					TIM5CH3_CAPTURE_STA|=0X80;//��ǳɹ�������һ��
					TIM5CH3_CAPTURE_VAL=0XFFFF;
				}else TIM5CH3_CAPTURE_STA++;
			}	 
		}

	if (TIM_GetITStatus(TIM5, TIM_IT_CC3) != RESET)//����1���������¼�
		{	
			if(TIM5CH3_CAPTURE_STA&0X40)		//����һ���½��� 		
			{	  			
				TIM5CH3_CAPTURE_STA|=0X80;		//��ǳɹ�����һ��������
				TIM5CH3_CAPTURE_VAL=TIM_GetCapture3(TIM5);
		   		TIM_OC3PolarityConfig(TIM5,TIM_ICPolarity_Rising); //CC1P=0 ����Ϊ�����ز���
			}else  								//��δ��ʼ,��һ�β���������
			{
				TIM5CH3_CAPTURE_STA=0;			//���
				TIM5CH3_CAPTURE_VAL*=0;
	 			TIM_SetCounter(TIM5,0);
				TIM5CH3_CAPTURE_STA|=0X40;		//��ǲ�����������
		   		TIM_OC3PolarityConfig(TIM5,TIM_ICPolarity_Falling);		//CC1P=1 ����Ϊ�½��ز���
			}		    
		}			     	    					   
 	} 

	if((TIM5CH4_CAPTURE_STA&0X80)==0)//��δ�ɹ�����	
	{	  
		if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)
		 
		{	    
			if(TIM5CH4_CAPTURE_STA&0X40)//�Ѿ����񵽸ߵ�ƽ��
			{
				if((TIM5CH4_CAPTURE_STA&0X3F)==0X3F)//�ߵ�ƽ̫����
				{
					TIM5CH4_CAPTURE_STA|=0X80;//��ǳɹ�������һ��
					TIM5CH4_CAPTURE_VAL=0XFFFF;
				}else TIM5CH4_CAPTURE_STA++;
			}	 
		}

	if (TIM_GetITStatus(TIM5, TIM_IT_CC4) != RESET)//����1���������¼�
		{	
			if(TIM5CH4_CAPTURE_STA&0X40)		//����һ���½��� 		
			{	  			
				TIM5CH4_CAPTURE_STA|=0X80;		//��ǳɹ�����һ��������
				TIM5CH4_CAPTURE_VAL=TIM_GetCapture4(TIM5);
		   		TIM_OC4PolarityConfig(TIM5,TIM_ICPolarity_Rising); //CC1P=0 ����Ϊ�����ز���
			}else  								//��δ��ʼ,��һ�β���������
			{
				TIM5CH4_CAPTURE_STA=0;			//���
				TIM5CH4_CAPTURE_VAL*=0;
	 			TIM_SetCounter(TIM5,0);
				TIM5CH4_CAPTURE_STA|=0X40;		//��ǲ�����������
		   		TIM_OC4PolarityConfig(TIM5,TIM_ICPolarity_Falling);		//CC1P=1 ����Ϊ�½��ز���
			}		    
		}			     	    					   
 	}
 
    TIM_ClearITPendingBit(TIM5, TIM_IT_CC1|TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4|TIM_IT_Update); //����жϱ�־λ

}


int Get_H_Pulse(COMPARE_type type)
{
int temp=0;
        switch(type)
		{
	 	    case(0):
			{
				if(TIM5CH1_CAPTURE_STA&0X80)//�ɹ�������һ��������
				{
					temp=TIM5CH1_CAPTURE_STA&0X3F;
					temp*=65536;//���ʱ���ܺ�
					temp+=TIM5CH1_CAPTURE_VAL;//�õ��ܵĸߵ�ƽʱ��
					//printf("HIGH:%d us\r\n",temp);//��ӡ�ܵĸߵ�ƽʱ��
					TIM5CH1_CAPTURE_STA=0;//������һ�β���
				}
				return temp;
			}
			 case(1):
			{
				if(TIM5CH2_CAPTURE_STA&0X80)//�ɹ�������һ��������
				{
					temp=TIM5CH2_CAPTURE_STA&0X3F;
					temp*=65536;//���ʱ���ܺ�
					temp+=TIM5CH2_CAPTURE_VAL;//�õ��ܵĸߵ�ƽʱ��
					//printf("HIGH:%d us\r\n",temp);//��ӡ�ܵĸߵ�ƽʱ��
					TIM5CH2_CAPTURE_STA=0;//������һ�β���
				}
				return temp;
			}
			 case(2):
			{
				if(TIM5CH3_CAPTURE_STA&0X80)//�ɹ�������һ��������
				{
					temp=TIM5CH3_CAPTURE_STA&0X3F;
					temp*=65536;//���ʱ���ܺ�
					temp+=TIM5CH3_CAPTURE_VAL;//�õ��ܵĸߵ�ƽʱ��
					//printf("HIGH:%d us\r\n",temp);//��ӡ�ܵĸߵ�ƽʱ��
					TIM5CH3_CAPTURE_STA=0;//������һ�β���
				}
				return temp;
			}
			 case(3):
			{
				if(TIM5CH4_CAPTURE_STA&0X80)//�ɹ�������һ��������
				{
					temp=TIM5CH4_CAPTURE_STA&0X3F;
					temp*=65536;//���ʱ���ܺ�
					temp+=TIM5CH4_CAPTURE_VAL;//�õ��ܵĸߵ�ƽʱ��
					//printf("HIGH:%d us\r\n",temp);//��ӡ�ܵĸߵ�ƽʱ��
					TIM5CH4_CAPTURE_STA=0;//������һ�β���
				}
				return temp;
			}
			
		}
	 return -1;
}

