// TB6560�Ĵ���: 

#include "sys.h"  
#include "usart.h" 
#include "delay.h"
#include "tb6560.h"

/*
��ע:
1.�����ŷ����
2.42�������
3.57�������
*/


//���������ת���ٽǶ� 
//stepx:����������,0/1; 
//deg:�Ƕ� 
//lr :��ת������ת 
#define DRVDEV    8   //��������ϸ���� 
#define STEPDEG   1.8 //��������Ĳ��� 

void Step_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;

	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//100MHz

	GPIO_Init(GPIOG, &GPIO_InitStructure);//	
}

void Step_Run(float deg,u8 lr,int delay) 
{    
	float clkf; 
	u16 nclk;    
	clkf=(deg*DRVDEV)/STEPDEG; //  (�Ƕ�*ϸ����)/��������Ĳ���
	nclk=clkf;//ȡ�������� 
 
	STEP_DIR=lr; 
	
	//��ʱʱ���ϸ�����й�
	if(delay == 0)
		delay = 800/DRVDEV;
	else if(delay == 1)
		delay = 800;
	else if(delay == 2)
		delay = 400;
 
	while(nclk--) 
	{ 
//		STEP_CLK=0; //����һ������,Ƶ��5Khz 
//		delay_us(400); 
//		STEP_CLK=1; 
//		delay_us(400);	
		
		//�������벽����
		STEP_CLK=0; //����һ������,Ƶ��5Khz 
		delay_us(delay); 
		STEP_CLK=1; 
		delay_us(delay);	
	} 

} 
//���������ת���ٸ�1.8�� 

//dx:1.8�ȵĸ���  --���ٸ�1.8��
//lr :0:��ת��1:��ת
void Step_Run_18(u16 dx,u8 lr) 
{    
	Step_Run(dx*1.8,lr,0);          
}


//���������ת
//dx:1.8�ȵĸ���
void Step_Run_Left(u16 dx)
{
	Step_Run_18(dx,0); 
}

//���������ת
//dx:1.8�ȵĸ���
void Step_Run_Right(u16 dx)
{
	Step_Run_18(dx,1); 
}

