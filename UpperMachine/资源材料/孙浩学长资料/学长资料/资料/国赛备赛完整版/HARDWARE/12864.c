#include <stm32f10x.h>
#include"12864.h"
#include"delay.h" 
void gpio_12864_init()
{
  GPIO_InitTypeDef GPIO_InitStruct;

  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC,ENABLE);

  GPIO_InitStruct. GPIO_Pin=GPIO_Pin_0|GPIO_Pin_2;
  GPIO_InitStruct. GPIO_Speed=GPIO_Speed_50MHz;
  GPIO_InitStruct. GPIO_Mode=GPIO_Mode_Out_PP;
  GPIO_Init( GPIOC, & GPIO_InitStruct);

  GPIO_InitStruct. GPIO_Pin=GPIO_Pin_1;
  GPIO_InitStruct. GPIO_Speed=GPIO_Speed_50MHz;
  GPIO_InitStruct. GPIO_Mode=GPIO_Mode_Out_PP;

  GPIO_Init( GPIOC, & GPIO_InitStruct);



}
/*******************************************************************/
//         端口初始化
/*******************************************************************/
void lcd_portinit(void)
{
	sck(0);
	cs(0);
	
}

/*******************************************************************/
//         写一个字节
/*******************************************************************/
void lcd_send_byte(unsigned char a)
{
	unsigned char i;
	for(i=8;i>0;i--)
	{  
	   sck(0);
	   if(a&(0x01<<(i-1)))
	   si(1);
	   else
	   si(0);			  
	   delay_us(100);
	   sck(1);
	   delay_us(100);
	   sck(0);
	   delay_us(100);
	} 
}

/*******************************************************************/
//         读一个字节
/*******************************************************************/
unsigned char lcd_read_byte(void)
{
	unsigned char i,dat=0;
	for(i=8;i>0;i--)
	{
	   sck(0);
	   delay_us(100);
	   sck(1);
	   //delay_us(100);
	   if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1)) 
	   dat|=(0x01<<(i-1));
	   delay_us(100);
	   sck(0);
	   delay_us(100);
	} 
	return dat;
}
/*******************************************************************/
//         忙标志检测
/*******************************************************************/
unsigned char lcd_bf(void)
{
	unsigned char readh,readl,BF;
	cs(1);
	delay_us(100);
	
	lcd_send_byte(0xfc);
	
	readh=lcd_read_byte();
	
	readl=lcd_read_byte();
	
	delay_us(100);
	cs(0);
	
	readl=(readl>>4);
	BF=(readh&0xf0)|(readl&0x0f);
	return BF;//BF=0x80，则状态为忙
}

/*******************************************************************/
//         写命令
/*******************************************************************/
void lcd_cmd(unsigned char comm)
{
	unsigned char temp;
	cs(1);
//	delay_us(100);
//	do{
//	   temp=lcd_bf();
//	}while(temp&0x80);
	delay_us(100);
	
	lcd_send_byte(SENDCOMM);
	
	temp=comm&0xF0;
	lcd_send_byte(temp);
	
	temp=((comm&0x0F)<<4)&0xF0;
	lcd_send_byte(temp);
	
	delay_us(100);
	cs(0);
}

/*******************************************************************/
//         写数据
/*******************************************************************/
void lcd_dat(unsigned char lcd_data)
{
	unsigned char temp;
	cs(1);
	delay_us(100);
	lcd_send_byte(SENDDATA);
	
	temp=lcd_data&0xf0;
	lcd_send_byte(temp);
	
	temp=(lcd_data&0x0F)<<4;
	lcd_send_byte(temp);
	
	delay_us(100);
	cs(0);
}
/*******************************************************************/
//          设置显示位置    X(1~16),Y(1~4)
/*******************************************************************/
void lcd_pos(unsigned char x,unsigned char y)
{
                          
   u8  pos;
   if (x==1)
     {x=0x80;}
   else if (x==2)
     {x=0x90;}
   else if (x==3)
     {x=0x88;}
   else if (x==4)
     {x=0x98;}
   pos = x+y ; 
 
   lcd_cmd(pos);     
}




void lcd_init(void)
{
    unsigned char i;
	lcd_portinit();
    gpio_12864_init();
	i=lcd_bf();

	while(i==0x80)
	{
	   delay_us(100);
	   i=lcd_bf();
	}  
	cs(1);
	delay_us(5000);
	lcd_cmd(0x30);//0011 0000 功能设置，一次送8位数据，基本指令集
	delay_us(1000);
	lcd_cmd(0x0C);//0000 1100 整体显示，游标off，游标位置off
	delay_us(1000);
	lcd_cmd(0x01);//0000 0001 清DDRAM
	delay_us(5000);
	lcd_cmd(0x02);//0000 0010 DDRAM地址归位
	delay_us(1000);
	lcd_cmd(0x80);//1000 0000 设定DDRAM 7位地址000，0000到地址计数器AC
	delay_us(100);
}

 void lcd_write_string(u8 *ch)
 {
 
    while(*ch!='\0')
    {
	lcd_dat(*ch);
	ch++;

    }
 
 }
/*********************************************************
*                                                        *
* 图形显示                                               *
*                                                        *
*********************************************************/
void photodisplay(unsigned char *bmp)	
{ 
  unsigned char i,j;

  lcd_cmd(0x34);        //写数据时,关闭图形显示

  for(i=0;i<32;i++)
  {
    lcd_cmd(0x80+i);    //先写入水平坐标值
    lcd_cmd(0x80);      //写入垂直坐标值
    for(j=0;j<16;j++)   //再写入两个8位元的数据    
    lcd_dat(*bmp++);     
    delay_us(100);
  }

  for(i=0;i<32;i++)
  { 
    lcd_cmd(0x80+i);
    lcd_cmd(0x88);
    for(j=0;j<16;j++)         
	lcd_dat(*bmp++);    
	delay_us(100);
  }
  lcd_cmd(0x36);       //写完数据,开图形显示 
}


//#include"12864_table.h"
// //unsigned char display[8]="12864";
/*12864显示*/
//int main()
//{

//printf("Rec_Dat_U1 is %d",Rec_Dat_U1);
//	delay_ms(50);
//	lcd_init();
//	delay_ms(50);
//	lcd_pos(1,0);
//	lcd_write_string(display);
//	delay_ms(5000);
//	lcd_cmd(0X01);
//	photodisplay(Photo1);
//	delay_ms(5000);
//	photodisplay(Photo2);
//  	delay_ms(5000);	
//}
/*12864显示*/
