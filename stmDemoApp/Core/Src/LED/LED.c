//*******************************LED*******************************************
//Copyright (c) 2025 Trenser Technology Solutions
//All Rights Reserved
//*****************************************************************************
//
//File     : LED.c
//Summary  : LED blinking on STM32 in GPIOA with delay of 1 second
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
#include "GPIO.h"

//*********************Local Types*********************************************

//*********************Local Constants*****************************************

//*********************Local Variables*****************************************

//*********************Local Functions*****************************************

//*********************.LEDBlink.**********************************************
//Purpose : LED blinking
//Inputs  : None
//Outputs : None
//Return  : TRUE - LED Blinking success, FALSE - failed
//Notes   : None
//*****************************************************************************
bool LEDBlink()
{
	static bool sblLEDState = FALSE;
	bool blFlag = FALSE;
	PORT_TYPE port = PORT_A;
	PIN_NUMBER pin = PIN_5;

	if(sblLEDState == FALSE)
	{
		blFlag = GPIOLEDSet(port, pin, TRUE);
		printf("LED ON\r\n");
		sblLEDState = TRUE;
	}
	else
	{
		blFlag = GPIOLEDSet(port, pin, FALSE);
		printf("LED OFF\r\n");
		sblLEDState = FALSE;
	}

	GPIODelay(1000);

	return blFlag;
}
//EOF
