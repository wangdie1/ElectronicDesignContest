#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usmart.h" 
#include "lcd.h"
#include "usart.h"
#include "mytask.h"
//#include "voice.h"
#include "timer.h"
#include "24l01.h" 	 

#include "malloc.h"
#include "sdio_sdcard.h"  
#include "w25qxx.h"    
#include "ff.h"  
#include "exfuns.h"   
#include "text.h"

 
 
/************************************************
 ALIENTEKս��STM32������ʵ��33
 ����ͨ�� ʵ��
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/

	char tmp_buf[32];
 int main(void)
 {	 
	//����ȫ�ֱ���
	u8 key;
	u16 t=0;	
	u8 i=1;

	//������ʼ��
//	Voice_Init();
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
 	usmart_dev.init(72);		//��ʼ��USMART	
	LED_Init();		  			//��ʼ����LED���ӵ�Ӳ���ӿ�
	KEY_Init();					//��ʼ������
	TIM7_Int_Init(200,7199);	//100us*200 = 20ms
	NRF24L01_Init();    		//��ʼ��NRF24L01 
	
	W25QXX_Init();				//��ʼ��W25Q128
	my_mem_init(SRAMIN);		//��ʼ���ڲ��ڴ��
	LCD_Init();			   		//��ʼ��LCD 
	exfuns_init();				//Ϊfatfs��ر��������ڴ�  
 	f_mount(fs[0],"0:",1); 		//����SD�� 
 	f_mount(fs[1],"1:",1); 		//����FLASH.	 
 
	//��������ֿ�
	while(font_init()) 			//����ֿ�
	{
		LCD_Clear(WHITE);		   	//����
 		POINT_COLOR=RED;			//��������Ϊ��ɫ	   	   	  
		LCD_ShowString(30,50,200,16,16,"WarShip STM32");
		while(SD_Init())			//���SD��
		{
			LCD_ShowString(30,70,200,16,16,"SD Card Failed!");
			delay_ms(200);
			LCD_Fill(30,70,200+30,70+16,WHITE);
			delay_ms(200);		    
		}								 						    
		LCD_ShowString(30,70,200,16,16,"SD Card OK");
		LCD_ShowString(30,90,200,16,16,"Font Updating...");
		key=update_font(20,110,16,"0:");//�����ֿ�
		while(key)//����ʧ��		
		{			 		  
			LCD_ShowString(30,110,200,16,16,"Font Update Failed!");
			delay_ms(200);
			LCD_Fill(20,110,200+20,110+16,WHITE);
			delay_ms(200);		       
		} 		  
		LCD_ShowString(30,110,200,16,16,"Font Update Success!   ");
		delay_ms(1500);	
		LCD_Clear(WHITE);//����	       
	}  
	
	//�������ͨ��
	while(NRF24L01_Check())
	{
		LCD_ShowString(30,130,200,16,16,"NRF24L01 Error");
		delay_ms(200);
		LCD_Fill(30,130,239,130+16,WHITE);
 		delay_ms(200);
	}

	//��ʼ������
	POINT_COLOR = MAGENTA; 
	Show_Str(20,20,200,24,"��ʮһ��ȫ������",24,0);
	Show_Str(80,50,200,24,"��ƴ���",24,0);	
	
	POINT_COLOR = BLUE;
	Show_Str(60,80,200,24,"�������ѧԺ",24,0);				    	 				    	 
	Show_Str(30,130,200,24,"������Ŀ����:",24,0);
	Show_Str(45,160,200,24,"��ת������",24,0);
	
	Show_Str(30,210,200,24,"������:��۳�",24,0);
	Show_Str(45,240,200,24,"������,�Ž�",24,0);
	
 	while(1)
	{

			
		
//		key=KEY_Scan(0);
//		if(key!=0)
//		{
//			set_Voice_by_one(i++);
//		}
//		printf("%d",i);
//		delay_ms(100);
		
//		delay_ms(10000);
//		set_Voice(3);
//		delay_ms(10000);
//		key=1;
//		//����ɨ��
//		key=KEY_Scan(0);
//		
//		if(key!=0)
//		{
//			set_Voice(i++);
//		}
//		
//		if(key!=0)
//		{
//			LCD_Clear(WHITE);
//			Show_Str(20,30,200,24,"���˵�:",24,0);
//			Show_Str(20,60,200,24,"����1:",24,0);
//			Show_Str(20,90,200,24,"����2:",24,0);
//			Show_Str(20,120,200,24,"����3:",24,0);
//			Show_Str(20,150,200,24,"����4:",24,0);
//			Show_Str(20,180,200,24,"����5:",24,0);
//			Show_Str(20,210,200,24,"����6:",24,0);
//			Show_Str(20,240,200,24,"����7:",24,0);
//			Show_Str(20,270,200,24,"����8:",24,0);
//			
//			while(1)
//			{
//				u8 a = 10;
//				
//				key=0;
//				key=KEY_Scan(0);
//				//WKUP_PRES  ����:����������
//				if(key==WKUP_PRES)
//				{
////					MUSE_TASK();
					
//				}
//				
//				//KEY1_PRES ����:ִ������1
//				else if(key==KEY0_PRES)
//				{
//					KEY0_TASK();
//				}
//				//KEY1_PRES ����:ִ������1
//				else if(key==KEY1_PRES)
//				{
//					KEY1_TASK();
//				}
//				//KEY2_PRES ����:ִ������2
//				else if(key==KEY2_PRES)
//				{
//					KEY2_TASK();
//				}
//				//KEY3_PRES ����:ִ������3
//				else if(key==KEY3_PRES)
//				{
//					KEY3_TASK();
//				}
//				//KEY4_PRES ����:ִ������4
//				else if(key==KEY4_PRES)
//				{
//					KEY4_TASK();
//				}
//				//KEY5_PRES ����:ִ������5
//				else if(key==KEY5_PRES)
//				{
//					KEY5_TASK();
//				}
//				//KEY6_PRES ����:ִ������6
//				else if(key==KEY6_PRES)
//				{
//					KEY6_TASK();
//				}
//				//KEY7_PRES ����:ִ������7
//				else if(key==KEY7_PRES)
//				{
//					KEY7_TASK();
//				}
//				//KEY8_PRES ����:ִ������8
////				else if(key==KEY8_PRES)
////				{
////					KEY8_TASK();
////				}
				
//			}
//		}

//		
//		t++;
//		if(t==100)
//			Show_Str(10,270,230,24,"��������������˵�",24,0);
// 		if(t==200)
//		{	
//			LCD_Fill(10,270,230,300,WHITE);
//			t=0; 
//		}
//		delay_ms(5);
	} 
}	
   	
//	if(mode==3)//RXģʽ
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



