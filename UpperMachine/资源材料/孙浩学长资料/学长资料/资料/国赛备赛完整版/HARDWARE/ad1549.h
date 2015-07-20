#ifndef _AD1549_H_
#define _AD1549_H_

#define AD_CLK  GPIO_Pin_0
#define AD_DATA GPIO_Pin_1
#define AD_CS   GPIO_Pin_2
#define AD_GPIO GPIOD
#define AD_GPIORCC  RCC_APB2Periph_GPIOD

#define  ADCLK(X)  X ? GPIO_SetBits(AD_GPIO,AD_CLK) :GPIO_ResetBits(AD_GPIO,AD_CLK)
#define  ADDATA GPIO_ReadInputDataBit(AD_GPIO,AD_DATA)//(X) X ? GPIO_SetBits(AD_GPIO,AD_DATA) :GPIO_ResetBits(AD_GPIO,AD_DATA)
#define  ADCS(X)   X ? GPIO_SetBits(AD_GPIO,AD_CS) :GPIO_ResetBits(AD_GPIO,AD_CS)

void AD1549_init(void);
unsigned int AD_Read(void);
#endif
