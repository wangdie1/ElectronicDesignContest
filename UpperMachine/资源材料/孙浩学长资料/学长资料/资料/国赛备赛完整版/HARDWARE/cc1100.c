#include "cc1100.h"
#include<stm32f10x.h>
//功率参数表
u8 PaTabel[8] = {0xc0,0xc0,0xc0,0xc0,0xc0,0xc0,0xc0,0xc0};

const RF_SETTINGS rfSettings = {
    0x29,  // IOCFG2              GDO2 Output Pin Configuration
    0x2E,  // IOCFG1              GDO1 Output Pin Configuration
    0x06,  // IOCFG0              GDO0 Output Pin Configuration
    0x07,  // FIFOTHR             RX FIFO and TX FIFO Thresholds
    0xD3,  // SYNC1               Sync Word, High Byte
    0x91,  // SYNC0               Sync Word, Low Byte
    0xFF,  // PKTLEN              Packet Length
    0x05,  // PKTCTRL1            Packet Automation Control
    0x05,  // PKTCTRL0            Packet Automation Control
    0x00,  // ADDR                Device Address
    0x02,  // CHANNR              Channel Number
    0x06,  // FSCTRL1             Frequency Synthesizer Control
    0x00,  // FSCTRL0             Frequency Synthesizer Control
    0x10,  // FREQ2               Frequency Control Word, High Byte
    0xA7,  // FREQ1               Frequency Control Word, Middle Byte
    0x62,  // FREQ0               Frequency Control Word, Low Byte
    0xF5,  // MDMCFG4             Modem Configuration
    0x83,  // MDMCFG3             Modem Configuration
    0x13,  // MDMCFG2             Modem Configuration
    0x22,  // MDMCFG1             Modem Configuration
    0xF8,  // MDMCFG0             Modem Configuration
    0x15,  // DEVIATN             Modem Deviation Setting
    0x07,  // MCSM2               Main Radio Control State Machine Configuration
    0x30,  // MCSM1               Main Radio Control State Machine Configuration
    0x18,  // MCSM0               Main Radio Control State Machine Configuration
    0x16,  // FOCCFG              Frequency Offset Compensation Configuration
    0x6C,  // BSCFG               Bit Synchronization Configuration
    0x03,  // AGCCTRL2            AGC Control
    0x40,  // AGCCTRL1            AGC Control
    0x91,  // AGCCTRL0            AGC Control
    0x87,  // WOREVT1             High Byte Event0 Timeout
    0x6B,  // WOREVT0             Low Byte Event0 Timeout
    0xFB,  // WORCTRL             Wake On Radio Control
    0x56,  // FREND1              Front End RX Configuration
    0x10,  // FREND0              Front End TX Configuration
    0xE9,  // FSCAL3              Frequency Synthesizer Calibration
    0x2A,  // FSCAL2              Frequency Synthesizer Calibration
    0x00,  // FSCAL1              Frequency Synthesizer Calibration
    0x1F,  // FSCAL0              Frequency Synthesizer Calibration
    0x41,  // RCCTRL1             RC Oscillator Configuration
    0x00,  // RCCTRL0             RC Oscillator Configuration
    0x59,  // FSTEST              Frequency Synthesizer Calibration Control
    0x7F,  // PTEST               Production Test
    0x3F,  // AGCTEST             AGC Test
    0x81,  // TEST2               Various Test Settings
    0x35,  // TEST1               Various Test Settings
    0x09,  // TEST0               Various Test Settings
    0x00,  // PARTNUM             Chip ID
    0x04,  // VERSION             Chip ID
    0x00,  // FREQEST             Frequency Offset Estimate from Demodulator
    0x00,  // LQI                 Demodulator Estimate for Link Quality
    0x00,  // RSSI                Received Signal Strength Indication
    0x00,  // MARCSTATE           Main Radio Control State Machine State
    0x00,  // WORTIME1            High Byte of WOR Time
    0x00,  // WORTIME0            Low Byte of WOR Time
    0x00,  // PKTSTATUS           Current GDOx Status and Packet Status
    0x00,  // VCO_VC_DAC          Current Setting from PLL Calibration Module
    0x00,  // TXBYTES             Underflow and Number of Bytes
    0x00,  // RXBYTES             Overflow and Number of Bytes
    0x00,  // RCCTRL1_STATUS      Last RC Oscillator Calibration Result
    0x00,  // RCCTRL0_STATUS      Last RC Oscillator Calibration Result
};

u16 CC1100_WriteReg(u8 Addr,u8 Data)
{
	u16 Temp;
	CS1_Low();
	Temp = SPI1_SendReadByte(Addr & 0x7f);
	Temp <<= 8;
	Temp += SPI1_SendReadByte(Data);
	CS1_High();
	return Temp;
}

