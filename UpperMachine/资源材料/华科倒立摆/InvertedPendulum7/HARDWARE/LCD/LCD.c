/*
*********************************************************************************************************
*
*                                        		LCD PACKAGE
*
*                                     ST Microelectronics STM32
*                                              on the
*
*                                         STM3240G-EVAL
*                                        Evaluation Board
*
* Filename      : LCD.c
* Version       : V1.00
* Programmer(s) : FF
*                 DC
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#include "LCD.h"
#include <string.h>
#include "stm32f10x.h"


 unsigned char Photo0[]=
 {
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X80,0X80,0XC0,0X40,0X40,0X20,0X20,0XA0,
0X90,0X50,0X90,0X08,0X08,0X08,0X08,0X04,0X04,0X04,0X54,0X24,0XB2,0X02,0X02,0X02,
0X02,0X02,0X00,0X00,0X38,0X00,0X01,0X2D,0X51,0X01,0X01,0X01,0X01,0X01,0X01,0X71,
0X09,0X11,0X29,0X51,0X00,0X00,0X00,0X00,0X02,0X02,0X02,0X42,0X02,0XA2,0X30,0X04,
0X04,0X04,0X04,0X08,0X08,0X08,0X48,0X90,0X90,0X90,0XA0,0X20,0X20,0X40,0X40,0XC0,
0X80,0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X80,0XC0,
0XE0,0X30,0X18,0X8C,0X04,0X06,0X03,0X01,0X01,0X20,0X00,0X80,0X00,0X00,0X00,0X84,
0X42,0X45,0X23,0X06,0X90,0X10,0X40,0X28,0X00,0X10,0X04,0X0C,0X04,0X04,0X04,0X04,
0X06,0X02,0X02,0X02,0XC0,0XC0,0X80,0X01,0X21,0X21,0X21,0X21,0X21,0X21,0X21,0X21,
0X21,0X61,0X61,0X60,0X60,0X60,0X62,0XE2,0XE2,0XE6,0XE6,0XC4,0XC4,0XC4,0X8C,0X04,
0X10,0X00,0X28,0X08,0X44,0X92,0X00,0X23,0X00,0X40,0X80,0X80,0X00,0X20,0X10,0X08,
0X80,0X55,0X41,0X23,0X16,0X84,0X4C,0X18,0X30,0XE0,0XC0,0X80,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XFE,0XFF,0X03,
0X00,0XA0,0X04,0X00,0X30,0X00,0X00,0X42,0X8C,0X02,0X00,0X78,0X84,0X03,0X01,0X00,
0X00,0X00,0X8C,0X03,0X00,0X00,0X00,0X00,0X00,0X00,0X80,0X80,0X80,0XE0,0X38,0X18,
0X20,0X30,0X78,0X18,0X00,0X30,0XB9,0X99,0X81,0XB0,0XBA,0X8A,0X80,0XC0,0XE0,0XF8,
0XF0,0X70,0X20,0X80,0XF2,0XFE,0X7E,0X1E,0X06,0X02,0X02,0X03,0X01,0X01,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X01,0X06,0X70,0X00,0X00,0X00,0X01,0X06,0XF8,0X00,
0X00,0X02,0X48,0X2A,0X0A,0X9A,0X1A,0X09,0X04,0X00,0X03,0XFF,0XFE,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,0X07,0X0F,
0X1C,0X30,0X60,0XC8,0XC4,0X86,0X01,0X41,0X00,0X20,0X00,0X10,0X01,0XC2,0X24,0X08,
0X00,0X90,0X01,0X22,0X04,0X4C,0X5C,0X1C,0XAC,0X90,0X40,0X00,0X9C,0X14,0X00,0X00,
0X00,0X1C,0X0C,0X14,0X00,0X10,0X1C,0X1C,0X14,0X00,0X10,0X1C,0X1C,0X1C,0X1C,0X0C,
0X04,0X00,0X04,0X1C,0X1C,0X10,0X10,0X0C,0X1C,0X14,0X00,0X14,0X00,0X9C,0X1C,0X40,
0X14,0XA4,0X1C,0X1C,0X4C,0X04,0X22,0X21,0X90,0X50,0X08,0X44,0XA2,0X01,0X50,0X84,
0X00,0X03,0X08,0X04,0X84,0X90,0XC0,0X62,0X30,0X1C,0X0F,0X07,0X01,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X01,0X03,0X02,0X06,0X04,0X05,0X08,0X09,0X11,0X12,0X10,
0X21,0X28,0X26,0X40,0X58,0X45,0X42,0X90,0XB8,0X80,0X84,0X08,0X01,0X25,0X09,0X41,
0X31,0X08,0X0A,0X1A,0X22,0X02,0X02,0X70,0X00,0X00,0X70,0X00,0X20,0X00,0X00,0X10,
0XA0,0X00,0X10,0X42,0X0A,0X02,0X32,0X42,0X30,0X51,0X05,0X09,0X11,0X39,0X18,0X80,
0X80,0X86,0X88,0X04,0X50,0X41,0X42,0X26,0X20,0X24,0X10,0X11,0X10,0X08,0X09,0X0C,
0X04,0X06,0X02,0X03,0X01,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,0X01,0X01,0X01,
0X01,0X01,0X00,0X00,0X00,0X02,0X02,0X02,0X02,0X02,0X02,0X02,0X02,0X02,0X02,0X02,
0X02,0X02,0X02,0X02,0X02,0X02,0X00,0X00,0X01,0X01,0X01,0X01,0X01,0X01,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X10,0XF0,0X90,0X90,0X96,0XFC,0XF4,0XD0,0X58,0XFC,0XAC,
0XAC,0X80,0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X80,0XC0,0X00,0X00,0X88,0XF8,0XF8,
0X20,0XA0,0XE0,0XB0,0X30,0X10,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X20,0XE0,
0XF0,0XD0,0XD8,0XA8,0XE0,0X60,0X00,0XF8,0XF8,0X08,0X80,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X80,0X80,0X80,0XF8,0XF8,0X20,0XA0,0XC0,0XC0,0X60,0X38,0XA8,0X98,
0X90,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0XF8,0XF8,0XB0,0X80,0XC0,0X40,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X14,0X3C,0X38,0XB0,0XAC,0X9C,0X3E,0X7E,0XD4,0XE4,0X74,0X5C,0X0E,0X0C,0X04,
0X00,0X04,0X04,0X04,0X16,0X12,0X1A,0X1B,0X0B,0X04,0XFF,0XFF,0X6F,0X06,0X05,0X05,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,0X03,0X03,0X01,0X20,0X7F,0X7F,
0X01,0X01,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,0X09,0X0D,0X0D,0X3E,
0X3F,0X01,0X02,0X00,0X0D,0X0D,0X04,0X7F,0X7F,0X01,0X01,0X01,0X00,0X00,0X00,0X00,
0X00,0X00,0X09,0X09,0X0C,0X24,0X3F,0X03,0X01,0X10,0X10,0X13,0X0D,0X0D,0X1F,0X3B,
0X11,0X10,0X10,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X04,0X04,0X16,0X16,0X1A,0X0F,
0X07,0X01,0X02,0X04,0X0C,0X18,0X18,0X18,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X08,0X08,0X18,0X0C,0X04,0X04,0X42,0X42,0X7F,0X7D,0X01,0X03,0X01,0X01,0X00,0X00,
};




/*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/
 u32 fontaddr = 0;
//LCD_LineMsg LCD_LineStr[8];
// extern OS_Q LCD_MSG_Q;

/*LCD GPIO 初始化*/
void  LCD_GPIO_Config()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef  SPI_InitStructure;
	
	//初始化LCD的各种配置
	
	/* 时能各引脚IO时钟 */
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE);
	//RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOD, ENABLE);
	
	/* 配置SCK引脚 */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = SPI2_SCK_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SPI2_SCK_PORT, &GPIO_InitStructure);
	
	/* 配置MISO引脚 */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = SPI2_MISO_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SPI2_MISO_PORT, &GPIO_InitStructure);

	/* 配置MOSI引脚 */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = SPI2_MOSI_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SPI2_MOSI_PORT, &GPIO_InitStructure);


	/* 配置SPI_CS引脚 */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = IC_CS_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(IC_CS_PORT, &GPIO_InitStructure);
	
	/* 配置LCD_CS引脚 */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = LCD_CS_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LCD_CS_PORT, &GPIO_InitStructure);	
	
	/* 配置LCD_RESET引脚 */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = LCD_RESET_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LCD_RESET_PORT, &GPIO_InitStructure);	
	
	/* 配置LCD_RS引脚 */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = LCD_RS_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(LCD_RS_PORT, &GPIO_InitStructure);	
		
	//配置SPI通信接口
	
	/* 释放LCD */
	LCD_CS_HIGH();
	
	/* 使能SPI2时钟 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
	
	/* 连接SPI1管脚 */
