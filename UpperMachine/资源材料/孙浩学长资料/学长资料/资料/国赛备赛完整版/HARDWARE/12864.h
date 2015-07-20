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
 void delay12864(unsigned int n);//延时函数
 void lcd_send_byte(unsigned char a);//向LCD送一个字节
 unsigned char lcd_read_byte(void);	//从LCD读一个字节
 unsigned char lcd_bf(void);			//忙标志检测
 void lcd_cmd(unsigned char comm);	//写命令
 void lcd_dat(unsigned char lcd_data);//写数据
 void lcd_pos(unsigned char x,unsigned char y);//设置显示位置
 void lcd_portinit(void);			//端口初始化
 void lcd_init(void);//液晶初始化
 void lcd_write_string(unsigned char *ch);
 void photodisplay(unsigned char *bmp);	  


#endif
