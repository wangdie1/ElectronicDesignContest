/******************** (C) 1209 Lab **************************
 * ÎÄ¼şÃû  : timer4_cap.c
 * ÃèÊö    £º¶¨Ê±Æ÷³õÊ¼»¯³ÌĞò£¬TIM4_Cap_Init£¨£©º¯Êı
             ¶¨Ê±Æ÷ÖÕ¶Ë·şÎñ³ÌĞò£TIM4_IRQHandler£¨£©º¯Êı
			 
 * ÊµÑéÆ½Ì¨£º
 * Ó²¼şÁ¬½Ó£º------------------
 *          | PB6  - TRIG      |
 *          | PC7  - ECHO      |
 *           ------------------
 * ¿â°æ±¾  £ºST3.5.0
 *
 * ×÷Õß    £ºLee 
*********************************************************************************/

#include "timer4_cap.h"
#include "usart.h"	
#include "stm32f10x_tim.h"

u8 TIM4CH1_CAPTURE_STA = 0;	//Í¨µÀ1ÊäÈë²¶»ñ±êÖ¾£¬¸ßÁ½Î»×ö²¶»ñ±êÖ¾£¬µÍ6Î»×öÒç³ö±êÖ¾		
u16 TIM4CH1_CAPTURE_UPVAL;
u16 TIM4CH1_CAPTURE_DOWNVAL;

u8 TIM4CH2_CAPTURE_STA = 0;	//Í¨µÀ2ÊäÈë²¶»ñ±êÖ¾£¬¸ßÁ½Î»×ö²¶»ñ±êÖ¾£¬µÍ6Î»×öÒç³ö±êÖ¾		
u16 TIM4CH2_CAPTURE_UPVAL;
u16 TIM4CH2_CAPTURE_DOWNVAL;

u8 TIM4CH3_CAPTURE_STA = 0;	//Í¨µÀ3ÊäÈë²¶»ñ±êÖ¾£¬¸ßÁ½Î»×ö²¶»ñ±êÖ¾£¬µÍ6Î»×öÒç³ö±êÖ¾		
u16 TIM4CH3_CAPTURE_UPVAL;
u16 TIM4CH3_CAPTURE_DOWNVAL;

u8 TIM4CH4_CAPTURE_STA = 0;	//Í¨µÀ4ÊäÈë²¶»ñ±êÖ¾£¬¸ßÁ½Î»×ö²¶»ñ±êÖ¾£¬µÍ6Î»×öÒç³ö±êÖ¾		
u16 TIM4CH4_CAPTURE_UPVAL;
u16 TIM4CH4_CAPTURE_DOWNVAL;

u32 tempup1 = 0;	//²¶»ñ×Ü¸ßµçÆ½µÄÊ±¼ä
u32 tempup2 = 0;	//²¶»ñ×Ü¸ßµçÆ½µÄÊ±¼ä
u32 tempup3 = 0;	//²¶»ñ×Ü¸ßµçÆ½µÄÊ±¼ä
u32 tempup4 = 0;	//²¶»ñ×Ü¸ßµçÆ½µÄÊ±¼ä

u32 tim4_T1;
u32 tim4_T2;
u32 tim4_T3;
u32 tim4_T4;

int pwmout1, pwmout2, pwmout3, pwmout4; 				//Êä³öÕ¼¿Õ±È

TIM_ICInitTypeDef TIM4_ICInitStructure;

