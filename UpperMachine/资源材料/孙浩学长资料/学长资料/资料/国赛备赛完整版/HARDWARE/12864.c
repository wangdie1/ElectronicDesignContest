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
//         �˿ڳ�ʼ��
/*******************************************************************/
void lcd_portinit(void)
{
	sck(0);
	cs(0);
	
}

/*******************************************************************/
//         дһ���ֽ�
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
//         ��һ���ֽ�
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
//         æ��־���
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
	return BF;//BF=0x80����״̬Ϊæ
}

/*******************************************************************/
//         д����
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
//         д����
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
//          ������ʾλ��    X(1~16),Y(1~4)
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
	lcd_cmd(0x30);//0011 0000 �������ã�һ����8λ���ݣ�����ָ�
	delay_us(1000);
	lcd_cmd(0x0C);//0000 1100 ������ʾ���α�off���α�λ��off
	delay_us(1000);
	lcd_cmd(0x01);//0000 0001 ��DDRAM
	delay_us(5000);
	lcd_cmd(0x02);//0000 0010 DDRAM��ַ��λ
	delay_us(1000);
	lcd_cmd(0x80);//1000 0000 �趨DDRAM 7λ��ַ000��0000����ַ������AC
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
* ͼ����ʾ                                               *
*                                                        *
*********************************************************/
void photodisplay(unsigned char *bmp)	
{ 
  unsigned char i,j;

  lcd_cmd(0x34);        //д����ʱ,�ر�ͼ����ʾ

  for(i=0;i<32;i++)
  {
    lcd_cmd(0x80+i);    //��д��ˮƽ����ֵ
    lcd_cmd(0x80);      //д�봹ֱ����ֵ
    for(j=0;j<16;j++)   //��д������8λԪ������    
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
  lcd_cmd(0x36);       //д������,��ͼ����ʾ 
}


//#include"12864_table.h"
// //unsigned char display[8]="12864";
/*12864��ʾ*/
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
/*12864��ʾ*/
