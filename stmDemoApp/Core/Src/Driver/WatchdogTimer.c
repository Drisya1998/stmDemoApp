//*******************************WatchDogTimer*********************************
//Copyright (c) 2025 Trenser Technology Solutions
//All Rights Reserved
//*****************************************************************************
//
//File     : WatchDogTimer.c
//Summary  : WatchDog Driver
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
	pstIWDG->stKR.ulKEY = WRITE_ACCESS;
	pstIWDG->stPR.ulPR = PRESCALAR_VALUE;
	pstIWDG->stRLR.ulRLR = RELOAD_VALUE;
	pstIWDG->stKR.ulKEY = RESET_COUNTER;
	pstIWDG->stKR.ulKEY = START_WATCHDOG;
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
	pstIWDG->stKR.ulKEY = RESET_COUNTER;
}

//EOF
