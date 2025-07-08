//*******************************osMsgq****************************************
//Copyright (c) 2025 Trenser Technology Solutions
//All Rights Reserved
//*****************************************************************************
//
//File     : osMsgq.c
//Summary  : Handles message queue operaions
//Note     : None
//Author   : Drisya P
//Date     : 08/Jul/2025
//
//*****************************************************************************

//*********************Include Files*******************************************
#include <osMsgq.h>
#include <stdio.h>
#include <stdbool.h>
#include "AppMain.h"
#include "cmsis_os2.h"
#include "PollerTask.h"
#include "RecieverTask.h"

//*********************Local Types*********************************************

//*********************Local Constants*****************************************

//*********************Local Variables*****************************************
osMessageQueueId_t PollerToReceiverId = NULL;
osMessageQueueId_t ReceiverToPollerId = NULL;

//*********************Local Functions*****************************************


//*********************.osMsgqPollerToRecieverInit.****************************
//Purpose :	initialize Message Queue from Poller Task to Receiver Task
//Inputs  : MsgSize - Size of Request Message
//Outputs : None
//Return  : TRUE - Message Queue Initialization completed, FALSE - error
//Notes   : None
//*****************************************************************************
bool osMsgqPollerToRecieverInit(uint32 MsgSize)
{
	bool blFlag = FALSE;

	PollerToReceiverId = osMessageQueueNew(MSG_COUNT, MsgSize, NULL);

	if(PollerToReceiverId != NULL)
	{
		blFlag = TRUE;
	}

	return blFlag;
}

//*********************.osMsgqRecieverToPollerInit.****************************
//Purpose :	initialize Message Queue from Receiver Task to Poller Task
//Inputs  : MsgSize - Size of Ack Message
//Outputs : None
//Return  : TRUE - Message Queue Initialization completed, FALSE - error
//Notes   : None
//*****************************************************************************
bool osMsgqRecieverToPollerInit(uint32 MsgSize)
{
	bool blFlag = FALSE;

	ReceiverToPollerId = osMessageQueueNew(MSG_COUNT, MsgSize, NULL);

	if(ReceiverToPollerId != NULL)
	{
		blFlag = TRUE;
	}

	return blFlag;
}

//*********************.osMsgqMessageSendToReceiver.***************************
//Purpose :	Send Message to Reciever through Message Queue
//Inputs  : stReqMsg -  Request Message
//Outputs : None
//Return  : TRUE - Message sent, FALSE - error
//Notes   : None
//*****************************************************************************
bool osMsgqMessageSendToReceiver(REQUEST_MSG stReqMsg)
{
	bool blFlag = FALSE;

	if(osMessageQueuePut(PollerToReceiverId, &stReqMsg, MSG_PRIORITY,
			osWaitForever) == osOK)
	{
		blFlag = TRUE;
	}

	return blFlag;
}

//*********************.osMsgqMessageRcvFromPoller.****************************
//Purpose :	Recieve Message from Poller through Message Queue
//Inputs  : stReqMsg -  Request Message
//Outputs : None
//Return  : TRUE - Message Received, FALSE - error
//Notes   : None
//*****************************************************************************
bool osMsgqMessageRcvFromPoller(REQUEST_MSG* stReqMsg)
{
	bool blFlag = FALSE;

	if(stReqMsg != NULL)
	{
		if (osMessageQueueGet(PollerToReceiverId, stReqMsg, NULL,
				osWaitForever) == osOK)
		{
			blFlag = TRUE;
		}
	}

	return blFlag;
}

//*********************.osMsgqMessageSendToPoller.*****************************
//Purpose :	Send Message to Poller through Message Queue
//Inputs  : stAckMsg -  Ack Message
//Outputs : None
//Return  : TRUE - Message Sent, FALSE - error
//Notes   : None
//*****************************************************************************
bool osMsgqMessageSendToPoller(ACK_MSG stAckMsg)
{
	bool blFlag = FALSE;

	if(osMessageQueuePut(ReceiverToPollerId, &stAckMsg, MSG_PRIORITY,
			                                 osWaitForever) == osOK)
	{
		blFlag = TRUE;
	}

	return blFlag;
}

//*********************.osMsgqMessageRcvFromPoller.****************************
//Purpose :	Recieve Message from Receiver through Message Queue
//Inputs  : stAckMsg -  Ack Message
//Outputs : None
//Return  : TRUE - Message Received, FALSE - error
//Notes   : None
//*****************************************************************************
bool osMsgqMessageRcvFromReceiver(ACK_MSG* stAckMsg)
{
	bool blFlag = FALSE;

	if(stAckMsg != NULL)
	{
		if (osMessageQueueGet(ReceiverToPollerId, stAckMsg, NULL,
										osWaitForever) == osOK)
		{
			blFlag = TRUE;
		}
	}

	return blFlag;
}

//EOF