void TIM4_Cap_Init(u16 arr, u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);	//Ê¹ÄÜTIM4Ê±ÖÓ
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //Ê¹ÄÜGPIOBÊ±ÖÓ

	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7| GPIO_Pin_8| GPIO_Pin_9;  //PB6,8,9 Çå³ıÖ®Ç°ÉèÖÃ  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PB6,7,8,9 ÊäÈë 
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOB, GPIO_Pin_6 | GPIO_Pin_7| GPIO_Pin_8 | GPIO_Pin_9);//PB6,8,9  ÏÂÀ­

	//³õÊ¼»¯¶¨Ê±Æ÷4 TIM4£¬¸Ã²¿·ÖÅäÖÃÖ÷ÒªÊÇÎªPWMÊä³ö·şÎñ 
	TIM_TimeBaseStructure.TIM_Period = arr; //Éè¶¨¼ÆÊıÆ÷×Ô¶¯ÖØ×°Öµ 
	TIM_TimeBaseStructure.TIM_Prescaler = psc; 	//Ô¤·ÖÆµÆ÷ 
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //ÉèÖÃÊ±ÖÓ·Ö¸î:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIMÏòÉÏ¼ÆÊıÄ£Ê½
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //¸ù¾İTIM_TimeBaseInitStructÖĞÖ¸¶¨µÄ²ÎÊı³õÊ¼»¯TIMxµÄÊ±¼ä»ùÊıµ¥Î»

	//³õÊ¼»¯TIM4ÊäÈë²¶»ñ²ÎÊı Í¨µÀ1
	TIM4_ICInitStructure.TIM_Channel = TIM_Channel_1; //CC1S=01 	Ñ¡ÔñÊäÈë¶Ë IC1Ó³Éäµ½TI1ÉÏ
	TIM4_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//ÉÏÉıÑØ²¶»ñ
	TIM4_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //Ó³Éäµ½TI1ÉÏ
	TIM4_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	  //ÅäÖÃÊäÈë·ÖÆµ,²»·ÖÆµ 
	TIM4_ICInitStructure.TIM_ICFilter = 0x00;	  //IC1F=0000 ÅäÖÃÊäÈëÂË²¨Æ÷ ²»ÂË²¨
	TIM_ICInit(TIM4, &TIM4_ICInitStructure);

	//³õÊ¼»¯TIM4ÊäÈë²¶»ñ²ÎÊı Í¨µÀ2
	TIM4_ICInitStructure.TIM_Channel = TIM_Channel_2; //CC1S=01 	Ñ¡ÔñÊäÈë¶Ë IC1Ó³Éäµ½TI1ÉÏ
	TIM4_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//ÉÏÉıÑØ²¶»ñ
	TIM4_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //Ó³Éäµ½TI1ÉÏ
	TIM4_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	  //ÅäÖÃÊäÈë·ÖÆµ,²»·ÖÆµ 
	TIM4_ICInitStructure.TIM_ICFilter = 0x00;	  //IC1F=0000 ÅäÖÃÊäÈëÂË²¨Æ÷ ²»ÂË²¨
	TIM_ICInit(TIM4, &TIM4_ICInitStructure);

	//³õÊ¼»¯TIM4ÊäÈë²¶»ñ²ÎÊı Í¨µÀ3
	TIM4_ICInitStructure.TIM_Channel = TIM_Channel_3; //CC1S=01 	Ñ¡ÔñÊäÈë¶Ë IC1Ó³Éäµ½TI1ÉÏ
	TIM4_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//ÉÏÉıÑØ²¶»ñ
	TIM4_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //Ó³Éäµ½TI1ÉÏ
	TIM4_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	  //ÅäÖÃÊäÈë·ÖÆµ,²»·ÖÆµ 
	TIM4_ICInitStructure.TIM_ICFilter = 0x00;	  //IC1F=0000 ÅäÖÃÊäÈëÂË²¨Æ÷ ²»ÂË²¨
	TIM_ICInit(TIM4, &TIM4_ICInitStructure);

	//³õÊ¼»¯TIM4ÊäÈë²¶»ñ²ÎÊı Í¨µÀ4
	TIM4_ICInitStructure.TIM_Channel = TIM_Channel_4; //CC1S=01 	Ñ¡ÔñÊäÈë¶Ë IC1Ó³Éäµ½TI1ÉÏ
	TIM4_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//ÉÏÉıÑØ²¶»ñ
	TIM4_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //Ó³Éäµ½TI1ÉÏ
	TIM4_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	  //ÅäÖÃÊäÈë·ÖÆµ,²»·ÖÆµ 
	TIM4_ICInitStructure.TIM_ICFilter = 0x00;	  //IC1F=0000 ÅäÖÃÊäÈëÂË²¨Æ÷ ²»ÂË²¨
	TIM_ICInit(TIM4, &TIM4_ICInitStructure);

	//ÖĞ¶Ï·Ö×é³õÊ¼»¯
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  //TIM4ÖĞ¶Ï
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //ÏÈÕ¼ÓÅÏÈ¼¶1¼¶
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //´ÓÓÅÏÈ¼¶0¼¶
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQÍ¨µÀ±»Ê¹ÄÜ
	NVIC_Init(&NVIC_InitStructure);   //¸ù¾İNVIC_InitStructÖĞÖ¸¶¨µÄ²ÎÊı³õÊ¼»¯ÍâÉèNVIC¼Ä´æÆ÷ 

	TIM_ITConfig(TIM4, TIM_IT_CC1 | TIM_IT_CC2 | TIM_IT_CC3 | TIM_IT_CC4,ENABLE);   //²»ÔÊĞí¸üĞÂÖĞ¶Ï£¬ÔÊĞíCC1IE,CC2IE,CC3IE,CC4IE²¶»ñÖĞ¶Ï	
	TIM_Cmd(TIM4, ENABLE); 		//Ê¹ÄÜ¶¨Ê±Æ÷4

}

