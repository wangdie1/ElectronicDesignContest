
#include "ili9320.h"
#include "ili9320_font.h"
#include "Font_Lib.h"	 //�Զ����ֿ��ļ���
#include "hz16.h"
#include "zifu16.h"

u16 DeviceCode;
//LCD�Ļ�����ɫ�ͱ���ɫ	   
u16 POINT_COLOR=0x0000;	//������ɫ
u16 BACK_COLOR=0xFFFF;  //����ɫ 

/* Private typedef -----------------------------------------------------------*/
typedef struct
{
  vu16 LCD_REG;
  vu16 LCD_RAM;
} LCD_TypeDef;

/* LCD is connected to the FSMC_Bank1_NOR/SRAM4 and NE4 is used as ship select signal */
#define LCD_BASE    ((u32)(0x60000000 | 0x0C000000))
#define LCD         ((LCD_TypeDef *) LCD_BASE)
////////////////////////////////////////////////////////////////////////////////////////
/*******************************************************************************
* Function Name  : LCD_CtrlLinesConfig
* Description    : Configures LCD Control lines (FSMC Pins) in alternate function
                   Push-Pull mode.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_CtrlLinesConfig(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Enable FSMC, GPIOD, GPIOE, GPIOF, GPIOG and AFIO clocks */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE |
                         RCC_APB2Periph_GPIOF | RCC_APB2Periph_GPIOG |
                         RCC_APB2Periph_AFIO, ENABLE);

  /* Set PD.00(D2), PD.01(D3), PD.04(NOE), PD.05(NWE), PD.08(D13), PD.09(D14),
     PD.10(D15), PD.14(D0), PD.15(D1) as alternate 
     function push pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5 |
                                GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_14 | 
                                GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

  /* Set PE.07(D4), PE.08(D5), PE.09(D6), PE.10(D7), PE.11(D8), PE.12(D9), PE.13(D10),
     PE.14(D11), PE.15(D12) as alternate function push pull */
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | 
                                GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | 
                                GPIO_Pin_15;
  GPIO_Init(GPIOE, &GPIO_InitStructure);

  GPIO_WriteBit(GPIOE, GPIO_Pin_6, Bit_SET);
  /* Set PF.00(A0 (RS)) as alternate function push pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_Init(GPIOF, &GPIO_InitStructure);

  /* Set PG.12(NE4 (LCD/CS)) as alternate function push pull - CE3(LCD /CS) */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
  GPIO_Init(GPIOG, &GPIO_InitStructure);
}

/*******************************************************************************
* Function Name  : LCD_FSMCConfig
* Description    : Configures the Parallel interface (FSMC) for LCD(Parallel mode)
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_FSMCConfig(void)
{
  FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
  FSMC_NORSRAMTimingInitTypeDef  p;

/*-- FSMC Configuration ------------------------------------------------------*/
/*----------------------- SRAM Bank 4 ----------------------------------------*/
  /* FSMC_Bank1_NORSRAM4 configuration */
  p.FSMC_AddressSetupTime = 0;
  p.FSMC_AddressHoldTime = 0;
  p.FSMC_DataSetupTime = 2;
  p.FSMC_BusTurnAroundDuration = 0;
  p.FSMC_CLKDivision = 0;
  p.FSMC_DataLatency = 0;
  p.FSMC_AccessMode = FSMC_AccessMode_A;

  /* Color LCD configuration ------------------------------------
     LCD configured as follow:
        - Data/Address MUX = Disable
        - Memory Type = SRAM
        - Data Width = 16bit
        - Write Operation = Enable
        - Extended Mode = Enable
        - Asynchronous Wait = Disable */
  FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM4;
  FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
  FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_SRAM;
  FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
  FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
  FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
  FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;
  FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
  FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
  FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
  FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;
  FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
  FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &p;
  FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &p;

  FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);  

  /* BANK 4 (of NOR/SRAM Bank 1~4) is enabled */
  FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM4, ENABLE);
}


void LCD_X_Init(void)
{
  /* Configure the LCD Control pins --------------------------------------------*/
  LCD_CtrlLinesConfig();

  /* Configure the FSMC Parallel interface -------------------------------------*/
  LCD_FSMCConfig();
}


/*******************************************************************************
* Function Name  : LCD_WriteReg
* Description    : Writes to the selected LCD register.
* Input          : - LCD_Reg: address of the selected register.
*                  - LCD_RegValue: value to write to the selected register.
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_WriteReg(u8 LCD_Reg,u16 LCD_RegValue)
{
  /* Write 16-bit Index, then Write Reg */
  LCD->LCD_REG = LCD_Reg;
  /* Write 16-bit Reg */
  LCD->LCD_RAM = LCD_RegValue;
}

/*******************************************************************************
* Function Name  : LCD_ReadReg
* Description    : Reads the selected LCD Register.
* Input          : None
* Output         : None
* Return         : LCD Register Value.
*******************************************************************************/
u16 LCD_ReadReg(u8 LCD_Reg)
{
  u16 temp;
  /* Write 16-bit Index (then Read Reg) */
  LCD->LCD_REG = LCD_Reg;
  temp = LCD->LCD_RAM;
  
  temp = LCD->LCD_RAM;
  /* Read 16-bit Reg */
  return temp;
}

/*******************************************************************************
* Function Name  : LCD_WriteRAM_Prepare
* Description    : Prepare to write to the LCD RAM.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_WriteRAM_Prepare(void)
{
  LCD->LCD_REG = R34;
}

/*******************************************************************************
* Function Name  : LCD_WriteRAM
* Description    : Writes to the LCD RAM.
* Input          : - RGB_Code: the pixel color in RGB mode (5-6-5).
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_WriteRAM(u16 RGB_Code)					 
{
  /* Write 16-bit GRAM Reg */
  LCD->LCD_RAM = RGB_Code;
}

/*******************************************************************************
* Function Name  : LCD_ReadRAM
* Description    : Reads the LCD RAM.
* Input          : None
* Output         : None
* Return         : LCD RAM Value.
*******************************************************************************/
u16 LCD_ReadRAM(void)
{
  vu16 dummy;
  /* Write 16-bit Index (then Read Reg) */
  LCD->LCD_REG = R34; /* Select GRAM Reg */
  /* Read 16-bit Reg */
  dummy = LCD->LCD_RAM; 
  return dummy;
}

