#include <stm32f10x.h>
#include "sys.h"
extern unsigned char Rec_Dat_U1;

int main()
{

 u16 currentCount=0;
	float angle=0;
	SYS_CONFIG();

	Encoder_Init();

   	while(1)
	{
			delay_ms(300);
			currentCount = TIM3 -> CNT;
			if(currentCount<=50000)
		{
			currentCount=currentCount%1600;
			angle=((currentCount+1)/1600.0)*360;
		}
			else {
				currentCount=currentCount-65000;
				currentCount=currentCount%1600;
				angle=((currentCount+1)/1600.0)*360;
			}
			
			printf("编码器计数值为：%f   count:%d\n", angle,currentCount) ;	  
	
	}	
	
}
