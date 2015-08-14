#include "Control.h"

/*************************¿ØÖÆÆ÷²ÎÊý³õÊ¼»¯************************/
void Controller_Init(void)
{
	/* PID ·´À¡¿ØÖÆÆ÷²ÎÊý³õÊ¼»¯ */
	SpeedPID.Kp = MAXON_RE25_SPEED_KP;
	SpeedPID.Ki = MAXON_RE25_SPEED_KI;
	SpeedPID.Kd = 0;
	SpeedPID.ErrorBond = 0 ;
	SpeedPID.ErrorPre =0;
	SpeedPID.OutputMax = PWM_MAX;
	SpeedPID.OutputMin = PWM_MIN;
	SpeedPID.ErrorSum =  0;
	SpeedPID.ErrorSumMax = INT32_MAX;
	SpeedPID.ErrorSumMin = INT32_MIN;
	
	
	PositionPID.Kp = MAXON_RE25_POSITION_KP ;
	PositionPID.Ki = 0 ;
	PositionPID.Kd = MAXON_RE25_POSITION_KD;
	PositionPID.ErrorBond = 0;
	PositionPID.ErrorPre  = 0;
	PositionPID.OutputMax = SPEED_MAX;
	PositionPID.OutputMin = SPEED_MIN;
	PositionPID.ErrorSum  = 0;
	PositionPID.ErrorSumMax = INT32_MAX;
	PositionPID.ErrorSumMin = INT32_MIN;
	
	/* FeedForward Ç°À¡¿ØÖÆÆ÷²ÎÊý³õÊ¼»¯ */
	PositionFF.Kv = 1.5;//1.6;
	PositionFF.Ka = 0;
	PositionFF.FFmax = SPEED_MAX;
	PositionFF.FFmin = SPEED_MIN;
}



//¶¨ÒåÈ«¾Ö±äÁ¿
float PID_P = 35.0;
float PID_I = 0.00;
float PID_D = 0.00;

void set_PID(u16 P,u16 I,u16 D)
{
	PID_P = P/100.0;
	PID_I = I/100.0;
	PID_D = D/100.0;
}

//PI¿ØÖÆÆ÷
float PI_P = 10;
float PI_I = 0;
void set_PI(u16 P,u16 I)
{
	PI_P = P/100.0;
	PI_I = I/100.0;
}

/* Çå³ý»ý·ÖÎó²î */
void ErrorClear(PID_Typedef *PID )
{
	PID->ErrorSum=0;
	
}

/*********************ËÙ¶È»·*0*****************/
s32  SpeedPI_Regulator(s32 SpeedError,PID_Typedef *PID)//Ö»ÐèÒªPI
{
	s32 output;
 
	PID->ErrorSum += SpeedError; 
	/* ¿¹»ý·Ö±¥ºÍ */
	if(PID->ErrorSum > PID->ErrorSumMax)
	{
		PID->ErrorSum = PID->ErrorSumMax;
	}
	else if(PID->ErrorSum < PID->ErrorSumMin)
	{
		PID->ErrorSum=PID->ErrorSumMin;
	}
 	
	output = SpeedError*PID->Kp + PID->ErrorSum *PID->Ki ;//¼ÆËãÊä³ö
	if(output > PID->OutputMax)
				output = PID->OutputMax;
	else if(output < PID->OutputMin)
			output = PID->OutputMin;
	return output;
}



/***************************Î»ÖÃ»·0*****************************/
s32 PositionPID_Regulator(s32 PositionError,PID_Typedef *PID)
{
	s32 output;
 
	PID->ErrorSum += PositionError; 
	/* ¿¹»ý·Ö±¥ºÍ */
	if(PID->ErrorSum > PID->ErrorSumMax)
	{
		PID->ErrorSum = PID->ErrorSumMax;
	}
	else if(PID->ErrorSum < PID->ErrorSumMin)
	{
		PID->ErrorSum=PID->ErrorSumMin;
	}
 	
	output = PositionError*PID->Kp + PID->ErrorSum *PID->Ki ;//¼ÆËãÊä³ö
	if(output > PID->OutputMax)
				output = PID->OutputMax;
	else if(output < PID->OutputMin)
			output = PID->OutputMin;
	return output;
}


