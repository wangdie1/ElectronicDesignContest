#include"color_det.h"


#define led_pin		      GPIO_Pin_3
#define s2_pin			  GPIO_Pin_4
#define s3_pin 			  GPIO_Pin_5

#define s2(x)         x?GPIO_SetBits(Color_Group,s2_pin):GPIO_ResetBits(Color_Group,s2_pin)
#define s3(x)	      x?GPIO_SetBits(Color_Group,s3_pin):GPIO_ResetBits(Color_Group,s3_pin)
#define led(x)	      x?GPIO_SetBits(Color_Group,led_pin):GPIO_ResetBits(Color_Group,led_pin)

#define Color_Group	  GPIOA
#define Color_Clk     RCC_APB2Periph_GPIOA 

int R_fac=0, G_fac=0, B_fac=0;
int R_dat=0, G_dat=0, B_dat=0;

void Color_Pin_Init()
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(Color_Clk, ENABLE );

	GPIO_InitStruct.GPIO_Pin=led_pin;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init( Color_Group, & GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin=s2_pin;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init( Color_Group, & GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin=s3_pin;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init( Color_Group, & GPIO_InitStruct);


}

void Color_measure(int R_fac,int G_fac,int B_fac)
{

	led(1);	
	//红光
	s2(0);
	s3(0);
	R_dat=(Get_H_Pulse(TIM5_1) );
	//绿光
	delay_ms(50);
	s2(0);
	s3(1); 
	G_dat=(Get_H_Pulse(TIM5_1) );
	//蓝光
	delay_ms(50);	
	s2(1);
	s3(1);
	B_dat=(Get_H_Pulse(TIM5_1) );

}

void White_bal()
{
 	Color_Pin_Init();
	led(1);
		
	//红光
	s2(0);
	s3(0);
	delay_ms(10);
	R_fac=Get_H_Pulse(TIM5_1);
	//绿光
	delay_ms(40);
	s2(0);
	s3(1);
	delay_ms(10); 
	G_fac=Get_H_Pulse(TIM5_1);
	//蓝光
	delay_ms(40);	
	s2(1);
	s3(1);
	delay_ms(10);
	B_fac=Get_H_Pulse(TIM5_1);

}

/*
extern int R_fac, G_fac, B_fac;
extern int R_dat, G_dat, B_dat;

int main()
{
	SYS_CONFIG();
	Input_Compare_Init( TIM5_1);
	White_bal();
	delay_ms(500);
	while(1)
	{
	 Color_measure(R_fac, G_fac, B_fac);
	 printf("%x   %x   %x  \r\n ",R_dat, G_dat, B_dat);
	 delay_ms(500);	
	}
}*/

