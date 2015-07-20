//首先添加spi初始化

#ifndef _cc1100_h_
#define _cc1100_h_

#include "spi.h"

// #define 	WRITE_BURST     	0x40						//连续写入
// #define 	READ_SINGLE     	0x80						//读
// #define 	READ_BURST      	0xC0						//连续读
// #define 	BYTES_IN_RXFIFO     0x7F  						//接收缓冲区的有效字节数
// #define 	CRC_OK              0x80 						//CRC校验通过位标志

#define MISO GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)
#define GDO0 GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_6)
#define GDO2 GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_7)

//↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓寄存器↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓//
//配置寄存器
#define CCxxx0_IOCFG2       0x00        // GDO2 output pin configuration
#define CCxxx0_IOCFG1       0x01        // GDO1 output pin configuration
#define CCxxx0_IOCFG0       0x02        // GDO0 output pin configuration
#define CCxxx0_FIFOTHR      0x03        // RX FIFO and TX FIFO thresholds
#define CCxxx0_SYNC1        0x04        // Sync word, high u8
#define CCxxx0_SYNC0        0x05        // Sync word, low u8
#define CCxxx0_PKTLEN       0x06        // Packet length
#define CCxxx0_PKTCTRL1     0x07        // Packet automation control
#define CCxxx0_PKTCTRL0     0x08        // Packet automation control
#define CCxxx0_ADDR         0x09        // Device address
#define CCxxx0_CHANNR       0x0A        // Channel number
#define CCxxx0_FSCTRL1      0x0B        // Frequency synthesizer control
#define CCxxx0_FSCTRL0      0x0C        // Frequency synthesizer control
#define CCxxx0_FREQ2        0x0D        // Frequency control word, high u8
#define CCxxx0_FREQ1        0x0E        // Frequency control word, middle u8
#define CCxxx0_FREQ0        0x0F        // Frequency control word, low u8
#define CCxxx0_MDMCFG4      0x10        // Modem configuration
#define CCxxx0_MDMCFG3      0x11        // Modem configuration
#define CCxxx0_MDMCFG2      0x12        // Modem configuration
#define CCxxx0_MDMCFG1      0x13        // Modem configuration
#define CCxxx0_MDMCFG0      0x14        // Modem configuration
#define CCxxx0_DEVIATN      0x15        // Modem deviation setting
#define CCxxx0_MCSM2        0x16        // Main Radio Control State Machine configuration
#define CCxxx0_MCSM1        0x17        // Main Radio Control State Machine configuration
#define CCxxx0_MCSM0        0x18        // Main Radio Control State Machine configuration
#define CCxxx0_FOCCFG       0x19        // Frequency Offset Compensation configuration
#define CCxxx0_BSCFG        0x1A        // Bit Synchronization configuration
#define CCxxx0_AGCCTRL2     0x1B        // AGC control
#define CCxxx0_AGCCTRL1     0x1C        // AGC control
#define CCxxx0_AGCCTRL0     0x1D        // AGC control
#define CCxxx0_WOREVT1      0x1E        // High u8 Event 0 timeout
#define CCxxx0_WOREVT0      0x1F        // Low u8 Event 0 timeout
#define CCxxx0_WORCTRL      0x20        // Wake On Radio control
#define CCxxx0_FREND1       0x21        // Front end RX configuration
#define CCxxx0_FREND0       0x22        // Front end TX configuration
#define CCxxx0_FSCAL3       0x23        // Frequency synthesizer calibration
#define CCxxx0_FSCAL2       0x24        // Frequency synthesizer calibration
#define CCxxx0_FSCAL1       0x25        // Frequency synthesizer calibration
#define CCxxx0_FSCAL0       0x26        // Frequency synthesizer calibration
#define CCxxx0_RCCTRL1      0x27        // RC oscillator configuration
#define CCxxx0_RCCTRL0      0x28        // RC oscillator configuration
#define CCxxx0_FSTEST       0x29        // Frequency synthesizer calibration control
#define CCxxx0_PTEST        0x2A        // Production test
#define CCxxx0_AGCTEST      0x2B        // AGC test
#define CCxxx0_TEST2        0x2C        // Various test settings
#define CCxxx0_TEST1        0x2D        // Various test settings
#define CCxxx0_TEST0        0x2E        // Various test settings