/*P¿ØÖÆÆ÷*/
double P_Controller(float Error,PID_Typedef *PID)
{
	double output;
	
	output = PID->Kp * Error;
	/*Êä³öÏÞÖÆ·ù¶È*/
	if(output > PID->OutputMax)
	{
		output = PID->OutputMax;
	}
	else if(output < PID->OutputMin)
	{
		output = PID->OutputMin;
	}
	
	return output;
}


/*PD ¿ØÖÆÆ÷*/
double PD_Controller(float Error,PID_Typedef *PID)
{
	double output;
	double pTerm;
	double dTerm;
	
	pTerm = PID->Kp * Error;
	dTerm = PID->Kd * (Error - PID->ErrorPre);
	PID->ErrorPre = Error;
	output = pTerm + dTerm;
	/*Êä³öÏÞÖÆ·ù¶È*/
	if(output > PID->OutputMax)
	{
		output = PID->OutputMax;
	}
	else if(output < PID->OutputMin)
	{
		output = PID->OutputMin;
	}
	
	return output;
}




/*PI ¿ØÖÆÆ÷*/
double PI_Controller(PID_Typedef *PID)
{
	double output;
	double pTerm;
	double iTerm;
	
	//
	if(abs_Double(PID->errNow) < PID->KiBond)//
	{
		PID->ErrorSum+=PID->errNow;	//
	}
	/*±ÜÃâ»ý·Ö±¥ºÍÒç³ö*/
	if(PID->ErrorSum > PID->ErrorSumMax)
	{
		PID->ErrorSum = PID->ErrorSumMax;
	}
	else if(PID->ErrorSum < PID->ErrorSumMin)
	{
		PID->ErrorSum = PID->ErrorSumMin;
	}
	
	pTerm = PID->Kp * PID->errNow;				//±ÈÀý×÷ÓÃ
	iTerm = PID->Ki * PID->ErrorSum;//»ý·Ö×÷ÓÃ
	
	output=iTerm+pTerm;
	/*Êä³öÏÞÖÆ·ù¶È*/
	if(output > PID->OutputMax)
	{
		output = PID->OutputMax;
	}
	else if(output < PID->OutputMin)
	{
		output = PID->OutputMin;
	}
	return output;
}

//PI¿ØÖÆÆ÷µÄÀý³Ì
PID_Typedef PI_control;
int User_PIControl(float spdNow)
{
	double output;
	PI_control.spdTag = 0;
	if(360 - spdNow < spdNow)
	{
		spdNow = spdNow - 360;
	}
	PI_control.errNow = PI_control.spdTag - spdNow;
	
	//Éè¶¨pid²ÎÊý
	PI_control.Kp = PI_P;
	PI_control.Ki = PI_I;
	
	PI_control.ErrorBond = 0;
	PI_control.OutputMax = 979;
	PI_control.OutputMin = -979;
	
	PI_control.ErrorSum = 0;
	PI_control.KiBond = 1000;
	PI_control.ErrorSumMax = INT32_MAX;
	PI_control.ErrorSumMin = INT32_MIN;

	output=PI_Controller(&PI_control);     //?'DD????ê?PID??·¨
	
//	PI_control.control = (int)output;       	//???????µè??? ??è?µ??µê?pwm
//	
//	MotorB_PWM_Update(-PI_control.control); 	
//	
//	return 0;
	return output;
}