/*******************************************************************************
* Function Name  : LCD_SetCursor
* Description    : Sets the cursor position.
* Input          : - Xpos: specifies the X position.
*                  - Ypos: specifies the Y position. 
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_SetCursor(u16 Xpos, u16 Ypos)
{
 	if(DeviceCode==0x8999||DeviceCode==0x9919)
	{
		LCD_WriteReg(0x004E, Xpos);
		LCD_WriteReg(0X004F, Ypos);
	}
	else 
	{
		LCD_WriteReg(0x0020, Xpos);
		LCD_WriteReg(0X0021, Ypos);
	}
}			 

void Delay(u32 nCount)
{
  u32 TimingDelay; 
  while(nCount--)
  {
    for(TimingDelay=0;TimingDelay<10000;TimingDelay++);
  }
}

/****************************************************************************
* ��    �ƣ�void ili9320_Initializtion()
* ��    �ܣ���ʼ�� ILI9320 ������
* ��ڲ�������
* ���ڲ�������
* ˵    ����
* ���÷�����ili9320_Initializtion();
****************************************************************************/
void ili9320_Initializtion(void)
{
  /*****************************
  **    Ӳ������˵��          **
  ** STM32         ili9320    **
  ** PE0~15 <----> DB0~15     **
  ** PD15   <----> nRD        **
  ** PD14   <----> RS         **
  ** PD13   <----> nWR        **
  ** PD12   <----> nCS        **
  ** PD11   <----> nReset     **
  ** PC0    <----> BK_LED     **
  ******************************/
  u16 i;
  LCD_X_Init();
  Delay(5); /* delay 50 ms */
  Delay(5); /* delay 50 ms */			//start internal osc
  DeviceCode = LCD_ReadReg(0x0000);
        if(DeviceCode==0x9325||DeviceCode==0x9328)
        {
        LCD_WriteReg(0x00e7,0x0010);      
        LCD_WriteReg(0x0000,0x0001);  			//start internal osc
        LCD_WriteReg(0x0001,0x0100);     
        LCD_WriteReg(0x0002,0x0700); 		    //power on sequence                     
        LCD_WriteReg(0x0003,(1<<12)|(1<<5)|(1<<4) ); 	//65K 
        LCD_WriteReg(0x0004,0x0000);                                   
        LCD_WriteReg(0x0008,0x0207);	           
        LCD_WriteReg(0x0009,0x0000);         
        LCD_WriteReg(0x000a,0x0000); 			//display setting         
        LCD_WriteReg(0x000c,0x0001);			//display setting          
        LCD_WriteReg(0x000d,0x0000); 			//0f3c          
        LCD_WriteReg(0x000f,0x0000);

        //Power On sequence //
        LCD_WriteReg(0x0010,0x0000);   
        LCD_WriteReg(0x0011,0x0007);
        LCD_WriteReg(0x0012,0x0000);                                                                 
        LCD_WriteReg(0x0013,0x0000);                 
        for(i=50000;i>0;i--);
	      for(i=50000;i>0;i--);
        LCD_WriteReg(0x0010,0x1590);   
        LCD_WriteReg(0x0011,0x0227);
        for(i=50000;i>0;i--);
	      for(i=50000;i>0;i--);
        LCD_WriteReg(0x0012,0x009c);                  
        for(i=50000;i>0;i--);
	      for(i=50000;i>0;i--);
        LCD_WriteReg(0x0013,0x1900);   
        LCD_WriteReg(0x0029,0x0023);
        LCD_WriteReg(0x002b,0x000e);
        for(i=50000;i>0;i--);
	      for(i=50000;i>0;i--);
        LCD_WriteReg(0x0020,0x0000);                                                            
        LCD_WriteReg(0x0021,0x0000);           
///////////////////////////////////////////////////////      
        for(i=50000;i>0;i--);
	      for(i=50000;i>0;i--);
        LCD_WriteReg(0x0030,0x0007); 
        LCD_WriteReg(0x0031,0x0707);   
        LCD_WriteReg(0x0032,0x0006);
        LCD_WriteReg(0x0035,0x0704);
        LCD_WriteReg(0x0036,0x1f04); 
        LCD_WriteReg(0x0037,0x0004);
        LCD_WriteReg(0x0038,0x0000);        
        LCD_WriteReg(0x0039,0x0706);     
        LCD_WriteReg(0x003c,0x0701);
        LCD_WriteReg(0x003d,0x000f);
        for(i=50000;i>0;i--);
	      for(i=50000;i>0;i--);
        LCD_WriteReg(0x0050,0x0000);        
        LCD_WriteReg(0x0051,0x00ef);   
        LCD_WriteReg(0x0052,0x0000);     
        LCD_WriteReg(0x0053,0x013f);
        LCD_WriteReg(0x0060,0xa700);        
        LCD_WriteReg(0x0061,0x0001); 
        LCD_WriteReg(0x006a,0x0000);
        LCD_WriteReg(0x0080,0x0000);
        LCD_WriteReg(0x0081,0x0000);
        LCD_WriteReg(0x0082,0x0000);
        LCD_WriteReg(0x0083,0x0000);
        LCD_WriteReg(0x0084,0x0000);
        LCD_WriteReg(0x0085,0x0000);
      
        LCD_WriteReg(0x0090,0x0010);     
        LCD_WriteReg(0x0092,0x0000);  
        LCD_WriteReg(0x0093,0x0003);
        LCD_WriteReg(0x0095,0x0110);
        LCD_WriteReg(0x0097,0x0000);        
        LCD_WriteReg(0x0098,0x0000);  
        //display on sequence     
        LCD_WriteReg(0x0007,0x0133);
    
        LCD_WriteReg(0x0020,0x0000);                                                            
        LCD_WriteReg(0x0021,0x0000);
    }
	else if(DeviceCode==0x8989)
	{
	    LCD_WriteReg(0x0000,0x0001);    ili9320_Delay(50000);   //�򿪾���
    	LCD_WriteReg(0x0003,0xA8A4);    ili9320_Delay(50000);   //0xA8A4
    	LCD_WriteReg(0x000C,0x0000);    ili9320_Delay(50000);   
    	LCD_WriteReg(0x000D,0x080C);    ili9320_Delay(50000);   
    	LCD_WriteReg(0x000E,0x2B00);    ili9320_Delay(50000);   
    	LCD_WriteReg(0x001E,0x00B0);    ili9320_Delay(50000);   
    	LCD_WriteReg(0x0001,0x2B3F);    ili9320_Delay(50000);   //�����������320*240  0x6B3F
    	LCD_WriteReg(0x0002,0x0600);    ili9320_Delay(50000);
    	LCD_WriteReg(0x0010,0x0000);    ili9320_Delay(50000);
    	LCD_WriteReg(0x0011,0x6070);    ili9320_Delay(50000);   //0x4030 �������ݸ�ʽ  16λɫ 		���� 0x6058
    	LCD_WriteReg(0x0005,0x0000);    ili9320_Delay(50000);
    	LCD_WriteReg(0x0006,0x0000);    ili9320_Delay(50000);
    	LCD_WriteReg(0x0016,0xEF1C);    ili9320_Delay(50000);
    	LCD_WriteReg(0x0017,0x0003);    ili9320_Delay(50000);
    	LCD_WriteReg(0x0007,0x0233);    ili9320_Delay(50000);   //0x0233       
    	LCD_WriteReg(0x000B,0x0000);    ili9320_Delay(50000);
    	LCD_WriteReg(0x000F,0x0000);    ili9320_Delay(50000);   //ɨ�迪ʼ��ַ
    	LCD_WriteReg(0x0041,0x0000);    ili9320_Delay(50000);
    	LCD_WriteReg(0x0042,0x0000);    ili9320_Delay(50000);
    	LCD_WriteReg(0x0048,0x0000);    ili9320_Delay(50000);
    	LCD_WriteReg(0x0049,0x013F);    ili9320_Delay(50000);
    	LCD_WriteReg(0x004A,0x0000);    ili9320_Delay(50000);
    	LCD_WriteReg(0x004B,0x0000);    ili9320_Delay(50000);
    	LCD_WriteReg(0x0044,0xEF00);    ili9320_Delay(50000);
    	LCD_WriteReg(0x0045,0x0000);    ili9320_Delay(50000);
    	LCD_WriteReg(0x0046,0x013F);    ili9320_Delay(50000);
    	LCD_WriteReg(0x0030,0x0707);    ili9320_Delay(50000);
    	LCD_WriteReg(0x0031,0x0204);    ili9320_Delay(50000);
    	LCD_WriteReg(0x0032,0x0204);    ili9320_Delay(50000);
    	LCD_WriteReg(0x0033,0x0502);    ili9320_Delay(50000);
    	LCD_WriteReg(0x0034,0x0507);    ili9320_Delay(50000);
    	LCD_WriteReg(0x0035,0x0204);    ili9320_Delay(50000);
    	LCD_WriteReg(0x0036,0x0204);    ili9320_Delay(50000);
    	LCD_WriteReg(0x0037,0x0502);    ili9320_Delay(50000);
    	LCD_WriteReg(0x003A,0x0302);    ili9320_Delay(50000);
    	LCD_WriteReg(0x003B,0x0302);    ili9320_Delay(50000);
    	LCD_WriteReg(0x0023,0x0000);    ili9320_Delay(50000);
    	LCD_WriteReg(0x0024,0x0000);    ili9320_Delay(50000);
    	LCD_WriteReg(0x0025,0x8000);    ili9320_Delay(50000);
    	LCD_WriteReg(0x004f,0);        //����ַ0
    	LCD_WriteReg(0x004e,0);        //����ַ0
	}
    else if(DeviceCode==0x9320||DeviceCode==0x9300)
    {
		LCD_WriteReg(0x00,0x0000);
		LCD_WriteReg(0x01,0x0100);	//Driver Output Contral.
		LCD_WriteReg(0x02,0x0700);	//LCD Driver Waveform Contral.
		LCD_WriteReg(0x03,0x1030);//Entry Mode Set.
		//LCD_WriteReg(0x03,0x1018);	//Entry Mode Set.
	
		LCD_WriteReg(0x04,0x0000);	//Scalling Contral.
		LCD_WriteReg(0x08,0x0202);	//Display Contral 2.(0x0207)
		LCD_WriteReg(0x09,0x0000);	//Display Contral 3.(0x0000)
		LCD_WriteReg(0x0a,0x0000);	//Frame Cycle Contal.(0x0000)
		LCD_WriteReg(0x0c,(1<<0));	//Extern Display Interface Contral 1.(0x0000)
		LCD_WriteReg(0x0d,0x0000);	//Frame Maker Position.
		LCD_WriteReg(0x0f,0x0000);	//Extern Display Interface Contral 2.	    
		ili9320_Delay(10); 
		LCD_WriteReg(0x07,0x0101);	//Display Contral.
		ili9320_Delay(10); 								  
		LCD_WriteReg(0x10,(1<<12)|(0<<8)|(1<<7)|(1<<6)|(0<<4));	//Power Control 1.(0x16b0)
		LCD_WriteReg(0x11,0x0007);								//Power Control 2.(0x0001)
		LCD_WriteReg(0x12,(1<<8)|(1<<4)|(0<<0));				//Power Control 3.(0x0138)
		LCD_WriteReg(0x13,0x0b00);								//Power Control 4.
		LCD_WriteReg(0x29,0x0000);								//Power Control 7.
	
		LCD_WriteReg(0x2b,(1<<14)|(1<<4));	    
		LCD_WriteReg(0x50,0);	//Set X Star
		//ˮƽGRAM��ֹλ��Set X End.
		LCD_WriteReg(0x51,239);	//Set Y Star
		LCD_WriteReg(0x52,0);	//Set Y End.t.
		LCD_WriteReg(0x53,319);	//
	
		LCD_WriteReg(0x60,0x2700);	//Driver Output Control.
		LCD_WriteReg(0x61,0x0001);	//Driver Output Control.
		LCD_WriteReg(0x6a,0x0000);	//Vertical Srcoll Control.
	
		LCD_WriteReg(0x80,0x0000);	//Display Position? Partial Display 1.
		LCD_WriteReg(0x81,0x0000);	//RAM Address Start? Partial Display 1.
		LCD_WriteReg(0x82,0x0000);	//RAM Address End-Partial Display 1.
		LCD_WriteReg(0x83,0x0000);	//Displsy Position? Partial Display 2.
		LCD_WriteReg(0x84,0x0000);	//RAM Address Start? Partial Display 2.
		LCD_WriteReg(0x85,0x0000);	//RAM Address End? Partial Display 2.
	
		LCD_WriteReg(0x90,(0<<7)|(16<<0));	//Frame Cycle Contral.(0x0013)
		LCD_WriteReg(0x92,0x0000);	//Panel Interface Contral 2.(0x0000)
		LCD_WriteReg(0x93,0x0001);	//Panel Interface Contral 3.
		LCD_WriteReg(0x95,0x0110);	//Frame Cycle Contral.(0x0110)
		LCD_WriteReg(0x97,(0<<8));	//
		LCD_WriteReg(0x98,0x0000);	//Frame Cycle Contral.	   
		LCD_WriteReg(0x07,0x0173);	//(0x0173)
		ili9320_Delay(10);
	}
	else if(DeviceCode==0x8999)	   //��Ӧ������ICΪSSD1289
	{
		//************* Start Initial Sequence **********//
		LCD_WriteReg(0x00, 0x0001); // Start internal OSC.
		LCD_WriteReg(0x01, 0x3B3F); // Driver output control, RL=0;REV=1;GD=1;BGR=0;SM=0;TB=1
		LCD_WriteReg(0x02, 0x0600); // set 1 line inversion
		//************* Power control setup ************/
		LCD_WriteReg(0x0C, 0x0007); // Adjust VCIX2 output voltage
		LCD_WriteReg(0x0D, 0x0006); // Set amplitude magnification of VLCD63
		LCD_WriteReg(0x0E, 0x3200); // Set alternating amplitude of VCOM
		LCD_WriteReg(0x1E, 0x00BB); // Set VcomH voltage
		LCD_WriteReg(0x03, 0x6A64); // Step-up factor/cycle setting
		//************ RAM position control **********/
		LCD_WriteReg(0x0F, 0x0000); // Gate scan position start at G0.
		LCD_WriteReg(0x44, 0xEF00); // Horizontal RAM address position
		LCD_WriteReg(0x45, 0x0000); // Vertical RAM address start position
		LCD_WriteReg(0x46, 0x013F); // Vertical RAM address end position
		// ----------- Adjust the Gamma Curve ----------//
		LCD_WriteReg(0x30, 0x0000);
		LCD_WriteReg(0x31, 0x0706);
		LCD_WriteReg(0x32, 0x0206);
		LCD_WriteReg(0x33, 0x0300);
		LCD_WriteReg(0x34, 0x0002);
		LCD_WriteReg(0x35, 0x0000);
		LCD_WriteReg(0x36, 0x0707);
		LCD_WriteReg(0x37, 0x0200);
		LCD_WriteReg(0x3A, 0x0908);
		LCD_WriteReg(0x3B, 0x0F0D);
		//************* Special command **************/
		LCD_WriteReg(0x28, 0x0006); // Enable test command
		LCD_WriteReg(0x2F, 0x12EB); // RAM speed tuning
		LCD_WriteReg(0x26, 0x7000); // Internal Bandgap strength
		LCD_WriteReg(0x20, 0xB0E3); // Internal Vcom strength
		LCD_WriteReg(0x27, 0x0044); // Internal Vcomh/VcomL timing
		LCD_WriteReg(0x2E, 0x7E45); // VCOM charge sharing time  
		//************* Turn On display ******************/
		LCD_WriteReg(0x10, 0x0000); // Sleep mode off.
		Delay(8); // Wait 30mS
		LCD_WriteReg(0x11, 0x6870); // Entry mode setup. 262K type B, take care on the data bus with 16it only
		LCD_WriteReg(0x07, 0x0033); // Display ON	*/
	}	

  for(i=50000;i>0;i--);
  ili9320_Clear(White);
}