// 	GPIO_PinAFConfig(SPI1_SCK_PORT, SPI1_SCK_SOURCE, GPIO_AF_SPI1);
// 	GPIO_PinAFConfig(SPI1_MISO_PORT, SPI1_MISO_SOURCE, GPIO_AF_SPI1);
// 	GPIO_PinAFConfig(SPI1_MOSI_PORT, SPI1_MOSI_SOURCE, GPIO_AF_SPI1);
	
	/* SPI2 配置 */
	SPI_I2S_DeInit(SPI2);
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	
	/* 初始化SPI2 */
	SPI_Init(SPI2, &SPI_InitStructure);
	
	/* 使能SPI2 */
	SPI_Cmd(SPI2, ENABLE);
}

void Delay(u32 t)
{
	while(t--);
}

void HardSPI2_WriteCommendByte(u8 cmd)
{
	LCD_RS_LOW();

	/*!< 写指令*/
	LCD_CS_LOW();
	//Delay(10);
	
	/*!< Loop while DR register in not emplty */
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);

	/*!< Send byte through the SPI1 peripheral */
	SPI_I2S_SendData(SPI2, cmd);
	
	/*!< Wait to receive a byte */
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);

	/*!< Receive the byte read from the SPI bus */
	SPI_I2S_ReceiveData(SPI2);

	//Delay(10);
	/*!< 释放lis302dl */
	//Delay(1000);
	LCD_CS_HIGH();
}

