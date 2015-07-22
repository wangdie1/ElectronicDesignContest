#include "LDC1000.h"
#include "spi.h"
//SPI写寄存器
//reg:指定寄存器地址
//value:写入的值
u8 LDC_Write_Reg(u8 add,u8 value)
{
  u8 status;	
  GPIO_ResetBits(GPIOG,GPIO_Pin_5);                //使能SPI传输
  status =SPI2_ReadWriteByte(add);//发送寄存器号 
  SPI2_ReadWriteByte(value);      //写入寄存器的值
  GPIO_SetBits(GPIOG,GPIO_Pin_5);                //禁止SPI传输	 
	
  return(status);       			//返回状态值
}

u8 LDC_Read_Reg(u8 add)
{
  u8 val;
  GPIO_ResetBits(GPIOG,GPIO_Pin_5);                //使能SPI传输
  SPI2_ReadWriteByte(add|0x80);                   //发送寄存器号 
	val=SPI2_ReadWriteByte(0XFF);
  GPIO_SetBits(GPIOG,GPIO_Pin_5);                  //禁止SPI传输	 
  
  return val;
}


/********************************************************************
 * @brief:		LDC1000初始化配置,ps:一次发送了16位的数据
 * 				????????????????????????
 * @param:		none
 * @return:		none
 *********************************************************************/
void LDC1000_init(void)
{

	LDC_Write_Reg(LDC1000_CMD_RPMAX,0x13);					//配置Rp_MAX(0x01)寄存器
	LDC_Write_Reg(LDC1000_CMD_RPMIN,0x38);					//配置Rp_MIN(0x02)寄存器
	LDC_Write_Reg(LDC1000_CMD_SENSORFREQ,0x94);						//配置Sensor Frequency(0x03)寄存器
	LDC_Write_Reg(LDC1000_CMD_LDCCONFIG,0x17);						//配置LDC Configuration(0x04)寄存器
	LDC_Write_Reg(LDC1000_CMD_CLKCONFIG,0x00);							//配置Clock Configuration(0x05)寄存器
																		//配置TBCLK作为时钟源

	LDC_Write_Reg(LDC1000_CMD_INTCONFIG,0x01);							//配置INTB Pin Configuration(0x0A),
																		//配置INTB为比较输出标志位(status of Comparator output)

	LDC_Write_Reg(LDC1000_CMD_THRESHILSB,0x50);						//配置Comparator Threshold High(0x06)寄存器低8位
	LDC_Write_Reg(LDC1000_CMD_THRESHIMSB,0x14);						//配置Comparator Threshold High(0x07)寄存器高8位
	LDC_Write_Reg(LDC1000_CMD_THRESLOLSB,0xC0);						//配置Comparator Threshold Low(0x08)寄存器低8位
	LDC_Write_Reg(LDC1000_CMD_THRESLOMSB,0x12);						//配置Comparator Threshold Low(0x09)寄存器高8位
	LDC_Write_Reg(LDC1000_CMD_PWRCONFIG,0x01);							//配置Power Configuration(0x0B)寄存器
																		//为Active Mode,使能转化
}




