//注释的地方时使用多通道采集是需要改变的


#include"adc.h"

vu16 ADC1ConvertedValue[12]={0};	   //存储多通道采集到的数据的数组
#define ADC1_DR_Address    ((u32)0x4001244C)

u16 convert_value[2]={0};

void dma_config(void)
{
  DMA_InitTypeDef DMA_InitStruct;
  DMA_DeInit(DMA1_Channel1);	
  DMA_InitStruct .DMA_PeripheralBaseAddr= ADC1_DR_Address;
  DMA_InitStruct .DMA_MemoryBaseAddr=(u32)ADC1ConvertedValue;
  DMA_InitStruct .DMA_DIR=DMA_DIR_PeripheralSRC;
  DMA_InitStruct .DMA_BufferSize=12;						//缓存数据
  DMA_InitStruct .DMA_PeripheralInc=DMA_PeripheralInc_Disable;
  DMA_InitStruct .DMA_MemoryInc=DMA_MemoryInc_Enable;	// 内存增长当用多通道时 使能
  DMA_InitStruct .DMA_PeripheralDataSize=DMA_PeripheralDataSize_HalfWord;
  DMA_InitStruct .DMA_MemoryDataSize= DMA_MemoryDataSize_HalfWord;
  DMA_InitStruct .DMA_Mode=DMA_Mode_Circular;
  DMA_InitStruct .DMA_Priority=DMA_Priority_High;
  DMA_InitStruct .DMA_M2M= DMA_M2M_Disable;

  DMA_Init( DMA1_Channel1, & DMA_InitStruct);
  DMA_Cmd( DMA1_Channel1, ENABLE);

}

void adc_config(void)
{
  ADC_InitTypeDef ADC_InitStruct;

  ADC_InitStruct .ADC_Mode=ADC_Mode_Independent;
  ADC_InitStruct .ADC_ScanConvMode=ENABLE; 	   //当使用多通道时使能
  ADC_InitStruct .ADC_ContinuousConvMode=ENABLE;
  ADC_InitStruct .ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;
  ADC_InitStruct .ADC_DataAlign=ADC_DataAlign_Right;
  ADC_InitStruct .ADC_NbrOfChannel=12;	  //所需要的通道个数

 ADC_Init(ADC1, & ADC_InitStruct);
 ADC_RegularChannelConfig(ADC1, ADC_Channel_0,  1,  ADC_SampleTime_239Cycles5); //多通道的配置中间数字为采集顺序
 ADC_RegularChannelConfig(ADC1, ADC_Channel_1,  2,  ADC_SampleTime_239Cycles5); //多通道的配置中间数字为采集顺序
 ADC_RegularChannelConfig(ADC1, ADC_Channel_2,  3,  ADC_SampleTime_239Cycles5); //多通道的配置中间数字为采集顺序
 ADC_RegularChannelConfig(ADC1, ADC_Channel_3,  4,  ADC_SampleTime_239Cycles5); //多通道的配置中间数字为采集顺序
 ADC_RegularChannelConfig(ADC1, ADC_Channel_4,  5,  ADC_SampleTime_239Cycles5); //多通道的配置中间数字为采集顺序
 ADC_RegularChannelConfig(ADC1, ADC_Channel_5,  6,  ADC_SampleTime_239Cycles5); //多通道的配置中间数字为采集顺序
 ADC_RegularChannelConfig(ADC1, ADC_Channel_6,  7,  ADC_SampleTime_239Cycles5); //多通道的配置中间数字为采集顺序
 ADC_RegularChannelConfig(ADC1, ADC_Channel_7,  8,  ADC_SampleTime_239Cycles5); //多通道的配置中间数字为采集顺序
 ADC_RegularChannelConfig(ADC1, ADC_Channel_8,  9,  ADC_SampleTime_239Cycles5); //多通道的配置中间数字为采集顺序
 ADC_RegularChannelConfig(ADC1, ADC_Channel_9,  10, ADC_SampleTime_239Cycles5); //多通道的配置中间数字为采集顺序
 ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 11, ADC_SampleTime_239Cycles5); //多通道的配置中间数字为采集顺序
 ADC_RegularChannelConfig(ADC1, ADC_Channel_11, 12, ADC_SampleTime_239Cycles5); //多通道的配置中间数字为采集顺序

 ADC_Cmd(ADC1, ENABLE);
 ADC_DMACmd(ADC1, ENABLE);
 

  ADC_ResetCalibration(ADC1);	  //重新校准
  /* Check the end of ADC1 reset calibration register */
  while(ADC_GetResetCalibrationStatus(ADC1));  //等待重新校准完成
  /* Start ADC1 calibaration */
  ADC_StartCalibration(ADC1);		//开始校准
  /* Check the end of ADC1 calibration */
  while(ADC_GetCalibrationStatus(ADC1));	   //等待校准完成
  /* Start ADC1 Software Conversion */ 
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);	//连续转换开始，ADC通过DMA方式不断的更新RAM区

}

