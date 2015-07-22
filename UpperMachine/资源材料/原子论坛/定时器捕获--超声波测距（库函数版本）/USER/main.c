#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"
#include "UltrasonicWave.h"
#include "timer4_cap.h"


//������������ӿƼ����޹�˾ 
 	
 int main(void)
 {	 
 	u8 x=0;
	u8 lcd_id[12];			//���LCD ID�ַ���
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(9600);	 	//���ڳ�ʼ��Ϊ9600
 	LED_Init();			     //LED�˿ڳ�ʼ��
	TIM4_Cap_Init(0xffff,72-1); //��1Mhz��Ƶ�ʼ���
	
	
	UltrasonicWave_Configuration();    //�Գ�����ģ���ʼ��
	 
	 LCD_Init();
	POINT_COLOR=RED;
	sprintf((char*)lcd_id,"LCD ID:%04X",lcddev.id);//��LCD ID��ӡ��lcd_id���顣				 	
  
	 POINT_COLOR=RED;	  
		LCD_ShowString(30,50,200,16,16,"WarShip STM32 ^_^");	
		LCD_ShowString(30,70,200,16,16,"TFTLCD TEST");	

 		LCD_ShowString(30,110,200,16,16,lcd_id);		//��ʾLCD ID	      					 
		LCD_ShowString(30,130,200,16,16,"2014/10/5");	  
	
	while(1) 
	{		 
		UltrasonicWave_StartMeasure(); 
		//LED2_TOGGLE;
		LCD_ShowxNum(60,190,tempup1,3,16,0X80);	//��ʾ����
		printf("Channel 1 : %d cm\r\n",tempup1);
//		delay_ms(10);
//		printf("Channel 2 : %d cm\r\n",tempup2);
//		delay_ms(10);
//		printf("Channel 3 : %d cm\r\n",tempup3);
//		delay_ms(10);
//		printf("Channel 4 : %d cm\r\n",tempup4);
		    					 
	    x++;
		if(x==12)x=0;
		LED0=!LED0;					 
	//	delay_ms(1000);	
	} 
}
