//*******************************WatchDogTimer*********************************
//Copyright (c) 2025 Trenser Technology Solutions
//All Rights Reserved
//*****************************************************************************
//
//File     : WatchDogTimer.c
//Summary  : Printf via UART and LED blinking
//Note     : None
//Author   : Drisya P
//Date     : 09/Jul/2025
//
//*****************************************************************************

//*********************Include Files*******************************************
#include "WatchDogTimer.h"
#include "stm32f103xb.h"

//*********************Local Types*********************************************

//*********************Local Constants*****************************************

//*********************Local Variables*****************************************
IWDG_TYPE* pstIWDG = IWDG_BASE_ADDRESS;
//*********************Local Functions*****************************************

//*********************.WatchDogTimerInit.*************************************
//Purpose : Initialize the WatchDog Registers.
//Inputs  : None
//Outputs : None
//Return  : None
//Notes   : None
//*****************************************************************************
void WatchDogTimerInit()
{
	pstIWDG->KR = WRITE_ACCESS;
	pstIWDG->PR = PRESCALAR_VALUE;
	pstIWDG->RLR = RELOAD_VALUE;
	pstIWDG->KR = RESET_COUNTER;
	pstIWDG->KR = START_WATCHDOG;
}

//*********************.WatchDogTimerClear.************************************
//Purpose : Reload the Timer to prevent the System reset
//Inputs  : None
//Outputs : None
//Return  : None
//Notes   : None
//*****************************************************************************
void WatchdogTimerClear()
{
	pstIWDG->KR = RESET_COUNTER;
}

//EOF
