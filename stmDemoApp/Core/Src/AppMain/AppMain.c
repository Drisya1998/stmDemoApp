//*******************************AppMain******************************************
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
#include "AppMain.h"
#include "LED.h"
#include <stdio.h>
#include <stdbool.h>

//*********************Local Types*********************************************

//*********************Local Constants*****************************************

//*********************Local Variables*****************************************

//*********************Local Functions*****************************************

//*********************.AppMain.***********************************************
//Purpose : Printf via UART and LED blinking
//Inputs  : None
//Outputs : None
//Return  : None
//Notes   : None
//*****************************************************************************
void AppMain()
{
	bool blFlag = FALSE;

	printf("Hello from STM32 via UART!\r\n");
	while (TRUE)
	{
		blFlag = LEDBlink();
		if(blFlag == FALSE)
		{
			printf("LED Blinking Failed");
		}
	}
}
//EOF
