#include "stm32f10x.h"
#include "stm32f10x_fsmc.h"
#include "ili9320.h"
#include "ili9320_font.h"
#include "ili9320_api.h"
#include "delay.h"
#define BmpHeadSize (54)
u16 PictureWidth;
u16 PictureHeight;
u16 DeviceCode;

/* Private typedef -----------------------------------------------------------*/
typedef struct
{
  vu16 LCD_REG;
  vu16 LCD_RAM;
} LCD_TypeDef;

/* LCD is connected to the FSMC_Bank1_NOR/SRAM4 and NE4 is used as ship select signal */
#define LCD_BASE   ((u32)(0x60000000 | 0x0C000000))
#define LCD         ((LCD_TypeDef *) LCD_BASE)

#define SetCs  
#define ClrCs  

//#define SetCs  GPIO_SetBits(GPIOG, GPIO_Pin_12);
//#define ClrCs  GPIO_ResetBits(GPIOG, GPIO_Pin_12);

//#define SetCs  GPIO_SetBits(GPIOB, GPIO_Pin_8);
//#define ClrCs  GPIO_ResetBits(GPIOB, GPIO_Pin_8);

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

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE |
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
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | 
                                GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | 
                                GPIO_Pin_15;
  GPIO_Init(GPIOE, &GPIO_InitStructure);

  /* Set PF.00(A0 (RS)) as alternate function push pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_Init(GPIOF, &GPIO_InitStructure);

  /* Set PG.12(NE4 (LCD/CS)) as alternate function push pull - CE3(LCD /CS) */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
  GPIO_Init(GPIOG, &GPIO_InitStructure);

  
  /* LEDs pins configuration */

  /* Set PD7 to disable NAND */

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
  p.FSMC_AddressSetupTime = 1;
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
 // FSMC_NORSRAMInitStructure.FSMC_AsyncWait = FSMC_AsyncWait_Disable;
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
void LCD_WriteReg(u16 LCD_Reg,u16 LCD_RegValue)
{
  /* Write 16-bit Index, then Write Reg */
  ClrCs
  LCD->LCD_REG = LCD_Reg;
  /* Write 16-bit Reg */
  LCD->LCD_RAM = LCD_RegValue;
  SetCs
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
  u16 data;
  /* Write 16-bit Index (then Read Reg) */
  ClrCs
  //LCD->LCD_REG = LCD_Reg;
  data = LCD->LCD_RAM; 
    SetCs
     return    data;

  /* Read 16-bit Reg */
  //return (LCD->LCD_RAM);
}

u16 LCD_ReadSta(void)
{
  u16 data;
  /* Write 16-bit Index, then Write Reg */
  ClrCs
  data = LCD->LCD_REG;
  SetCs
  return    data;
}

void LCD_WriteCommand(u16 LCD_RegValue)
{
  /* Write 16-bit Index, then Write Reg */
  ClrCs
  LCD->LCD_REG = LCD_RegValue;
  SetCs
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
  ClrCs
  LCD->LCD_REG = R34;
  SetCs
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
  ClrCs
  /* Write 16-bit GRAM Reg */
  LCD->LCD_RAM = RGB_Code;
  SetCs
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
  u16 dummy;
  u16 data;
  /* Write 16-bit Index (then Read Reg) */
  ClrCs
  LCD->LCD_REG = R34; /* Select GRAM Reg */
  /* Read 16-bit Reg */
  dummy = LCD->LCD_RAM; 
  dummy++;
  data = LCD->LCD_RAM; 
  SetCs
  return    data;
  //return LCD->LCD_RAM;
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
  LCD_WriteReg(0x06,Ypos>>8);
  LCD_WriteReg(0x07,Ypos);
  
  LCD_WriteReg(0x02,Xpos>>8);
  LCD_WriteReg(0x03,Xpos);  
}			 

void Delay_nms(int n)
{
  
  u32 f=n,k;
  for (; f!=0; f--)
  {
    for(k=0xFFF; k!=0; k--);
  }
  
}

// void Delay(u32 nCount)
// {
//  u32 TimingDelay; 
//  while(nCount--)
//    {
//     for(TimingDelay=0;TimingDelay<10000;TimingDelay++);
//    }
// }

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
  delay_ms(20); /* delay 50 ms */
 // LCD_WriteReg(0x0000,0x0001);  
 // Delay(5); /* delay 50 ms */			//start internal osc
  DeviceCode = LCD_ReadReg(0x0000);
    delay_ms(5); /* delay 50 ms */
  DeviceCode = LCD_ReadReg(0x0000);  