/****************************************************************************
* ��    �ƣ�void ili9320_SetCursor(u16 x,u16 y)
* ��    �ܣ�������Ļ����
* ��ڲ�����x      ������
*           y      ������
* ���ڲ�������
* ˵    ����
* ���÷�����ili9320_SetCursor(10,10);
****************************************************************************/
__inline void ili9320_SetCursor(u16 x,u16 y)
{
  if(DeviceCode==0x8989)
  {
    LCD_WriteReg(0x004e,y);        //��
    LCD_WriteReg(0x004f,0x13f-x);  //��
  }
  else if(DeviceCode==0x9919)
  {
    LCD_WriteReg(0x004e,x);        //��
  	LCD_WriteReg(0x004f,y);        //��	
  }
  else
  {
    LCD_WriteReg(0x20,x);        //��
  	LCD_WriteReg(0x21,y);  //��
  }
}

/****************************************************************************
* ��    �ƣ�void ili9320_SetWindows(u16 StartX,u16 StartY,u16 EndX,u16 EndY)
* ��    �ܣ����ô�������
* ��ڲ�����StartX     ����ʼ����
*           StartY     ����ʼ����
*           EndX       �н�������
*           EndY       �н�������
* ���ڲ�������
* ˵    ����
* ���÷�����ili9320_SetWindows(0,0,100,100)��
****************************************************************************/
__inline void ili9320_SetWindows(u16 StartX,u16 StartY,u16 Height,u16 Width)
{
  LCD_WriteReg(R80, StartX);	   	   	//ˮƽ����GRAM��ʼ��ַ
  LCD_WriteReg(R81, StartX+Height); 	//ˮƽ����GRAM������ַ 
  LCD_WriteReg(R82, StartY);		  	//��ֱ����GRAM��ʼ��ַ
  LCD_WriteReg(R83, StartY+Width);  	//��ֱ����GRAM������ַ
  
  ili9320_SetCursor(StartX,StartY);

}

