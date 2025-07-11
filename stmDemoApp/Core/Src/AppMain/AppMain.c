//*******************************AppMain***************************************
//Copyright (c) 2025 Trenser Technology Solutions
//All Rights Reserved
//*****************************************************************************
//
//File     : AppMain.c
//Summary  : Printf via UART and LED blinking
//Note     : None
//Author   : Drisya P
//Date     : 27/Jun/2025
//
//*****************************************************************************

//*********************Include Files*******************************************
#include <osTask.h>
#include <stdio.h>
#include <stdbool.h>
#include "AppMain.h"
#include "PwmHandler.h"

//*********************Local Types*********************************************

//*********************Local Constants*****************************************

//*********************Local Variables*****************************************

//*********************Local Functions*****************************************

//*********************.AppMain.***********************************************
//Purpose : Printf via UART and Initialize the Tasks.
//Inputs  : None
//Outputs : None
//Return  : None
//Notes   : None
//*****************************************************************************
void AppMain()
{
	bool blFlag =  FALSE;

	printf("Hello from STM32 via UART!\r\n");
	blFlag = PwmHandler();

	if(blFlag == FALSE)
	{
		printf("PWM Failed\r\n");
	}

	blFlag = TaskInit();

	if(blFlag == FALSE)
	{
		printf("Thread Creation Failed\r\n");
	}
}

//EOF
