#include "ST168.H"
#include "stm32f10x.h"


void ST168_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);////ʹ��PORTA,PORTEʱ��

	  /* Disable the Serial Wire Jtag Debug Port SWJ-DP */
   GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;//pb 0 1 2 3 4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOB
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8;  //pc 6 7 8
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIOC.0
	
}
//  ST168_DirTest(void)
// {
// 	if(ST1==LIGHT)
// 		ytemp+=1;
// 	if(ST2==LIGHT)
// 	{
// 			xtemp=
// 	}
// 	
// }