/****************************************************************************
* ��    �ƣ�void ili9320_Clear(u16 dat)
* ��    �ܣ�����Ļ����ָ������ɫ��������������� 0xffff
* ��ڲ�����dat      ���ֵ
* ���ڲ�������
* ˵    ����
* ���÷�����ili9320_Clear(0xffff);
****************************************************************************/
void ili9320_Clear(u16 Color)
{
  u32 index=0;
  ili9320_SetCursor(0,0); 
  LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
  for(index=0;index<76800;index++)
  {
    LCD->LCD_RAM=Color;
  }
}

/****************************************************************************
* ��    �ƣ�u16 ili9320_GetPoint(u16 x,u16 y)
* ��    �ܣ���ȡָ���������ɫֵ
* ��ڲ�����x      ������
*           y      ������
* ���ڲ�������ǰ������ɫֵ
* ˵    ����
* ���÷�����i=ili9320_GetPoint(10,10);
****************************************************************************/
u16 ili9320_GetPoint(u16 x,u16 y)
{
  ili9320_SetCursor(x,y);
  if(DeviceCode==0x7783)
    return (LCD_ReadRAM());
  else
    return (ili9320_BGR2RGB(LCD_ReadRAM()));
}
/****************************************************************************
* ��    �ƣ�void ili9320_SetPoint(u16 x,u16 y,u16 point)
* ��    �ܣ���ָ�����껭��
* ��ڲ�����x      ������
*           y      ������
*           point  �����ɫ
* ���ڲ�������
* ˵    ����
* ���÷�����ili9320_SetPoint(10,10,0x0fe0);
****************************************************************************/
void ili9320_SetPoint(u16 x,u16 y,u16 point)
{
  if ( (x>320)||(y>240) ) return;
  ili9320_SetCursor(x,y);

  LCD_WriteRAM_Prepare();
  LCD_WriteRAM(point);
}

/****************************************************************************
* ��    �ƣ�void ili9320_DrawPicture(u16 StartX,u16 StartY,u16 EndX,u16 EndY,u16 *pic)
* ��    �ܣ���ָ�����귶Χ��ʾһ��ͼƬ
* ��ڲ�����StartX     ����ʼ����
*           StartY     ����ʼ����
*           EndX       �н�������
*           EndY       �н�������
            pic        ͼƬͷָ��
* ���ڲ�������
* ˵    ����ͼƬȡģ��ʽΪˮƽɨ�裬16λ��ɫģʽ
* ���÷�����ili9320_DrawPicture(0,0,100,100,(u16*)demo);
****************************************************************************/
void ili9320_DrawPicture(u16 StartX,u16 StartY,u16 Height,u16 Width,u8 *pic)
{
  u32  i;
  
  u16 *bitmap = (u16 *)pic;
  if(DeviceCode==0x8999)
  {
	//����ͼƬ��ʾ���ڴ�С
	LCD_WriteReg(0x44,StartX|(StartX+Width-1)<<8); //����ˮƽ����GRAM��ʼ��ַ(���ֽ�Ϊ��ʼ��ַ�����ֽ�Ϊ������ַ)
	LCD_WriteReg(0x45,StartY);				  	//���ô��ڵ�Y����Ŀ�ʼλ��
	LCD_WriteReg(0x46,StartY+Height-1);			//���ô��ڵ�Y����Ľ���λ��
  }
  else 
  {
  	LCD_WriteReg(R80, StartX);	   	   	//ˮƽ����GRAM��ʼ��ַ
  	LCD_WriteReg(R81, StartX+Width-1); 	//ˮƽ����GRAM������ַ 
  	LCD_WriteReg(R82, StartY);		  	//��ֱ����GRAM��ʼ��ַ
  	LCD_WriteReg(R83, StartY+Height-1);  	//��ֱ����GRAM������ַ
  }

//  ili9320_SetWindows(StartX, StartY, Width-1, Height-1);
  LCD_SetCursor(StartX,StartY);
  LCD_WriteRAM_Prepare();

  for (i=0;i<(Height*Width);i++)
  {
    LCD_WriteRAM(*bitmap++);
  }
//  ili9320_SetWindows(0x00,0x00,0xef,0x13f);
  if(DeviceCode==0x8999)
  {
	//�ָ�����
	LCD_WriteReg(0x44,0|239<<8); 					//���ô��ڵ�X����ʼλ�úͽ���λ��
	LCD_WriteReg(0x45,0);				  			//���ô��ڵ�Y����Ŀ�ʼλ��
	LCD_WriteReg(0x46,319);							//���ô��ڵ�Y����Ľ���λ��
  }
  else
  {
  	LCD_WriteReg(R80, 0);	   	   	//ˮƽ����GRAM��ʼ��ַ
  	LCD_WriteReg(R81, 0xef); 	//ˮƽ����GRAM������ַ 
  	LCD_WriteReg(R82, 0);		  	//��ֱ����GRAM��ʼ��ַ
  	LCD_WriteReg(R83, 0x13f);  	//��ֱ����GRAM������ַ
  }
}

/****************************************************************************
* ��    �ƣ�void ili9320_PutChar(u16 x,u16 y,u8 c,u16 charColor,u16 bkColor)
* ��    �ܣ���ָ��������ʾһ��8x16�����ascii�ַ�
* ��ڲ�����x          ������
*           y          ������
*           charColor  �ַ�����ɫ
*           bkColor    �ַ�������ɫ
* ���ڲ�������
* ˵    ������ʾ��Χ�޶�Ϊ����ʾ��ascii��
* ���÷�����ili9320_PutChar(10,10,'a',0x0000,0xffff);
****************************************************************************/
void ili9320_PutChar(u16 x,u16 y,u8 c,u16 charColor,u16 bkColor)
{
  u16 i=0;
  u16 j=0;
  
  u8 tmp_char=0;

  for (i=0;i<16;i++)
  {
    tmp_char=ascii_8x16[((c-0x20)*16)+i];
    for (j=0;j<8;j++)
    {
      if ( (tmp_char >> 7-j) & 0x01 == 0x01)
      {
        ili9320_SetPoint(x+j,y+i,charColor); // �ַ���ɫ
      }
      else
      {
        ili9320_SetPoint(x+j,y+i,bkColor); // ������ɫ
      }
    }
  }
}

/****************************************************************************
* ��    �ƣ�u16 ili9320_BGR2RGB(u16 c)
* ��    �ܣ�RRRRRGGGGGGBBBBB ��Ϊ BBBBBGGGGGGRRRRR ��ʽ
* ��ڲ�����c      BRG ��ɫֵ
* ���ڲ�����RGB ��ɫֵ
* ˵    �����ڲ���������
* ���÷�����
****************************************************************************/
u16 ili9320_BGR2RGB(u16 c)
{
  u16  r, g, b, rgb;

  b = (c>>0)  & 0x1f;
  g = (c>>5)  & 0x3f;
  r = (c>>11) & 0x1f;
  
  rgb =  (b<<11) + (g<<5) + (r<<0);

  return( rgb );
}

