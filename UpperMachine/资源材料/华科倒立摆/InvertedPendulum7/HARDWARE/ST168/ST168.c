#include "ST168.H"
#include "stm32f10x.h"


void ST168_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);//¨º1?¨¹PORTA,PORTE¨º¡À?¨®

	  /* Disable the Serial Wire Jtag Debug Port SWJ-DP */
   GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3
	|GPIO_Pin_4;//PE2~4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //
 	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //
 	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
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