void HardSPI2_WriteDataByte(u8 data)
{
	LCD_RS_HIGH();

	/*!< 写数据*/
	LCD_CS_LOW();
	//Delay(10);
	
	/*!< Loop while DR register in not emplty */
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);

	/*!< Send byte through the SPI1 peripheral */
	SPI_I2S_SendData(SPI2, data);
	
	/*!< Wait to receive a byte */
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);

	/*!< Receive the byte read from the SPI bus */
	SPI_I2S_ReceiveData(SPI2);

	//Delay(10);
	/*!< 释放lis302dl */
	//Delay(100);
	LCD_CS_HIGH();
}

/*LCD模块初始化*/
void LCD_Init()
{
//	u32 i;
	
	LCD_GPIO_Config();
	
	LCD_CS_LOW();
	LCD_CS_HIGH();
	LCD_RESET_LOW();
	Delay(100);
	LCD_RESET_HIGH();
	Delay(100);
	HardSPI2_WriteCommendByte(0xe2);	/*软复位*/
	Delay(50);
	HardSPI2_WriteCommendByte(0x2c); /*升压步骤1*/
	Delay(50);
	HardSPI2_WriteCommendByte(0x2e); /*升压步骤2*/
	Delay(50);
	HardSPI2_WriteCommendByte(0x2f); /*升压步骤3*/
	Delay(50);
	HardSPI2_WriteCommendByte(0x24); /*粗调对比度，可设范围0x23-0x27*/
	HardSPI2_WriteCommendByte(0x81); /*微调对比度*/
	HardSPI2_WriteCommendByte(0x1a); /*0x1a,微调对比度的值，可设范围0x00-0x3f*/
	HardSPI2_WriteCommendByte(0xa2); /*1/9偏压比*/
	HardSPI2_WriteCommendByte(0xc8); /*行扫描顺序：从上到下*/
	HardSPI2_WriteCommendByte(0xa0); /*列扫描顺序：从左到右*/
	HardSPI2_WriteCommendByte(0x60);
	HardSPI2_WriteCommendByte(0xaf);
	LCD_CS_HIGH();
	
	//for(i = 0; i < 8; i++)
	//	LCD_LineStr[i].line_num = i+1;
	
}