//    printf("\n\r ###### DeviceCode = LCD_ReadReg(0x0000) = 0x%x ###### ", DeviceCode);
//    printf("\n\r ###### DeviceCode = LCD->LCD_RAM = 0x%x ###### ", LCD->LCD_RAM);
//    printf("\n\r ######&LCD->LCD_REG =  0x%x ,  &LCD->LCD_RAM =  0x%x ###### ",  &LCD->LCD_REG,  &LCD->LCD_RAM);
//    printf("\n\r ###### DeviceCode = LCD_ReadReg(0x0000) = 0x%x ###### ", LCD_ReadReg(0x0000));
/*   
  ClrCs
   printf("\n\r ###### LCD->LCD_REG = 0x%x ###### ", LCD->LCD_REG);
  SetCs
*/    
  if(DeviceCode == 0x9325)
    {
//        printf("\n\r This LCD is ili9325 ");
    }
	if(DeviceCode==0x9325||DeviceCode==0x9328)
	{
#if 0	
	Lcd_Light_ON;
//	DataToWrite(0xffff);//������ȫ��
//	Set_nWr;
//	SetCs;
//	SetRs;
//	Set_nRd;
//	Set_Rst;
//	Set_Rst;
//	Delay_nms(1);
//	Clr_Rst;
//	Delay_nms(1);
//	Set_Rst;
//	Delay_nms(1);       
#ifdef ILI9325        
	LCD_WriteReg(0x00e3,0x3008);
	LCD_WriteReg(0x00e7,0x0012);
	LCD_WriteReg(0x00ef,0x1231);//Set the internal vcore voltage
	LCD_WriteReg(0x0001,0x0100);//S
#endif  
#ifdef ILI9320
	LCD_WriteReg(0x00e5,0x8000);
	LCD_WriteReg(0x0000,0x0001);
	LCD_WriteReg(0x0001,0x0100);//S
	Delay_nms(10);
#endif        
	LCD_WriteReg(0x0002,0x0700);//Line inversion        
#if   ID_AM==000       
	LCD_WriteReg(0x0003,0x0000);//��Ļ��ת���� TFM=0,TRI=0,SWAP=1,16 bits system interface  swap RGB to BRG���˴�ORG��HWM Ϊ0
#elif ID_AM==001        
	LCD_WriteReg(0x0003,0x0008);      
#elif ID_AM==010  
	LCD_WriteReg(0x0003,0x0010);        
#elif ID_AM==011
	LCD_WriteReg(0x0003,0x0018);
#elif ID_AM==100  
	LCD_WriteReg(0x0003,0x0020);      
#elif ID_AM==101  
	LCD_WriteReg(0x0003,0x0028);      
#elif ID_AM==110  
	LCD_WriteReg(0x0003,0x0030);      
#elif ID_AM==111  
	LCD_WriteReg(0x0003,0x0038);
#endif      
	LCD_WriteReg(0x0004,0x0000);
	LCD_WriteReg(0x0008,0x0207);
	LCD_WriteReg(0x0009,0x0000);
	LCD_WriteReg(0x000a,0x0000);
	LCD_WriteReg(0x000c,0x0001);//�˴����ýӿ����� 16λ system�ӿ�
	LCD_WriteReg(0x000d,0x0000);
	LCD_WriteReg(0x000f,0x0000);      
	//��Դ����
	LCD_WriteReg(0x0010,0x0000);
//bear	LCD_WriteReg(0x0011,0x0000);
       LCD_WriteReg(0x0011,0x0007);
	LCD_WriteReg(0x0012,0x0000);
	LCD_WriteReg(0x0013,0x0000);
	Delay_nms(200);
	LCD_WriteReg(0x0010,0x17b0);
	LCD_WriteReg(0x0011,0x0137);
	Delay_nms(50);
	LCD_WriteReg(0x0012,0x0139);
	Delay_nms(50);
	LCD_WriteReg(0x0013,0x1700);
	LCD_WriteReg(0x0029,0x000c);
	LCD_WriteReg(0x002b,0x000C);
	Delay_nms(50);      
#if   ID_AM==000         
	LCD_WriteReg(0x0020,0x00ef);//GRAMˮƽ��ʼλ��
	LCD_WriteReg(0x0021,0x013f);      
#elif ID_AM==001
	LCD_WriteReg(0x0020,0x00ef);
	LCD_WriteReg(0x0021,0x013f);      
#elif ID_AM==010
	LCD_WriteReg(0x0020,0x0000);
	LCD_WriteReg(0x0021,0x013f);      
#elif ID_AM==011
	LCD_WriteReg(0x0020,0x0000);
	LCD_WriteReg(0x0021,0x013f);       
#elif ID_AM==100
	LCD_WriteReg(0x0020,0x00ef);
	LCD_WriteReg(0x0021,0x0000);      
#elif ID_AM==101  
	LCD_WriteReg(0x0020,0x00ef);
	LCD_WriteReg(0x0021,0x0000);      
#elif ID_AM==110
	LCD_WriteReg(0x0020,0x0000);
	LCD_WriteReg(0x0021,0x0000);      
#elif ID_AM==111
	LCD_WriteReg(0x0020,0x0000);
	LCD_WriteReg(0x0021,0x0000);         
#endif       
	LCD_WriteReg(0x0030,0x0000);
	LCD_WriteReg(0x0031,0x0507);
	LCD_WriteReg(0x0032,0x0104);
	LCD_WriteReg(0x0035,0x0105);
	LCD_WriteReg(0x0036,0x0404);
	LCD_WriteReg(0x0037,0x0603);
	LCD_WriteReg(0x0038,0x0004);
	LCD_WriteReg(0x0039,0x0007);
	LCD_WriteReg(0x003c,0x0501);
	LCD_WriteReg(0x003d,0x0404);
	LCD_WriteReg(0x0050,0x0000);//ˮƽ GRAM��ʼλ��
	LCD_WriteReg(0x0051,0x00ef);//ˮƽGRAM��ֹλ��
	LCD_WriteReg(0x0052,0x0000);//��ֱGRAM��ʼλ��
	LCD_WriteReg(0x0053,0x013f);//��ֱGRAM��ֹλ��
#ifdef ILI9325        
	LCD_WriteReg(0x0060,0xa700);//G
#endif
#ifdef ILI9320        
	LCD_WriteReg(0x0060,0x2700);//G  
#endif    
	LCD_WriteReg(0x0061,0x0001);//Enables the grayscale inversion of the image by setting REV=1.??????????????????????????????
	LCD_WriteReg(0x006a,0x0000);//��ʹ�þ�������
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
	//��ʾ����д�� 0x0130�ǲ���ʾ��ǰ����
	//0x0173����ʾ��ǰ����
	LCD_WriteReg(0x0007,0x0133);
#ifdef Immediately
	LCD_WriteReg(0x0007,0x0173);      
#endif        
//      LCD_WriteCommand(0x0022);
	//��һ�����صĶ�ȡ��������Чֵ���������ȶ�ȡһ�Σ���ȥ��Чֵ

   Delay(5); /* delay 50 ms */
//    printf("\n\r ######********* LCD_ReadSta() = 0x%x ###### ", LCD_ReadSta());
#endif   
#if 1
	LCD_WriteReg(0x00e3,0x3008);
	LCD_WriteReg(0x00e7,0x0012);
	LCD_WriteReg(0x00ef,0x1231);//Set the internal vcore voltage
 // 		LCD_WriteReg(0x00e7,0x0010);      
        LCD_WriteReg(0x0000,0x0001);  			//start internal osc
        LCD_WriteReg(0x0001,0x0100);     
        LCD_WriteReg(0x0002,0x0700); 				//power on sequence                     
        LCD_WriteReg(0x0003,(1<<12)|(1<<5)|(1<<4) ); 	//65K 
        LCD_WriteReg(0x0004,0x0000);                                   
        LCD_WriteReg(0x0008,0x0207);	           
        LCD_WriteReg(0x0009,0x0000);         
        LCD_WriteReg(0x000a,0x0000); 				//display setting         
        LCD_WriteReg(0x000c,0x0001);				//display setting          
        LCD_WriteReg(0x000d,0x0000); 				//0f3c          
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
//bear        LCD_WriteReg(0x0092,0x0000);  
        LCD_WriteReg(0x0092,0x0600);  
	if(DeviceCode==0x9328)
      {   
           LCD_WriteReg(0x0093,0x0003);
           LCD_WriteReg(0x0095,0x0110);
           LCD_WriteReg(0x0097,0x0000);        
           LCD_WriteReg(0x0098,0x0000);  
       }
         //display on sequence     
        LCD_WriteReg(0x0007,0x0133);
    
        LCD_WriteReg(0x0020,0x0000);                                                            
        LCD_WriteReg(0x0021,0x0000);
        
#endif
	}
	else if(DeviceCode==0x9320||DeviceCode==0x9300)
	{
		LCD_WriteReg(0x00,0x0000);
		LCD_WriteReg(0x01,0x0100);	//Driver Output Contral.
		LCD_WriteReg(0x02,0x0700);	//LCD Driver Waveform Contral.
//		LCD_WriteReg(0x03,0x1030);	//Entry Mode Set.
		LCD_WriteReg(0x03,0x1018);	//Entry Mode Set.
	
		LCD_WriteReg(0x04,0x0000);	//Scalling Contral.
		LCD_WriteReg(0x08,0x0202);	//Display Contral 2.(0x0207)
		LCD_WriteReg(0x09,0x0000);	//Display Contral 3.(0x0000)
		LCD_WriteReg(0x0a,0x0000);	//Frame Cycle Contal.(0x0000)
		LCD_WriteReg(0x0c,(1<<0));	//Extern Display Interface Contral 1.(0x0000)
		LCD_WriteReg(0x0d,0x0000);	//Frame Maker Position.
		LCD_WriteReg(0x0f,0x0000);	//Extern Display Interface Contral 2.
	
		for(i=50000;i>0;i--);
		for(i=50000;i>0;i--);
		LCD_WriteReg(0x07,0x0101);	//Display Contral.
		for(i=50000;i>0;i--);
		for(i=50000;i>0;i--);
	
		LCD_WriteReg(0x10,(1<<12)|(0<<8)|(1<<7)|(1<<6)|(0<<4));	//Power Control 1.(0x16b0)
		LCD_WriteReg(0x11,0x0007);								//Power Control 2.(0x0001)
		LCD_WriteReg(0x12,(1<<8)|(1<<4)|(0<<0));					//Power Control 3.(0x0138)
		LCD_WriteReg(0x13,0x0b00);								//Power Control 4.
		LCD_WriteReg(0x29,0x0000);								//Power Control 7.
	
		LCD_WriteReg(0x2b,(1<<14)|(1<<4));
		
		LCD_WriteReg(0x50,0);		//Set X Start.
		LCD_WriteReg(0x51,239);	//Set X End.
		LCD_WriteReg(0x52,0);		//Set Y Start.
		LCD_WriteReg(0x53,319);	//Set Y End.
	
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
	}
	else if(DeviceCode==0x9331)
	{
		LCD_WriteReg(0x00E7, 0x1014);
		LCD_WriteReg(0x0001, 0x0100); // set SS and SM bit   0x0100
		LCD_WriteReg(0x0002, 0x0200); // set 1 line inversion
		LCD_WriteReg(0x0003, 0x1030); // set GRAM write direction and BGR=1.     0x1030
		LCD_WriteReg(0x0008, 0x0202); // set the back porch and front porch
		LCD_WriteReg(0x0009, 0x0000); // set non-display area refresh cycle ISC[3:0]
		LCD_WriteReg(0x000A, 0x0000); // FMARK function
		LCD_WriteReg(0x000C, 0x0000); // RGB interface setting
		LCD_WriteReg(0x000D, 0x0000); // Frame marker Position
		LCD_WriteReg(0x000F, 0x0000); // RGB interface polarity
		//*************Power On sequence ****************//
		LCD_WriteReg(0x0010, 0x0000); // SAP, BT[3:0], AP, DSTB, SLP, STB
		LCD_WriteReg(0x0011, 0x0007); // DC1[2:0], DC0[2:0], VC[2:0]
		LCD_WriteReg(0x0012, 0x0000); // VREG1OUT voltage
		LCD_WriteReg(0x0013, 0x0000); // VDV[4:0] for VCOM amplitude
		ili9320_Delay(200); // Dis-charge capacitor power voltage
		LCD_WriteReg(0x0010, 0x1690); // SAP, BT[3:0], AP, DSTB, SLP, STB
		LCD_WriteReg(0x0011, 0x0227); // DC1[2:0], DC0[2:0], VC[2:0]
		ili9320_Delay(50); // Delay 50ms
		LCD_WriteReg(0x0012, 0x000C); // Internal reference voltage= Vci;
		ili9320_Delay(50); // Delay 50ms
		LCD_WriteReg(0x0013, 0x0800); // Set VDV[4:0] for VCOM amplitude
		LCD_WriteReg(0x0029, 0x0011); // Set VCM[5:0] for VCOMH
		LCD_WriteReg(0x002B, 0x000B); // Set Frame Rate
		ili9320_Delay(50); // Delay 50ms
		LCD_WriteReg(0x0020, 0x0000); // GRAM horizontal Address
		LCD_WriteReg(0x0021, 0x0000); // GRAM Vertical Address
		// ----------- Adjust the Gamma Curve ----------//
		LCD_WriteReg(0x0030, 0x0000);
		LCD_WriteReg(0x0031, 0x0106);
		LCD_WriteReg(0x0032, 0x0000);
		LCD_WriteReg(0x0035, 0x0204);
		LCD_WriteReg(0x0036, 0x160A);
		LCD_WriteReg(0x0037, 0x0707);
		LCD_WriteReg(0x0038, 0x0106);
		LCD_WriteReg(0x0039, 0x0707);
		LCD_WriteReg(0x003C, 0x0402);
		LCD_WriteReg(0x003D, 0x0C0F);
		//------------------ Set GRAM area ---------------//
		LCD_WriteReg(0x0050, 0x0000); // Horizontal GRAM Start Address
		LCD_WriteReg(0x0051, 0x00EF); // Horizontal GRAM End Address
		LCD_WriteReg(0x0052, 0x0000); // Vertical GRAM Start Address
		LCD_WriteReg(0x0053, 0x013F); // Vertical GRAM Start Address
		LCD_WriteReg(0x0060, 0x2700); // Gate Scan Line
		LCD_WriteReg(0x0061, 0x0001); // NDL,VLE, REV
		LCD_WriteReg(0x006A, 0x0000); // set scrolling line
		//-------------- Partial Display Control ---------//
		LCD_WriteReg(0x0080, 0x0000);
		LCD_WriteReg(0x0081, 0x0000);
		LCD_WriteReg(0x0082, 0x0000);
		LCD_WriteReg(0x0083, 0x0000);
		LCD_WriteReg(0x0084, 0x0000);
		LCD_WriteReg(0x0085, 0x0000);
		//-------------- Panel Control -------------------//
		LCD_WriteReg(0x0090, 0x0010);
		LCD_WriteReg(0x0092, 0x0600);
		LCD_WriteReg(0x0007,0x0021);		
		ili9320_Delay(50);
		LCD_WriteReg(0x0007,0x0061);
		ili9320_Delay(50);
		LCD_WriteReg(0x0007,0x0133);  // 262K color and display ON
		ili9320_Delay(50);
	}
	else if(DeviceCode==0x9919)
	{
		//*********POWER ON &RESET DISPLAY OFF
		 LCD_WriteReg(0x28,0x0006);
		
		 LCD_WriteReg(0x00,0x0001);
		
		 LCD_WriteReg(0x10,0x0000);
		
		 LCD_WriteReg(0x01,0x72ef);

		 LCD_WriteReg(0x02,0x0600);

		 LCD_WriteReg(0x03,0x6a38);
		
		 LCD_WriteReg(0x11,0x6874);//70
		
		 
		     //  RAM WRITE DATA MASK
		 LCD_WriteReg(0x0f,0x0000); 
		    //  RAM WRITE DATA MASK
		 LCD_WriteReg(0x0b,0x5308); 
		
		 LCD_WriteReg(0x0c,0x0003);
		
		 LCD_WriteReg(0x0d,0x000a);
		
		 LCD_WriteReg(0x0e,0x2e00);  //0030
		
		 LCD_WriteReg(0x1e,0x00be);
		
		 LCD_WriteReg(0x25,0x8000);
		
		 LCD_WriteReg(0x26,0x7800);
		
		 LCD_WriteReg(0x27,0x0078);
		
		 LCD_WriteReg(0x4e,0x0000);
		
		 LCD_WriteReg(0x4f,0x0000);
		
		 LCD_WriteReg(0x12,0x08d9);
		
		 // -----------------Adjust the Gamma Curve----//
		 LCD_WriteReg(0x30,0x0000);	 //0007
		
		 LCD_WriteReg(0x31,0x0104);	   //0203
		
		 LCD_WriteReg(0x32,0x0100);		//0001

		 LCD_WriteReg(0x33,0x0305);	  //0007

		 LCD_WriteReg(0x34,0x0505);	  //0007
		
		 LCD_WriteReg(0x35,0x0305);		 //0407
		
		 LCD_WriteReg(0x36,0x0707);		 //0407
		
		 LCD_WriteReg(0x37,0x0300);		  //0607
		
		 LCD_WriteReg(0x3a,0x1200);		 //0106
		
		 LCD_WriteReg(0x3b,0x0800);		 

		 LCD_WriteReg(0x07,0x0033);
	}
	else if(DeviceCode==0x1505)
	{
// second release on 3/5  ,luminance is acceptable,water wave appear during camera preview
        LCD_WriteReg(0x0007,0x0000);
        ili9320_Delay(5);
        LCD_WriteReg(0x0012,0x011C);//0x011A   why need to set several times?
        LCD_WriteReg(0x00A4,0x0001);//NVM
    //
        LCD_WriteReg(0x0008,0x000F);
        LCD_WriteReg(0x000A,0x0008);
        LCD_WriteReg(0x000D,0x0008);
       
  //GAMMA CONTROL/
        LCD_WriteReg(0x0030,0x0707);
        LCD_WriteReg(0x0031,0x0007); //0x0707
        LCD_WriteReg(0x0032,0x0603); 
        LCD_WriteReg(0x0033,0x0700); 
        LCD_WriteReg(0x0034,0x0202); 
        LCD_WriteReg(0x0035,0x0002); //?0x0606
        LCD_WriteReg(0x0036,0x1F0F);
        LCD_WriteReg(0x0037,0x0707); //0x0f0f  0x0105
        LCD_WriteReg(0x0038,0x0000); 
        LCD_WriteReg(0x0039,0x0000); 
        LCD_WriteReg(0x003A,0x0707); 
        LCD_WriteReg(0x003B,0x0000); //0x0303
        LCD_WriteReg(0x003C,0x0007); //?0x0707
        LCD_WriteReg(0x003D,0x0000); //0x1313//0x1f08
        ili9320_Delay(5);
        LCD_WriteReg(0x0007,0x0001);
        LCD_WriteReg(0x0017,0x0001);   //Power supply startup enable
        ili9320_Delay(5);
  
  //power control//
        LCD_WriteReg(0x0010,0x17A0); 
        LCD_WriteReg(0x0011,0x0217); //reference voltage VC[2:0]   Vciout = 1.00*Vcivl
        LCD_WriteReg(0x0012,0x011E);//0x011c  //Vreg1out = Vcilvl*1.80   is it the same as Vgama1out ?
        LCD_WriteReg(0x0013,0x0F00); //VDV[4:0]-->VCOM Amplitude VcomL = VcomH - Vcom Ampl
        LCD_WriteReg(0x002A,0x0000);  
        LCD_WriteReg(0x0029,0x000A); //0x0001F  Vcomh = VCM1[4:0]*Vreg1out    gate source voltage??
        LCD_WriteReg(0x0012,0x013E); // 0x013C  power supply on
           //Coordinates Control//
        LCD_WriteReg(0x0050,0x0000);//0x0e00
        LCD_WriteReg(0x0051,0x00EF); 
        LCD_WriteReg(0x0052,0x0000); 
        LCD_WriteReg(0x0053,0x013F); 
    //Pannel Image Control//
        LCD_WriteReg(0x0060,0x2700); 
        LCD_WriteReg(0x0061,0x0001); 
        LCD_WriteReg(0x006A,0x0000); 
        LCD_WriteReg(0x0080,0x0000); 
    //Partial Image Control//
        LCD_WriteReg(0x0081,0x0000); 
        LCD_WriteReg(0x0082,0x0000); 
        LCD_WriteReg(0x0083,0x0000); 
        LCD_WriteReg(0x0084,0x0000); 
        LCD_WriteReg(0x0085,0x0000); 
  //Panel Interface Control//
        LCD_WriteReg(0x0090,0x0013); //0x0010 frenqucy
        LCD_WriteReg(0x0092,0x0300); 
        LCD_WriteReg(0x0093,0x0005); 
        LCD_WriteReg(0x0095,0x0000); 
        LCD_WriteReg(0x0097,0x0000); 
        LCD_WriteReg(0x0098,0x0000); 
  
        LCD_WriteReg(0x0001,0x0100); 
        LCD_WriteReg(0x0002,0x0700); 
        LCD_WriteReg(0x0003,0x1030); 
        LCD_WriteReg(0x0004,0x0000); 
        LCD_WriteReg(0x000C,0x0000); 
        LCD_WriteReg(0x000F,0x0000); 
        LCD_WriteReg(0x0020,0x0000); 
        LCD_WriteReg(0x0021,0x0000); 
        LCD_WriteReg(0x0007,0x0021); 
        ili9320_Delay(20);
        LCD_WriteReg(0x0007,0x0061); 
        ili9320_Delay(20);
        LCD_WriteReg(0x0007,0x0173); 
        ili9320_Delay(20);
	}							 
	else if(DeviceCode==0x8989)
	{
	    LCD_WriteReg(0x0000,0x0001);		//�򿪾���
	    LCD_WriteReg(0x0003,0xA8A4);		//0xA8A4
	    LCD_WriteReg(0x000C,0x0000);        
	    LCD_WriteReg(0x000D,0x080C);        
	    LCD_WriteReg(0x000E,0x2B00);        
	    LCD_WriteReg(0x001E,0x00B0);        
	    LCD_WriteReg(0x0001,0x2B3F);		//�����������320*240  0x693F
	    LCD_WriteReg(0x0002,0x0600);     	//LCD Driving Waveform control
	    LCD_WriteReg(0x0010,0x0000);     
	    LCD_WriteReg(0x0011,0x6070);		//0x4030	//�������ݸ�ʽ  16λɫ	���� 0x6058
	    LCD_WriteReg(0x0005,0x0000);     
	    LCD_WriteReg(0x0006,0x0000);     
	    LCD_WriteReg(0x0016,0xEF1C);     
	    LCD_WriteReg(0x0017,0x0003);     
	    LCD_WriteReg(0x0007,0x0233);		//0x0233       
	    LCD_WriteReg(0x000B,0x0000);     
	    LCD_WriteReg(0x000F,0x0000);		//ɨ�迪ʼ��ַ
	    LCD_WriteReg(0x0041,0x0000);     
	    LCD_WriteReg(0x0042,0x0000);     
	    LCD_WriteReg(0x0048,0x0000);     
	    LCD_WriteReg(0x0049,0x013F);     
	    LCD_WriteReg(0x004A,0x0000);     
	    LCD_WriteReg(0x004B,0x0000);     
	    LCD_WriteReg(0x0044,0xEF00);     
	    LCD_WriteReg(0x0045,0x0000);     
	    LCD_WriteReg(0x0046,0x013F);     
	    LCD_WriteReg(0x0030,0x0707);     
	    LCD_WriteReg(0x0031,0x0204);     
	    LCD_WriteReg(0x0032,0x0204);     
	    LCD_WriteReg(0x0033,0x0502);     
	    LCD_WriteReg(0x0034,0x0507);     
	    LCD_WriteReg(0x0035,0x0204);     
	    LCD_WriteReg(0x0036,0x0204);     
	    LCD_WriteReg(0x0037,0x0502);     
	    LCD_WriteReg(0x003A,0x0302);     
	    LCD_WriteReg(0x003B,0x0302);     
	    LCD_WriteReg(0x0023,0x0000);     
	    LCD_WriteReg(0x0024,0x0000);     
	    LCD_WriteReg(0x0025,0x8000);     
	    LCD_WriteReg(0x004e,0);        //��(X)��ַ0
	    LCD_WriteReg(0x004f,0);        //��(Y)��ַ0
	}
    else
    {
//        printf("\n\r ###### Err: Unknow DeviceCode 0x%x ###### ", DeviceCode);
    }
  for(i=50000;i>0;i--);
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
//inline void ili9320_SetCursor(u16 x,u16 y)
void ili9320_SetCursor(u16 x,u16 y)
{
	if(DeviceCode==0x8989)
	{
	 	LCD_WriteReg(0x004e,y);        //��
    	LCD_WriteReg(0x004f,0x13f-x);  //��
	}
	else if((DeviceCode==0x9919))
	{
		LCD_WriteReg(0x004e,x); // ��
  		LCD_WriteReg(0x004f,y); // ��	
	}
    /*
	else if((DeviceCode==0x9325))
	{
		LCD_WriteReg(0x0020,x); // ��
  		LCD_WriteReg(0x0021,y); // ��	
	}
	*/
	else
	{
  		LCD_WriteReg(0x0020,y); // ��
  		LCD_WriteReg(0x0021,0x13f-x); // ��
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
//inline void ili9320_SetWindows(u16 StartX,u16 StartY,u16 EndX,u16 EndY)
void ili9320_SetWindows(u16 StartX,u16 StartY,u16 EndX,u16 EndY)
{
  ili9320_SetCursor(StartX,StartY);
  LCD_WriteReg(0x0050, StartX);
  LCD_WriteReg(0x0052, StartY);
  LCD_WriteReg(0x0051, EndX);
  LCD_WriteReg(0x0053, EndY);
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
* ��    �ߣ� www.armjishu.com
****************************************************************************/
void ili9320_DrawPicture(u16 StartX,u16 StartY,u16 EndX,u16 EndY,u16 *pic)
{
  u32  i, total;
  u16 data1,data2,data3;
  u16 *picturepointer = pic;
  u16 x,y;
  
//   printf("ili9320_DrawPicture StartX %d StartY %d EndX %d EndY %d \n\r", StartX, StartY, EndX, EndY);

  x=StartX;
  y=StartY;
  
  total = (EndX - StartX + 1)*(EndY - StartY + 1 )/2;

  for (i=0;i<total;i++)
  {
      data1 = *picturepointer++;
      data2 = *picturepointer++;
      data3 = ((data1 >>3)& 0x001f) |((data1>>5) & 0x07E0) | ((data2<<8) & 0xF800);
      ili9320_SetPoint(x,y,data3);
      y++;
      if(y > EndY)
      {
          x++;
          y=StartY;
      }


      data1 = data2;
      data2 = *picturepointer++;
      data3 = ((data1 >>11)& 0x001f) |((data2<<3) & 0x07E0) | ((data2) & 0xF800);
      ili9320_SetPoint(x,y,data3);
      y++;
      if(y > EndY)
      {
          x++;
          y=StartY;
      }
  }

}
#if 0
void ili9320_DrawPicture(u16 StartX,u16 StartY,u16 EndX,u16 EndY,u16 *pic)
{
  u32  i, total;
  u16 data1,data2,data3;
  u16 *picturepointer = pic;
  //ili9320_SetWindows(StartX,StartY,EndX,EndY);

  LCD_WriteReg(0x0003,(1<<12)|(0<<5)|(1<<4) ); 

  ili9320_SetCursor(StartX,StartY);
  
  LCD_WriteRAM_Prepare();
  total = (EndX + 1)*(EndY + 1 ) / 2;
  for (i=0;i<total;i++)
  {
      data1 = *picturepointer++;
      data2 = *picturepointer++;
      data3 = ((data1 >>3)& 0x001f) |((data1>>5) & 0x07E0) | ((data2<<8) & 0xF800);
      LCD_WriteRAM(data3);
      data1 = data2;
      data2 = *picturepointer++;
      data3 = ((data1 >>11)& 0x001f) |((data2<<3) & 0x07E0) | ((data2) & 0xF800);
      LCD_WriteRAM(data3);
  }

  LCD_WriteReg(0x0003,(1<<12)|(1<<5)|(1<<4) ); 
}
#endif
/*
void ili9320_DrawPicture(u16 StartX,u16 StartY,u16 EndX,u16 EndY,u16 *pic)
{
  u32  i, total;
  ili9320_SetWindows(StartX,StartY,EndX,EndY);
  ili9320_SetCursor(StartX,StartY);
  
  LCD_WriteRAM_Prepare();
  total = EndX*EndY;
  for (i=0;i<total;i++)
  {
      LCD_WriteRAM(*pic++);
  }
}
*/
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
void ili9320_PutChar(u16 x,u16 y,u8 c,u16 charColor,u16 bkColor)  // Lihao
{
  u16 i=0;
  u16 j=0;
  
  u8 tmp_char=0;
  
  if(HyalineBackColor == bkColor)
  {
    for (i=0;i<16;i++)
    {
      tmp_char=ascii_8x16[((c-0x20)*16)+i];
      for (j=0;j<8;j++)
      {
        if ( ((tmp_char >> (7-j)) & 0x01 )== 0x01)
          {
            ili9320_SetPoint(x+j,y+i,charColor); // �ַ���ɫ
          }
          else
          {
            // do nothing // ͸������
          }
      }
    }
  }
  else
  {
        for (i=0;i<16;i++)
    {
      tmp_char=ascii_8x16[((c-0x20)*16)+i];
      for (j=0;j<8;j++)
      {
        if ( ((tmp_char >> (7-j)) & 0x01 )== 0x01)
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
}
			
/****************************************************************************
* ��    �ƣ�ili9320_PutChar_16x24(u16 x,u16 y,u8 c,u16 charColor,u16 bkColor)
* ��    �ܣ���ָ��������ʾһ��16x24�����ascii�ַ�
* ��ڲ�����x          ������
*           y          ������
*           charColor  �ַ�����ɫ
*           bkColor    �ַ�������ɫ
* ���ڲ�������
* ˵    ������ʾ��Χ�޶�Ϊ����ʾ��ascii��
* ���÷�����ili9320_PutChar(10,10,'a',0x0000,0xffff);
****************************************************************************/
void ili9320_PutChar_16x24(u16 x,u16 y,u8 c,u16 charColor,u16 bkColor)
{

  u16 i=0;
  u16 j=0;
  
  u16 tmp_char=0;

  if(HyalineBackColor == bkColor)
  {
    for (i=0;i<24;i++)
    {
      tmp_char=ASCII_Table_16x24[((c-0x20)*24)+i];
      for (j=0;j<16;j++)
      {
        if ( ((tmp_char >> j) & 0x01) == 0x01)
          {
            ili9320_SetPoint(x+j,y+i,charColor); // �ַ���ɫ
          }
          else
          {
              // do nothing // ͸������
          }
      }
    }
  }
  else
  {
    for (i=0;i<24;i++)
    {
      tmp_char=ASCII_Table_16x24[((c-0x20)*24)+i];
      for (j=0;j<16;j++)
      {
        if (( (tmp_char >> j) & 0x01) == 0x01)
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
   delay_ms(nCount);
  //for(; nCount != 0; nCount--);
}

void ili9320_PutStr_16x24(u16 StartX, u16 StartY, u8 *str, u16 len, u16 charColor, u16 bkColor)
{
  u16 i;
  u8 *pstr = str;
      
      for (i=0 ;i<len;i++)
      {
        ili9320_PutChar_16x24((StartX+16*i),StartY,*pstr++,charColor,bkColor);
      }
      
}

void ili9320_PutStr_16x24_Center(u16 StartY, u8 *str, u16 len, u16 charColor, u16 bkColor)
{
  u16 StartX;

  StartX = (320 - 16*len)/2;
      
      ili9320_PutStr_16x24(StartX,StartY, str, len, charColor, bkColor);
}

void ili9320_ColorScreen(void)
{
  u16 i, j, k, Color;
  
  for(i=0,k=0; i<320; i++)
  {
      if(!(k & 0x3F))
      {
          k= k + 19;
      }
      else
      {
          k++;
      }
      j = (k>>1) & 0x1F;
      switch(k>>6)
      {
         case 0:
              Color = (j<<11) ;
              break;
         case 1:
              Color = (j<<11) | (j<<6) ;
              break;
         case 2:
              Color =  (j<<6) ;
              break;
         case 3:
              Color =  (j<<6) | j;
              break;
         case 4:
              Color = j;              
              break;
         case 5:
              Color = (j<<11) | j;
              break;
         default:
              Color = (j<<11) |(j<<6) | j;
      }
      GUI_Line(i, 0, i, 239, Color);
  }
}

void ili9320_GreyScreen(void)
{
  u16 i, j, Color;
  
  for(i=0; i<320; i++)
  {
      j =  i /10;
      Color = (j<<11) | (j<<6) | j;       
      GUI_Line(i, 0, i, 239, Color);
  }
}

void DrawPicture_Center(u16 *PictureAddr)  
{
    PictureWidth = (picture[0x13] << 8) | picture[0x12];
    PictureHeight  = (picture[0x17] << 8) | picture[0x16];
    
//     printf("\n\r PictureWidth is %d  0x%X ", PictureWidth, PictureWidth);
//     printf("\n\r PictureHeight is %d  0x%X ", PictureHeight, PictureHeight);
    
    ili9320_Clear(Blue); 
    ili9320_DrawPicture(0, (240-PictureWidth+1)/2, 320-1, ((240+PictureWidth+1)/2)-1, (u16 *)(picture + BmpHeadSize));
}
/**pBuffer��ź��ֱ���ֵ*pointָ�����ַ���
����=�������λ�ֽ�-0xA0��λ��=�������λ�ֽ�-0xA0��
������ʼλ��=32*[������-1��*94+��λ��-1��]
����t[3]="��"����t[0]�Ǹ�λ�ֽ�,t[1]�ǵ�λ�ֽ�
*/
void GetChineseCode(u8 *pBuffer,u8 *point)
{
  
  u8 High8bit,Low8bit,i;
 
  High8bit=*point;
  Low8bit=*(point+1);
  High8bit=High8bit-0xA0;
  Low8bit=Low8bit-0xA0;
  //*(pBuffer+i)�൱��chinesebuffer[i]
  for(i=0;i<32;i++)
  {
   *(pBuffer+i)= *(HzLib + 32*((High8bit-0x10)*94+Low8bit-1) + i);
   //*(pBuffer+i)= *(HzLib + 32*((High8bit-0xb0)*94+Low8bit-0xa1) + i);
  }
}
/****************************************************************
��������Lcdд1�����ĺ���
��ڲ�����x,�������꣬�����ҷֱ���0~15
          y,�������꣬���ϵ��·ֱ�Ϊ0~19
          CharColaor,�ַ�����ɫ 
          CharBackColor,�ַ�������ɫ 
         ASCIICode,��Ӧ���ĵı���
Ҳ����˵��320240�ֱ��ʵ���ʾ������������ʾ15�����ַ�����������ʾ20��
����ֵ����

ע�⣡���������������ʹ�ô˺�����Ӧ�ü���Lcd_Rs_H()��Set_Cs;Ϊ���Ż�ϵͳʡȥ��
���ָ�����˺���ִ�е���һ�������д�����RS_L�������д�뽫����
����ΪILI9320��Ϊ��RS_Lʱд���������
*****************************************************************/
void Lcd_WriteChineseString(u8 x,u8 y,u16 CharColor,u16 CharBackColor,u8 *s)
{  
	u8 *pBuffer;
    u8 High8bit,Low8bit,i;
	u8 ByteCounter,BitCounter;
	u8 ChineseBuffer[32];//��ź��ֱ���
	u8 X,Y;
	X=x	;Y=y;
    do
    {   //*s="����һ����";
		High8bit=*s++;//�������8λ
		Low8bit=*s++;//�������8λ
		High8bit=High8bit-0xA0;// ����
		Low8bit=Low8bit-0xA0;  //λ��
		for(i=0;i<32;i++)
		{
		     ChineseBuffer[i]= *(HzLib + 32*((High8bit-0x10)*94+Low8bit-1) + i);	
		}
		pBuffer=ChineseBuffer;
//		ClrCs;
//		Address_set((Y)*16,y*16,x*16+15,y*16+15);
//		SetCs;      
		//32��8�ֽ��� 
		if(HyalineBackColor ==CharBackColor) 
		{  
		for(ByteCounter=0; ByteCounter<32; ByteCounter++)
		{ 
			for(BitCounter=0;BitCounter<8;BitCounter++)
			{
				
				if((*(pBuffer+ByteCounter) & (0x80 >> BitCounter)) == 0x00)
				{	 
				     //Lcd_Write_Data(CharBackColor);
				}
				else
				{	
				     ili9320_SetPoint(X,Y,CharColor);
				} 
				X++;
				if(((X-x)-15)>0)
				{
					X=x;
					Y++;
				}    
			}
		//pBuffer++;
		}
		}
		else
		{
		  for(ByteCounter=0; ByteCounter<32; ByteCounter++)
		{ 
			for(BitCounter=0;BitCounter<8;BitCounter++)
			{
				if((*(pBuffer+ByteCounter) & (0x80 >> BitCounter)) == 0x00)
				{	 
				     ili9320_SetPoint(X,Y,CharBackColor); // ������ɫ
				}
				else
				{	
				     ili9320_SetPoint(X,Y,CharColor); //�ַ���ɫ
				} 
				X++;
				if(((X-x)-15)>0)
				{
					X=x;
					Y++;
				}    
			}
		//pBuffer++;
		}
		}
		X=X+16;	 //�������в�д ���������ų���
		Y=Y-16;
		x=X;
		y=Y;
    } 	
     while(*s!=0);
}


// int main()
// {
// //u8 c[]="��";
// u8 b[]="�����ɵ��";
// u8 c2[1]="w";

// u16 CharColor;
// u16 CharBackColor;
// SYS_CONFIG();

//  ili9320_Clear(Blue);  

// CharColor=Black;
// CharBackColor=White;										

// ili9320_PutChar(20,20,c2[0],CharColor,CharBackColor);
// Lcd_WriteChineseString(40,40,CharColor,CharBackColor,b);
// printf("���� %d",1);
//  while (1); 
// }
/*����lcd*/
//u8 c[]="��";
//u8 b[]="�����ɵ��";
//u8 c2[1]="w";
////  u16 i, len, c2len;
////  u16 x;
////  u16 y;
////  u8 c[] = "www.armjishu.com";
////  u8 c2[] = "MP3 LCD 320X240";
////  u8 *str;
////  u16 charColor;
////  u16 bkColor;
////  
////  len = sizeof(c)-1;
////  c2len = sizeof(c2)-1;
//u16 CharColor;
//u16 CharBackColor;
// SYS_CONFIG();

//  ili9320_Clear(Blue);  
//
//CharColor=Black;
//CharBackColor=White;										
////  x = 0;
////  y = 0;
////  str = c;
////  charColor = Black;
////  bkColor = White;
////  for (i=0;i<len;i++)
////  {
////    ili9320_PutChar((x+8*i),y,*str++,charColor,bkColor);
////  }
////
////  charColor = Yellow;
////  bkColor = Red;
//// ili9320_PutStr_16x24_Center(20, c2, c2len,charColor, bkColor);
//// GUI_Line(20, 20, 100, 100,Green);
//// GUI_Circle(165,120,100,Red,0);
//// GUI_Rectangle(20, 20, 160, 160 ,Red,1);
//// ili9320_SetPoint(200,200,Red);
//ili9320_PutChar(20,20,c2[0],CharColor,CharBackColor);
//Lcd_WriteChineseString(40,40,CharColor,CharBackColor,b);
////Lcd_Write32X32ChineseString(100,100,CharColor,CharBackColor,c);
////ili9320_PutHZ_16x16(40, 40, 10, CharColor, CharBackColor,b);
//  while (1); 
////  {
////      DrawPicture_Center((u16 *)picture);
////      ili9320_PutStr_16x24_Center(20, c, len,charColor, bkColor);
////	  
////      ili9320_PutStr_16x24_Center(200, c2, c2len,charColor, bkColor);
////delay_ms(5000);    
////      ili9320_ColorScreen();
////      ili9320_PutStr_16x24_Center(108, c, len,White, HyalineBackColor);
////delay_ms(5000);
////      ili9320_GreyScreen();
////      ili9320_PutStr_16x24_Center(108, c, len,White, HyalineBackColor);
////delay_ms(5000); 
////  }
/*����lcd*/
