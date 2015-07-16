#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usmart.h" 
#include "lcd.h"
#include "usart.h"
#include "24l01.h" 	 
#include "malloc.h"
#include "sdio_sdcard.h"  
#include "w25qxx.h"    
#include "ff.h"  
#include "exfuns.h"   
#include "text.h"
#include "mytask.h"

/************************************************
 ALIENTEKս��STM32������ʵ��33
 ����ͨ�� ʵ��
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/


//���˵�
void MUSE_TASK()
{
	u8 t=0;
	LCD_Clear(WHITE);
	Show_Str(20,30,200,24,"���˵�:",24,0);
	Show_Str(20,60,200,24,"����1:",24,0);
	Show_Str(20,90,200,24,"����2:",24,0);
	Show_Str(20,120,200,24,"����3:",24,0);
	Show_Str(20,150,200,24,"����4:",24,0);
	Show_Str(20,180,200,24,"����5:",24,0);
	Show_Str(20,210,200,24,"����6:",24,0);
	Show_Str(20,240,200,24,"����7:",24,0);
	Show_Str(20,270,200,24,"����8:",24,0);
	
	t++;
	if(t==100)
		//LCD_ShowString(10,150,230,16,16,"KEY0:RX_Mode  KEY1:TX_Mode"); //��˸��ʾ��ʾ��Ϣ
		Show_Str(10,150,230,24,"�������ѡ��",24,0);
	if(t==200)
	{	
		LCD_Fill(10,150,240,150+50,WHITE);
		t=0; 
	}
	delay_ms(5);
}


//����0
// ���ȷ������ݣ�Ȼ���������
void KEY0_TASK()
{
	u8 key,mode;
	u8 time ; //���㷢�ʹ���
	u16 t=0;			 
	u8 tmp_buf[33];	
	
	u8 key_buf[33] = "key0_pres";
	
	
	LCD_Clear(WHITE);
	Show_Str(50,50,200,24,"��ǰ����0 :",24,0);

	NRF24L01_TX_Mode();
	mode=' ';//�ӿո����ʼ  
	
	//�������� key0_pres
	while(NRF24L01_TxPacket(tmp_buf)==TX_OK && time != 3)
	{
		time ++;
		LCD_ShowString(30,170,239,32,16,"Sended DATA:");	
		LCD_ShowString(0,190,lcddev.width-1,32,16,tmp_buf); 
		for(t=0;t<32;t++)
		{
			
			tmp_buf[t]=key_buf[t];	
		}	  
		tmp_buf[32]=0;//���������		   
	}
	time = 0;

	//LED0=!LED0;
	//delay_ms(1500);		
	
	//Ȼ��������� ��ȡһ�ΰ���������������Ϣ
	NRF24L01_RX_Mode();		  
	while(1)
	{	 
		Show_Str(50,70,200,24,"biaozhiwei :",24,0);
		if(t%2==0)
		{
			if(NRF24L01_RxPacket(tmp_buf)==0)//һ�����յ���Ϣ,����ʾ����.
			{
				tmp_buf[32]=0;//�����ַ���������
				LCD_ShowString(0,190,lcddev.width-1,32,16,tmp_buf);    
			}
			else
				delay_us(100);	
		}
		if(t%4==0)
		{
			t=0;
			key=KEY_Scan(0);
			if(key==WKUP_PRES)
			{
				Show_Str(50,100,200,24,"��ǰ���� :",24,0);
				break;
			}
		}
		t++;    
	}	
	
}




//����1
void KEY1_TASK()
{
	u8 key,mode;
	u16 t=0;			 
	u8 tmp_buf[33];	
	
	u8 key_buf[33] = "key1_pres";
	
	
	LCD_Clear(WHITE);
	Show_Str(50,50,200,24,"��ǰ����1 :",24,0);

	NRF24L01_TX_Mode();
	mode=' ';//�ӿո����ʼ  
	
	while(NRF24L01_TxPacket(tmp_buf)==TX_OK)
	{
		LCD_ShowString(30,170,239,32,16,"Sended DATA:");	
		LCD_ShowString(0,190,lcddev.width-1,32,16,tmp_buf); 
		for(t=0;t<32;t++)
		{
			
			tmp_buf[t]=key_buf[t];	
		}	  
		tmp_buf[32]=0;//���������		   
	}

//	LED0=!LED0;
//	delay_ms(1500);
	NRF24L01_RX_Mode();		  
	while(1)
	{	 
		if(t%2==0)
		{
			if(NRF24L01_RxPacket(tmp_buf)==0)//һ�����յ���Ϣ,����ʾ����.
			{
				tmp_buf[32]=0;//�����ַ���������
				LCD_ShowString(0,190,lcddev.width-1,32,16,tmp_buf);    
			}
			else
				delay_us(100);	
		}
		else if(t%4==0)
		{
			t=0;
			key=KEY_Scan(0);
			if(key==WKUP_PRES)
			{
				break;
			}
		}
		t++;    
	}		
}





//����2
void KEY2_TASK()
{
	LCD_Clear(WHITE);
	Show_Str(20,50,200,24,"��ǰ����2",24,0);
}

//����3
void KEY3_TASK()
{
	LCD_Clear(WHITE);
	Show_Str(20,50,200,24,"��ǰ����3:",24,0);
}

//����4
void KEY4_TASK()
{
	LCD_Clear(WHITE);
	Show_Str(20,50,200,24,"��ǰ����4:",24,0);
}

//����5
void KEY5_TASK()
{
	LCD_Clear(WHITE);
	Show_Str(20,50,200,24,"��ǰ����5:",24,0);
}

//����6
void KEY6_TASK()
{
	LCD_Clear(WHITE);
	Show_Str(20,50,200,24,"��ǰ����6:",24,0);
}

//����7
void KEY7_TASK()
{
	LCD_Clear(WHITE);
	Show_Str(20,50,200,24,"��ǰ����7:",24,0);
}

//����8
void KEY8_TASK()
{
	LCD_Clear(WHITE);
	Show_Str(20,50,200,24,"��ǰ����8",24,0);
}