
#include "ili9320.h"
#include "ili9320_font.h"
#include "Font_Lib.h"	 //自定义字库文件库
#include "hz16.h"
#include "zifu16.h"

u16 DeviceCode;
//LCD的画笔颜色和背景色	   
u16 POINT_COLOR=0x0000;	//画笔颜色
u16 BACK_COLOR=0xFFFF;  //背景色 

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
* 名    称：void ili9320_Initializtion()
* 功    能：初始化 ILI9320 控制器
* 入口参数：无
* 出口参数：无
* 说    明：
* 调用方法：ili9320_Initializtion();
****************************************************************************/
void ili9320_Initializtion(void)
{
  /*****************************
  **    硬件连接说明          **
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
	    LCD_WriteReg(0x0000,0x0001);    ili9320_Delay(50000);   //打开晶振
    	LCD_WriteReg(0x0003,0xA8A4);    ili9320_Delay(50000);   //0xA8A4
    	LCD_WriteReg(0x000C,0x0000);    ili9320_Delay(50000);   
    	LCD_WriteReg(0x000D,0x080C);    ili9320_Delay(50000);   
    	LCD_WriteReg(0x000E,0x2B00);    ili9320_Delay(50000);   
    	LCD_WriteReg(0x001E,0x00B0);    ili9320_Delay(50000);   
    	LCD_WriteReg(0x0001,0x2B3F);    ili9320_Delay(50000);   //驱动输出控制320*240  0x6B3F
    	LCD_WriteReg(0x0002,0x0600);    ili9320_Delay(50000);
    	LCD_WriteReg(0x0010,0x0000);    ili9320_Delay(50000);
    	LCD_WriteReg(0x0011,0x6070);    ili9320_Delay(50000);   //0x4030 定义数据格式  16位色 		横屏 0x6058
    	LCD_WriteReg(0x0005,0x0000);    ili9320_Delay(50000);
    	LCD_WriteReg(0x0006,0x0000);    ili9320_Delay(50000);
    	LCD_WriteReg(0x0016,0xEF1C);    ili9320_Delay(50000);
    	LCD_WriteReg(0x0017,0x0003);    ili9320_Delay(50000);
    	LCD_WriteReg(0x0007,0x0233);    ili9320_Delay(50000);   //0x0233       
    	LCD_WriteReg(0x000B,0x0000);    ili9320_Delay(50000);
    	LCD_WriteReg(0x000F,0x0000);    ili9320_Delay(50000);   //扫描开始地址
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
    	LCD_WriteReg(0x004f,0);        //行首址0
    	LCD_WriteReg(0x004e,0);        //列首址0
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
		//水平GRAM终止位置Set X End.
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
	else if(DeviceCode==0x8999)	   //对应的驱动IC为SSD1289
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
* 名    称：void ili9320_SetCursor(u16 x,u16 y)
* 功    能：设置屏幕座标
* 入口参数：x      行座标
*           y      列座标
* 出口参数：无
* 说    明：
* 调用方法：ili9320_SetCursor(10,10);
****************************************************************************/
__inline void ili9320_SetCursor(u16 x,u16 y)
{
  if(DeviceCode==0x8989)
  {
    LCD_WriteReg(0x004e,y);        //行
    LCD_WriteReg(0x004f,0x13f-x);  //列
  }
  else if(DeviceCode==0x9919)
  {
    LCD_WriteReg(0x004e,x);        //行
  	LCD_WriteReg(0x004f,y);        //列	
  }
  else
  {
    LCD_WriteReg(0x20,x);        //行
  	LCD_WriteReg(0x21,y);  //列
  }
}

/****************************************************************************
* 名    称：void ili9320_SetWindows(u16 StartX,u16 StartY,u16 EndX,u16 EndY)
* 功    能：设置窗口区域
* 入口参数：StartX     行起始座标
*           StartY     列起始座标
*           EndX       行结束座标
*           EndY       列结束座标
* 出口参数：无
* 说    明：
* 调用方法：ili9320_SetWindows(0,0,100,100)；
****************************************************************************/
__inline void ili9320_SetWindows(u16 StartX,u16 StartY,u16 Height,u16 Width)
{
  LCD_WriteReg(R80, StartX);	   	   	//水平方向GRAM起始地址
  LCD_WriteReg(R81, StartX+Height); 	//水平方向GRAM结束地址 
  LCD_WriteReg(R82, StartY);		  	//垂直方向GRAM起始地址
  LCD_WriteReg(R83, StartY+Width);  	//垂直方向GRAM结束地址
  
  ili9320_SetCursor(StartX,StartY);

}

/****************************************************************************
* 名    称：void ili9320_Clear(u16 dat)
* 功    能：将屏幕填充成指定的颜色，如清屏，则填充 0xffff
* 入口参数：dat      填充值
* 出口参数：无
* 说    明：
* 调用方法：ili9320_Clear(0xffff);
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
* 名    称：u16 ili9320_GetPoint(u16 x,u16 y)
* 功    能：获取指定座标的颜色值
* 入口参数：x      行座标
*           y      列座标
* 出口参数：当前座标颜色值
* 说    明：
* 调用方法：i=ili9320_GetPoint(10,10);
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
* 名    称：void ili9320_SetPoint(u16 x,u16 y,u16 point)
* 功    能：在指定座标画点
* 入口参数：x      行座标
*           y      列座标
*           point  点的颜色
* 出口参数：无
* 说    明：
* 调用方法：ili9320_SetPoint(10,10,0x0fe0);
****************************************************************************/
void ili9320_SetPoint(u16 x,u16 y,u16 point)
{
  if ( (x>320)||(y>240) ) return;
  ili9320_SetCursor(x,y);

  LCD_WriteRAM_Prepare();
  LCD_WriteRAM(point);
}

/****************************************************************************
* 名    称：void ili9320_DrawPicture(u16 StartX,u16 StartY,u16 EndX,u16 EndY,u16 *pic)
* 功    能：在指定座标范围显示一副图片
* 入口参数：StartX     行起始座标
*           StartY     列起始座标
*           EndX       行结束座标
*           EndY       列结束座标
            pic        图片头指针
* 出口参数：无
* 说    明：图片取模格式为水平扫描，16位颜色模式
* 调用方法：ili9320_DrawPicture(0,0,100,100,(u16*)demo);
****************************************************************************/
void ili9320_DrawPicture(u16 StartX,u16 StartY,u16 Height,u16 Width,u8 *pic)
{
  u32  i;
  
  u16 *bitmap = (u16 *)pic;
  if(DeviceCode==0x8999)
  {
	//设置图片显示窗口大小
	LCD_WriteReg(0x44,StartX|(StartX+Width-1)<<8); //设置水平方向GRAM起始地址(低字节为起始地址，高字节为结束地址)
	LCD_WriteReg(0x45,StartY);				  	//设置窗口的Y方向的开始位置
	LCD_WriteReg(0x46,StartY+Height-1);			//设置窗口的Y方向的结束位置
  }
  else 
  {
  	LCD_WriteReg(R80, StartX);	   	   	//水平方向GRAM起始地址
  	LCD_WriteReg(R81, StartX+Width-1); 	//水平方向GRAM结束地址 
  	LCD_WriteReg(R82, StartY);		  	//垂直方向GRAM起始地址
  	LCD_WriteReg(R83, StartY+Height-1);  	//垂直方向GRAM结束地址
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
	//恢复窗口
	LCD_WriteReg(0x44,0|239<<8); 					//设置窗口的X方向开始位置和结束位置
	LCD_WriteReg(0x45,0);				  			//设置窗口的Y方向的开始位置
	LCD_WriteReg(0x46,319);							//设置窗口的Y方向的结束位置
  }
  else
  {
  	LCD_WriteReg(R80, 0);	   	   	//水平方向GRAM起始地址
  	LCD_WriteReg(R81, 0xef); 	//水平方向GRAM结束地址 
  	LCD_WriteReg(R82, 0);		  	//垂直方向GRAM起始地址
  	LCD_WriteReg(R83, 0x13f);  	//垂直方向GRAM结束地址
  }
}

/****************************************************************************
* 名    称：void ili9320_PutChar(u16 x,u16 y,u8 c,u16 charColor,u16 bkColor)
* 功    能：在指定座标显示一个8x16点阵的ascii字符
* 入口参数：x          列座标
*           y          行座标
*           charColor  字符的颜色
*           bkColor    字符背景颜色
* 出口参数：无
* 说    明：显示范围限定为可显示的ascii码
* 调用方法：ili9320_PutChar(10,10,'a',0x0000,0xffff);
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
        ili9320_SetPoint(x+j,y+i,charColor); // 字符颜色
      }
      else
      {
        ili9320_SetPoint(x+j,y+i,bkColor); // 背景颜色
      }
    }
  }
}

/****************************************************************************
* 名    称：u16 ili9320_BGR2RGB(u16 c)
* 功    能：RRRRRGGGGGGBBBBB 改为 BBBBBGGGGGGRRRRR 格式
* 入口参数：c      BRG 颜色值
* 出口参数：RGB 颜色值
* 说    明：内部函数调用
* 调用方法：
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
* 名    称：void ili9320_BackLight(u8 status)
* 功    能：开、关液晶背光
* 入口参数：status     1:背光开  0:背光关
* 出口参数：无
* 说    明：
* 调用方法：ili9320_BackLight(1);
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
* 名    称：void ili9320_Delay(vu32 nCount)
* 功    能：延时
* 入口参数：nCount   延时值
* 出口参数：无
* 说    明：
* 调用方法：ili9320_Delay(10000);
****************************************************************************/
void ili9320_Delay(vu32 nCount)
{
  for(; nCount != 0; nCount--);
}

/****************************************************************************
* 名    称：ili9320_DisplayStringLine
* 功    能：显示最多40个字符一行在LCD上
* 入口参数：Line 行数 *ptr指向字符串的指针 charColor字符颜色 bkColor背景颜色
* 出口参数：无
* 说    明：
* 调用方法：ili9320_DisplayStringLine(Line0,"I Love you...",White,Blue);  
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
** 函数名称: WriteString
** 功能描述: 在指定位置开始显示一个字符串和一串汉字
				支持自动换行
** 作  　者: Dream
** 日　  期: 2010年12月06日
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
            break;                                     /* 字符串结束            */
        }      
        x0 = x0 + (usWidth);                           /* 调节字符串显示松紧度         */
        if(*pcStr > 0x80)                              /* 判断为汉字                   */
        {
		    if((x0 + 16) > LCD_W)                      /* 检查剩余空间是否足够         */
            {
			    x0 = 0;
                y0 = y0 + 16;                          /* 改变显示坐标                 */
                if(y0 > LCD_H)                         /* 纵坐标超出                   */
                {
				    y0 = 0;
                }
            }
            usIndex = findHzIndex(pcStr);
            usWidth = WriteOneHzChar((u8 *)&(ptGb16[usIndex].Msk[0]), x0, y0, color);
                                                       /* 显示字符                     */
            pcStr += 2;
        }
		else 
		{                                               /* 判断为非汉字                 */
            if (*pcStr == '\r')                         /* 换行                         */
            { 
			    y0 = y0 + 16;                           /* 改变显示坐标                 */
                if(y0 > LCD_H)                          /* 纵坐标超出                   */
                {
				    y0 = 0;
                }
                pcStr++;
                usWidth = 0;
                continue;
            } 
			else if (*pcStr == '\n')                    /* 对齐到起点                   */
            {
			    x0 = 0;
                pcStr++;
                usWidth = 0;
                continue;
            } 
			else 
			{
                if((x0 + 8) > LCD_W)                     /* 检查剩余空间是否足够         */
                {
				    x0 = 0;
                    y0 = y0 + 16;                        /* 改变显示坐标                 */
                    if(y0 > LCD_H)                       /* 纵坐标超出                   */
                    { 
					    y0 = 0;
                    }
                }
                usWidth = WriteOneASCII((u8 *)&ASCII_1608[(*pcStr - 0x20)][0], x0, y0, color);
                                                         /* ASCII码表21H的值对应区位码3区*/
                pcStr += 1;
            }
		}
	}												  	  
}
/*****************************************************************************
** 函数名称: WriteOneHzChar
** 功能描述: 显示一个指定大小的汉字
** 作  　者: Dream
** 日　  期: 2010年12月06日
*****************************************************************************/
u16 WriteOneHzChar(u8 *pucMsk, u16 x0,u16 y0,u16 color)
{
    u16 i,j;
    u16 mod[16];                                      /* 当前字模                     */
    u16 *pusMsk;                                      /* 当前字库地址                 */
    u16 y;
    
    pusMsk = (u16 *)pucMsk;
    for(i=0; i<16; i++)                                    /* 保存当前汉字点阵式字模       */
    {
        mod[i] = *pusMsk++;                                /* 取得当前字模，半字对齐访问   */
        mod[i] = ((mod[i] & 0xff00) >> 8) | ((mod[i] & 0x00ff) << 8);/* 字模交换高低字节（为了显示   */
                                                           /* 需要）                       */
    }
    y = y0;
    for(i=0; i<16; i++)                                    /* 16行                         */
    { 
	    #ifdef __DISPLAY_BUFFER                            /* 使用显存显示                 */
        for(j=0; j<16; j++)                                /* 16列                         */
        {
		    if((mod[i] << j)& 0x8000)                      /* 显示字模                     */
            {
			    DispBuf[240*(y0+i) + x0+j] = color;
            }
        }
        #else                                              /* 直接显示                     */
        
        LCD_SetCursor(x0, y);                              /* 设置写数据地址指针           */
		LCD_WriteRAM_Prepare();        					   /*开始写入GRAM	*/   
        for(j=0; j<16; j++)                                /* 16列                         */
        {
		    if((mod[i] << j) & 0x8000)                     /* 显示字模                     */
            { 
			    LCD_WriteRAM(color);
            } 
			else 
			{
                LCD_WriteRAM(Black);                     /* 用读方式跳过写空白点的像素   */
            	//LCD_ReadDat();
			}
        }
        y++;
        #endif
    }
    return (16);                                          /* 返回16位列宽                 */
}
/*****************************************************************************
** 函数名称: WriteOneASCII
** 功能描述: 显示一个指定大小的字符
** 作  　者: Dream
** 日　  期: 2010年12月06日
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
    for(i=0; i<16; i++) {                                 /* 16行                         */
        ucChar = *pucMsk++;
        #ifdef __DISPLAY_BUFFER                           /* 使用显存显示                 */
        for(j=0; j<8; j++) {                              /* 8列                          */
            if((ucChar << j)& 0x80) {                     /* 显示字模                     */
                DispBuf[240*(y0+i) + x0+j] = color;
            }
        }
        #else                                             /* 直接显示                     */
        
        LCD_SetCursor(x0, y);                             /* 设置写数据地址指针           */
		LCD_WriteRAM_Prepare();        					  /* 开始写入GRAM	    		  */
        for(j=0; j<8; j++) {                              /* 8列                          */
            if((ucChar << j) & 0x80) {                    /* 显示字模                     */
                LCD_WriteRAM(color);
            } else {
                LCD_WriteRAM(Black);
				  //LCD_ReadDat();
            }
        }
        y++;
        #endif
    }
    return (8);                                           /* 返回16位列宽                 */
}


