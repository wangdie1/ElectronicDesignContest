
#include "wt_display.h"
#include "remote.h"
extern u8 bMenu_index;
volatile static u16 hTimebase_Blinking;
static u8 bPrevious_Visualization=0;
static u8 bPresent_Visualization;


void Display_Welcome_Message(void)
{
	u8 *ptr="һ��λ�Ʋ���״̬";
	LCD_StrShow(0,0,ptr);
	ptr="����λ�ƿ���״̬";
	LCD_StrShow(0,1,ptr);
	ptr="��������λ��ת��";
	LCD_StrShow(0,2,ptr);
	ptr="�ġ�����";
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
				ptr="һ��λ�Ʋ���״̬";
				LCD_StrShow(0,0,ptr);
				ptr="����λ�ƿ���״̬";
				LCD_StrShow(0,1,ptr);
				ptr="��������λ��ת��";
				LCD_StrShow(0,2,ptr);
				ptr="�ġ�����";
				LCD_StrShow(0,3,ptr);
				break;
			case (VISUALIZATION_1):
				ptr="һ��λ�Ʋ���״̬";
				LCD_StrShow(0,0,ptr);
				ptr="A���ѹ��";
				LCD_StrShow(0,1,ptr);
				ptr="B���ѹ��";
				LCD_StrShow(0,2,ptr);
				ptr="λ��:";
				LCD_StrShow(0,3,ptr);
				break;
			case (VISUALIZATION_2):
				ptr="����λ�ƿ���״̬";
				LCD_StrShow(0,0,ptr);
				ptr="A���ѹ��";
				LCD_StrShow(0,1,ptr);
				ptr="Ŀ��λ�ƣ�";
				LCD_StrShow(0,2,ptr);
				ptr="��ǰλ��:";
				LCD_StrShow(0,3,ptr);
				break;
			case(VISUALIZATION_3):
				ptr="��������λ��ת��";
				LCD_StrShow(0,0,ptr);
				ptr="������";
				LCD_StrShow(0,1,ptr);
				ptr="Ŀ��λ�ƣ�";
				LCD_StrShow(0,2,ptr);
				ptr="��ǰλ��:";
				LCD_StrShow(0,3,ptr);
				break;
			case (VISUALIZATION_4):
				ptr="�ġ�����";
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