void adc_convert(u16 *convert_value)
{

    convert_value[0]=((ADC1ConvertedValue[0]*100)/4096)*33;
	convert_value[1]=((ADC1ConvertedValue[1]*100)/4096)*33;
	convert_value[2]=((ADC1ConvertedValue[2]*100)/4096)*33;
	convert_value[3]=((ADC1ConvertedValue[3]*100)/4096)*33;
	convert_value[4]=((ADC1ConvertedValue[4]*100)/4096)*33;
	convert_value[5]=((ADC1ConvertedValue[5]*100)/4096)*33;
	convert_value[6]=((ADC1ConvertedValue[6]*100)/4096)*33;
	convert_value[7]=((ADC1ConvertedValue[7]*100)/4096)*33;
	convert_value[8]=((ADC1ConvertedValue[8]*100)/4096)*33;
	convert_value[9]=((ADC1ConvertedValue[9]*100)/4096)*33;
	convert_value[10]=((ADC1ConvertedValue[10]*100)/4096)*33;
	convert_value[11]=((ADC1ConvertedValue[11]*100)/4096)*33;



}


void adc_gpio_init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;

  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB| RCC_APB2Periph_ADC1|RCC_APB2Periph_AFIO, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC| RCC_APB2Periph_GPIOA, ENABLE);

  GPIO_InitStruct .GPIO_Pin=GPIO_Pin_0;
  GPIO_InitStruct .GPIO_Mode=GPIO_Mode_AIN;
  GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct .GPIO_Pin=GPIO_Pin_1;
  GPIO_InitStruct .GPIO_Mode=GPIO_Mode_AIN;
  GPIO_Init(GPIOA, &GPIO_InitStruct);

   GPIO_InitStruct .GPIO_Pin=GPIO_Pin_2;
  GPIO_InitStruct .GPIO_Mode=GPIO_Mode_AIN;
  GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct .GPIO_Pin=GPIO_Pin_3;
  GPIO_InitStruct .GPIO_Mode=GPIO_Mode_AIN;
  GPIO_Init(GPIOA, &GPIO_InitStruct);

   GPIO_InitStruct .GPIO_Pin=GPIO_Pin_4;
  GPIO_InitStruct .GPIO_Mode=GPIO_Mode_AIN;
  GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct .GPIO_Pin=GPIO_Pin_1;
  GPIO_InitStruct .GPIO_Mode=GPIO_Mode_AIN;
  GPIO_Init(GPIOA, &GPIO_InitStruct);

   GPIO_InitStruct .GPIO_Pin=GPIO_Pin_5;
  GPIO_InitStruct .GPIO_Mode=GPIO_Mode_AIN;
  GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct .GPIO_Pin=GPIO_Pin_6;
  GPIO_InitStruct .GPIO_Mode=GPIO_Mode_AIN;
  GPIO_Init(GPIOA, &GPIO_InitStruct);

   GPIO_InitStruct .GPIO_Pin=GPIO_Pin_7;
  GPIO_InitStruct .GPIO_Mode=GPIO_Mode_AIN;
  GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct .GPIO_Pin=GPIO_Pin_0;
  GPIO_InitStruct .GPIO_Mode=GPIO_Mode_AIN;
  GPIO_Init(GPIOB, &GPIO_InitStruct);

   GPIO_InitStruct .GPIO_Pin=GPIO_Pin_1;
  GPIO_InitStruct .GPIO_Mode=GPIO_Mode_AIN;
  GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct .GPIO_Pin=GPIO_Pin_0;
  GPIO_InitStruct .GPIO_Mode=GPIO_Mode_AIN;
  GPIO_Init(GPIOC, &GPIO_InitStruct);

      GPIO_InitStruct .GPIO_Pin=GPIO_Pin_1;
  GPIO_InitStruct .GPIO_Mode=GPIO_Mode_AIN;
  GPIO_Init(GPIOC, &GPIO_InitStruct);

   GPIO_InitStruct .GPIO_Pin=GPIO_Pin_2;
  GPIO_InitStruct .GPIO_Mode=GPIO_Mode_AIN;
  GPIO_Init(GPIOC, &GPIO_InitStruct);


}
void adc_init(void)
{
 adc_gpio_init();
 dma_config();
 adc_config();
 

}


