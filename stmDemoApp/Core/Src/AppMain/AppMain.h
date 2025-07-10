//**************************** appTimer ***************************************
// Copyright (c) 2025 Trenser Technology Solutions
// All Rights Reserved
//*****************************************************************************
//
// Summary : AppMain header File
// Note    : Added Macros
//
//*****************************************************************************

#ifndef INC_APPMAIN_H_
#define INC_APPMAIN_H_

//******************************* Include Files *******************************
#include "stdbool.h"

//******************************* Global Types ********************************
typedef unsigned short uint16;
typedef signed char int8;
typedef unsigned char uint8;
typedef unsigned long uint32;

typedef struct _REQUEST_MSG_
{
    uint32 ulUId;
    uint8 ucCmd;
    uint32 ulData;
}REQUEST_MSG;

typedef struct _ACK_MSG_
{
    uint32 ulUId;
    uint8 ucCmd;
    uint8 ucState;
    uint32 ulData;
}ACK_MSG;

//***************************** Global Constants ******************************
#define TRUE                1
#define FALSE               0
#define DELAY_300			300
#define DELAY_100			100

//***************************** Global Variables ******************************
extern uint8 ucLedStatus;

//***************************** Function Declaration **************************
void AppMain();

//*********************** Inline Method Implementations ***********************

#endif /* INC_APPMAIN_H_ */