//命令滤波
#define CCxxx0_SRES         0x30        // Reset chip.
#define CCxxx0_SFSTXON      0x31        // Enable and calibrate frequency synthesizer (if MCSM0.FS_AUTOCAL=1).
                                        // If in RX/TX: Go to a wait state where only the synthesizer is
                                        // running (for quick RX / TX turnaround).
#define CCxxx0_SXOFF        0x32        // Turn off crystal oscillator.
#define CCxxx0_SCAL         0x33        // Calibrate frequency synthesizer and turn it off
                                        // (enables quick start).
#define CCxxx0_SRX          0x34        // Enable RX. Perform calibration first if coming from IDLE and
                                        // MCSM0.FS_AUTOCAL=1.
#define CCxxx0_STX          0x35        // In IDLE state: Enable TX. Perform calibration first if
                                        // MCSM0.FS_AUTOCAL=1. If in RX state and CCA is enabled:
                                        // Only go to TX if channel is clear.
#define CCxxx0_SIDLE        0x36        // Exit RX / TX, turn off frequency synthesizer and exit
                                        // Wake-On-Radio mode if applicable.
#define CCxxx0_SAFC         0x37        // Perform AFC adjustment of the frequency synthesizer
#define CCxxx0_SWOR         0x38        // Start automatic RX polling sequence (Wake-on-Radio)
#define CCxxx0_SPWD         0x39        // Enter power down mode when CSn goes high.
#define CCxxx0_SFRX         0x3A        // Flush the RX FIFO buffer.
#define CCxxx0_SFTX         0x3B        // Flush the TX FIFO buffer.
#define CCxxx0_SWORRST      0x3C        // Reset real time clock.
#define CCxxx0_SNOP         0x3D        // No operation. May be used to pad strobe commands to two
                                        // u8s for simpler software.
//状态寄存器
#define CCxxx0_PARTNUM      0x30
#define CCxxx0_VERSION      0x31
#define CCxxx0_FREQEST      0x32
#define CCxxx0_LQI          0x33
#define CCxxx0_RSSI         0x34
#define CCxxx0_MARCSTATE    0x35
#define CCxxx0_WORTIME1     0x36
#define CCxxx0_WORTIME0     0x37
#define CCxxx0_PKTSTATUS    0x38
#define CCxxx0_VCO_VC_DAC   0x39
#define CCxxx0_TXBYTES      0x3A
#define CCxxx0_RXBYTES      0x3B
//功率控制，发送，接收
#define CCxxx0_PATABLE      0x3E
#define CCxxx0_TXFIFO       0x3F
#define CCxxx0_RXFIFO       0x3F
//↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑//