/**************************************Î»ÖÃÊ½pid*************************************************/
/* Ò»°ãµÄÎ»ÖÃÊ½PID  */
double PID_Pos_Controller(PID_Pos_Typedef *PID)
{
	double output;
	double pTerm;//±ÈÀý×÷ÓÃ
	double iTerm;//»ý·Ö×÷ÓÃ
	double dTerm;//Î¢·Ö×÷ÓÃ
	
	//»ý·Ö·ÖÀë
	if(abs_Double(PID->errNow) < PID->KiBond)//»ý·Ö·ÖÀë ,Ð¡Îó²îÊÇ¿ªÊ¼»ý·Ö×÷ÓÃ
	{
		PID->ErrorSum+=PID->errNow;	//¼ÆËãÎó²îÀÛ¼Æ»ý·Ö
	}
	
	/* ¿¹±¥ºÍ»ý·Ö*/
	if(PID->ErrorSum > PID->ErrorSumMax)
	{
		PID->ErrorSum = PID->ErrorSumMax;
	}
	else if(PID->ErrorSum < PID->ErrorSumMin)
	{
		PID->ErrorSum=PID->ErrorSumMin;
	}
	/*  */
	pTerm=PID->Kp*PID->errNow;//±ÈÀý×÷ÓÃ
	iTerm=PID->Ki*PID->ErrorSum;//»ý·Ö×÷ÓÃ
	dTerm=PID->Kd*(PID->errNow-PID->ErrorPre);//Î¢·Ö×÷ÓÃ
	output=  pTerm+iTerm+dTerm;//pidµÄÊä³öÖµ
	
	PID->ErrorPre=PID->errNow;//¼ÇÂ¼Ç°Ò»´ÎÎó²î
	
	/* ÏÞ·ù¶ÈÊä³ö */
	if(output > PID->OutputMax)
	{
		output=PID->OutputMax;
	}
	else if(output < PID->OutputMin)
	{
		output=PID->OutputMin;
	}
	return output ;
}

/***************Î»ÖÃ¿ØÖÆ**************/
PID_Pos_Typedef PID_Pos;//¶¨ÒåPIDËã·¨µÄ½á¹¹Ìå

//Ò»°ãµÄpid¿ØÖÆËã·¨

//int User_PidPosControl(u16 spdNow,u16 spdTag)
//{
//	double output;
//  // spdNow = 180;
//	PID_Pos.spdTag = spdTag;

//	PID_Pos.errNow =  PID_Pos.spdTag - spdNow; //¼ÆËã²¢Ð´ÈëËÙ¶ÈÎó²î
//   
//   //ÐÞ¸Äpid²ÎÊý
//	PID_Pos.Kp = 35;			   //±ÈÀýÏµÊý²ÎÊý
//	PID_Pos.Ki = 0; 	           //»ý·ÖÏµÊý²ÎÊý
//	PID_Pos.Kd = 1;      	       //Î¢·ÖÏµÊý²ÎÊý
//	
//	PID_Pos.ErrorBond = 0;
//	PID_Pos.ErrorPre  = 0;
//	PID_Pos.OutputMax = 979;
//	PID_Pos.OutputMin = -979;
//	PID_Pos.ErrorSum  = 0;
//	PID_Pos.KiBond = 1000;
//	PID_Pos.ErrorSumMax = INT32_MAX;
//	PID_Pos.ErrorSumMin = INT32_MIN;
// 
//	output=PID_Pos_Controller(&PID_Pos);     //Ö´ÐÐ¾ø¶ÔÊ½PIDËã·¨
//	
////	PID_Pos.control = (int)output;       	//¶Ô¿ØÖÆÖµÈ¡Õû »ñÈ¡µÄÖµÊÇpwm
////	
////	MotorB_PWM_Update(PID_Pos.control); 	 //·ÅÈëpwmÓÃÓÚÊÕÁ²ËÙ¶ÈµÄ¿ØÖÆ
////	
////	return 0;
//	return output;
//}
/**************************************************************************************************/