/*全屏清屏*/
void clear_screen()
{
	u8 i,j;
	LCD_CS_LOW();
	LCD_CS_HIGH();
	for(i=0; i<9; i++)
	{

		HardSPI2_WriteCommendByte(0xb0 + i);
		HardSPI2_WriteCommendByte(0x10);
		HardSPI2_WriteCommendByte(0x00);
		for(j=0; j<132; j++)
		{
			HardSPI2_WriteDataByte(0x00);
		}
	}
	LCD_CS_HIGH();
}
/* 显示图像 */
void display_photo(unsigned char *photo)
{
	u8 i,j;
	u8 page_address;
	u8 column_address_L, column_address_H;
	

	
	LCD_CS_LOW();
	LCD_CS_HIGH();
	for(i=0; i<8; i++)
	{
		page_address=i;
		if(page_address<4)
		{
			page_address+=4;
		}
		else
		{
			page_address-=4;
		}
		HardSPI2_WriteCommendByte(0xb0 + page_address);
		HardSPI2_WriteCommendByte(0x10);
		HardSPI2_WriteCommendByte(0x00);
		for(j=0; j<128; j++)
		{
			HardSPI2_WriteDataByte(photo[i*128+j]);
// // 				HardSPI2_WriteDataByte(0xf1);
// 			HardSPI2_WriteDataByte(*photo);
// 			photo+=8;
		}
	}
	LCD_CS_HIGH();
}
/*显示16x16点阵图像、汉字、生僻字或16x16点阵的其他图标*/
void display_graphic_16x16(u16 page,u16 column,u8 *dp)
{
	u8 i,j;
	u8 page_address;
	u8 column_address_L, column_address_H;
	
	page_address = 0xb0 + page - 1;
	column_address_L = column&0x0f;
	column_address_H = ((column>>4)&0x0f) + 0x10;
	LCD_CS_LOW();
	LCD_CS_HIGH();
	
	for(j=0; j<2; j++)
	{
		HardSPI2_WriteCommendByte(page_address+j);
		HardSPI2_WriteCommendByte(column_address_H);
		HardSPI2_WriteCommendByte(column_address_L);
		for(i=0; i<16; i++)
		{
			HardSPI2_WriteDataByte(*dp);
			dp++;
		}
	}
	LCD_CS_HIGH();
}

/*显示8x16点阵图像、ASCII, 或8x16点阵的自造字符、其他图标*/
void display_graphic_8x16(u16 page, u8 column, u8 *dp)
{
	u16 i,j;
	u8 page_address;
	u8 column_address_L, column_address_H;
	LCD_CS_LOW();
	page_address = 0xb0+page-1;
	column_address_L = column&0x0f;
	column_address_H = ((column>>4)&0x0f)+0x10;
	
	for(j=0; j<2; j++)
	{
		HardSPI2_WriteCommendByte(page_address+j);
		HardSPI2_WriteCommendByte(column_address_H);
		HardSPI2_WriteCommendByte(column_address_L);
		for(i=0; i<8; i++)
		{
			HardSPI2_WriteDataByte(*dp);
			dp++;
		}
	}
	LCD_CS_HIGH();
}	

/*显示5x7点阵图像、ASCII，或5x7点阵的自造字符、其他图标*/
void display_graphic_5x7(u16 page,u8 column, u8 *dp)
{
	u16 col_cnt;
	u8 page_address;
	u8 column_address_L, column_address_H;
	page_address = 0xb0+page-1;
	
	LCD_CS_HIGH();
	
	column_address_L = column&0x0f;
	column_address_H = ((column>>4)&0x0f)+0x10;
	
	HardSPI2_WriteCommendByte(page_address);
	HardSPI2_WriteCommendByte(column_address_H);
	HardSPI2_WriteCommendByte(column_address_L);
	for(col_cnt=0; col_cnt<8; col_cnt++)
	{
		HardSPI2_WriteDataByte(*dp);
		dp++;
	}
	LCD_CS_HIGH();
}

/*送指令到字库IC*/
void send_command_to_ROM(u8 datau)
{
	/*!< 写指令*/
	/*!< Loop while DR register in not emplty */
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);

	/*!< Send byte through the SPI1 peripheral */
	SPI_I2S_SendData(SPI2, datau);
	
	/*!< Wait to receive a byte */
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);

	/*!< Receive the byte read from the SPI bus */
	SPI_I2S_ReceiveData(SPI2);

	Delay(100);
	/*!< 释放lis302dl */
}

