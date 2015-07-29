#include "led.h"
#include "rtc.h"
#include "Encoder.h"
#include "Control.h"
#include "delay.h"
#include "Motor.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"	 
#include "24l01.h"
#include "mytask.h"
#include "UltrasonicWave.h"
#include "timer4_cap.h"
#include "TimeBase.h"
#include "usmart.h"
 
 
/************************************************
 ALIENTEKս��STM32������ʵ��33
 ����ͨ�� ʵ��
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/
void led_set(u8 sta)
{
	LED1 = sta;
	LED0 = sta;
}

void test_fun(void(*ledset)(u8),u8 sta)
{
	ledset(sta);
} 

 int main(void)
 {	 
	//ȫ�ֱ���
	double mm,ff;
	u8 key,x;
	 u8 i=0;
	u16 time = 350;
	u8 mode;
	 u8 state;
	u16 t=0;			 
	u8 tmp_buf[33];		    
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200   
 	LED_Init();		  			//��ʼ����LED���ӵ�Ӳ���ӿ�
	KEY_Init();					//��ʼ����
	RTC_Init();
//	usmart_dev.init(72);		//��ʼ��USMART
//	TIM_PWM_Init();
	 MotorInit();
	//ENC_Init();
	 Encoder_Init();
//	UltrasonicWave_Configuration();
//	TIM4_Cap_Init(65535,72-1); //��1Mhz��Ƶ�ʼ���  1/1M = 1/1,000,000   f 72M/72 = 1M  ,T  1us  ������65536
	LCD_Init();			   		//��ʼ��LCD  
 	NRF24L01_Init();    		//��ʼ��NRF24L01 
 	POINT_COLOR=RED;			//��������Ϊ��ɫ 
	TB_Init(10-1,719);
	LCD_ShowString(30,50,200,16,16,"WarShip STM32");	
	LCD_ShowString(30,70,200,16,16,"NRF24L01 TEST");	
	LCD_ShowString(30,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(30,110,200,16,16,"2015/1/17"); 

	//����ͨ��ģ��ļ��
//	while(NRF24L01_Check())
//	{
//		LCD_ShowString(30,130,200,16,16,"NRF24L01 Error");
//		delay_ms(200);
//		LCD_Fill(30,130,239,130+16,WHITE);
// 		delay_ms(200);
//	}
//	LCD_ShowString(30,130,200,16,16,"NRF24L01 OK");
	

	while(1) //������
	{
		if(TB_SetLed_IsElapsed() == true)
		{
//			LED1 = ~LED1;
//			LED0 = ~LED0;
			if(LED1 == 0)
			{
				LED1 = 1;
				LED0 = 0;
			}
			else 
			{
				LED1 = 0;
				LED0 = 1;
			}
			TB_SetLed_Time(LED_DELAY);
		}
		
//		LED0 = ~LED0;
//		LED1 = ~LED1;
//		delay_ms(1000);
	}	
}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
//	������
// 	while(1)
//	{	
//		key=KEY_Scan(0);
//		
//		if(key==KEY0_PRES)
//		{
//			mode=0;   
//			break;
//		}
//		else if(key==KEY1_PRES)
//		{
//			mode=1;
//			break;
//		}
//		t++;
//		if(t==100)LCD_ShowString(10,150,230,16,16,"KEY0:RX_Mode  KEY1:TX_Mode"); //��˸��ʾ��ʾ��Ϣ
// 		if(t==200)
//		{	
//			LCD_Fill(10,150,230,150+16,WHITE);
//			t=0; 
//		}
//		delay_ms(5);	  
//	}   
// 	LCD_Fill(10,150,240,166,WHITE);//����������ʾ		  
// 	POINT_COLOR=BLUE;//��������Ϊ��ɫ	   
//	if(mode==0)//RXģʽ
//	{
//		LCD_ShowString(30,150,200,16,16,"NRF24L01 RX_Mode");	
//		LCD_ShowString(30,170,200,16,16,"Received DATA:");	
//		NRF24L01_RX_Mode();		  
//		while(1)
//		{	  		    		    				 
//			if(NRF24L01_RxPacket(tmp_buf)==0)//һ�����յ���Ϣ,����ʾ����.
//			{
//				tmp_buf[32]=0;//�����ַ���������
//				LCD_ShowString(0,190,lcddev.width-1,32,16,tmp_buf);    
//			}else delay_us(100);	   
//			t++;
//			if(t==10000)//��Լ1s�Ӹı�һ��״̬
//			{
//				t=0;
//				LED0=!LED0;
//			} 				    
//		};	
//	}
//	else//TXģʽ
//	{							    
//		LCD_ShowString(30,150,200,16,16,"NRF24L01 TX_Mode");	
//		NRF24L01_TX_Mode();
//		mode=' ';//�ӿո����ʼ  
//		while(1)
//		{	  		   				 
//			if(NRF24L01_TxPacket(tmp_buf)==TX_OK)
//			{
//				LCD_ShowString(30,170,239,32,16,"Sended DATA:");	
//				LCD_ShowString(0,190,lcddev.width-1,32,16,tmp_buf); 
//				key=mode;
//				for(t=0;t<32;t++)
//				{
//					key++;
//					if(key>('~'))key=' ';
//					tmp_buf[t]=key;	
//				}
//				mode++; 
//				if(mode>'~')mode=' ';  	  
//				tmp_buf[32]=0;//���������		   
//			}else
//			{										   	
// 				LCD_Fill(0,170,lcddev.width,170+16*3,WHITE);//�����ʾ			   
//				LCD_ShowString(30,170,lcddev.width-1,32,16,"Send Failed "); 
//			};
//			LED0=!LED0;
//			delay_ms(1500);				    
//		};
//	} 
