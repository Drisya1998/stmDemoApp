//**************************** OSInterface ***************************************
// Copyright (c) 2025 Trenser Technology Solutions
// All Rights Reserved
//*****************************************************************************
//
// Summary : OSInterface header File
// Note    : Added Macros
//
//*****************************************************************************

#ifndef INC_OS_INTERFACE_H_
#define INC_OS_INTERFACE_H_

//******************************* Include Files *******************************
#include "cmsis_os2.h"
#include "AppMain.h"
#include "stdbool.h"
//******************************* Global Types ********************************

//***************************** Global Constants ******************************

//***************************** Global Variables ******************************
extern osMessageQueueId_t PollerToReceiverId;
extern osMessageQueueId_t ReceiverToPollerId;
extern osMutexId_t uartMutex;

//***************************** Function Declaration **************************
bool CreateThread();
bool PollerToRecieverMsgQInit();
bool RecieverToPollerMsgQInit();
bool MessageSendToReceiver(REQUEST_MSG);
bool MessageRcvFromPoller(REQUEST_MSG*);
bool MessageSendToPoller(ACK_MSG);
bool MessageRcvFromReceiver(ACK_MSG*);
bool CreateUARTMutex();
bool UARTMutexAcquire();
bool UARTMutexRelease();
void Delay(uint32);

//*********************** Inline Method Implementations ***********************

#endif /* INC_OS_INTERFACE_H_ */
