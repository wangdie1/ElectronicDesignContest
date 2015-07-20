#include<stm32f10x.h>
#include"spi.h"

//��������ӿ�SPI1�ĳ�ʼ����SPI1���ó���ģʽ
void SPI1_Init(void)
{
	SPI_InitTypeDef  SPI_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	//����SPIʱ��
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOA, GPIO_Pin_4);
	SPI_Cmd(SPI1, DISABLE);
	/* SPI1 configuration */ 
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex; //SPI1����Ϊ����ȫ˫��
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;	                   //����SPI1Ϊ��ģʽ
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;                  //SPI���ͽ���8λ֡�ṹ
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;	 		               //����ʱ���ڲ�����ʱ��ʱ��Ϊ�ߵ�ƽ
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;		               //�ڶ���ʱ���ؿ�ʼ��������
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;			               //NSS�ź��������ʹ��SSIλ������
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8; //���岨����Ԥ��Ƶ��ֵ:������Ԥ��ƵֵΪ8
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;				   //���ݴ����MSBλ��ʼ
	SPI_InitStructure.SPI_CRCPolynomial = 7;						   //CRCֵ����Ķ���ʽ
	SPI_Init(SPI1, &SPI_InitStructure);
	/* Enable SPI1  */
	SPI_Cmd(SPI1, ENABLE); 	//ʹ��SPI1����
		//�ж�����
	SPI_NVIC_Configuration();
}

//��������ӿ�SPI2�ĳ�ʼ����SPI2���ó���ģʽ
void SPI2_Init(void)
{
	SPI_InitTypeDef  SPI_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	//����SPIʱ��
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
	
	/* SPI1 configuration */ 
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex; //SPI2����Ϊ����ȫ˫��
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;	                   //����SPI2Ϊ��ģʽ
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;                  //SPI���ͽ���8λ֡�ṹ
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;	 		               //����ʱ���ڲ�����ʱ��ʱ��Ϊ�ߵ�ƽ
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;		               //�ڶ���ʱ���ؿ�ʼ��������
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;			               //NSS�ź��������ʹ��SSIλ������
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8; //���岨����Ԥ��Ƶ��ֵ:������Ԥ��ƵֵΪ8
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;				   //���ݴ����MSBλ��ʼ
	SPI_InitStructure.SPI_CRCPolynomial = 7;						   //CRCֵ����Ķ���ʽ
	SPI_Init(SPI2, &SPI_InitStructure);
	/* Enable SPI2  */
	SPI_Cmd(SPI2, ENABLE); 		//ʹ��SPI2����

}
void SPI2_SetSpeed(u8 SPI_BaudRatePrescaler)
{
  	assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));
	SPI2->CR1&=0XFFC7;
	SPI2->CR1|=SPI_BaudRatePrescaler;	//����SPI2�ٶ� 
	SPI_Cmd(SPI2,ENABLE); 

} 
void SPI_NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

	NVIC_InitStructure.NVIC_IRQChannel = SPI1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 6;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	//SPI_I2S_ITConfig(SPI2,SPI_I2S_IT_RXNE,ENABLE);
					//|SPI_I2S_IT_TXE
					//|SPI_I2S_IT_RXNE
					//|SPI_I2S_IT_ERR
}
u8 SPI1_SendReadByte(u8 TxData)
{		
	u8 retry=0;				 
	while((SPI1->SR&1<<1)==0)//�ȴ���������	
	{
		retry++;
		if(retry>200)return 0;
	}			  
	SPI1->DR=TxData;	 	  //����һ��byte 
	retry=0;
	while((SPI1->SR&1<<0)==0) //�ȴ�������һ��byte  
	{
		retry++;
		if(retry>200)return 0;
	}	  						    
	return SPI1->DR;          //�����յ�������				    
}

u8 SPI2_SendReadByte(u8 TxData)
{		
	u8 retry=0;				 
	while((SPI2->SR&1<<1)==0)//�ȴ���������	
	{
		retry++;
		if(retry>200)return 0;
	}			  
	SPI2->DR=TxData;	 	  //����һ��byte 
	retry=0;
	while((SPI2->SR&1<<0)==0) //�ȴ�������һ��byte  
	{
		retry++;
		if(retry>200)return 0;
	}	  						    
	return SPI2->DR;          //�����յ�������				    
}
// //SPI1 ��дһ���ֽ�
// //����ֵ:��ȡ�����ֽ�
// u16 SPI1_SendReadByte(u16 Data)
// {
//   while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
//   SPI_I2S_SendData(SPI2, Data);
//   while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
//   return SPI_I2S_ReceiveData(SPI2);
// }

// //SPI2 ��дһ���ֽ�
// //����ֵ:��ȡ�����ֽ�
// u16 SPI2_SendReadByte(u16 Data)
// {
//   while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);
//   SPI_I2S_SendData(SPI2, Data);
//   while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);
//   return SPI_I2S_ReceiveData(SPI2);
// }
