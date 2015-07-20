#ifndef _ADC_H
#define _ADC_H

#include<stm32f10x.h>

void dma_config(void);
void adc_config(void);
void adc_init(void);
void adc_gpio_init(void);
void adc_convert(u16 *convert_value);

#endif

