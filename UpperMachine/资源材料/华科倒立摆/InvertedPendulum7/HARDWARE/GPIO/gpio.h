#ifndef _GPIO_H
#define _GPIO_H
#define GPIO_PORT GPIOC
#define GPIO_PORT_CLK RCC_APB2Periph_GPIOC
#define GPIO_PIN			GPIO_Pin_4

void EnableGPIO_Init(void);
void Disable(void);
void Enable(void);

#endif