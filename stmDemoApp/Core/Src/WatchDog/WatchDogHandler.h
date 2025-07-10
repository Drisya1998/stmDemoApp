//**************************** WatchDogHandler ********************************
// Copyright (c) 2025 Trenser Technology Solutions
// All Rights Reserved
//*****************************************************************************
//
// Summary : watchDog HAndler header File
// Note    : Added Macros
//
//*****************************************************************************

#ifndef INC_WATCHDOG_HANDLER_H_
#define INC_WATCHDOG_HANDLER_H_

//******************************* Include Files *******************************
#include "AppMain.h"

//******************************* Global Types ********************************
typedef enum {
    WATCHDOG_SRC_POLLER = 0x01,
    WATCHDOG_SRC_RECEIVER = 0x02
} WATCHDOG_SRC;

typedef union _WATCHDOG_EVENT_FLAGS_
{
    struct
    {
        uint8 ucPoller : 1;
        uint8 ucReceiver : 1;
    }BITS;
    uint8 ucAll;
}WATCHDOG_EVENT_FLAGS;

typedef struct _WATCHDOG_EVENT_
{
    WATCHDOG_SRC src;
}WATCHDOG_EVENT;

//***************************** Global Constants ******************************
#define ALL_EVENTS_SET 			0x03
//***************************** Global Variables ******************************

//***************************** Function Declaration **************************
void WatchDogHandler();

//*********************** Inline Method Implementations ***********************

#endif /* INC_WATCHDOG_HANDLER_H_ */
