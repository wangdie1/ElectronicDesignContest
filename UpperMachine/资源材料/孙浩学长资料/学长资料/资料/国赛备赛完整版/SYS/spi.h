#ifndef _SPI_H_
#define _SPI_H_
#include "sys.h"


// SPI总线速度设置 
#define SPI_SPEED_2   0
#define SPI_SPEED_8   1
#define SPI_SPEED_16  2
#define SPI_SPEED_256 3

#define CS2_Low() GPIO_ResetBits(GPIOB,GPIO_Pin_12)
#define CS2_High() GPIO_SetBits(GPIOB,GPIO_Pin_12)
#define CS1_Low() GPIO_ResetBits(GPIOA,GPIO_Pin_4)
#define CS1_High() GPIO_SetBits(GPIOA,GPIO_Pin_4)

void SPI1_Init(void);			 //初始化SPI1口
void SPI2_Init(void);			 //初始化SPI2口
void SPI2_SetSpeed(u8 SPI_BaudRatePrescaler);
u8 SPI1_SendReadByte(u8 TxData);
u8 SPI2_SendReadByte(u8 TxData);
// u16 SPI1_SendReadByte(u16 Data);//SPI1总线读写一个字节
// u16 SPI2_SendReadByte(u16 Data);//SPI1总线读写一个字节
void SPI_NVIC_Configuration(void);
#endif
