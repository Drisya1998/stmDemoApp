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
bool GPIOLEDSet(PORT_TYPE LEDPort, PIN_NUMBER LEDPin, bool blLEDStatus)
{
	bool blFlag = FALSE;
	GPIO_TypeDef* gpioPort = NULL;
	uint32_t gpioPin = 1;
	uint8 ucIndex = 0;

	switch(LEDPort)
	{
		case PORT_A:
			gpioPort = GPIOA;
			break;
		case PORT_B:
			gpioPort = GPIOB;
			break;
		case PORT_C:
			gpioPort = GPIOC;
			break;
		case PORT_D:
			gpioPort = GPIOD;
			break;
	}

	for(ucIndex = 0; ucIndex<16; ucIndex++)
	{
		if(LEDPin == ucIndex)
		{
			gpioPin = gpioPin << LEDPin;
		}
	}

	if(gpioPort != NULL)
	{
		HAL_GPIO_WritePin(gpioPort, gpioPin, blLEDStatus);
		blFlag = TRUE;
	}

	return blFlag;
}

//*********************.Delay.********************************************
//Purpose : To set delay on LED Blinking
//Inputs  : delay - delay in milliseconds
//Outputs : None
//Return  : None
//Notes   : None
//*****************************************************************************
void Delay(uint32_t delay)
{
	HAL_Delay(delay);
}

//EOF
