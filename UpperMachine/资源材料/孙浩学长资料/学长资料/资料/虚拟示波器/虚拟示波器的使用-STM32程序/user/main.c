/************
  ����ʾ����ʹ�÷���
  ʹ��ǰ���ã�Ӧ��ѡ���ƽ�֮���VisualScope_Crack���򣬼�����ѡ��win95����98
  Ȼ����Setup->Communication protocol->CRC16���á�ͬʱ��Tools->Scom Assistant�е��
  Open���鿴�Ƿ������ݷ�������Ҫ���У���رպ������ٵ��
  ���ƣ������Ƚ����Ի���������ʾ��ǰ״ֵ̬�����Բ���Ҫ��ʱ����

***************/

#include"stm32f10x.h"
#include"delay.h"
#include"usart.h" /* printf����������������ڣ����Ա����������ļ� */
#include"ocsctl.h"
#include<stdio.h>  /* ��Ϊ�õ���printf���������Ա����������ļ� */
int main(void)
{
   SystemInit();
   delay_init(72);
   InitUart();
 	
   while(1)
   {
       OCS_displayData(10.0,100.0,255.0,1000.9);
	   delay_us(1);								
   }
  
}