typedef struct S_RF_SETTINGS{
    u8 IOCFG2;        //GDO2 Output Pin Configuration
    u8 IOCFG1;        //GDO1 Output Pin Configuration
    u8 IOCFG0;        //GDO0 Output Pin Configuration
    u8 FIFOTHR;       //RX FIFO and TX FIFO Thresholds
    u8 SYNC1;         //Sync Word, High Byte
    u8 SYNC0;         //Sync Word, Low Byte
    u8 PKTLEN;        //Packet Length
    u8 PKTCTRL1;      //Packet Automation Control
    u8 PKTCTRL0;      //Packet Automation Control
    u8 ADDR;          //Device Address
    u8 CHANNR;        //Channel Number
    u8 FSCTRL1;       //Frequency Synthesizer Control
    u8 FSCTRL0;       //Frequency Synthesizer Control
    u8 FREQ2;         //Frequency Control Word, High Byte
    u8 FREQ1;         //Frequency Control Word, Middle Byte
    u8 FREQ0;         //Frequency Control Word, Low Byte
    u8 MDMCFG4;       //Modem Configuration
    u8 MDMCFG3;       //Modem Configuration
    u8 MDMCFG2;       //Modem Configuration
    u8 MDMCFG1;       //Modem Configuration
    u8 MDMCFG0;       //Modem Configuration
    u8 DEVIATN;       //Modem Deviation Setting
    u8 MCSM2;         //Main Radio Control State Machine Configuration
    u8 MCSM1;         //Main Radio Control State Machine Configuration
    u8 MCSM0;         //Main Radio Control State Machine Configuration
    u8 FOCCFG;        //Frequency Offset Compensation Configuration
    u8 BSCFG;         //Bit Synchronization Configuration
    u8 AGCCTRL2;      //AGC Control
    u8 AGCCTRL1;      //AGC Control
    u8 AGCCTRL0;      //AGC Control
    u8 WOREVT1;       //High Byte Event0 Timeout
    u8 WOREVT0;       //Low Byte Event0 Timeout
    u8 WORCTRL;       //Wake On Radio Control
    u8 FREND1;        //Front End RX Configuration
    u8 FREND0;        //Front End TX Configuration
    u8 FSCAL3;        //Frequency Synthesizer Calibration
    u8 FSCAL2;        //Frequency Synthesizer Calibration
    u8 FSCAL1;        //Frequency Synthesizer Calibration
    u8 FSCAL0;        //Frequency Synthesizer Calibration
    u8 RCCTRL1;       //RC Oscillator Configuration
    u8 RCCTRL0;       //RC Oscillator Configuration
    u8 FSTEST;        //Frequency Synthesizer Calibration Control
    u8 PTEST;         //Production Test
    u8 AGCTEST;       //AGC Test
    u8 TEST2;         //Various Test Settings
    u8 TEST1;         //Various Test Settings
    u8 TEST0;         //Various Test Settings
    u8 PARTNUM;       //Chip ID
    u8 VERSION;       //Chip ID
    u8 FREQEST;       //Frequency Offset Estimate from Demodulator
    u8 LQI;           //Demodulator Estimate for Link Quality
    u8 RSSI;          //Received Signal Strength Indication
    u8 MARCSTATE;     //Main Radio Control State Machine State
    u8 WORTIME1;      //High Byte of WOR Time
    u8 WORTIME0;      //Low Byte of WOR Time
    u8 PKTSTATUS;     //Current GDOx Status and Packet Status
    u8 VCO_VC_DAC;    //Current Setting from PLL Calibration Module
    u8 TXBYTES;       //Underflow and Number of Bytes
    u8 RXBYTES;       //Overflow and Number of Bytes
    u8 RCCTRL1_STATUS;//Last RC Oscillator Calibration Result
    u8 RCCTRL0_STATUS;//Last RC Oscillator Calibration Result
} RF_SETTINGS;

u16 CC1100_WriteReg(u8 Addr,u8 Data);
u16 CC1100_ReadReg(u8 Addr);
void CC1100_PowerUpReset(void);
void CC1100_Reset(void);
void CC1100_SendCommand(u8 Commnad);
void CC1100_WriteSettings(void);
//突发写寄存器
void CC1100_WriteRegBurst(u8 Addr_Start,u8 *Buffer,u8 Lenght);
//突发读寄存器
void CC1100_ReadRegBurst(u8 Addr_Start,u8 *Buffer,u8 Lenght);
//修改发射功率
void CC1100_SetTransPower(void);
//
void CC1100_SendPacket(u8 *Buffer,u8 Lenght);
u16 CC1100_RecevicePacket(u8 *Buffer,u8 *Length);
u16 CC1100_ReadRegStatus(u8 Addr);
void CC1100_Init(void);
void CC1100_WriteSettings(void);
void CC1100_PowerUpReset(void);
void CC1100_Reset(void);
void GPIO_Configuration(void);

#endif
