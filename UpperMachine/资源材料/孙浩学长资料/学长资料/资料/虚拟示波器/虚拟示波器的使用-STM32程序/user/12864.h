#ifndef __12864_H
#define __12864_H
 /***********************************************/
 /**********12864的串行工作方式
     接口说明：E(SCLK)接(GPIOE, GPIO_Pin_2)
	           R/W(SID)接(GPIOE, GPIO_Pin_3)
			   PSB接低电平
			   RS接高电平
			   因此只要2根数据线就行进行数据传输
			   　     ***************/ 
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
void lcd_clear(void);        //清除显示
void lcd_pos(unsigned char y_add , unsigned char x_add);
void lcd_wstr(unsigned char y_add , unsigned char x_add , unsigned char *str) ;
void write_figer(unsigned char y_add , unsigned char x_add , unsigned int figer);//在任何位置写数字
void lcd_init(void);     //
unsigned char get_byte(void); 

 
#endif 
