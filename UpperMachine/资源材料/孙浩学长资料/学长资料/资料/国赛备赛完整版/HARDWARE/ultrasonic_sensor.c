//对于输出引脚取决于输入捕获的引脚
//定时器5时接PA0,PA1,PA2,PA3
//定时器2时接PA0,PA1,PA2,PA3
//定时器3时接PA6,PA7,PB0,PB1
//定时器4时接PB6,PB7,PB8,PB9
#include"ultrasonic_sensor.h"
#include"delay.h"
#include<stm32f10x.h>

#define Trig_Pin   GPIO_Pin_5
#define Trig_Group GPIOA
#define Trig_Clk   RCC_APB2Periph_GPIOA

void Triger_start()
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(Trig_Clk, ENABLE );
	GPIO_InitStruct.GPIO_Pin=Trig_Pin;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init( Trig_Group, & GPIO_InitStruct);
	
	
	Trig_Group->BRR=Trig_Pin;
	Trig_Group->BSRR=Trig_Pin;
	delay_us(20);
	Trig_Group->BRR=Trig_Pin;

}


/*
int main()
{
	SYS_CONFIG();
		Input_Compare_Init( TIM5_1);
	while(1)
	{
	Triger_start();
	printf("当前距离： %f mm\r\n", Get_H_Pulse(TIM5_1)*1.7/100 );
	delay_ms(200);		
	}
}

*/

