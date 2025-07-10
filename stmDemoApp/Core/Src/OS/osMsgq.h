//**************************** osMsgq *****************************************
// Copyright (c) 2025 Trenser Technology Solutions
// All Rights Reserved
//*****************************************************************************
//
// Summary : osMsgq header File
// Note    : Added Macros
//
//*****************************************************************************

#ifndef INC_OS_MSGQ_H_
#define INC_OS_MSGQ_H_

//******************************* Include Files *******************************
#include "cmsis_os2.h"
#include "stdbool.h"
#include "osTask.h"
#include "WatchDogHandler.h"

//******************************* Global Types ********************************

//***************************** Global Constants ******************************
#define MSG_COUNT			5
#define MSG_PRIORITY		0

//***************************** Global Variables ******************************
extern osMessageQueueId_t PollerToReceiverId;
extern osMessageQueueId_t ReceiverToPollerId;
extern osMessageQueueId_t WatchdogQueueId;

//***************************** Function Declaration **************************
bool osMsgqPollerToRecieverInit(uint32);
bool osMsgqRecieverToPollerInit(uint32);
bool osMsgqMessageSendToReceiver(REQUEST_MSG);
bool osMsgqMessageRcvFromPoller(REQUEST_MSG*);
bool osMsgqMessageSendToPoller(ACK_MSG);
bool osMsgqMessageRcvFromReceiver(ACK_MSG*);
bool osMsgqSendToWatchdog(WATCHDOG_EVENT);
bool osMsgqRcvFromWatchdog(WATCHDOG_EVENT*);
bool osMsgqWatchdogInit(uint32);

//*********************** Inline Method Implementations ***********************

#endif /* INC_OS_MSGQ_H_ */