/****************************************************************************
* ��    �ƣ�void ili9320_BackLight(u8 status)
* ��    �ܣ�������Һ������
* ��ڲ�����status     1:���⿪  0:�����
* ���ڲ�������
* ˵    ����
* ���÷�����ili9320_BackLight(1);
****************************************************************************/
void ili9320_BackLight(u8 status)
{
  if ( status >= 1 )
  {
    Lcd_Light_ON;
  }
  else
  {
    Lcd_Light_OFF;
  }
}

/****************************************************************************
* ��    �ƣ�void ili9320_Delay(vu32 nCount)
* ��    �ܣ���ʱ
* ��ڲ�����nCount   ��ʱֵ
* ���ڲ�������
* ˵    ����
* ���÷�����ili9320_Delay(10000);
****************************************************************************/
void ili9320_Delay(vu32 nCount)
{
  for(; nCount != 0; nCount--);
}

/****************************************************************************
* ��    �ƣ�ili9320_DisplayStringLine
* ��    �ܣ���ʾ���40���ַ�һ����LCD��
* ��ڲ�����Line ���� *ptrָ���ַ�����ָ�� charColor�ַ���ɫ bkColor������ɫ
* ���ڲ�������
* ˵    ����
* ���÷�����ili9320_DisplayStringLine(Line0,"I Love you...",White,Blue);  
****************************************************************************/
void ili9320_DisplayStringLine(u8 Line, u8 *ptr, u16 charColor, u16 bkColor)
{
  u32 i = 0;
  u16 refcolumn = 0;

  /* Send the string character by character on lCD */
  while ((*ptr != 0) & (i < 40))
  {
    /* Display one character on LCD */
    ili9320_PutChar(refcolumn, Line, *ptr, charColor, bkColor);
    /* Decrement the column position by 8 */
    refcolumn += 8;
    /* Point on the next character */
    ptr++;
    /* Increment the character counter */
    i++;
  }
}
/*****************************************************************************
** ��������: WriteString
** ��������: ��ָ��λ�ÿ�ʼ��ʾһ���ַ�����һ������
				֧���Զ�����
** ��  ����: Dream
** �ա�  ��: 2010��12��06��
*****************************************************************************/   			   
void WriteString(u16 x0, u16 y0,u8 *pcStr, u16 color)
{
	u16 usIndex;
    u16 usWidth = 0;
    FNT_GB16 *ptGb16 = 0;
    
    ptGb16 = (FNT_GB16 *)GBHZ_16;  
	while(1)
    {
        if(*pcStr == 0) 
		{
            break;                                     /* �ַ�������            */
        }      
        x0 = x0 + (usWidth);                           /* �����ַ�����ʾ�ɽ���         */
        if(*pcStr > 0x80)                              /* �ж�Ϊ����                   */
        {
		    if((x0 + 16) > LCD_W)                      /* ���ʣ��ռ��Ƿ��㹻         */
            {
			    x0 = 0;
                y0 = y0 + 16;                          /* �ı���ʾ����                 */
                if(y0 > LCD_H)                         /* �����곬��                   */
                {
				    y0 = 0;
                }
            }
            usIndex = findHzIndex(pcStr);
            usWidth = WriteOneHzChar((u8 *)&(ptGb16[usIndex].Msk[0]), x0, y0, color);
                                                       /* ��ʾ�ַ�                     */
            pcStr += 2;
        }
		else 
		{                                               /* �ж�Ϊ�Ǻ���                 */
            if (*pcStr == '\r')                         /* ����                         */
            { 
			    y0 = y0 + 16;                           /* �ı���ʾ����                 */
                if(y0 > LCD_H)                          /* �����곬��                   */
                {
				    y0 = 0;
                }
                pcStr++;
                usWidth = 0;
                continue;
            } 
			else if (*pcStr == '\n')                    /* ���뵽���                   */
            {
			    x0 = 0;
                pcStr++;
                usWidth = 0;
                continue;
            } 
			else 
			{
                if((x0 + 8) > LCD_W)                     /* ���ʣ��ռ��Ƿ��㹻         */
                {
				    x0 = 0;
                    y0 = y0 + 16;                        /* �ı���ʾ����                 */
                    if(y0 > LCD_H)                       /* �����곬��                   */
                    { 
					    y0 = 0;
                    }
                }
                usWidth = WriteOneASCII((u8 *)&ASCII_1608[(*pcStr - 0x20)][0], x0, y0, color);
                                                         /* ASCII���21H��ֵ��Ӧ��λ��3��*/
                pcStr += 1;
            }
		}
	}												  	  
}
/*****************************************************************************
** ��������: WriteOneHzChar
** ��������: ��ʾһ��ָ����С�ĺ���
** ��  ����: Dream
** �ա�  ��: 2010��12��06��
*****************************************************************************/
u16 WriteOneHzChar(u8 *pucMsk, u16 x0,u16 y0,u16 color)
{
    u16 i,j;
    u16 mod[16];                                      /* ��ǰ��ģ                     */
    u16 *pusMsk;                                      /* ��ǰ�ֿ��ַ                 */
    u16 y;
    
    pusMsk = (u16 *)pucMsk;
    for(i=0; i<16; i++)                                    /* ���浱ǰ���ֵ���ʽ��ģ       */
    {
        mod[i] = *pusMsk++;                                /* ȡ�õ�ǰ��ģ�����ֶ������   */
        mod[i] = ((mod[i] & 0xff00) >> 8) | ((mod[i] & 0x00ff) << 8);/* ��ģ�����ߵ��ֽڣ�Ϊ����ʾ   */
                                                           /* ��Ҫ��                       */
    }
    y = y0;
    for(i=0; i<16; i++)                                    /* 16��                         */
    { 
	    #ifdef __DISPLAY_BUFFER                            /* ʹ���Դ���ʾ                 */
        for(j=0; j<16; j++)                                /* 16��                         */
        {
		    if((mod[i] << j)& 0x8000)                      /* ��ʾ��ģ                     */
            {
			    DispBuf[240*(y0+i) + x0+j] = color;
            }
        }
        #else                                              /* ֱ����ʾ                     */
        
        LCD_SetCursor(x0, y);                              /* ����д���ݵ�ַָ��           */
		LCD_WriteRAM_Prepare();        					   /*��ʼд��GRAM	*/   
        for(j=0; j<16; j++)                                /* 16��                         */
        {
		    if((mod[i] << j) & 0x8000)                     /* ��ʾ��ģ                     */
            { 
			    LCD_WriteRAM(color);
            } 
			else 
			{
                LCD_WriteRAM(Black);                     /* �ö���ʽ����д�հ׵������   */
            	//LCD_ReadDat();
			}
        }
        y++;
        #endif
    }
    return (16);                                          /* ����16λ�п�                 */
}
/*****************************************************************************
** ��������: WriteOneASCII
** ��������: ��ʾһ��ָ����С���ַ�
** ��  ����: Dream
** �ա�  ��: 2010��12��06��
*****************************************************************************/
u16 WriteOneASCII(u8 *pucMsk,
                              u16 x0,
                              u16 y0,
                              u16 color)
{
    u16 i,j;
    u16 y;
    u8 ucChar;
    
    y = y0;
    for(i=0; i<16; i++) {                                 /* 16��                         */
        ucChar = *pucMsk++;
        #ifdef __DISPLAY_BUFFER                           /* ʹ���Դ���ʾ                 */
        for(j=0; j<8; j++) {                              /* 8��                          */
            if((ucChar << j)& 0x80) {                     /* ��ʾ��ģ                     */
                DispBuf[240*(y0+i) + x0+j] = color;
            }
        }
        #else                                             /* ֱ����ʾ                     */
        
        LCD_SetCursor(x0, y);                             /* ����д���ݵ�ַָ��           */
		LCD_WriteRAM_Prepare();        					  /* ��ʼд��GRAM	    		  */
        for(j=0; j<8; j++) {                              /* 8��                          */
            if((ucChar << j) & 0x80) {                    /* ��ʾ��ģ                     */
                LCD_WriteRAM(color);
            } else {
                LCD_WriteRAM(Black);
				  //LCD_ReadDat();
            }
        }
        y++;
        #endif
    }
    return (8);                                           /* ����16λ�п�                 */
}