//显示数字,高位为0,则不显示
//x,y :起点坐标	 
//len :数字的位数
//size:字体大小
//color:颜色 
//num:数值(0~4294967295);	 
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



//在指定位置显示一个字符
//x,y:起始坐标
//num:要显示的字符:" "--->"~"
//size:字体大小 12/16
//mode:叠加方式(1)还是非叠加方式(0)
void LCD_ShowChar(u16 x,u16 y,u8 num,u8 size,u8 mode)
{  							  
    u8 temp,t1,t;
	u16 y0=y;
	u16 colortemp=POINT_COLOR;      			     
	//设置窗口		   
	num=num-' ';//得到偏移后的值
	if(!mode) //非叠加方式
	{
	    for(t=0;t<size;t++)
	    {   
			if(size==12)temp=asc2_1206[num][t];  //调用1206字体
			else temp=asc2_1608[num][t];		 //调用1608字体 	                          
	        for(t1=0;t1<8;t1++)
			{			    
		        if(temp&0x80)POINT_COLOR=colortemp;
				else POINT_COLOR=BACK_COLOR;
				LCD_DrawPoint(x,y);	
				temp<<=1;
				y++;
				if(x>=240){POINT_COLOR=colortemp;return;}//超区域了
				if((y-y0)==size)
				{
					y=y0;
					x++;
					if(x>=320){POINT_COLOR=colortemp;return;}//超区域了
					break;
				}
			}  	 
	    }    
	}else//叠加方式
	{
	    for(t=0;t<size;t++)
	    {   
			if(size==12)temp=asc2_1206[num][t];  //调用1206字体
			else temp=asc2_1608[num][t];		 //调用1608字体 	                          
	        for(t1=0;t1<8;t1++)
			{			    
		        if(temp&0x80)LCD_DrawPoint(x,y); 
				temp<<=1;
				y++;
				if(x>=320){POINT_COLOR=colortemp;return;}//超区域了
				if((y-y0)==size)
				{
					y=y0;
					x++;
					if(x>=240){POINT_COLOR=colortemp;return;}//超区域了
					break;
				}
			}  	 
	    }     
	}
	POINT_COLOR=colortemp;	    	   	 	  
}   

