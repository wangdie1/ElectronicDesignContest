#include"pid.h"


void TIM4_PWMINPUT_INIT(u16 arr,u16 psc)
{
  
        TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;        //TIM???????
        NVIC_InitTypeDef NVIC_InitStructure;                        //????
        TIM_ICInitTypeDef  TIM4_ICInitStructure;                 //TIM4  PWM?????
        GPIO_InitTypeDef GPIO_InitStructure;                         //IO??????
 
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);     //Open TIM4 clock
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //open gpioB clock
 
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;             //GPIO 7
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;          //????
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
 
        TIM_TimeBaseStructure.TIM_Period = arr; //???????????????????????????  
        TIM_TimeBaseStructure.TIM_Prescaler =psc; //??????TIMx???????????  
        TIM_TimeBaseStructure.TIM_ClockDivision = 0; //??????:TDTS = Tck_tim
        TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM??????
        TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //??TIM_TimeBaseInitStruct?????????TIMx???????
 
        
        /*???????*/
        NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;                     
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
 
  TIM4_ICInitStructure.TIM_Channel = TIM_Channel_2;                   
  TIM4_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;       
  TIM4_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;   
  TIM4_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1; 
  TIM4_ICInitStructure.TIM_ICFilter = 0x3;   //Filter:??
 
  TIM_PWMIConfig(TIM4, &TIM4_ICInitStructure);     //PWM????           
  TIM_SelectInputTrigger(TIM4, TIM_TS_TI2FP2);     //???????        
  TIM_SelectSlaveMode(TIM4, TIM_SlaveMode_Reset);  //?????????
  TIM_SelectMasterSlaveMode(TIM4, TIM_MasterSlaveMode_Enable);//??????????                                       
  TIM_ITConfig(TIM4, TIM_IT_CC2|TIM_IT_Update, ENABLE);          //????
  TIM_ClearITPendingBit(TIM4, TIM_IT_CC2|TIM_IT_Update); //???????
  TIM_Cmd(TIM4, ENABLE);    
}


void TIM4_IRQHandler(void)
{

                if (TIM_GetITStatus(TIM4, TIM_IT_CC2) != RESET)//??1??????
                        {        
                                duty_TIM4    =   TIM_GetCapture1(TIM4);          //?????                
               if  (TIM_GetCapture2(TIM4)>600)         period_TIM4        =        TIM_GetCapture2(TIM4);//?????
                                CollectFlag_TIM4 = 0;                        
        }        
                TIM_ClearITPendingBit(TIM4, TIM_IT_CC2|TIM_IT_Update); //???????
}


/*?????TIM1_PWMINPUT_INIT(u16 arr,u16 psc)
  ??      PWM?????*/
 
void TIM1_PWMINPUT_INIT(u16 arr,u16 psc)
{
  
        TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;        //TIM???????
        NVIC_InitTypeDef NVIC_InitStructure;                        //????
        TIM_ICInitTypeDef  TIM1_ICInitStructure;                 //PWM?????
        GPIO_InitTypeDef GPIO_InitStructure;                         //IO??????
 
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);     //Open TIM1 clock
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);  //open gpioE clock
   GPIO_PinRemapConfig(GPIO_FullRemap_TIM1, ENABLE); //Timer1?????  TIM1_CH2->PE11        
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;             //GPIO 11
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;          //????
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
 
        TIM_TimeBaseStructure.TIM_Period = arr; //???????????????????????????  
        TIM_TimeBaseStructure.TIM_Prescaler =psc; //??????TIMx???????????  
        TIM_TimeBaseStructure.TIM_ClockDivision = 0; //??????:TDTS = Tck_tim
        TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM??????
        TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //??TIM_TimeBaseInitStruct?????????TIMx???????
 
        
        /*???????*/
  NVIC_InitStructure.NVIC_IRQChannel =  TIM1_CC_IRQn;   //TIM1????                      
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
 
  TIM1_ICInitStructure.TIM_Channel = TIM_Channel_2;                   
  TIM1_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;       
  TIM1_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;   
  TIM1_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1; 
  TIM1_ICInitStructure.TIM_ICFilter = 0x03;   //Filter:??
 
  TIM_PWMIConfig(TIM1, &TIM1_ICInitStructure);     //PWM????           
  TIM_SelectInputTrigger(TIM1, TIM_TS_TI2FP2);     //???????        
  TIM_SelectSlaveMode(TIM1, TIM_SlaveMode_Reset);  //?????????
  TIM_SelectMasterSlaveMode(TIM1, TIM_MasterSlaveMode_Enable);//??????????                                       
 // TIM_ITConfig(TIM1, TIM_IT_CC2|TIM_IT_Update, ENABLE);          //????
  TIM_ITConfig(TIM1, TIM_IT_CC2, ENABLE); //??2 ??????
  //TIM_ClearITPendingBit(TIM1, TIM_IT_CC2|TIM_IT_Update); //???????
  TIM_Cmd(TIM1, ENABLE);    
}