//��ʾ����,��λΪ0,����ʾ
//x,y :�������	 
//len :���ֵ�λ��
//size:�����С
//color:��ɫ 
//num:��ֵ(0~4294967295);	 
void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size)
{         	
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/LCD_Pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				LCD_ShowChar(x+(size/2)*t,y,' ',size,0);
				continue;
			}else enshow=1; 
		 	 
		}
	 	LCD_ShowChar(x+(size/2)*t,y,temp+'0',size,0); 
	}
} 



//��ָ��λ����ʾһ���ַ�
//x,y:��ʼ����
//num:Ҫ��ʾ���ַ�:" "--->"~"
//size:�����С 12/16
//mode:���ӷ�ʽ(1)���Ƿǵ��ӷ�ʽ(0)
void LCD_ShowChar(u16 x,u16 y,u8 num,u8 size,u8 mode)
{  							  
    u8 temp,t1,t;
	u16 y0=y;
	u16 colortemp=POINT_COLOR;      			     
	//���ô���		   
	num=num-' ';//�õ�ƫ�ƺ��ֵ
	if(!mode) //�ǵ��ӷ�ʽ
	{
	    for(t=0;t<size;t++)
	    {   
			if(size==12)temp=asc2_1206[num][t];  //����1206����
			else temp=asc2_1608[num][t];		 //����1608���� 	                          
	        for(t1=0;t1<8;t1++)
			{			    
		        if(temp&0x80)POINT_COLOR=colortemp;
				else POINT_COLOR=BACK_COLOR;
				LCD_DrawPoint(x,y);	
				temp<<=1;
				y++;
				if(x>=240){POINT_COLOR=colortemp;return;}//��������
				if((y-y0)==size)
				{
					y=y0;
					x++;
					if(x>=320){POINT_COLOR=colortemp;return;}//��������
					break;
				}
			}  	 
	    }    
	}else//���ӷ�ʽ
	{
	    for(t=0;t<size;t++)
	    {   
			if(size==12)temp=asc2_1206[num][t];  //����1206����
			else temp=asc2_1608[num][t];		 //����1608���� 	                          
	        for(t1=0;t1<8;t1++)
			{			    
		        if(temp&0x80)LCD_DrawPoint(x,y); 
				temp<<=1;
				y++;
				if(x>=320){POINT_COLOR=colortemp;return;}//��������
				if((y-y0)==size)
				{
					y=y0;
					x++;
					if(x>=240){POINT_COLOR=colortemp;return;}//��������
					break;
				}
			}  	 
	    }     
	}
	POINT_COLOR=colortemp;	    	   	 	  
}   

//����
//x,y:����
//POINT_COLOR:�˵����ɫ
void LCD_DrawPoint(u16 x,u16 y)
{
	LCD_SetCursor(x,y);		//���ù��λ�� 
	LCD_WriteRAM_Prepare();	//��ʼд��GRAM
	LCD->LCD_RAM=POINT_COLOR; 
}


//m^n����
//����ֵ:m^n�η�.
u32 LCD_Pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}			

void LCD_ShowString(u16 x,u16 y,u16 width,u16 height,u8 size,u8 *p)
{         
	u8 x0=x;
	width+=x;
	height+=y;
    while((*p<='~')&&(*p>=' '))//�ж��ǲ��ǷǷ��ַ�!
    {       
        if(x>=width){x=x0;y+=size;}
        if(y>=height)break;//�˳�
        LCD_ShowChar(x,y,*p,size,0);
        x+=size/2;
        p++;
    }  
}





/************************************************************************************
* ��    �ƣ�void ShowOneChinese(u8 Number, u8 x, u16 y,u16 PenColor,u16 BackColor)
* ��    �ܣ���ʾһ�����֣���ȡģ���� ������FONTS.h�У�
* ��ڲ�����u8 Number    : ��ģ�����еĵڼ�������
*			u8 x         ��X������
*           u16 y        ��Y������
*			u16 PenColor ������ɫ
*			u16 BackColor������ɫd
* ���ڲ�������
* ˵    ������ʾһ������
* ���÷�����
************************************************************************************/
void ShowOneChinese1(u8 Number, u8 Step,u8 x, u16 y,u16 PenColor,u16 BackColor)
{
    u8 i,j;
	/*  ����Ϊ16*16  */
	if(Step==16)
	{
	
		u8 sizex = 16;
		u8 sizey = 16;		
		u8 *Chinese_buf = &Chinese_Table1[Number * sizex * 2];
 
		for(i=0; i<sizex; i++)                        /* sizex��   */
		{                                              
			for(j=0; j<sizey; j++)                    /* sizey��   */
			{
				if((Chinese_buf[i*2+j/8] << (j%8)) & 0x80)      /* ��ʾ��i�� ��16���� */
				{ 
					LCD_SetPoint(x+i,y+j,PenColor);
				} 
				else 
				{
					LCD_SetPoint(x+i,y+j,BackColor);         
				}
			}
		}

	
	}else if(Step==32)
	{
		u8 sizex = 32;
		u8 sizey = 32;
		u8 *Chinese_buf = &Chinese_Table1[Number * sizex * 4];
	 
		for(i=0; i<sizex; i++)                        /* sizex��   */
		{                                              
			for(j=0; j<sizey; j++)                    /* sizey��   */
			{
				if((Chinese_buf[i*4+j/8] << (j%8)) & 0x80)      /* ��ʾ��i�� ��16���� */
				{ 
					LCD_SetPoint(x+i,y+j,PenColor);
				} 
				else 
				{
					LCD_SetPoint(x+i,y+j,BackColor);         
				}
			}
		}

	
	}
	else if(Step==64)
	{
		u8 sizex = 64;
		u8 sizey = 64;
		u8 *Chinese_buf = &Chinese_Table1[Number * sizex * 8];

		for(i=0; i<sizex; i++)                        /* sizex��   */
		{                                              
			for(j=0; j<sizey; j++)                    /* sizey��   */
			{
				if((Chinese_buf[i*8+j/8] << (j%8)) & 0x80)      /* ��ʾ��i�� ��16���� */
				{ 
					LCD_SetPoint(x+i,y+j,PenColor);
				} 
				else 
				{
					LCD_SetPoint(x+i,y+j,BackColor);         
				}
			}
		}	
	}
}
/************************************************************************************
* ��    �ƣ�void ShowOneChinese(u8 Number, u8 x, u16 y,u16 PenColor,u16 BackColor)
* ��    �ܣ���ʾһ�����֣���ȡģ���� ������FONTS.h�У�
* ��ڲ�����u8 Number    : ��ģ�����еĵڼ�������
			u8  Step      : ѡ�������С16*16  32*32  64*64
*			u8 x         ��X������
*           u16 y        ��Y������
*			u16 PenColor ������ɫ
*			u16 BackColor������ɫd
* ���ڲ�������
* ˵    ��������һ����ʾ����
* ���÷�����LCD_SetDisplayWindow(0,0,240,320)
************************************************************************************/
void ShowLineChinese1(u8 Number,u8 counter ,u8 Step,u8 x, u16 y,u16 PenColor,u16 BackColor)
{
    u8 i;
    for(i=0;i<counter;i++)
	{
	    ShowOneChinese1(Number + i,Step, x + i*Step, y ,PenColor ,BackColor);    
	}
}