//¶¨Ê±Æ÷4ÖĞ¶Ï·şÎñ³ÌĞò,ÓÃCH1×÷Îª³¬Éù²¨×ª»»µÄÍ¨µÀ ¼´PB6¶Ë¿Ú
void TIM4_IRQHandler(void)
{
	if ((TIM4CH1_CAPTURE_STA & 0X80) == 0) 		//»¹Î´³É¹¦²¶»ñ	
	{
		if (TIM_GetITStatus(TIM4, TIM_IT_CC1) != RESET) 		//²¶»ñ1·¢Éú²¶»ñÊÂ¼ş
		{
			TIM_ClearITPendingBit(TIM4, TIM_IT_CC1); 		//Çå³ıÖĞ¶Ï±êÖ¾Î»
			if (TIM4CH1_CAPTURE_STA & 0X40)		//²¶»ñµ½Ò»¸öÏÂ½µÑØ
			{
				TIM4CH1_CAPTURE_DOWNVAL = TIM_GetCapture1(TIM4);//¼ÇÂ¼ÏÂ´ËÊ±µÄ¶¨Ê±Æ÷¼ÆÊıÖ
				printf("Channel 1 : %d cm\r\n",TIM4CH1_CAPTURE_DOWNVAL);
				if (TIM4CH1_CAPTURE_DOWNVAL < TIM4CH1_CAPTURE_UPVAL)
				{/* Èç¹û¼ÆÊıÆ÷³õÊ¼Öµ´óÓÚÄ©Î²Öµ£¬ËµÃ÷¼ÆÊıÆ÷ÓĞÒç³ö */
					tim4_T1 = 65535;
				}
				else
				{
					tim4_T1 = 0;  
				}
				tempup1 = TIM4CH1_CAPTURE_DOWNVAL - TIM4CH1_CAPTURE_UPVAL + tim4_T1;		//µÃµ½×ÜµÄ¸ßµçÆ½µÄÊ±¼ä
				//pwmout1 = tempup1;		//×ÜµÄ¸ßµçÆ½µÄÊ±¼ä
				tempup1 =tempup1 *17/1000;//¼ÆËã¾àÀë&&UltrasonicWave_Distance<85    t *  10e-6 * 170*100 = t * 17 *e-3
				
				TIM4CH1_CAPTURE_STA = 0; 		//²¶»ñ±êÖ¾Î»ÇåÁã£¬ÕâÒ»²½ºÜÖØÒª£¡
				TIM_OC1PolarityConfig(TIM4, TIM_ICPolarity_Rising); //ÉèÖÃÎªÉÏÉıÑØ²¶»ñ		  
			}
			else //·¢Éú²¶»ñÊ±¼äµ«²»ÊÇÏÂ½µÑØ£¬µÚÒ»´Î²¶»ñµ½ÉÏÉıÑØ£¬¼ÇÂ¼´ËÊ±µÄ¶¨Ê±Æ÷¼ÆÊıÖµ
			{
				TIM4CH1_CAPTURE_UPVAL = TIM_GetCapture1(TIM4);		//»ñÈ¡ÉÏÉıÑØÊı¾İ
				TIM4CH1_CAPTURE_STA |= 0X40;		//±ê¼ÇÒÑ²¶»ñµ½ÉÏÉıÑØ
				TIM_OC1PolarityConfig(TIM4, TIM_ICPolarity_Falling);//ÉèÖÃÎªÏÂ½µÑØ²¶»ñ
			}
		}
	}

	if ((TIM4CH2_CAPTURE_STA & 0X80) == 0)		//»¹Î´³É¹¦²¶»ñ	
	{
		if (TIM_GetITStatus(TIM4, TIM_IT_CC2) != RESET)		//²¶»ñ2·¢Éú²¶»ñÊÂ¼ş
		{
			TIM_ClearITPendingBit(TIM4, TIM_IT_CC2);		//Çå³ıÖĞ¶Ï±êÖ¾Î»
			if (TIM4CH2_CAPTURE_STA & 0X40)		//²¶»ñµ½Ò»¸öÏÂ½µÑØ
			{
				TIM4CH2_CAPTURE_DOWNVAL = TIM_GetCapture2(TIM4);//¼ÇÂ¼ÏÂ´ËÊ±µÄ¶¨Ê±Æ÷¼ÆÊıÖµ
				if (TIM4CH2_CAPTURE_DOWNVAL < TIM4CH2_CAPTURE_UPVAL)
				{
					tim4_T2 = 65535;
				}
				else
					tim4_T2 = 0;
				tempup2 = TIM4CH2_CAPTURE_DOWNVAL - TIM4CH2_CAPTURE_UPVAL
						+ tim4_T2;		//µÃµ½×ÜµÄ¸ßµçÆ½µÄÊ±¼ä
				pwmout2 = tempup2;		//×ÜµÄ¸ßµçÆ½µÄÊ±¼ä
				TIM4CH2_CAPTURE_STA = 0;		//²¶»ñ±êÖ¾Î»ÇåÁã
				TIM_OC2PolarityConfig(TIM4, TIM_ICPolarity_Rising); //ÉèÖÃÎªÉÏÉıÑØ²¶»ñ		  
			}
			else //·¢Éú²¶»ñÊ±¼äµ«²»ÊÇÏÂ½µÑØ£¬µÚÒ»´Î²¶»ñµ½ÉÏÉıÑØ£¬¼ÇÂ¼´ËÊ±µÄ¶¨Ê±Æ÷¼ÆÊıÖµ
			{
				TIM4CH2_CAPTURE_UPVAL = TIM_GetCapture2(TIM4);		//»ñÈ¡ÉÏÉıÑØÊı¾İ
				TIM4CH2_CAPTURE_STA |= 0X40;		//±ê¼ÇÒÑ²¶»ñµ½ÉÏÉıÑØ
				TIM_OC2PolarityConfig(TIM4, TIM_ICPolarity_Falling);//ÉèÖÃÎªÏÂ½µÑØ²¶»ñ
			}
		}
	}

	if ((TIM4CH3_CAPTURE_STA & 0X80) == 0)		//»¹Î´³É¹¦²¶»ñ	
	{
		if (TIM_GetITStatus(TIM4, TIM_IT_CC3) != RESET)		//²¶»ñ3·¢Éú²¶»ñÊÂ¼ş
		{
			TIM_ClearITPendingBit(TIM4, TIM_IT_CC3);		//Çå³ıÖĞ¶Ï±êÖ¾Î»
			if (TIM4CH3_CAPTURE_STA & 0X40)		//²¶»ñµ½Ò»¸öÏÂ½µÑØ
			{
				TIM4CH3_CAPTURE_DOWNVAL = TIM_GetCapture3(TIM4);//¼ÇÂ¼ÏÂ´ËÊ±µÄ¶¨Ê±Æ÷¼ÆÊıÖµ
				if (TIM4CH3_CAPTURE_DOWNVAL < TIM4CH3_CAPTURE_UPVAL)
				{
					tim4_T3 = 65535;
				}
				else
					tim4_T3 = 0;
				tempup3 = TIM4CH3_CAPTURE_DOWNVAL - TIM4CH3_CAPTURE_UPVAL
						+ tim4_T3;		//µÃµ½×ÜµÄ¸ßµçÆ½µÄÊ±¼ä
				pwmout3 = tempup3;		//×ÜµÄ¸ßµçÆ½µÄÊ±¼ä
				TIM4CH3_CAPTURE_STA = 0;		//²¶»ñ±êÖ¾Î»ÇåÁã
				TIM_OC3PolarityConfig(TIM4, TIM_ICPolarity_Rising); //ÉèÖÃÎªÉÏÉıÑØ²¶»ñ		  
			}
			else //·¢Éú²¶»ñÊ±¼äµ«²»ÊÇÏÂ½µÑØ£¬µÚÒ»´Î²¶»ñµ½ÉÏÉıÑØ£¬¼ÇÂ¼´ËÊ±µÄ¶¨Ê±Æ÷¼ÆÊıÖµ
			{
				TIM4CH3_CAPTURE_UPVAL = TIM_GetCapture3(TIM4);		//»ñÈ¡ÉÏÉıÑØÊı¾İ
				TIM4CH3_CAPTURE_STA |= 0X40;		//±ê¼ÇÒÑ²¶»ñµ½ÉÏÉıÑØ
				TIM_OC3PolarityConfig(TIM4, TIM_ICPolarity_Falling);//ÉèÖÃÎªÏÂ½µÑØ²¶»ñ
			}
		}
	}

	if ((TIM4CH4_CAPTURE_STA & 0X80) == 0)		//»¹Î´³É¹¦²¶»ñ	
	{
		if (TIM_GetITStatus(TIM4, TIM_IT_CC4) != RESET)		//²¶»ñ4·¢Éú²¶»ñÊÂ¼ş
		{
			TIM_ClearITPendingBit(TIM4, TIM_IT_CC4);		//Çå³ıÖĞ¶Ï±êÖ¾Î»
			if (TIM4CH4_CAPTURE_STA & 0X40)		//²¶»ñµ½Ò»¸öÏÂ½µÑØ
			{
				TIM4CH4_CAPTURE_DOWNVAL = TIM_GetCapture4(TIM4);//¼ÇÂ¼ÏÂ´ËÊ±µÄ¶¨Ê±Æ÷¼ÆÊıÖµ
				if (TIM4CH4_CAPTURE_DOWNVAL < TIM4CH4_CAPTURE_UPVAL)
				{
					tim4_T4 = 65535;
				}
				else
					tim4_T4 = 0;
				tempup4 = TIM4CH4_CAPTURE_DOWNVAL - TIM4CH4_CAPTURE_UPVAL
						+ tim4_T4;		//µÃµ½×ÜµÄ¸ßµçÆ½µÄÊ±¼ä
				pwmout4 = tempup4;		//×ÜµÄ¸ßµçÆ½µÄÊ±¼ä
				TIM4CH4_CAPTURE_STA = 0;		//²¶»ñ±êÖ¾Î»ÇåÁã
				TIM_OC4PolarityConfig(TIM4, TIM_ICPolarity_Rising); //ÉèÖÃÎªÉÏÉıÑØ²¶»ñ		  
			}
			else //·¢Éú²¶»ñÊ±¼äµ«²»ÊÇÏÂ½µÑØ£¬µÚÒ»´Î²¶»ñµ½ÉÏÉıÑØ£¬¼ÇÂ¼´ËÊ±µÄ¶¨Ê±Æ÷¼ÆÊıÖµ
			{
				TIM4CH4_CAPTURE_UPVAL = TIM_GetCapture4(TIM4);		//»ñÈ¡ÉÏÉıÑØÊı¾İ
				TIM4CH4_CAPTURE_STA |= 0X40;		//±ê¼ÇÒÑ²¶»ñµ½ÉÏÉıÑØ
				TIM_OC4PolarityConfig(TIM4, TIM_ICPolarity_Falling);//ÉèÖÃÎªÏÂ½µÑØ²¶»ñ
			}
		}
	}
}
