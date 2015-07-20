#include<stm32f10x.h>
#include"sys.h"

extern vu16 ADC1ConvertedValue[12];

extern unsigned char Rec_Dat_U1;
extern unsigned char Rec_String_U1[200];
extern int conut_flag_1;

int tem_high=40;
int tem_low=0;
int alarm_flag=1;

#define WADDR   0X90  //Ð´µØÖ·
#define RADDR   0X91  //¶ÁµØÖ·
#define CONF   0X01  //ÅäÖÃ¼Ä´æÆ÷
#define TEMP   0X00  //ÎÂ¶È¼Ä´æÆ÷ Ö»¶Á

#define in_1(x)    x?GPIO_ResetBits(GPIOC , GPIO_Pin_0): GPIO_SetBits(GPIOC , GPIO_Pin_0)
#define in_2(x)    x?GPIO_ResetBits(GPIOC , GPIO_Pin_1): GPIO_SetBits(GPIOC , GPIO_Pin_1)
#define in_3(x)    x?GPIO_ResetBits(GPIOB , GPIO_Pin_10): GPIO_SetBits(GPIOB , GPIO_Pin_10)
#define in_4(x)    x?GPIO_ResetBits(GPIOB , GPIO_Pin_11): GPIO_SetBits(GPIOB , GPIO_Pin_11)


void CAR_GPIO_INIT(void);

int main()
{

	SYS_CONFIG();

	while(1)
	{
		printf("the num is:%d\r\n",ADC1ConvertedValue[0] );
	  delay_ms(500);
		

		}
	
}





		

void CAR_GPIO_INIT()				
{

  GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOD, ENABLE);	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_Out_PP; 
  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);           
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_Out_PP;  
  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;  
	GPIO_Init(GPIOB, &GPIO_InitStructure);        
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_Out_PP;    
 GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	
	GPIO_Init(GPIOC, &GPIO_InitStructure);          
		
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_Out_PP;  
 GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	
	GPIO_Init(GPIOC, &GPIO_InitStructure);         
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_IPU;  	
	GPIO_Init(GPIOD, &GPIO_InitStructure);          
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_IPU;  
	
	GPIO_Init(GPIOD, &GPIO_InitStructure);     
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_IPU;   
	GPIO_Init(GPIOD, &GPIO_InitStructure);          
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_IPU;  
	GPIO_Init(GPIOD, &GPIO_InitStructure);   	
}