void TIM1_CC_IRQHandler(void)
{

        {
                if (TIM_GetITStatus(TIM1, TIM_IT_CC2) != RESET)//??1??????
                        {        
                                duty_TIM1    =   TIM_GetCapture1(TIM1);          //?????                
                           if  (TIM_GetCapture2(TIM1)>600)         period_TIM1        =        TIM_GetCapture2(TIM1);
                                CollectFlag_TIM1 = 0;
                        }        
        }        
                TIM_ClearITPendingBit(TIM1, TIM_IT_CC2|TIM_IT_Update); //???????
}

 
/*?????TIM2_PWMINPUT_INIT(u16 arr,u16 psc)
  ??      PWM?????*/

void TIM2_PWMINPUT_INIT(u16 arr,u16 psc)
{
  
        TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;        //TIM???????
        NVIC_InitTypeDef NVIC_InitStructure;                        //????
        TIM_ICInitTypeDef  TIM2_ICInitStructure;                 //TIM2  PWM?????
        GPIO_InitTypeDef GPIO_InitStructure;                         //IO??????
 
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);     //Open TIM2 clock
 // RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //open gpioB clock
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  | RCC_APB2Periph_AFIO, ENABLE);  //??GPIO???AFIO????????
 GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);          //??JTAG
         GPIO_PinRemapConfig(GPIO_FullRemap_TIM2, ENABLE); //Timer2?????  TIM2_CH2->PB3

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;             //GPIO 3
        GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_IPU;          //???? ????
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOB, &GPIO_InitStructure);
 
        TIM_TimeBaseStructure.TIM_Period = arr; //???????????????????????????  
        TIM_TimeBaseStructure.TIM_Prescaler =psc; //??????TIMx???????????  
        TIM_TimeBaseStructure.TIM_ClockDivision = 0; //??????:TDTS = Tck_tim
        TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM??????
        TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //??TIM_TimeBaseInitStruct?????????TIMx???????
 
        
        /*???????*/
        NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;                     
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
 
  TIM2_ICInitStructure.TIM_Channel = TIM_Channel_2;                   
  TIM2_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;       
  TIM2_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;   
  TIM2_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1; 
  TIM2_ICInitStructure.TIM_ICFilter = 0x3;   //Filter:??
 
  TIM_PWMIConfig(TIM2, &TIM2_ICInitStructure);     //PWM????           
  TIM_SelectInputTrigger(TIM2, TIM_TS_TI2FP2);     //???????        
  TIM_SelectSlaveMode(TIM2, TIM_SlaveMode_Reset);  //?????????
  TIM_SelectMasterSlaveMode(TIM2, TIM_MasterSlaveMode_Enable);//??????????                                       
  TIM_ITConfig(TIM2, TIM_IT_CC2|TIM_IT_Update, ENABLE);          //????
  TIM_ClearITPendingBit(TIM2, TIM_IT_CC2|TIM_IT_Update); //???????
  TIM_Cmd(TIM2, ENABLE);    
}


void TIM2_IRQHandler(void)
{
        {
                if (TIM_GetITStatus(TIM2, TIM_IT_CC2) != RESET)//??1??????
                        {        
                                duty_TIM2    =   TIM_GetCapture1(TIM2);          //?????                
                           if  (TIM_GetCapture2(TIM2)>600)         period_TIM2        =        TIM_GetCapture2(TIM2);
                                CollectFlag_TIM2 = 0;
                        }                        
        }        
                TIM_ClearITPendingBit(TIM2, TIM_IT_CC2|TIM_IT_Update); //???????
}

 /*?????TIM5_PWMINPUT_INIT(u16 arr,u16 psc)
  ??      PWM?????*/

