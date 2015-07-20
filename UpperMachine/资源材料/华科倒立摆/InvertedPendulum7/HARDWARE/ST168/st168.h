#ifndef _st168_h
#define _st168_h
#define DARK  0
#define LIGHT	1

#define ST0  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)
#define ST1  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)
#define ST2  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_6)
#define ST3  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_7)
#define ST4  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_8)
#define ST5  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4)
#define ST6  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3)
#define ST7  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_2)
void ST168_Init(void);
#endif