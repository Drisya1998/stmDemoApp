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
#define MSG_COUNT			10
#define MSG_PRIORITY		0

//***************************** Global Variables ******************************
extern osMessageQueueId_t PollerToReceiverId;
extern osMessageQueueId_t ReceiverToPollerId;
extern osMessageQueueId_t WatchdogQueueId;
extern osMessageQueueId_t ReceiverToLoggerId;
extern osMessageQueueId_t LoggerToReceiverId;

//***************************** Function Declaration **************************
//Poller and Receiver Message Queue
bool osMsgqPollerToRecieverInit(uint32);
bool osMsgqRecieverToPollerInit(uint32);
bool osMsgqMessageSendToReceiver(REQUEST_MSG);
bool osMsgqMessageRcvFromPoller(REQUEST_MSG*);
bool osMsgqMessageSendToPoller(ACK_MSG);
bool osMsgqMessageRcvFromReceiver(ACK_MSG*);

//Receiver and Logger Message Queue
bool osMsgqReceiverToLoggerInit(uint32);
bool osMsgqLoggerToReceiverInit(uint32);
bool osMsgqMessageSendToLogger(LOGGER_MSG);
bool osMsgqMsgRcvFromReceiver(LOGGER_MSG*);
bool osMsgqMsgSendToReceiver(LOGACK_MSG);
bool osMsgqMessageRcvFromLogger(LOGACK_MSG*);

//WatchDog Message Queue
bool osMsgqWatchdogInit(uint32);
bool osMsgqSendToWatchdog(WATCHDOG_EVENT);
bool osMsgqRcvFromWatchdog(WATCHDOG_EVENT*);

//*********************** Inline Method Implementations ***********************

#endif /* INC_OS_MSGQ_H_ */
