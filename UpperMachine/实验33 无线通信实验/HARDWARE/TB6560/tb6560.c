// TB6560�Ĵ���: 

#include "sys.h"  
#include "usart.h" 
#include "delay.h"
#include "tb6560.h"


//���������ת���ٽǶ� 
//stepx:����������,0/1; 
//deg:�Ƕ� 
//lr :��ת������ת 
#define DRVDEV    8   //��������ϸ���� 
#define STEPDEG   1.8 //��������Ĳ��� 

void Step_Init(void)
{
 
	GPIO_InitTypeDef  GPIO_InitStructure;

	//RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);//
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//
	//GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;//100MHz
	//GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//
	GPIO_Init(GPIOG, &GPIO_InitStructure);//
	
}

void Step_Run(float deg,u8 lr) 
{    
	float clkf; 
	u16 nclk;    
	clkf=(deg*DRVDEV)/STEPDEG; //  (�Ƕ�*ϸ����)/��������Ĳ���
	nclk=clkf;//ȡ�������� 
 
	STEP_DIR=lr; 
 
	while(nclk--) 
	{ 
//		STEP_CLK=0; //����һ������,Ƶ��5Khz 
//		delay_us(400); 
//		STEP_CLK=1; 
//		delay_us(400);	
		
		//�������벽����
		STEP_CLK=0; //����һ������,Ƶ��5Khz 
		delay_us(800); 
		STEP_CLK=1; 
		delay_us(800);	
	} 

} 
//���������ת���ٸ�1.8�� 

//dx:1.8�ȵĸ���  --���ٸ�1.8��
//lr :0:��ת��1:��ת
void Step_Run_18(u16 dx,u8 lr) 
{    
	Step_Run(dx*1.8,lr);          
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


 
 