void ShowOneChinese2(u8 Number, u8 Step,u8 x, u16 y,u16 PenColor,u16 BackColor)
{
    u8 i,j;
	/*  ����Ϊ16*16  */
	if(Step==16)
	{
	
		u8 sizex = 16;
		u8 sizey = 16;		
		u8 *Chinese_buf = &Chinese_Table2[Number * sizex * 2];
 
		for(i=0; i<sizex; i++)                        /* sizex��   */
		{                                              
			for(j=0; j<sizey; j++)                    /* sizey��   */
			{
				if((Chinese_buf[i*2+j/8] << (j%8)) & 0x80)      /* ��ʾ��i�� ��16���� */
				{ 
					LCD_SetPoint(x+i,y+j,PenColor);
				} 
				else 
				{
					LCD_SetPoint(x+i,y+j,BackColor);         
				}
			}
		}

	
	}else if(Step==32)
	{
		u8 sizex = 32;
		u8 sizey = 32;
		u8 *Chinese_buf = &Chinese_Table2[Number * sizex * 4];
	 
		for(i=0; i<sizex; i++)                        /* sizex��   */
		{                                              
			for(j=0; j<sizey; j++)                    /* sizey��   */
			{
				if((Chinese_buf[i*4+j/8] << (j%8)) & 0x80)      /* ��ʾ��i�� ��16���� */
				{ 
					LCD_SetPoint(x+i,y+j,PenColor);
				} 
				else 
				{
					LCD_SetPoint(x+i,y+j,BackColor);         
				}
			}
		}

	
	}
	else if(Step==64)
	{
		u8 sizex = 64;
		u8 sizey = 64;
		u8 *Chinese_buf = &Chinese_Table2[Number * sizex * 8];

		for(i=0; i<sizex; i++)                        /* sizex��   */
		{                                              
			for(j=0; j<sizey; j++)                    /* sizey��   */
			{
				if((Chinese_buf[i*8+j/8] << (j%8)) & 0x80)      /* ��ʾ��i�� ��16���� */
				{ 
					LCD_SetPoint(x+i,y+j,PenColor);
				} 
				else 
				{
					LCD_SetPoint(x+i,y+j,BackColor);         
				}
			}
		}	
	}
}



void ShowLineChinese2(u8 Number,u8 counter ,u8 Step,u8 x, u16 y,u16 PenColor,u16 BackColor)
{
    u8 i;
    for(i=0;i<counter;i++)
	{
	    ShowOneChinese2(Number + i,Step, x+ i*Step , y ,PenColor ,BackColor);    
	}
}





void ShowOneChinese3(u8 Number, u8 Step,u8 x, u16 y,u16 PenColor,u16 BackColor)
{
    u8 i,j;
	/*  ����Ϊ16*16  */
	if(Step==16)
	{
	
		u8 sizex = 16;
		u8 sizey = 16;		
		u8 *Chinese_buf = &Chinese_Table3[Number * sizex * 2];
 
		for(i=0; i<sizex; i++)                        /* sizex��   */
		{                                              
			for(j=0; j<sizey; j++)                    /* sizey��   */
			{
				if((Chinese_buf[i*2+j/8] << (j%8)) & 0x80)      /* ��ʾ��i�� ��16���� */
				{ 
					LCD_SetPoint(x+i,y+j,PenColor);
				} 
				else 
				{
					LCD_SetPoint(x+i,y+j,BackColor);         
				}
			}
		}

	
	}else if(Step==32)
	{
		u8 sizex = 32;
		u8 sizey = 32;
		u8 *Chinese_buf = &Chinese_Table3[Number * sizex * 4];
	 
		for(i=0; i<sizex; i++)                        /* sizex��   */
		{                                              
			for(j=0; j<sizey; j++)                    /* sizey��   */
			{
				if((Chinese_buf[i*4+j/8] << (j%8)) & 0x80)      /* ��ʾ��i�� ��16���� */
				{ 
					LCD_SetPoint(x+i,y+j,PenColor);
				} 
				else 
				{
					LCD_SetPoint(x+i,y+j,BackColor);         
				}
			}
		}

	
	}
	else if(Step==64)
	{
		u8 sizex = 64;
		u8 sizey = 64;
		u8 *Chinese_buf = &Chinese_Table2[Number * sizex * 8];

		for(i=0; i<sizex; i++)                        /* sizex��   */
		{                                              
			for(j=0; j<sizey; j++)                    /* sizey��   */
			{
				if((Chinese_buf[i*8+j/8] << (j%8)) & 0x80)      /* ��ʾ��i�� ��16���� */
				{ 
					LCD_SetPoint(x+i,y+j,PenColor);
				} 
				else 
				{
					LCD_SetPoint(x+i,y+j,BackColor);         
				}
			}
		}	
	}
}



void ShowLineChinese3(u8 Number,u8 counter ,u8 Step,u8 x, u16 y,u16 PenColor,u16 BackColor)
{
    u8 i;
    for(i=0;i<counter;i++)
	{
	    ShowOneChinese3(Number + i,Step, x+ i*Step , y ,PenColor ,BackColor);    
	}
}





void ShowOneChinese4(u8 Number, u8 Step,u8 x, u16 y,u16 PenColor,u16 BackColor)
{
    u8 i,j;
	/*  ����Ϊ16*16  */
	if(Step==16)
	{
	
		u8 sizex = 16;
		u8 sizey = 16;		
		u8 *Chinese_buf = &Chinese_Table4[Number * sizex * 2];
 
		for(i=0; i<sizex; i++)                        /* sizex��   */
		{                                              
			for(j=0; j<sizey; j++)                    /* sizey��   */
			{
				if((Chinese_buf[i*2+j/8] << (j%8)) & 0x80)      /* ��ʾ��i�� ��16���� */
				{ 
					LCD_SetPoint(x+i,y+j,PenColor);
				} 
				else 
				{
					LCD_SetPoint(x+i,y+j,BackColor);         
				}
			}
		}

	
	}else if(Step==32)
	{
		u8 sizex = 32;
		u8 sizey = 32;
		u8 *Chinese_buf = &Chinese_Table4[Number * sizex * 4];
	 
		for(i=0; i<sizex; i++)                        /* sizex��   */
		{                                              
			for(j=0; j<sizey; j++)                    /* sizey��   */
			{
				if((Chinese_buf[i*4+j/8] << (j%8)) & 0x80)      /* ��ʾ��i�� ��16���� */
				{ 
					LCD_SetPoint(x+i,y+j,PenColor);
				} 
				else 
				{
					LCD_SetPoint(x+i,y+j,BackColor);         
				}
			}
		}

	
	}
	else if(Step==64)
	{
		u8 sizex = 64;
		u8 sizey = 64;
		u8 *Chinese_buf = &Chinese_Table4[Number * sizex * 8];

		for(i=0; i<sizex; i++)                        /* sizex��   */
		{                                              
			for(j=0; j<sizey; j++)                    /* sizey��   */
			{
				if((Chinese_buf[i*8+j/8] << (j%8)) & 0x80)      /* ��ʾ��i�� ��16���� */
				{ 
					LCD_SetPoint(x+i,y+j,PenColor);
				} 
				else 
				{
					LCD_SetPoint(x+i,y+j,BackColor);         
				}
			}
		}	
	}
}



void ShowLineChinese4(u8 Number,u8 counter ,u8 Step,u8 x, u16 y,u16 PenColor,u16 BackColor)
{
    u8 i;
    for(i=0;i<counter;i++)
	{
	    ShowOneChinese4(Number + i,Step, x+ i*Step , y ,PenColor ,BackColor);    
	}
}




