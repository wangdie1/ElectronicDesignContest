#include "color_del.h"
#include "usart.h"
#include "color_convert.h"
#include "lcd.h"
 void RGBtoHSL( u32 color, COLOR_HSV *Hsv)
{
   Hsv->hue=hsv_h_table[color];
	 Hsv->saturation=hsv_s_table[color];
	 Hsv->value=hsv_v_table[color];
	
	
	
	
}

 void HSLtoRGB( COLOR_HSV *Hsv,COLOR_RGB *Rgb )
{

	   int   h = Hsv->hue;                  // h must be [0, 360]  
     float s = Hsv->saturation/100.f;     // s must be [0, 1]  
     float v = Hsv->value/100.f;      // l must be [0, 1]  
     float f,q,t,p;
	   int hi;
	   
	   hi=(h/60)%6;
     f=(float)(h/60.f)-hi;
	   p=v*(1-s);
		 q=v*(1-f*s);
		 t=v*(1-(1-f)*s);
       
    switch(hi)
	  {
      case(0):
		  {
       Rgb->red = v*255;  
       Rgb->green =t*255;    
       Rgb->blue = p*255;
				break;
			}
			case(1):
		  {
			 Rgb->red = q*255;  
       Rgb->green =v*255;    
       Rgb->blue = p*255;
				break;
			}
			case(2):
		  {
			 Rgb->red = p*255;  
       Rgb->green =v*255;    
       Rgb->blue = t*255;
				break;
			}
			case(3):
		  {
			 Rgb->red = p*255;  
       Rgb->green =q*255;    
       Rgb->blue = v*255;
				break;
			}
			case(4):
		  {
			 Rgb->red = t*255;  
       Rgb->green =p*255;    
       Rgb->blue = v*255;
				break;
			}
			case(5):
		  {
			 Rgb->red = v*255;  
       Rgb->green =p*255;    
       Rgb->blue = q*255;
				break;
			}

	 }
  
      

}




