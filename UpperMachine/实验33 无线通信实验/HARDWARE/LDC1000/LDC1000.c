#include "LDC1000.h"
#include "spi.h"
//SPIд�Ĵ���
//reg:ָ���Ĵ�����ַ
//value:д���ֵ
u8 LDC_Write_Reg(u8 add,u8 value)
{
  u8 status;	
  GPIO_ResetBits(GPIOG,GPIO_Pin_5);                //ʹ��SPI����
  status =SPI2_ReadWriteByte(add);//���ͼĴ����� 
  SPI2_ReadWriteByte(value);      //д��Ĵ�����ֵ
  GPIO_SetBits(GPIOG,GPIO_Pin_5);                //��ֹSPI����	 
	
  return(status);       			//����״ֵ̬
}

u8 LDC_Read_Reg(u8 add)
{
  u8 val;
  GPIO_ResetBits(GPIOG,GPIO_Pin_5);                //ʹ��SPI����
  SPI2_ReadWriteByte(add|0x80);                   //���ͼĴ����� 
	val=SPI2_ReadWriteByte(0XFF);
  GPIO_SetBits(GPIOG,GPIO_Pin_5);                  //��ֹSPI����	 
  
  return val;
}


/********************************************************************
 * @brief:		LDC1000��ʼ������,ps:һ�η�����16λ������
 * 				????????????????????????
 * @param:		none
 * @return:		none
 *********************************************************************/
void LDC1000_init(void)
{

	LDC_Write_Reg(LDC1000_CMD_RPMAX,0x13);					//����Rp_MAX(0x01)�Ĵ���
	LDC_Write_Reg(LDC1000_CMD_RPMIN,0x38);					//����Rp_MIN(0x02)�Ĵ���
	LDC_Write_Reg(LDC1000_CMD_SENSORFREQ,0x94);						//����Sensor Frequency(0x03)�Ĵ���
	LDC_Write_Reg(LDC1000_CMD_LDCCONFIG,0x17);						//����LDC Configuration(0x04)�Ĵ���
	LDC_Write_Reg(LDC1000_CMD_CLKCONFIG,0x00);							//����Clock Configuration(0x05)�Ĵ���
																		//����TBCLK��Ϊʱ��Դ

	LDC_Write_Reg(LDC1000_CMD_INTCONFIG,0x01);							//����INTB Pin Configuration(0x0A),
																		//����INTBΪ�Ƚ������־λ(status of Comparator output)

	LDC_Write_Reg(LDC1000_CMD_THRESHILSB,0x50);						//����Comparator Threshold High(0x06)�Ĵ�����8λ
	LDC_Write_Reg(LDC1000_CMD_THRESHIMSB,0x14);						//����Comparator Threshold High(0x07)�Ĵ�����8λ
	LDC_Write_Reg(LDC1000_CMD_THRESLOLSB,0xC0);						//����Comparator Threshold Low(0x08)�Ĵ�����8λ
	LDC_Write_Reg(LDC1000_CMD_THRESLOMSB,0x12);						//����Comparator Threshold Low(0x09)�Ĵ�����8λ
	LDC_Write_Reg(LDC1000_CMD_PWRCONFIG,0x01);							//����Power Configuration(0x0B)�Ĵ���
																		//ΪActive Mode,ʹ��ת��
}