/**************************************ÔöÁ¿Ê½pid*************************************************/
/* Ò»°ãµÄÔöÁ¿Ê½PID  */
int PID_Inc_Controller(PID_Inc_Typedef *PID_INC)
{
	
	double pTerm,iTerm,dTerm;  //PID¸÷ÏîÖµ
	float dErrP, dErrI, dErrD;

	//¼ÆËãÎó²îÀÛ¼Æ»ý·Ö
	if(abs_Double(PID_INC->errNow) < PID_INC->KiBond)//»ý·Ö·ÖÀë ,Ð¡Îó²îÊÇ¿ªÊ¼»ý·Ö×÷ÓÃ
	{
		PID_INC->ErrorSum+=PID_INC->errNow;	//¼ÆËãÎó²îÀÛ¼Æ»ý·Ö
	}
	
	// ¿¹±¥ºÍ»ý·Ö
	if(PID_INC->ErrorSum > PID_INC->ErrorSumMax)
	{
		PID_INC->ErrorSum = PID_INC->ErrorSumMax;
	}
	else if(PID_INC->ErrorSum < PID_INC->ErrorSumMin)
	{
		PID_INC->ErrorSum=PID_INC->ErrorSumMin;
	}

	
	dErrP = PID_INC->errNow - PID_INC->errOld1;
	dErrI = PID_INC->errNow;
	dErrD = PID_INC->errNow - 2 * PID_INC->errOld1 + PID_INC->errOld2;

	pTerm = PID_INC ->Kp * dErrP;
	iTerm = PID_INC ->Ki * dErrI;
	dTerm = PID_INC ->Kd * dErrD;	

	/*ÔöÁ¿Ê½PID¼ÆËã*/
	PID_INC->dCtrOut=  pTerm+iTerm+dTerm; 
	
	PID_INC->errOld2 = PID_INC->errOld1; //¶þ½×Îó²îÎ¢·Ö
	PID_INC->errOld1 = PID_INC->errNow;  //Ò»½×Îó²îÎ¢·Ö

	
	if(PID_INC->Kp == 0 && PID_INC->Ki == 0 && PID_INC->Kd == 0)
		PID_INC->dCtrOut = 0;
	else
		PID_INC->ctrOut += PID_INC->dCtrOut;
	
	/* ÏÞ·ù¶ÈÊä³ö */
	if(PID_INC->ctrOut>PID_INC->OutputMax)
	{
		PID_INC->ctrOut=PID_INC->OutputMax;
	}
	else if(PID_INC->ctrOut<PID_INC->OutputMin)
	{
		PID_INC->ctrOut=PID_INC->OutputMin;
	}
	
	return (int)PID_INC->ctrOut ;
}


/***************ÔöÁ¿¿ØÖÆ**************/
//PID_Inc_Typedef PID_Inc;//¶¨ÒåPIDËã·¨µÄ½á¹¹Ìå

////Ò»°ãµÄpid¿ØÖÆËã·¨
//int User_PidIncControl(u16 spdNow)
//{
//	double output;
//	// spdNow = V2;
//	PID_Inc.spdTag = 400;

//	PID_Inc.errNow =  PID_Pos.spdTag - spdNow; //¼ÆËã²¢Ð´ÈëËÙ¶ÈÎó²î

//	//ÐÞ¸Äpid²ÎÊý
//	PID_Inc.Kp = PID_P;			   //±ÈÀýÏµÊý²ÎÊý
//	PID_Inc.Ki = PID_I; 	           //»ý·ÖÏµÊý²ÎÊý
//	PID_Inc.Kd = PID_D;      	       //Î¢·ÖÏµÊý²ÎÊý
//	
//	PID_Inc.ErrorBond = 1000;
//	//PID_Inc.ErrorPre  = 0;
//	PID_Inc.OutputMax = 979;
//	PID_Inc.OutputMin = -979;
//	PID_Inc.ErrorSum  = 0;
//	PID_Inc.ErrorSumMax = INT32_MAX;
//	PID_Inc.ErrorSumMin = INT32_MIN;

//	output=PID_Inc_Controller(&PID_Inc);     //Ö´ÐÐ¾ø¶ÔÊ½PIDËã·¨

//	PID_Inc.control = (int)output;       //¶Ô¿ØÖÆÖµÈ¡Õû »ñÈ¡µÄÖµÊÇpwm

//	MotorB_PWM_Update(PID_Inc.control);  //·ÅÈëpwmÓÃÓÚÊÕÁ²ËÙ¶ÈµÄ¿ØÖÆ
//	
//	return 0;
//}



double FF_Controller(double rin,FForward_Typedef *FF )
{
	double output;
	
	FF->rinV = rin - FF->rinPre; //Ò»½×Î¢·Ö
	FF->rinA = FF->rinV - FF->rinV_Pre;//¶þ½×Î¢·Ö
	FF->rinPre = rin;
	FF->rinV_Pre = FF->rinV;
	output = FF->rinV * FF->Kv + FF->rinA * FF->Ka ;//
	if(output > FF->FFmax)
	{
		output = FF->FFmax;
	}
	else if(output < FF->FFmin)
	{
		output =  FF->FFmin;
	}
	
	return output;
}
