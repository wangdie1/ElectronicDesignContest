/*
*********************************************************************************************************
*
*                                      		LCD CONFIGURATION
*
*                                     ST Microelectronics STM32
*                                              on the
*
*                                           STM3240G-EVAL
*                                         Evaluation Board
*
* Filename      : LCD.h
* Version       : V1.00
* Programmer(s) : FT
*                 DC
*********************************************************************************************************
*/

#ifndef  __LCD_H__
#define  __LCD_H__

// #include <bsp.h>
#include "stm32f10x.h"
/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/
/* LCDÒý½Å½Ó¿Ú */
#define SPI2_SCK_PORT			GPIOB
#define SPI2_SCK_PIN			GPIO_Pin_13
#define SPI2_SCK_CLK			RCC_APB2Periph_GPIOB
#define SPI2_SCK_SOURCE		GPIO_PinSource13
#define SPI2_SCK_LOW()		GPIO_ResetBits(SPI2_SCK_PORT, SPI2_SCK_PIN) 
#define SPI2_SCK_HIGH()		GPIO_SetBits(SPI2_SCK_PORT, SPI2_SCK_PIN) 

#define SPI2_MISO_PORT		GPIOB
#define SPI2_MISO_PIN			GPIO_Pin_14
#define SPI2_MISO_CLK			RCC_APB2Periph_GPIOB
#define SPI2_MISO_SOURCE	GPIO_PinSource14
#define SPI2_MISO_LOW()		GPIO_ResetBits(SPI2_MISO_PORT, SPI2_MISO_PIN) 
#define SPI2_MISO_HIGH()	GPIO_SetBits(SPI2_MISO_PORT, SPI2_MISO_PIN) 

#define SPI2_MOSI_PORT		GPIOB
#define SPI2_MOSI_PIN			GPIO_Pin_15
#define SPI2_MOSI_CLK			RCC_APB2Periph_GPIOB
#define SPI2_MOSI_SOURCE	GPIO_PinSource15

//×Ö¿â
#define IC_CS_PORT				GPIOB
#define IC_CS_PIN					GPIO_Pin_10
#define IC_CS_CLK					RCC_APB2Periph_GPIOB
#define IC_CS_LOW()				GPIO_ResetBits(IC_CS_PORT, IC_CS_PIN) 
#define IC_CS_HIGH()			GPIO_SetBits(IC_CS_PORT, IC_CS_PIN)

//LCD
#define LCD_CS_PORT				GPIOB
#define LCD_CS_PIN				GPIO_Pin_11
#define LCD_CS_CLK				RCC_APB2Periph_GPIOB
#define LCD_CS_LOW()			GPIO_ResetBits(LCD_CS_PORT, LCD_CS_PIN) 
#define LCD_CS_HIGH()			GPIO_SetBits(LCD_CS_PORT, LCD_CS_PIN) 

#define LCD_RS_PORT				GPIOB
#define LCD_RS_PIN				GPIO_Pin_12
#define LCD_RS_CLK				RCC_APB2Periph_GPIOB
#define LCD_RS_LOW()			GPIO_ResetBits(LCD_RS_PORT, LCD_RS_PIN) 
#define LCD_RS_HIGH()			GPIO_SetBits(LCD_RS_PORT, LCD_RS_PIN) 

#define LCD_RESET_PORT		GPIOB
#define LCD_RESET_PIN			GPIO_Pin_1
#define LCD_RESET_CLK			RCC_APB2Periph_GPIOB
#define LCD_RESET_LOW()		GPIO_ResetBits(LCD_RESET_PORT, LCD_RESET_PIN) 
#define LCD_RESET_HIGH()	GPIO_SetBits(LCD_RESET_PORT, LCD_RESET_PIN) 

// typedef struct _LCD_LineMsg
// {
// 	u8 line_num;
// 	u8 msg[16];
// } LCD_LineMsg;

void Delay(u32 t);
void HardSPI1_WriteCommendByte(u8 cmd);
void HardSPI1_WriteDataByte(u8 data);
void clear_screen(void);
void display_graphic_16x16(u16 page,u16 column,u8 *dp);
void display_graphic_8x16(u16 page, u8 column, u8 *dp);
void display_graphic_5x7(u16 page,u8 column, u8 *dp);
void send_command_to_ROM(u8 datau);
static u8 get_data_from_ROM(void);
void get_n_bytes_data_from_ROM(u8 addrHigh,u8 addrMid, u8 addrLow,u8 *pBuff,u8 DataLen);
void display_GB2312_string(u8 y, u8 x, u8 *text);
void display_string_5x7(u8 y, u8 x, u8 *text);
void LCD_LineStrChange(u8 line_num, u8* msg);
void LCD_Init(void);
void display_photo(unsigned char *photo);

#endif
