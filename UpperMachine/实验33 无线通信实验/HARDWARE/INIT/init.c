#include "init.h"

//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//������ʼ������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/2
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////// 






void Init(void)
{	    
	//�������ܳ�ʼ��
	delay_init();	    	 							//��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);		//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 								//���ڳ�ʼ��Ϊ115200   
 	LED_Init();		  									//��ʼ����LED���ӵ�Ӳ���ӿ�
	KEY_Init();											//������ʼ��
	RTC_Init();		//�ڲ�ʱ�ӳ�ʼ��
	BEEP_Init();
//	LCD_Init();											//��ʼ��LCD 
	TB_Init(10-1,719); 									//����Ƶ�ʳ�ʼ��
	
	
	usmart_dev.init(72);		//��ʼ��USMART
	MPU_Init();					//��ʼ��MPU6050
	
	/*��չ���ܳ�ʼ
	
	*/
	//1.USMART��ʼ��
//	usmart_dev.init(72);		//��ʼ��USMART

	
	//2.���ģ���ʼ��
//	MotorInit();
//	 Encoder_Init();
//	 Encoder1_Init();
//	 TIM_PWM_Init();
	
	//3.������ģ���ʼ��
//	UltrasonicWave_Configuration();
//	TIM4_Cap_Init(65535,72-1); 							 //��1Mhz��Ƶ�ʼ���  1/1M = 1/1,000,000   f 72M/72 = 1M  ,T  1us  ������65536
				   		 
 	
	//4.����ģ���ʼ��
//	NRF24L01_Init();    		//��ʼ��NRF24L01 

	//5.mpu6050ģ��
//	u8 MPU_Init(void); 

	//6.������λ��ģ��
	
	//������մ�����
//	Remote_Init();	
}