/*从字库IC中取汉字或字符数据（1个字节）*/
static u8 get_data_from_ROM(void)
{
	u8 rdata;
	SPI2_SCK_HIGH();

	Delay(100);
	
	/*!< Loop while DR register in not emplty */
//	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	/*!< Send the command through the SPI1 peripheral */
	//SPI_I2S_SendData(SPI1, cmd);
	
	
	/*!< Wait to receive a byte */
//	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
	/*!< Receive the byte read from the SPI bus */
//	rdata =  SPI_I2S_ReceiveData(SPI1);
	SPI2_SCK_LOW();
	/*!< Loop while DR register in not emplty */
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);
	/*!< Send a dummy byte through the SPI2 peripheral */
	SPI_I2S_SendData(SPI2, 0xff);

	/*!< Wait to receive a byte */
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);
	/*!< Receive the byte read from the SPI bus */
	rdata =  SPI_I2S_ReceiveData(SPI2);
	
	/*!< 释放lis302dl */
	Delay(100);
	SPI2_SCK_HIGH();
	
	return rdata;
}

/*从相关地址(addrHigh: 地址高8位,assrLow: 地址8位,共24位)中连续读出Dantalen个字节的数据到pBuff的地址*/
/*连续读取*/
void get_n_bytes_data_from_ROM(u8 addrHigh,u8 addrMid, u8 addrLow,u8 *pBuff,u8 DataLen)
{
	u8 i;
	IC_CS_LOW();
	LCD_CS_HIGH();
	SPI2_SCK_LOW();
	send_command_to_ROM(0x03);
	send_command_to_ROM(addrHigh);
	send_command_to_ROM(addrMid);
	send_command_to_ROM(addrLow);
	for(i=0; i<DataLen; i++)
	{
		*(pBuff + i) = get_data_from_ROM();
	} 
	IC_CS_HIGH();
}
/* 显示中文字符 */
void display_GB2312_string(u8 y, u8 x, u8 *text)
{
	u8 i = 0;
	u8 addrHigh, addrMid, addrLow;
	u8 fontbuf[32];
	while((text[i] > 0x00))
	{
		if(((text[i]>=0xb0)&&(text[i]<0xf7))&&(text[i+1]>=0xa1))
		{
			fontaddr = (u32)(((text[i]-0xb0)*94 + (text[i+1]-0xa1)+846)*32);
			
			addrHigh = (fontaddr&0xff0000)>>16;
			addrMid = (fontaddr&0xff00)>>8;
			addrLow = fontaddr&0xff;
			get_n_bytes_data_from_ROM(addrHigh, addrMid, addrLow, fontbuf, 32);
	    if(y<5)
			{
				display_graphic_16x16(y+4,x,fontbuf);
			}
			else
			{
				display_graphic_16x16((y-4),x,fontbuf);
			}			
			i+=2;
			x+=16;
		}
		else if((text[i]>=0x20)&&(text[i]<=0x7e))
		{
			u8 fontbuf[16];
			fontaddr = (u32)((text[i]-0x20)*16 + 0x3b7c0);
			addrHigh = (fontaddr&0xff0000)>>16;
			addrMid = (fontaddr&0xff00)>>8;
			addrLow = fontaddr&0xff;
			get_n_bytes_data_from_ROM(addrHigh, addrMid, addrLow, fontbuf, 16);
		 if(y<5)
			{
				display_graphic_8x16(y+4,x,fontbuf);
			}
			else
			{
				display_graphic_8x16((y-4),x,fontbuf);
			}
			
			i+=1;
			x+=8;
		}
		else
			i++;
	}
}
/* 显示5×7大小的英文字符 */
void display_string_5x7(u8 y, u8 x, u8 *text)
{
	u8 i = 0;
	u8 addrHigh, addrMid, addrLow;
	while((text[i]>0x00))
	{
		if((text[i]>=0x20)&&(text[i]<=0x7e))
		{
			u8 fontbuf[8];
			fontaddr = (text[i]-0x20);
			fontaddr = (u32)(fontaddr*8);
			fontaddr = (u32)(fontaddr+0x3bfc0);
			addrHigh = (fontaddr&0xff0000)>>16;
			addrMid = (fontaddr&0xff00)>>8;
			addrLow = fontaddr&0xff;
			get_n_bytes_data_from_ROM(addrHigh, addrMid, addrLow, fontbuf,8);
			if(y<5)
			{
				display_graphic_5x7(y+4,x,fontbuf);
			}
			else
			{
				display_graphic_5x7((y-4),x,fontbuf);
			}
			i+=1;
			x+=8;
		}
		else
			i++;
	}
}


