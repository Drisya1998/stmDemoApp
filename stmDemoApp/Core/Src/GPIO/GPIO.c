//*******************************GPIO******************************************
//Copyright (c) 2025 Trenser Technology Solutions
//All Rights Reserved
//*****************************************************************************
//
//File     : GPIO.c
//Summary  : GPIO Interface
//Note     : None
//Author   : Drisya P
//Date     : 30/Jun/2025
//
//*****************************************************************************

//*********************Include Files*******************************************
#include <stdbool.h>
#include <stdio.h>
#include "main.h"
#include "AppMain.h"
#include "GPIO.h"

//*********************Local Types*********************************************

//*********************Local Constants*****************************************

//*********************Local Variables*****************************************

//*********************Local Functions*****************************************

//*********************.GPIOLEDSet.********************************************
//Purpose : To set a pin with HIGH
//Inputs  : Port, Pin Number and LED status need to be set in the Pin.
//Outputs : None
//Return  : None
//Notes   : None
//*****************************************************************************
bool GPIOLEDSet(GPIO_TypeDef* gpioPort, uint16_t LEDPin, bool blLEDStatus)
{
	bool blFlag = FALSE;

	if(gpioPort != NULL)
	{
		HAL_GPIO_WritePin(gpioPort, LEDPin, blLEDStatus);
		blFlag = TRUE;
	}

	return blFlag;
}

//EOF
