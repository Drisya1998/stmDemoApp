//*******************************PwmHandler*********************************
//Copyright (c) 2025 Trenser Technology Solutions
//All Rights Reserved
//*****************************************************************************
//
//File     : PwmHandler.c
//Summary  : LED blinking using pwm
//Note     : None
//Author   : Drisya P
//Date     : 10/Jul/2025
//
//*****************************************************************************

//*********************Include Files*******************************************
#include "PwmDriver.h"
#include "PwmHandler.h"

//*********************Local Types*********************************************

//*********************Local Constants*****************************************

//*********************Local Variables*****************************************

//*********************Local Functions*****************************************

//*********************.PwmDriverInit.*************************************
//Purpose : Initialize the Pwm.
//Inputs  : None
//Outputs : None
//Return  : None
//Notes   : None
//*****************************************************************************
bool PwmHandler()
{
	bool blFlag = FALSE;

	PWMDriverInit();
	PWMDriverSet();
	PWMDriverStart(DUTY_CYCLE);

	blFlag = TRUE;

	return blFlag;
}

//EOF
