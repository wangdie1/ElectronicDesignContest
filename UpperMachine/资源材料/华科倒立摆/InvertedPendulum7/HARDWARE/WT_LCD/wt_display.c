
#include "wt_display.h"
#include "remote.h"
extern u8 bMenu_index;
volatile static u16 hTimebase_Blinking;
static u8 bPrevious_Visualization=0;
static u8 bPresent_Visualization;


void Display_Welcome_Message(void)
{
	u8 *ptr="一、位移测量状态";
	LCD_StrShow(0,0,ptr);
	ptr="二、位移控制状态";
	LCD_StrShow(0,1,ptr);
	ptr="三、重量位移转换";
	LCD_StrShow(0,2,ptr);
	ptr="四、其他";
	LCD_StrShow(0,3,ptr);
}
void Display_LCD(void)
{
	if(TB_DisplayDelay_IsElapsed()==TRUE)
	{
		TB_SetDisplayDelay_Time(LCD_DISPLAY_DELAY);
		bPrevious_Visualization = bPresent_Visualization;
		bPresent_Visualization = ComputerVisualization(bMenu_index);
		
		switch(bPresent_Visualization)
		{
			u8 *ptr;
			s16 temp;
			case(VISUALIZATION_0):
				ptr="一、位移测量状态";
				LCD_StrShow(0,0,ptr);
				ptr="二、位移控制状态";
				LCD_StrShow(0,1,ptr);
				ptr="三、重量位移转换";
				LCD_StrShow(0,2,ptr);
				ptr="四、其他";
				LCD_StrShow(0,3,ptr);
				break;
			case (VISUALIZATION_1):
				ptr="一、位移测量状态";
				LCD_StrShow(0,0,ptr);
				ptr="A点电压：";
				LCD_StrShow(0,1,ptr);
				ptr="B点电压：";
				LCD_StrShow(0,2,ptr);
				ptr="位移:";
				LCD_StrShow(0,3,ptr);
				break;
			case (VISUALIZATION_2):
				ptr="二、位移控制状态";
				LCD_StrShow(0,0,ptr);
				ptr="A点电压：";
				LCD_StrShow(0,1,ptr);
				ptr="目标位移：";
				LCD_StrShow(0,2,ptr);
				ptr="当前位移:";
				LCD_StrShow(0,3,ptr);
				break;
			case(VISUALIZATION_3):
				ptr="三、重量位移转换";
				LCD_StrShow(0,0,ptr);
				ptr="重量：";
				LCD_StrShow(0,1,ptr);
				ptr="目标位移：";
				LCD_StrShow(0,2,ptr);
				ptr="当前位移:";
				LCD_StrShow(0,3,ptr);
				break;
			case (VISUALIZATION_4):
				ptr="四、其他";
				LCD_StrShow(0,0,ptr);
				break;
			default:break;
		}
	}
}

u8 ComputerVisualization(u8 bLocal_MenuIndex)
{
	u8 bTemp;
	switch(bLocal_MenuIndex)
	{
		case (MODE_SELECT_MENU):
			bTemp=VISUALIZATION_0;
		break;
		case (POSITION_MEASURE_MENU):
			bTemp=VISUALIZATION_1;
		break;
		case (POSITION_CONTROL_MENU):
			bTemp=VISUALIZATION_2;
		break;
		case (WEIGHT_POSITION_MENU):
			bTemp=VISUALIZATION_3;
		break;
		case (OTHERS_MODE_MENU):
			bTemp=VISUALIZATION_4;
		break;
		defualt:
		break;
		
	}
	  return (bTemp);
}