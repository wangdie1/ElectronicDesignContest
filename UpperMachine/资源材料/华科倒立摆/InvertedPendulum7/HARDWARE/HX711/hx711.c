#include "stm32f10x.h"
#include "sys.h"
#include "hx711.h"
#include "delay.h"

#define DELAY 1
#define WEIGHT_BUFFER_SIZE 20
u32 weight_buffer[WEIGHT_BUFFER_SIZE]={0};
u32 weight_buffer_index=0;


void HX711_INIT(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);	 //使能PF端口时钟
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;				 
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出 sclk
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 GPIO_Init(GPIOA, &GPIO_InitStructure);


	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_5;//sd
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
	

}
u32  weight_buffer_init()
{
	u32 wtemp;
	u32 i;
	for(i=0;i<WEIGHT_BUFFER_SIZE;i++)
	{
		weight_buffer[i]=ReadHx711();
		delay_ms(1);
	}
	for(i=0;i<WEIGHT_BUFFER_SIZE;i++)
	{
		wtemp+=weight_buffer[i];
	}
	wtemp/=WEIGHT_BUFFER_SIZE;
	return wtemp;
}

u32 ReadHx711(void)
{
   	u32 Count;
   	u8 i;
   	ADSK_L;
		delay_us(DELAY);
   	Count=0;
   	while(ADDO);
   	for (i=0;i<24;i++)
   	{
				
      	ADSK_H;
			delay_us(DELAY);
      	Count=Count<<1;
			delay_us(DELAY);
      	ADSK_L;
			delay_us(DELAY);
      	if(ADDO) Count++;
			delay_us(DELAY);
   	}
		
   	ADSK_H;
		delay_us(DELAY);
   	Count=Count^0x800000;
		delay_us(DELAY);
   	ADSK_L;
		delay_us(DELAY);
   	return(Count);
}
u32 ReadHx711_Average()
{
	u32 wtemp;
	u32 i;
	
	wtemp=ReadHx711();
	weight_buffer[weight_buffer_index]=wtemp;
	weight_buffer_index++;
	if(weight_buffer_index==WEIGHT_BUFFER_SIZE)
	{
		weight_buffer_index=0;
	}
	wtemp=0;
	for(i=0;i<WEIGHT_BUFFER_SIZE;i++)
	{
		wtemp+=weight_buffer[weight_buffer_index];
	}
	wtemp/=WEIGHT_BUFFER_SIZE;
	return wtemp;
}