void TIM5_PWMINPUT_INIT(u16 arr,u16 psc)
{
  
        TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;        //TIM???????
        NVIC_InitTypeDef NVIC_InitStructure;                        //????
        TIM_ICInitTypeDef  TIM5_ICInitStructure;                 //TIM4  PWM?????
        GPIO_InitTypeDef GPIO_InitStructure;                         //IO??????
 
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);     //Open TIM4 clock
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //open gpioB clock
 
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;             //GPIO 1
  GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_IPU;          //???? ????
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
 
        TIM_TimeBaseStructure.TIM_Period = arr; //???????????????????????????  
        TIM_TimeBaseStructure.TIM_Prescaler =psc; //??????TIMx???????????  
        TIM_TimeBaseStructure.TIM_ClockDivision = 0; //??????:TDTS = Tck_tim
        TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM??????
        TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); //??TIM_TimeBaseInitStruct?????????TIMx???????
 
        
        /*???????*/
        NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;                     
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
 
  TIM5_ICInitStructure.TIM_Channel = TIM_Channel_2;                   
  TIM5_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;       
  TIM5_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;   
  TIM5_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1; 
  TIM5_ICInitStructure.TIM_ICFilter = 0x3;   //Filter:??
 
  TIM_PWMIConfig(TIM5, &TIM5_ICInitStructure);     //PWM????           
  TIM_SelectInputTrigger(TIM5, TIM_TS_TI2FP2);     //???????        
  TIM_SelectSlaveMode(TIM5, TIM_SlaveMode_Reset);  //?????????
  TIM_SelectMasterSlaveMode(TIM5, TIM_MasterSlaveMode_Enable);//??????????                                       
  TIM_ITConfig(TIM5, TIM_IT_CC2|TIM_IT_Update, ENABLE);          //????
  TIM_ClearITPendingBit(TIM5, TIM_IT_CC2|TIM_IT_Update); //???????
  TIM_Cmd(TIM5, ENABLE);    
}


void TIM5_IRQHandler(void)
{
        {
                if (TIM_GetITStatus(TIM5, TIM_IT_CC2) != RESET)//??1??????
                        {        
                                duty_TIM5    =   TIM_GetCapture1(TIM5);          //?????                
                        if  (TIM_GetCapture2(TIM5)>600)         period_TIM5        =        TIM_GetCapture2(TIM5);
                                CollectFlag_TIM5 = 0;
                        }                        
        }        
                TIM_ClearITPendingBit(TIM5, TIM_IT_CC2|TIM_IT_Update); //???????
}


int incPIDcalc(PIDtypedef *PIDx,u16 nextpoint)
{
 int iError,iincpid;
 iError=PIDx->setpoint-nextpoint;  //????
 /*iincpid=                                               //????
 PIDx->proportion*iError                //e[k]?
 -PIDx->integral*PIDx->last_error          //e[k-1]
 +PIDx->derivative*PIDx->prev_error;//e[k-2]
*/
iincpid=                                                          //????
PIDx->proportion*(iError-PIDx->last_error)
+PIDx->integral*iError
+PIDx->derivative*(iError-2*PIDx->last_error+PIDx->prev_error);

 PIDx->prev_error=PIDx->last_error; //????,??????
 PIDx->last_error=iError;
 return(iincpid) ;
}


void TIM6_IRQHandler(void)        //        ?????,??????
{          
        
 if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET)//????
        {
        frequency1=1000000/period_TIM4        ; //??????????????
        frequency2=1000000/period_TIM1        ;
        frequency3=1000000/period_TIM2        ;
        frequency4=1000000/period_TIM5        ;
/********PID1??**********/
        PID1.sum_error+=(incPIDcalc(&PID1,frequency1));         //??????? 
       pwm1=PID1.sum_error*4.6875  ;   //pwm1 ??????PWM????
          frequency1=0; //??
     period_TIM4=0;
/********PID2??**********/
         PID2.sum_error+=(incPIDcalc(&PID2,frequency2));         //???????  Y=Y+Y'                
         pwm2=PID2.sum_error*4.6875 ;   //????PWM???? 
        frequency2=0;
        period_TIM1=0;
/********PID3??**********/
         PID3.sum_error+=(incPIDcalc(&PID3,frequency3));          //??PID??
        pwm3=PID3.sum_error*4.6875 ;   //????PWM????
        frequency3=0;
        period_TIM2=0;
/********PID4??**********/
            PID4.sum_error+=(incPIDcalc(&PID4,frequency4));         //???????
         pwm4=PID4.sum_error*4.6875 ;   //????PWM???? 
        frequency4=0;
        period_TIM5=0; 
          }
TIM_SetCompare(pwm1,pwm2,pwm3,pwm4);             //????PWM?
 TIM_ClearITPendingBit(TIM6, TIM_IT_Update); //???????                
}