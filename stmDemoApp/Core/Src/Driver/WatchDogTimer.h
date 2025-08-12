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
typedef struct _KR_
{
    uint32 ulKEY : 16;  // Only 16 bits used
    uint32 ulRESERVED :16;
} KR;

typedef struct _PR_
{
    uint32 ulPR : 3;     // Prescaler is 3 bits (as per STM32 IWDG spec)
    uint32 ulRESERVED : 29;
} PR;

typedef struct _RLR_
{
    uint32 ulRLR : 12;    // Reload value is 12 bits
    uint32 ulRESERVED : 20;
} RLR;

typedef struct _SR_
{
    uint32 ulPVU : 1;    // Prescaler Value Update ongoing
    uint32 ulRVU : 1;    // Reload Value Update ongoing
    uint32 ulRESERVED : 30;
} SR;

typedef struct _IWDG_TYPE_
{
	KR stKR;
	PR stPR;
	RLR stRLR;
	SR stSR;
}IWDG_TYPE;

//***************************** Global Constants ******************************
#define IWDG_BASE_ADDRESS	((IWDG_TYPE *)0x40003000)
#define WRITE_ACCESS		0x5555
#define RESET_COUNTER		0xAAAA
#define START_WATCHDOG		0xCCCC
#define PRESCALAR_VALUE		0x06
#define RELOAD_VALUE		274
//***************************** Global Variables ******************************

//***************************** Function Declaration **************************
void WatchDogTimerInit();
void WatchdogTimerClear();

//*********************** Inline Method Implementations ***********************

#endif /* INC_WATCHDOG_TIMER_H_ */
