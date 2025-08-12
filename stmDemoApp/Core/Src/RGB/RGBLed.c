//*******************************RGBLed*********************************
//Copyright (c) 2025 Trenser Technology Solutions
//All Rights Reserved
//*****************************************************************************
//
//File     : RGBLed.c
//Summary  : LED will ON in RGB colour combination
//Note     : None
//Author   : Drisya P
//Date     : 14/Jul/2025
//
//*****************************************************************************

//*********************Include Files*******************************************
#include "RGBLed.h"
#include "WS2811Driver.h"
#include <stdio.h>

//*********************Local Types*********************************************

//*********************Local Constants*****************************************

//*********************Local Variables*****************************************

//*********************Local Functions*****************************************

//*********************.RGBLedHandler.*****************************************
//Purpose : handles the Ws2811 Led
//Inputs  : None
//Outputs : None
//Return  : TRUe - success , FALSE - failure
//Notes   : None
//*****************************************************************************
bool RGBLedHandler()
{
	bool blFlag = FALSE;

	WS2811DriverInit();
	WS2811PrepareBuffer(0xFF, 0xFF, 0x00);
	WS2811DriverSendData();
	printf("RGB Data Sent\r\n");
	blFlag = TRUE;

	return blFlag;
}

//EOF