u16 CC1100_ReadReg(u8 Addr)
{
	u16 Temp;
	CS1_Low();
	while(MISO);
	Temp = SPI1_SendReadByte(Addr | 0x80);
	Temp <<= 8;
	Temp += SPI1_SendReadByte(0x00);
	CS1_High();
	return Temp;
}

void CC1100_PowerUpReset(void)
{
	u8 i;
	CS1_High();
	for(i = 0;i < 0xff;i++);
	CS1_Low();
	for(i = 0;i < 0xff;i++);
	CS1_High();
	for(i = 0;i < 0xff;i++);
	CC1100_Reset();

	CC1100_WriteSettings();		//配置寄存器
	CC1100_SetTransPower();		//设置发送功率
}

void CC1100_Reset(void)
{
	CS1_Low();
	while(MISO);
	SPI1_SendReadByte(0x30);
	while(MISO);
	CS1_High();
}

void CC1100_SendCommand(u8 Command)
{
	CS1_Low();
	while(MISO);
	SPI1_SendReadByte(Command);
	CS1_High();
}

void CC1100_WriteSettings(void) 
{
		CC1100_WriteReg(CCxxx0_FSCTRL0,  0x00);		//不添加此句将无法修改CCxxx0_FSCTRL1寄存器中的内容
		CC1100_WriteReg(CCxxx0_FSCTRL1,  rfSettings.FSCTRL1);
    CC1100_WriteReg(CCxxx0_FSCTRL0,  rfSettings.FSCTRL0);
    CC1100_WriteReg(CCxxx0_FREQ2,    rfSettings.FREQ2);
    CC1100_WriteReg(CCxxx0_FREQ1,    rfSettings.FREQ1);
    CC1100_WriteReg(CCxxx0_FREQ0,    rfSettings.FREQ0);
    CC1100_WriteReg(CCxxx0_MDMCFG4,  rfSettings.MDMCFG4);
    CC1100_WriteReg(CCxxx0_MDMCFG3,  rfSettings.MDMCFG3);
    CC1100_WriteReg(CCxxx0_MDMCFG2,  rfSettings.MDMCFG2);
    CC1100_WriteReg(CCxxx0_MDMCFG1,  rfSettings.MDMCFG1);
    CC1100_WriteReg(CCxxx0_MDMCFG0,  rfSettings.MDMCFG0);
    CC1100_WriteReg(CCxxx0_CHANNR,   rfSettings.CHANNR);
    CC1100_WriteReg(CCxxx0_DEVIATN,  rfSettings.DEVIATN);
    CC1100_WriteReg(CCxxx0_FREND1,   rfSettings.FREND1);
    CC1100_WriteReg(CCxxx0_FREND0,   rfSettings.FREND0);
    CC1100_WriteReg(CCxxx0_MCSM0 ,   rfSettings.MCSM0 );
    CC1100_WriteReg(CCxxx0_FOCCFG,   rfSettings.FOCCFG);
    CC1100_WriteReg(CCxxx0_BSCFG,    rfSettings.BSCFG);
    CC1100_WriteReg(CCxxx0_AGCCTRL2, rfSettings.AGCCTRL2);
		CC1100_WriteReg(CCxxx0_AGCCTRL1, rfSettings.AGCCTRL1);
    CC1100_WriteReg(CCxxx0_AGCCTRL0, rfSettings.AGCCTRL0);
    CC1100_WriteReg(CCxxx0_FSCAL3,   rfSettings.FSCAL3);
		CC1100_WriteReg(CCxxx0_FSCAL2,   rfSettings.FSCAL2);
		CC1100_WriteReg(CCxxx0_FSCAL1,   rfSettings.FSCAL1);
    CC1100_WriteReg(CCxxx0_FSCAL0,   rfSettings.FSCAL0);
    CC1100_WriteReg(CCxxx0_FSTEST,   rfSettings.FSTEST);
    CC1100_WriteReg(CCxxx0_TEST2,    rfSettings.TEST2);
    CC1100_WriteReg(CCxxx0_TEST1,    rfSettings.TEST1);
    CC1100_WriteReg(CCxxx0_TEST0,    rfSettings.TEST0);
    CC1100_WriteReg(CCxxx0_IOCFG2,   rfSettings.IOCFG2);
    CC1100_WriteReg(CCxxx0_IOCFG0,   rfSettings.IOCFG0);    
    CC1100_WriteReg(CCxxx0_PKTCTRL1, rfSettings.PKTCTRL1);
    CC1100_WriteReg(CCxxx0_PKTCTRL0, rfSettings.PKTCTRL0);
    CC1100_WriteReg(CCxxx0_ADDR,     rfSettings.ADDR);
    CC1100_WriteReg(CCxxx0_PKTLEN,   rfSettings.PKTLEN);
}
//SPI读状态寄存器
u16 CC1100_ReadRegStatus(u8 Addr)
{
	u16 Temp;
	CS1_Low();
	while(MISO);
	Temp = SPI1_SendReadByte(Addr | 0xc0);
	Temp <<= 8;
	Temp += SPI1_SendReadByte(0x00);
	CS1_High();
	return Temp;
}
//突发写寄存器
void CC1100_WriteRegBurst(u8 Addr_Start,u8 *Buffer,u8 Lenght)
{
	u8 i,Temp;
	Temp = Addr_Start | 0x40;	//突发访问位
	CS1_Low();
	while(MISO);
	SPI1_SendReadByte(Temp);
	for(i = 0;i < Lenght;i++)
	SPI1_SendReadByte(*(Buffer + i));
	CS1_High();
}

