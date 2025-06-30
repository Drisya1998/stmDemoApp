//*******************************LED*******************************************
//Copyright (c) 2025 Trenser Technology Solutions
//All Rights Reserved
//*****************************************************************************
//
//File     : LED.c
//Summary  : LED blinking
//Note     : None
//Author   : Drisya P
//Date     : 27/Jun/2025
//
//*****************************************************************************

//*********************Include Files*******************************************
#include <stdbool.h>
#include <stdio.h>
#include "LED.h"
#include "AppMain.h"
#include "main.h"

//*********************Local Types*********************************************

//*********************Local Constants*****************************************

//*********************Local Variables*****************************************

//*********************Local Functions*****************************************

//*********************.LEDBlink.**********************************************
//Purpose : LED blinking
//Inputs  : None
//Outputs : None
//Return  : TRUE - LED Blinking success
//			FALSE - failed
//Notes   : None
//*****************************************************************************
bool LEDBlink()
{
	static bool sblLEDState = FALSE;
	bool blFlag = FALSE;

	if(sblLEDState == FALSE)
	{
		GPIOSet();
		printf("LED ON\r\n");
		sblLEDState = TRUE;
		blFlag = TRUE;
	}
	else
	{
		GPIOClear();
		printf("LED OFF\r\n");
		sblLEDState = FALSE;
		blFlag = TRUE;
	}

	HAL_Delay(2000);

	return blFlag;
}
//EOF
