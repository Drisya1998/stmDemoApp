//**************************** WatchDogTimer ********************************
// Copyright (c) 2025 Trenser Technology Solutions
// All Rights Reserved
//*****************************************************************************
//
// Summary : watchDog Timer header File
// Note    : Added Macros
//
//*****************************************************************************

#ifndef INC_WATCHDOG_TIMER_H_
#define INC_WATCHDOG_TIMER_H_

//******************************* Include Files *******************************
#include "AppMain.h"
//******************************* Global Types ********************************
typedef struct _IWDG_TYPE_
{
	uint32 KR;
	uint32 PR;
	uint32 RLR;
	uint32 SR;
}IWDG_TYPE;

//***************************** Global Constants ******************************
#define IWDG_BASE_ADDRESS	((IWDG_TYPE *)0x40003000)
#define WRITE_ACCESS		0x5555
#define RESET_COUNTER		0xAAAA
#define START_WATCHDOG		0xCCCC
#define PRESCALAR_VALUE		0x06
#define RELOAD_VALUE		109
//***************************** Global Variables ******************************

//***************************** Function Declaration **************************
void WatchDogTimerInit();
void WatchdogTimerClear();

//*********************** Inline Method Implementations ***********************

#endif /* INC_WATCHDOG_TIMER_H_ */
