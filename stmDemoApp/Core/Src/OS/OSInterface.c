//*******************************OSInterface***********************************
//Copyright (c) 2025 Trenser Technology Solutions
//All Rights Reserved
//*****************************************************************************
//
//File     : OSInterface.c
//Summary  : Handles Thread Operations and message queue operaions
//Note     : None
//Author   : Drisya P
//Date     : 03/Jul/2025
//
//*****************************************************************************

//*********************Include Files*******************************************
#include "OSInterface.h"
#include <stdio.h>
#include <stdbool.h>
#include "AppMain.h"
#include "cmsis_os2.h"

//*********************Local Types*********************************************

//*********************Local Constants*****************************************

//*********************Local Variables*****************************************
static osThreadId_t ThreadHandles[2] = {0,0};
static uint8 ucThreadIndex = 0;
osMessageQueueId_t PollerToReceiverId = NULL;
osMessageQueueId_t ReceiverToPollerId = NULL;
osMutexId_t uartMutex = NULL;

//*********************Local Functions*****************************************

//*********************.CreateThread.******************************************
//Purpose :	Create the thread
//Inputs  : stTask - structure include Thread name , stack size , priority ,
//				and	the function executed by thread.
//Outputs : None
//Return  : TRUE - created thread successfully , FALSE - error
//Notes   : None
//*****************************************************************************
bool CreateThread(TASKS *stTask)
{
	bool blFlag = FALSE;

	if(stTask != NULL)
	{
		osThreadAttr_t attr = {
		    .name = (const char *)stTask->pucTaskName,
		    .stack_size = stTask->ulStackSize,
		    .priority = (osPriority_t)osPriorityNormal,
		};

		ThreadHandles[ucThreadIndex] = osThreadNew(stTask->pTaskFunc,
														NULL, &attr);

		if(ThreadHandles[ucThreadIndex] == NULL)
		{
			blFlag = FALSE;
		    printf("Failed to create thread: %s\r\n", stTask->pucTaskName);
		}
		else
		{
			printf("Created thread: %s\r\n", stTask->pucTaskName);
			ucThreadIndex++;
			blFlag = TRUE;
		}

	}

	return blFlag;
}

//*********************.PollerToRecieverMsgQInit.******************************
//Purpose :	initialize Message Queue from Poller Task to Receiver Task
//Inputs  : MsgSize - Size of Request Message
//Outputs : None
//Return  : TRUE - Message Queue Initialization completed, FALSE - error
//Notes   : None
//*****************************************************************************
bool PollerToRecieverMsgQInit(uint32 MsgSize)
{
	bool blFlag = FALSE;

	PollerToReceiverId = osMessageQueueNew(5, MsgSize, NULL);

	if(PollerToReceiverId != NULL)
	{
		blFlag = TRUE;
	}

	return blFlag;
}

//*********************.RecieverToPollerMsgQInit.******************************
//Purpose :	initialize Message Queue from Receiver Task to Poller Task
//Inputs  : MsgSize - Size of Ack Message
//Outputs : None
//Return  : TRUE - Message Queue Initialization completed, FALSE - error
//Notes   : None
//*****************************************************************************
bool RecieverToPollerMsgQInit(uint32 MsgSize)
{
	bool blFlag = FALSE;

	ReceiverToPollerId = osMessageQueueNew(5, MsgSize, NULL);

	if(ReceiverToPollerId != NULL)
	{
		blFlag = TRUE;
	}

	return blFlag;
}

//*********************.MessageSendToReceiver.*******************************
//Purpose :	Send Message to Reciever through Message Queue
//Inputs  : stReqMsg -  Request Message
//Outputs : None
//Return  : TRUE - Message sent, FALSE - error
//Notes   : None
//***************************************************************************
bool MessageSendToReceiver(REQUEST_MSG stReqMsg)
{
	bool blFlag = FALSE;

	if(osMessageQueuePut(PollerToReceiverId, &stReqMsg, 0, osWaitForever) ==
																	osOK)
	{
		blFlag = TRUE;
	}

	return blFlag;
}

//*********************.MessageRcvFromPoller.**********************************
//Purpose :	Recieve Message from Poller through Message Queue
//Inputs  : stReqMsg -  Request Message
//Outputs : None
//Return  : TRUE - Message Received, FALSE - error
//Notes   : None
//*****************************************************************************
bool MessageRcvFromPoller(REQUEST_MSG* stReqMsg)
{
	bool blFlag = FALSE;

	if(stReqMsg != NULL)
	{
		if (osMessageQueueGet(PollerToReceiverId, stReqMsg, NULL, osWaitForever)
																		== osOK)
		{
			blFlag = TRUE;
		}
	}

	return blFlag;
}

//*********************.MessageSendToPoller.*******************************
//Purpose :	Send Message to Poller through Message Queue
//Inputs  : stAckMsg -  Ack Message
//Outputs : None
//Return  : TRUE - Message Sent, FALSE - error
//Notes   : None
//***************************************************************************
bool MessageSendToPoller(ACK_MSG stAckMsg)
{
	bool blFlag = FALSE;

	if(osMessageQueuePut(ReceiverToPollerId, &stAckMsg, 0, osWaitForever) ==
																	osOK)
	{
		blFlag = TRUE;
	}

	return blFlag;
}

//*********************.MessageRcvFromPoller.**********************************
//Purpose :	Recieve Message from Receiver through Message Queue
//Inputs  : stAckMsg -  Ack Message
//Outputs : None
//Return  : TRUE - Message Received, FALSE - error
//Notes   : None
//*****************************************************************************
bool MessageRcvFromReceiver(ACK_MSG* stAckMsg)
{
	bool blFlag = FALSE;

	if(stAckMsg != NULL)
	{
		if (osMessageQueueGet(ReceiverToPollerId, stAckMsg, NULL, osWaitForever)
																		== osOK)
		{
			blFlag = TRUE;
		}
	}

	return blFlag;
}

//*********************.CreateUARTMutex.************************************************
//Purpose : Create Mutex
//Inputs  : None
//Outputs : None
//Return  : TRUE - return success , FALSE - Failed
//Notes   : None
//*****************************************************************************
bool CreateUARTMutex()
{
	bool blFlag = FALSE;

	uartMutex = osMutexNew(NULL);

	if(uartMutex != NULL)
	{
		blFlag = TRUE;
	}

	return blFlag;
}


//*********************.UARTMutexRelease.************************************************
//Purpose : unlock Mutex
//Inputs  : None
//Outputs : None
//Return  : TRUE - return success , FALSE - Failed
//Notes   : None
//*****************************************************************************
bool UARTMutexRelease()
{
	bool blFlag = FALSE;

	if(osMutexRelease(uartMutex) == osOK)
	{
		blFlag = TRUE;
	}

	return blFlag;
}

//*********************.UARTMutexAcquire.************************************************
//Purpose : lock Mutex
//Inputs  : None
//Outputs : None
//Return  : TRUE - return success , FALSE - Failed
//Notes   : None
//*****************************************************************************
bool UARTMutexAcquire()
{
	bool blFlag = FALSE;

	if(osMutexAcquire(uartMutex, osWaitForever) == osOK)
	{
		blFlag = TRUE;
	}

	return blFlag;
}

//*********************.Delay.************************************************
//Purpose : To set delay on LED Blinking
//Inputs  : delay - delay in milliseconds
//Outputs : None
//Return  : None
//Notes   : None
//*****************************************************************************
void Delay(uint32 delay)
{
	osDelay(delay);
}

//EOF
