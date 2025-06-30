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

//*********************Local Types*********************************************

//*********************Local Constants*****************************************

//*********************Local Variables*****************************************

//*********************Local Functions*****************************************

//*********************.GPIOSet.**********************************************
//Purpose : To set a pin with HIGH
//Inputs  : None
//Outputs : None
//Return  : None
//Notes   : None
//*****************************************************************************
void GPIOSet()
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
}

//*********************.GPIOClear.**********************************************
//Purpose : To set a pin with LOW
//Inputs  : None
//Outputs : None
//Return  : None
//Notes   : None
//*****************************************************************************
void GPIOClear()
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
}

//EOF