//画点
//x,y:坐标
//POINT_COLOR:此点的颜色
void LCD_DrawPoint(u16 x,u16 y)
{
	LCD_SetCursor(x,y);		//设置光标位置 
	LCD_WriteRAM_Prepare();	//开始写入GRAM
	LCD->LCD_RAM=POINT_COLOR; 
}


//m^n函数
//返回值:m^n次方.
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
    while((*p<='~')&&(*p>=' '))//判断是不是非法字符!
    {       
        if(x>=width){x=x0;y+=size;}
        if(y>=height)break;//退出
        LCD_ShowChar(x,y,*p,size,0);
        x+=size/2;
        p++;
    }  
}





/************************************************************************************
* 名    称：void ShowOneChinese(u8 Number, u8 x, u16 y,u16 PenColor,u16 BackColor)
* 功    能：显示一个汉字（自取模汉字 数据在FONTS.h中）
* 入口参数：u8 Number    : 字模数组中的第几个汉字
*			u8 x         ：X轴坐标
*           u16 y        ：Y轴坐标
*			u16 PenColor ：字体色
*			u16 BackColor：背景色d
* 出口参数：无
* 说    明：显示一个汉字
* 调用方法：
************************************************************************************/
void ShowOneChinese1(u8 Number, u8 Step,u8 x, u16 y,u16 PenColor,u16 BackColor)
{
    u8 i,j;
	/*  汉字为16*16  */
	if(Step==16)
	{
	
		u8 sizex = 16;
		u8 sizey = 16;		
		u8 *Chinese_buf = &Chinese_Table1[Number * sizex * 2];
 
		for(i=0; i<sizex; i++)                        /* sizex行   */
		{                                              
			for(j=0; j<sizey; j++)                    /* sizey列   */
			{
				if((Chinese_buf[i*2+j/8] << (j%8)) & 0x80)      /* 显示第i行 共16个点 */
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
	 
		for(i=0; i<sizex; i++)                        /* sizex行   */
		{                                              
			for(j=0; j<sizey; j++)                    /* sizey列   */
			{
				if((Chinese_buf[i*4+j/8] << (j%8)) & 0x80)      /* 显示第i行 共16个点 */
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

		for(i=0; i<sizex; i++)                        /* sizex行   */
		{                                              
			for(j=0; j<sizey; j++)                    /* sizey列   */
			{
				if((Chinese_buf[i*8+j/8] << (j%8)) & 0x80)      /* 显示第i行 共16个点 */
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
* 名    称：void ShowOneChinese(u8 Number, u8 x, u16 y,u16 PenColor,u16 BackColor)
* 功    能：显示一个汉字（自取模汉字 数据在FONTS.h中）
* 入口参数：u8 Number    : 字模数组中的第几个汉字
			u8  Step      : 选择字体大小16*16  32*32  64*64
*			u8 x         ：X轴坐标
*           u16 y        ：Y轴坐标
*			u16 PenColor ：字体色
*			u16 BackColor：背景色d
* 出口参数：无
* 说    明：设置一个显示窗口
* 调用方法：LCD_SetDisplayWindow(0,0,240,320)
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
	/*  汉字为16*16  */
	if(Step==16)
	{
	
		u8 sizex = 16;
		u8 sizey = 16;		
		u8 *Chinese_buf = &Chinese_Table2[Number * sizex * 2];
 
		for(i=0; i<sizex; i++)                        /* sizex行   */
		{                                              
			for(j=0; j<sizey; j++)                    /* sizey列   */
			{
				if((Chinese_buf[i*2+j/8] << (j%8)) & 0x80)      /* 显示第i行 共16个点 */
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
	 
		for(i=0; i<sizex; i++)                        /* sizex行   */
		{                                              
			for(j=0; j<sizey; j++)                    /* sizey列   */
			{
				if((Chinese_buf[i*4+j/8] << (j%8)) & 0x80)      /* 显示第i行 共16个点 */
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

		for(i=0; i<sizex; i++)                        /* sizex行   */
		{                                              
			for(j=0; j<sizey; j++)                    /* sizey列   */
			{
				if((Chinese_buf[i*8+j/8] << (j%8)) & 0x80)      /* 显示第i行 共16个点 */
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
	/*  汉字为16*16  */
	if(Step==16)
	{
	
		u8 sizex = 16;
		u8 sizey = 16;		
		u8 *Chinese_buf = &Chinese_Table3[Number * sizex * 2];
 
		for(i=0; i<sizex; i++)                        /* sizex行   */
		{                                              
			for(j=0; j<sizey; j++)                    /* sizey列   */
			{
				if((Chinese_buf[i*2+j/8] << (j%8)) & 0x80)      /* 显示第i行 共16个点 */
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
	 
		for(i=0; i<sizex; i++)                        /* sizex行   */
		{                                              
			for(j=0; j<sizey; j++)                    /* sizey列   */
			{
				if((Chinese_buf[i*4+j/8] << (j%8)) & 0x80)      /* 显示第i行 共16个点 */
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

		for(i=0; i<sizex; i++)                        /* sizex行   */
		{                                              
			for(j=0; j<sizey; j++)                    /* sizey列   */
			{
				if((Chinese_buf[i*8+j/8] << (j%8)) & 0x80)      /* 显示第i行 共16个点 */
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
	/*  汉字为16*16  */
	if(Step==16)
	{
	
		u8 sizex = 16;
		u8 sizey = 16;		
		u8 *Chinese_buf = &Chinese_Table4[Number * sizex * 2];
 
		for(i=0; i<sizex; i++)                        /* sizex行   */
		{                                              
			for(j=0; j<sizey; j++)                    /* sizey列   */
			{
				if((Chinese_buf[i*2+j/8] << (j%8)) & 0x80)      /* 显示第i行 共16个点 */
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
	 
		for(i=0; i<sizex; i++)                        /* sizex行   */
		{                                              
			for(j=0; j<sizey; j++)                    /* sizey列   */
			{
				if((Chinese_buf[i*4+j/8] << (j%8)) & 0x80)      /* 显示第i行 共16个点 */
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

		for(i=0; i<sizex; i++)                        /* sizex行   */
		{                                              
			for(j=0; j<sizey; j++)                    /* sizey列   */
			{
				if((Chinese_buf[i*8+j/8] << (j%8)) & 0x80)      /* 显示第i行 共16个点 */
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
	/*  汉字为16*16  */
	if(Step==16)
	{
	
		u8 sizex = 16;
		u8 sizey = 16;		
		u8 *Chinese_buf = &Chinese_Table5[Number * sizex * 2];
 
		for(i=0; i<sizex; i++)                        /* sizex行   */
		{                                              
			for(j=0; j<sizey; j++)                    /* sizey列   */
			{
				if((Chinese_buf[i*2+j/8] << (j%8)) & 0x80)      /* 显示第i行 共16个点 */
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
	 
		for(i=0; i<sizex; i++)                        /* sizex行   */
		{                                              
			for(j=0; j<sizey; j++)                    /* sizey列   */
			{
				if((Chinese_buf[i*4+j/8] << (j%8)) & 0x80)      /* 显示第i行 共16个点 */
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

		for(i=0; i<sizex; i++)                        /* sizex行   */
		{                                              
			for(j=0; j<sizey; j++)                    /* sizey列   */
			{
				if((Chinese_buf[i*8+j/8] << (j%8)) & 0x80)      /* 显示第i行 共16个点 */
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
	/*  汉字为16*16  */
	if(Step==16)
	{
	
		u8 sizex = 16;
		u8 sizey = 16;		
		u8 *Chinese_buf = &Chinese_Table6[Number * sizex * 2];
 
		for(i=0; i<sizex; i++)                        /* sizex行   */
		{                                              
			for(j=0; j<sizey; j++)                    /* sizey列   */
			{
				if((Chinese_buf[i*2+j/8] << (j%8)) & 0x80)      /* 显示第i行 共16个点 */
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
	 
		for(i=0; i<sizex; i++)                        /* sizex行   */
		{                                              
			for(j=0; j<sizey; j++)                    /* sizey列   */
			{
				if((Chinese_buf[i*4+j/8] << (j%8)) & 0x80)      /* 显示第i行 共16个点 */
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

		for(i=0; i<sizex; i++)                        /* sizex行   */
		{                                              
			for(j=0; j<sizey; j++)                    /* sizey列   */
			{
				if((Chinese_buf[i*8+j/8] << (j%8)) & 0x80)      /* 显示第i行 共16个点 */
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
* 名    称：void LCD_SetPoint(u16 x,u16 y,u16 point)
* 功    能：在指定座标画点
* 入口参数：x      行座标
*           y      列座标
*           point  点的颜色
* 出口参数：无
* 说    明：
* 调用方法：ili9320_SetPoint(10,10,0x0fe0);
****************************************************************************/
void LCD_SetPoint(u16 x,u16 y,u16 point)
{
  if ( (x>240)||(y>360) ) return;
  LCD_SetCursor(x,y);
  LCD_WriteRAM_Prepare();
  LCD_WriteRAM(point);
}


//在指定位置画一个指定大小的圆
//(x,y):中心点
//r    :半径
void Draw_Circle(u16 x0,u16 y0,u8 r)
{
	int a,b;
	int di;
	a=0;b=r;	  
	di=3-(r<<1);             //判断下个点位置的标志
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
		//使用Bresenham算法画圆     
		if(di<0)di +=4*a+6;	  
		else
		{
			di+=10+4*(a-b);   
			b--;
		} 						    
	}
} 	

//画矩形	  
//(x1,y1),(x2,y2):矩形的对角坐标
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2)
{
	LCD_DrawLine(x1,y1,x2,y1);
	LCD_DrawLine(x1,y1,x1,y2);
	LCD_DrawLine(x1,y2,x2,y2);
	LCD_DrawLine(x2,y1,x2,y2);
}

//画线
//x1,y1:起点坐标
//x2,y2:终点坐标  
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2)
{
	u16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 
	delta_x=x2-x1; //计算坐标增量 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //设置单步方向 
	else if(delta_x==0)incx=0;//垂直线 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//水平线 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //选取基本增量坐标轴 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//画线输出 
	{  
		LCD_DrawPoint(uRow,uCol);//画点 
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


//在指定区域内填充指定颜色块			 
//(sx,sy),(ex,ey):填充矩形对角坐标,区域大小为:(ex-sx+1)*(ey-sy+1)   
//color:要填充的颜色
void LCD_Color_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 *color)
{  
	u16 height,width;
	u16 i,j;
	width=ex-sx+1; 		//得到填充的宽度
	height=ey-sy+1;		//高度
 	for(i=0;i<height;i++)
	{
 		LCD_SetCursor(sx,sy+i);   	//设置光标位置 
		LCD_WriteRAM_Prepare();     //开始写入GRAM
		for(j=0;j<width;j++)LCD->LCD_RAM=color[i*height+j];//写入数据 
	}	  
}  


void LCD_Clear(u16 color)
{
	u32 index=0;      
	u32 totalpoint=240;
	totalpoint*=320; 	//得到总点数
	LCD_SetCursor(0x00,0x0000);	//设置光标位置 
	LCD_WriteRAM_Prepare();     //开始写入GRAM	 	  
	for(index=0;index<totalpoint;index++)
	{
		LCD->LCD_RAM=color;	   
	}
}  