void ShowOneChinese5(u8 Number, u8 Step,u8 x, u16 y,u16 PenColor,u16 BackColor)
{
    u8 i,j;
	/*  ����Ϊ16*16  */
	if(Step==16)
	{
	
		u8 sizex = 16;
		u8 sizey = 16;		
		u8 *Chinese_buf = &Chinese_Table5[Number * sizex * 2];
 
		for(i=0; i<sizex; i++)                        /* sizex��   */
		{                                              
			for(j=0; j<sizey; j++)                    /* sizey��   */
			{
				if((Chinese_buf[i*2+j/8] << (j%8)) & 0x80)      /* ��ʾ��i�� ��16���� */
				{ 
					LCD_SetPoint(x+i,y+j,PenColor);
				} 
				else 
				{
					LCD_SetPoint(x+i,y+j,BackColor);         
				}
			}
		}

	
	}else if(Step==32)
	{
		u8 sizex = 32;
		u8 sizey = 32;
		u8 *Chinese_buf = &Chinese_Table5[Number * sizex * 4];
	 
		for(i=0; i<sizex; i++)                        /* sizex��   */
		{                                              
			for(j=0; j<sizey; j++)                    /* sizey��   */
			{
				if((Chinese_buf[i*4+j/8] << (j%8)) & 0x80)      /* ��ʾ��i�� ��16���� */
				{ 
					LCD_SetPoint(x+i,y+j,PenColor);
				} 
				else 
				{
					LCD_SetPoint(x+i,y+j,BackColor);         
				}
			}
		}

	
	}
	else if(Step==64)
	{
		u8 sizex = 64;
		u8 sizey = 64;
		u8 *Chinese_buf = &Chinese_Table5[Number * sizex * 8];

		for(i=0; i<sizex; i++)                        /* sizex��   */
		{                                              
			for(j=0; j<sizey; j++)                    /* sizey��   */
			{
				if((Chinese_buf[i*8+j/8] << (j%8)) & 0x80)      /* ��ʾ��i�� ��16���� */
				{ 
					LCD_SetPoint(x+i,y+j,PenColor);
				} 
				else 
				{
					LCD_SetPoint(x+i,y+j,BackColor);         
				}
			}
		}	
	}
}



void ShowLineChinese5(u8 Number,u8 counter ,u8 Step,u8 x, u16 y,u16 PenColor,u16 BackColor)
{
    u8 i;
    for(i=0;i<counter;i++)
	{
	    ShowOneChinese5(Number + i,Step, x + i*Step, y ,PenColor ,BackColor);    
	}
}




void ShowOneChinese6(u8 Number, u8 Step,u8 x, u16 y,u16 PenColor,u16 BackColor)
{
    u8 i,j;
	/*  ����Ϊ16*16  */
	if(Step==16)
	{
	
		u8 sizex = 16;
		u8 sizey = 16;		
		u8 *Chinese_buf = &Chinese_Table6[Number * sizex * 2];
 
		for(i=0; i<sizex; i++)                        /* sizex��   */
		{                                              
			for(j=0; j<sizey; j++)                    /* sizey��   */
			{
				if((Chinese_buf[i*2+j/8] << (j%8)) & 0x80)      /* ��ʾ��i�� ��16���� */
				{ 
					LCD_SetPoint(x+i,y+j,PenColor);
				} 
				else 
				{
					LCD_SetPoint(x+i,y+j,BackColor);         
				}
			}
		}

	
	}else if(Step==32)
	{
		u8 sizex = 32;
		u8 sizey = 32;
		u8 *Chinese_buf = &Chinese_Table6[Number * sizex * 4];
	 
		for(i=0; i<sizex; i++)                        /* sizex��   */
		{                                              
			for(j=0; j<sizey; j++)                    /* sizey��   */
			{
				if((Chinese_buf[i*4+j/8] << (j%8)) & 0x80)      /* ��ʾ��i�� ��16���� */
				{ 
					LCD_SetPoint(x+i,y+j,PenColor);
				} 
				else 
				{
					LCD_SetPoint(x+i,y+j,BackColor);         
				}
			}
		}

	
	}
	else if(Step==64)
	{
		u8 sizex = 64;
		u8 sizey = 64;
		u8 *Chinese_buf = &Chinese_Table6[Number * sizex * 8];

		for(i=0; i<sizex; i++)                        /* sizex��   */
		{                                              
			for(j=0; j<sizey; j++)                    /* sizey��   */
			{
				if((Chinese_buf[i*8+j/8] << (j%8)) & 0x80)      /* ��ʾ��i�� ��16���� */
				{ 
					LCD_SetPoint(x+i,y+j,PenColor);
				} 
				else 
				{
					LCD_SetPoint(x+i,y+j,BackColor);         
				}
			}
		}	
	}
}



void ShowLineChinese6(u8 Number,u8 counter ,u8 Step,u8 x, u16 y,u16 PenColor,u16 BackColor)
{
    u8 i;
    for(i=0;i<counter;i++)
	{
	    ShowOneChinese6(Number + i,Step, x + i*Step, y ,PenColor ,BackColor);    
	}
}
/****************************************************************************
* ��    �ƣ�void LCD_SetPoint(u16 x,u16 y,u16 point)
* ��    �ܣ���ָ�����껭��
* ��ڲ�����x      ������
*           y      ������
*           point  �����ɫ
* ���ڲ�������
* ˵    ����
* ���÷�����ili9320_SetPoint(10,10,0x0fe0);
****************************************************************************/
void LCD_SetPoint(u16 x,u16 y,u16 point)
{
  if ( (x>240)||(y>360) ) return;
  LCD_SetCursor(x,y);
  LCD_WriteRAM_Prepare();
  LCD_WriteRAM(point);
}


//��ָ��λ�û�һ��ָ����С��Բ
//(x,y):���ĵ�
//r    :�뾶
void Draw_Circle(u16 x0,u16 y0,u8 r)
{
	int a,b;
	int di;
	a=0;b=r;	  
	di=3-(r<<1);             //�ж��¸���λ�õı�־
	while(a<=b)
	{
		LCD_DrawPoint(x0+a,y0-b);             //5
 		LCD_DrawPoint(x0+b,y0-a);             //0           
		LCD_DrawPoint(x0+b,y0+a);             //4               
		LCD_DrawPoint(x0+a,y0+b);             //6 
		LCD_DrawPoint(x0-a,y0+b);             //1       
 		LCD_DrawPoint(x0-b,y0+a);             
		LCD_DrawPoint(x0-a,y0-b);             //2             
  		LCD_DrawPoint(x0-b,y0-a);             //7     	         
		a++;
		//ʹ��Bresenham�㷨��Բ     
		if(di<0)di +=4*a+6;	  
		else
		{
			di+=10+4*(a-b);   
			b--;
		} 						    
	}
} 	

//������	  
//(x1,y1),(x2,y2):���εĶԽ�����
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2)
{
	LCD_DrawLine(x1,y1,x2,y1);
	LCD_DrawLine(x1,y1,x1,y2);
	LCD_DrawLine(x1,y2,x2,y2);
	LCD_DrawLine(x2,y1,x2,y2);
}

//����
//x1,y1:�������
//x2,y2:�յ�����  
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2)
{
	u16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 
	delta_x=x2-x1; //������������ 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //���õ������� 
	else if(delta_x==0)incx=0;//��ֱ�� 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//ˮƽ�� 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //ѡȡ�������������� 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//������� 
	{  
		LCD_DrawPoint(uRow,uCol);//���� 
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  
}   


//��ָ�����������ָ����ɫ��			 
//(sx,sy),(ex,ey):�����ζԽ�����,�����СΪ:(ex-sx+1)*(ey-sy+1)   
//color:Ҫ������ɫ
void LCD_Color_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 *color)
{  
	u16 height,width;
	u16 i,j;
	width=ex-sx+1; 		//�õ����Ŀ��
	height=ey-sy+1;		//�߶�
 	for(i=0;i<height;i++)
	{
 		LCD_SetCursor(sx,sy+i);   	//���ù��λ�� 
		LCD_WriteRAM_Prepare();     //��ʼд��GRAM
		for(j=0;j<width;j++)LCD->LCD_RAM=color[i*height+j];//д������ 
	}	  
}  


void LCD_Clear(u16 color)
{
	u32 index=0;      
	u32 totalpoint=240;
	totalpoint*=320; 	//�õ��ܵ���
	LCD_SetCursor(0x00,0x0000);	//���ù��λ�� 
	LCD_WriteRAM_Prepare();     //��ʼд��GRAM	 	  
	for(index=0;index<totalpoint;index++)
	{
		LCD->LCD_RAM=color;	   
	}
}  