void con_565to888(unsigned short color,COLOR_RGB *Rgb)
{
	unsigned short C16;

	C16 =color;

	Rgb->red   =	 (unsigned char)((C16&0xf800)>>8);
	Rgb->green =	 (unsigned char)((C16&0x07e0)>>3);
	Rgb->blue  =     (unsigned char)((C16&0x001f)<<3);
}




 int ColorMatch( COLOR_HSV *Hsv, TARGET_CONDI *Condition)
{
	if( 
		Hsv->hue		>=	Condition->H_MIN &&
		Hsv->hue		<=	Condition->H_MAX &&
		Hsv->saturation	>=	Condition->S_MIN &&
		Hsv->saturation	<=   Condition->S_MAX &&
		Hsv->value	>=	Condition->V_MIN &&
		Hsv->value	<=   Condition->V_MAX 
    )
		return 1;
	else
		return 0;
}


 int SearchCentre(unsigned int *x,unsigned int *y, TARGET_CONDI *Condition, SEARCH_AREA *Area)
{
	unsigned int SpaceX,SpaceY,i,j,k,FailCount=0;

	COLOR_HSV Hsl;
	u16 temp_color=0;
	
	SpaceX = Condition->WIDTH_MIN/3;
	SpaceY = Condition->HIGHT_MIN/3;

	for(i=Area->Y_Start;i<Area->Y_End;i+=SpaceY)
	{
		for(j=Area->X_Start;j<Area->X_End;j+=SpaceX)
		{
			FailCount=0;
			for(k=0;k<SpaceX+SpaceY;k++)
			{
				if(k<SpaceX)
					temp_color=LCD_ReadPoint(j+k,i+SpaceY/2);
				else
					temp_color=LCD_ReadPoint(j+SpaceX/2,i+(k-SpaceX));
				
				RGBtoHSL(temp_color,&Hsl);
				
				if(!ColorMatch(&Hsl,Condition))
					FailCount++;
				if(FailCount>((SpaceX+SpaceY)>>ALLOW_FAIL_PER))
					break;
			}
			if(k==SpaceX+SpaceY)
			{
				*x = j+SpaceX/2;
				*y = i+SpaceY/2;
				return 1;
			}
		}
	}
	return 0;
}




 int Corrode(unsigned int oldx,unsigned int oldy, TARGET_CONDI *Condition,RESULT *Resu)
{
	unsigned int Xmin,Xmax,Ymin,Ymax,i,FailCount=0;
	COLOR_HSV Hsv;
	unsigned int color_dat;
	 
	for(i=oldx;i>IMG_X;i--)
	{
		color_dat=LCD_ReadPoint(i,oldy);
		RGBtoHSL(color_dat,&Hsv);
		if(!ColorMatch(&Hsv,Condition))
			FailCount++;
		if(FailCount>(((Condition->WIDTH_MIN+Condition->WIDTH_MAX)>>2)>>ALLOW_FAIL_PER))
			break;	
	}
	Xmin=i;
	FailCount=0;
	
	for(i=oldx;i<IMG_X+IMG_W;i++)
	{
		color_dat=LCD_ReadPoint(i,oldy);
		RGBtoHSL(color_dat,&Hsv);
		if(!ColorMatch(&Hsv,Condition))
			FailCount++;
		if(FailCount>(((Condition->WIDTH_MIN+Condition->WIDTH_MAX)>>2)>>ALLOW_FAIL_PER))
			break;	
	}
	Xmax=i;
	FailCount=0;
	
	for(i=oldy;i>IMG_Y;i--)
	{
		color_dat=LCD_ReadPoint(oldx,i);
		RGBtoHSL(color_dat,&Hsv);
		if(!ColorMatch(&Hsv,Condition))
			FailCount++;
		if(FailCount>(((Condition->HIGHT_MIN+Condition->HIGHT_MAX)>>2)>>ALLOW_FAIL_PER))
			break;	
	}
	Ymin=i;
	FailCount=0;
	
	for(i=oldy;i<IMG_Y+IMG_H;i++)
	{
		color_dat=LCD_ReadPoint(oldx,i);
		RGBtoHSL(color_dat,&Hsv);
		if(!ColorMatch(&Hsv,Condition))
			FailCount++;
		if(FailCount>(((Condition->HIGHT_MIN+Condition->HIGHT_MAX)>>2)>>ALLOW_FAIL_PER))
			break;	
	}
	Ymax=i;
	FailCount=0;
	
	Resu->x	= (Xmin+Xmax)/2;
	Resu->y	= (Ymin+Ymax)/2;
	Resu->w	= Xmax-Xmin;
	Resu->h	= Ymax-Ymin;
 LCD_DrawRectangle(Xmin, Ymin, Xmax, Ymax);	
	if(((Xmax-Xmin)>(Condition->WIDTH_MIN)) && ((Ymax-Ymin)>(Condition->HIGHT_MIN)) &&\
	   ((Xmax-Xmin)<(Condition->WIDTH_MAX)) && ((Ymax-Ymin)<(Condition->HIGHT_MAX)) )
		return 1;	
	else
		return 0;	
}


int Trace( TARGET_CONDI *Condition,RESULT *Resu)
{
	unsigned int i;
	static unsigned int x0,y0,flag=0;
	static SEARCH_AREA Area={IMG_X,IMG_X+IMG_W,IMG_Y,IMG_Y+IMG_H};
	RESULT Result;	
	

	if(flag==0)
	{
		if(SearchCentre(&x0,&y0,Condition,&Area))
			flag=1;
		else
		{
			Area.X_Start= IMG_X	;
			Area.X_End  = IMG_X+IMG_W  ;
			Area.Y_Start= IMG_Y		;
			Area.Y_End  = IMG_Y+IMG_H;

			if(SearchCentre(&x0,&y0,Condition,&Area))	
			{
				flag=0;
				return 0;
			}	
		}
	}
	Result.x = x0;
	Result.y = y0;
	
	for(i=0;i<ITERATE_NUM;i++)
		Corrode(Result.x,Result.y,Condition,&Result);
		
	if(Corrode(Result.x,Result.y,Condition,&Result))
	{
		x0=Result.x;
		y0=Result.y;
		Resu->x=Result.x;
		Resu->y=Result.y;
		Resu->w=Result.w;
		Resu->h=Result.h;
		flag=1;

		Area.X_Start= Result.x - ((Result.w)>>1);
		Area.X_End  = Result.x + ((Result.w)>>1);
		Area.Y_Start= Result.y - ((Result.h)>>1);
		Area.Y_End  = Result.y + ((Result.h)>>1);


		return 1;
	}
	else
	{
		flag=0;
		return 0;
	}

}

