#include "Angle.h"

volatile float hAngle_Buffer[ANGLE_BUFFER_SIZE];
static u8 bAngle_Buffer_Index =0;

float ADC1_ConvertedValue = 0;
float ADC1_PrecentValue = 0;
int  bIs_First_AngleMeasure =0;


float ANG_Measure(void)
{
	ADC1_ConvertedValue = ADC_ConvertedValue;
	ADC1_PrecentValue = (ADC1_ConvertedValue/4095*3.3);
	return ADC1_PrecentValue;		
}
float ANG_Average_Calc(void)
{
		float wtemp;
		u32 i;
// 		wtemp = ANG_Measure();
		wtemp=ADC_ConvertedValue;
	
		hAngle_Buffer[bAngle_Buffer_Index] = (float)wtemp;
		bAngle_Buffer_Index++;
		if(bAngle_Buffer_Index == ANGLE_BUFFER_SIZE)
			{
				bAngle_Buffer_Index=0;
			}
			wtemp=0;
			for(i=0;i<ANGLE_BUFFER_SIZE;i++)
			{
					wtemp+=hAngle_Buffer[i];
			}
			wtemp/=ANGLE_BUFFER_SIZE;
			return wtemp;
}

void Clear_Angle_Buffer(void)
{
		u32 i;
	for(i=0;i<ANGLE_BUFFER_SIZE;i++)
	{
			hAngle_Buffer[i]=0;
	}
		bIs_First_AngleMeasure = 0;
}
void InitAngleBuffer(void)
{
		u32 i;
	for(i=0;i<ANGLE_BUFFER_SIZE;i++)
	{
			hAngle_Buffer[i]=ADC_ConvertedValue;
	}
}
	