//突发读寄存器
void CC1100_ReadRegBurst(u8 Addr_Start,u8 *Buffer,u8 Lenght)
{
	u8 i,Temp;
	Temp = Addr_Start | 0xc0;	//突发访问位
	CS1_Low();
	while(MISO);
	SPI1_SendReadByte(Temp);
	for(i = 0;i < Lenght;i++)
		*(Buffer + i) = SPI1_SendReadByte(Temp);
	CS1_High();
}

//修改发射功率
void CC1100_SetTransPower(void)
{
	CC1100_WriteRegBurst(CCxxx0_PATABLE,PaTabel,8);
}

//发送数据包
void CC1100_SendPacket(u8 *Buffer,u8 Lenght)
{
//	int i;
	CC1100_WriteReg(CCxxx0_TXFIFO,Lenght);
	CC1100_WriteRegBurst(CCxxx0_TXFIFO,&(*Buffer),Lenght);

	CC1100_SendCommand(CCxxx0_STX);
	while(!GDO0);
	while(GDO0);
	CC1100_SendCommand(CCxxx0_SFTX); 	//清洗发送缓存区
	
//	for(i = 0;i < 50000;i++);
}

u16 CC1100_RecevicePacket(u8 *Buffer,u8 *Length)
{
	u8 status[2];
	u8 packetLength;
	u8 i=(*Length)*4;// 具体多少要根据datarate和length来决定
	CC1100_SendCommand(CCxxx0_SRX);//进入接收状态
	delay_us(10);
	while(GDO0)
	{
		delay_us(10);
		--i;
		if(i<1)
			return 0;
	}
	if((CC1100_ReadRegStatus(CCxxx0_RXBYTES)&0x7f))//如果接的字节数不为0
	{
		packetLength=CC1100_ReadReg(CCxxx0_RXFIFO);//读出第一个字节，此字节为该帧数据长度
		if(packetLength<=*Length)//如果所要的有效数据长度小于等于接收到的数据包的长度
		{
			CC1100_ReadRegBurst(CCxxx0_RXFIFO,Buffer,packetLength);//读出所有接收到的数据
			*Length = packetLength;//把接收数据长度的修改为当前数据的长度
			CC1100_ReadRegBurst(CCxxx0_RXFIFO,status,2);//读出CRC校验位
			CC1100_SendCommand(CCxxx0_SFRX);//清洗接收缓冲区
			return (status[1]&0x80);//如果校验成功返回接收成功
		}
		else
		{
			*Length = packetLength;
       CC1100_SendCommand(CCxxx0_SFRX);		//清洗接收缓冲区
       return 0;
		}	
	}
	else
		return 0;
}
void GPIO_Configuration(void)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}
void CC1100_Init(void)
{
	GPIO_Configuration();
	CC1100_PowerUpReset();
	CC1100_WriteSettings();
	CC1100_SetTransPower();
}

// int main()
// {
// 		SYS_CONFIG();
	/*无线传输CC1100*/
 /*	u8 TxBuf[8]={0};
	u8 RxBuf[8]={0};
	u8 leng =8;
	TxBuf[1] = 1 ;
	TxBuf[2] = 1 ;
// 	


while(1)
{
// 	CC1100_SendPacket(TxBuf,8);	// Transmit Tx buffer data
// 	delay_us(6000);
// 	printf("发送的数据 %d",TxBuf[1]);
// 	while(1)
// 	{
// 		CC1100_RecevicePacket(RxBuf,&leng);
// 			printf("返回数据 %d",RxBuf);
// 	}
	if(CC1100_RecevicePacket(RxBuf,&leng))
	{
		printf("收到的数据 %d",RxBuf[1]);
		if(RxBuf[1]==1)
		{
			GPIO_SetBits(GPIOC,GPIO_Pin_7);
			CC1100_SendPacket(TxBuf,8);
		}
		if(RxBuf[2]==1)
		{
			GPIO_SetBits(GPIOC,GPIO_Pin_8);	
		}
		while(1);
	}*/
	/*无线传输CC1100*/
// 	

