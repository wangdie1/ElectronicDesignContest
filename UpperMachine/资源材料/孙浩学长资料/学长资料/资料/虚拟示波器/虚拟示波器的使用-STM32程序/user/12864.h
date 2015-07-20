#ifndef __12864_H
#define __12864_H
 /***********************************************/
 /**********12864�Ĵ��й�����ʽ
     �ӿ�˵����E(SCLK)��(GPIOE, GPIO_Pin_2)
	           R/W(SID)��(GPIOE, GPIO_Pin_3)
			   PSB�ӵ͵�ƽ
			   RS�Ӹߵ�ƽ
			   ���ֻҪ2�������߾��н������ݴ���
			   ��     ***************/ 
 /***********************************************/
#include "stm32f10x.h"
#include "delay.h"

#define CLK_1 GPIO_SetBits(GPIOE, GPIO_Pin_2);  
#define CLK_0 GPIO_ResetBits(GPIOE, GPIO_Pin_2); 

#define SID_1 GPIO_SetBits(GPIOE, GPIO_Pin_3);  
#define SID_0 GPIO_ResetBits(GPIOE, GPIO_Pin_3);  


void check_busy(void);
void send_cmd(unsigned char cmd);
void write_char(unsigned char dat);
void lcd_clear(void);        //�����ʾ
void lcd_pos(unsigned char y_add , unsigned char x_add);
void lcd_wstr(unsigned char y_add , unsigned char x_add , unsigned char *str) ;
void write_figer(unsigned char y_add , unsigned char x_add , unsigned int figer);//���κ�λ��д����
void lcd_init(void);     //
unsigned char get_byte(void); 

 
#endif 
