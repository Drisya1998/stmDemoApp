//**************************** GPIO ******************************************
// Copyright (c) 2025 Trenser Technology Solutions
// All Rights Reserved
//*****************************************************************************
//
// Summary : GPIO header File
// Note    :
//
//*****************************************************************************

#ifndef INC_GPIO_H_
#define INC_GPIO_H_
//******************************* Include Files *******************************
#include "AppMain.h"

//******************************* Global Types ********************************
typedef enum{
	PORT_A,
	PORT_B,
	PORT_C,
	PORT_D
}PORT_TYPE;

typedef enum{
	PIN_0,
	PIN_1,
	PIN_2,
	PIN_3,
	PIN_4,
	PIN_5,
	PIN_6,
	PIN_7,
	PIN_8,
	PIN_9,
	PIN_10,
	PIN_11,
	PIN_12,
	PIN_13,
	PIN_14,
	PIN_15
}PIN_NUMBER;

//***************************** Global Constants ******************************

//***************************** Global Variables ******************************

//***************************** Function Declaration **************************
bool GPIOLEDSet(PORT_TYPE, PIN_NUMBER, bool);
bool GPIOReadButtonPress();
void GPIODelay(uint32);

//*********************** Inline Method Implementations ***********************

#endif /* INC_GPIO_H_ */
