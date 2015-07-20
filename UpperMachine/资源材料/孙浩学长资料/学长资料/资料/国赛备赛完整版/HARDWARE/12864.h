#ifndef _12864_H
#define _12864_H

#define cs(x)  x?GPIO_SetBits(GPIOC,GPIO_Pin_0):GPIO_ResetBits(GPIOC,GPIO_Pin_0)
#define si(x)  x?GPIO_SetBits(GPIOC,GPIO_Pin_1):GPIO_ResetBits(GPIOC,GPIO_Pin_1)
#define sck(x) x?GPIO_SetBits(GPIOC,GPIO_Pin_2):GPIO_ResetBits(GPIOC,GPIO_Pin_2)

#define SENDCOMM 0xF8     //0x1111 1000 
#define READCOMM 0xFC     //0x1111 1100
#define SENDDATA 0xFA     //0x1111 1010
#define READDATA 0xFE     //0x1111 11

 
 void gpio_12864_init(void);
 void delay12864(unsigned int n);//��ʱ����
 void lcd_send_byte(unsigned char a);//��LCD��һ���ֽ�
 unsigned char lcd_read_byte(void);	//��LCD��һ���ֽ�
 unsigned char lcd_bf(void);			//æ��־���
 void lcd_cmd(unsigned char comm);	//д����
 void lcd_dat(unsigned char lcd_data);//д����
 void lcd_pos(unsigned char x,unsigned char y);//������ʾλ��
 void lcd_portinit(void);			//�˿ڳ�ʼ��
 void lcd_init(void);//Һ����ʼ��
 void lcd_write_string(unsigned char *ch);
 void photodisplay(unsigned char *bmp);	  


#endif
