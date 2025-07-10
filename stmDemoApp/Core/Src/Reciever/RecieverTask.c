//*******************************RecieverTask**********************************
//Copyright (c) 2025 Trenser Technology Solutions
//All Rights Reserved
//*****************************************************************************
//
//File     : RecieverTask.c
//Summary  : Receive the Request from Poller Task and Toggle the LED.
//Note     : None
//Author   : Drisya P
//Date     : 03/Jul/2025
//
//*****************************************************************************

//*********************Include Files*******************************************
#include "osMsgq.h"
#include "osTask.h"
#include <stdio.h>
#include <stdbool.h>
#include "RecieverTask.h"
#include "LED.h"
#include "AppMain.h"
#include "WatchDogHandler.h"

//*********************Local Types*********************************************

//*********************Local Constants*****************************************

//*********************Local Variables*****************************************
static uint32 sgulUId = 0;
static uint32 sgulData = ACK_ERROR_DATA;
uint8 gucLEDState = FALSE;

//*********************Local Functions*****************************************
static bool ReceiverTaskSetAckMsg(ACK_MSG*, uint8);
static bool RecieverTaskProcessRequest(REQUEST_MSG*);
static bool RecieverTaskProcessUID(REQUEST_MSG*);
static bool RecieverTaskProcessCMD(REQUEST_MSG*);
static bool RecieverTaskProcessDATA(REQUEST_MSG*);
static bool RecieverTaskBuildLoggerMsg(LOGGER_MSG*);

//*********************.RecieverTask.******************************************
//Purpose : Receive the request from Poller Task and Toggle the LED
//Inputs  : None
//Outputs : None
//Return  : None
//Notes   : None
//*****************************************************************************
void RecieverTask()
{
	REQUEST_MSG stReqMsg = {0, 0, 0};
	ACK_MSG stAckMsg = {0, 0, 0, 0};
	LOGGER_MSG stLogMsg = {0, 0};
	LOGACK_MSG stLogAckMsg = {0, 0};
	bool blFlag = FALSE;
	uint8 ucStatus = 0;
	WATCHDOG_EVENT stReceiverEvent = {0};

	if((osMsgqRecieverToPollerInit(sizeof(stAckMsg))) && \
			(osMsgqReceiverToLoggerInit(sizeof(stLogMsg))))
	{
		while(1)
		{
			if(osMsgqMessageRcvFromPoller(&stReqMsg))
			{
				LOG("Receiver: REQUID=%lu CMD=0x%02X DATA=0x%08lX\r\n",
						stReqMsg.ulUId, stReqMsg.ucCmd, stReqMsg.ulData);
				blFlag = RecieverTaskProcessRequest(&stReqMsg);
				ucStatus = (blFlag != FALSE) ? ACK_STATUS_OK : ACK_STAUS_ERROR;

				if(ReceiverTaskSetAckMsg(&stAckMsg, ucStatus))
				{
					if(osMsgqMessageSendToPoller(stAckMsg))
					{
						osTaskDelay(DELAY_200);
					}
				}

				if(RecieverTaskBuildLoggerMsg(&stLogMsg))
				{
					if(osMsgqMessageSendToLogger(stLogMsg))
					{
						osTaskDelay(DELAY_200);
					}
				}

				if(osMsgqMessageRcvFromLogger(&stLogAckMsg))
				{
					LOG("Receiver: LOGACKUID=%lu State=0x%02X\r\n",
							stLogAckMsg.ulUId, stLogAckMsg.ucState);
				}
			}
			stReceiverEvent.src = WATCHDOG_SRC_RECEIVER;
			if(!osMsgqSendToWatchdog(stReceiverEvent))
			{
				LOG("Receiver : Send Event to watchDogHandler Failed");
			}
			osTaskDelay(DELAY_100);
		}
	}
}

//*********************.ReceiverTaskSetAckMsg.*********************************
//Purpose : Set Ack Message according to Cmd and and the LED toggling process
//Inputs  : stReqMsg - Request Msg from Poller,ucState - Ack State Ok or Error
//Inputs  : stAckMsg - Ack Message that going to send from Receiver
//Outputs : None
//Return  : None
//Notes   : None
//*****************************************************************************
static bool ReceiverTaskSetAckMsg(ACK_MSG* stAckMsg, uint8 ucState)
{
	bool blFlag = FALSE;
	CMD_TYPE cmd = CMD_ACK;

	if(stAckMsg != NULL)
	{
		stAckMsg->ulUId = sgulUId;
		stAckMsg->ucCmd = cmd;
		stAckMsg->ulData = sgulData;
		stAckMsg->ucState = ucState;
		blFlag = TRUE;
	}

	return blFlag;
}

//*********************.RecieverTaskProcessRequest.****************************
//Purpose : Proceess Request Message received from Poller Task
//Inputs  : stReqMsg - Request Msg from Poller
//Outputs : None
//Return  : TRUE - Request Message Processed, FALSE - error
//Notes   : None
//*****************************************************************************
static bool RecieverTaskProcessRequest(REQUEST_MSG* stReqMsg)
{
	bool blFlag = FALSE;

	do
	{
		if(stReqMsg == NULL)
		{
			break;
		}

		if(!RecieverTaskProcessUID(stReqMsg))
		{
			break;
		}

		if(!RecieverTaskProcessDATA(stReqMsg))
		{
			break;
		}

		if(!RecieverTaskProcessCMD(stReqMsg))
		{
			break;
		}

		// If all succeeded
		blFlag = TRUE;

	}while(0);

	return blFlag;
}

//*********************.RecieverTaskProcessUID.********************************
//Purpose : Process UID for Acknowledgment
//Inputs  : stReqMsg - Request Msg from Poller
//Outputs : None
//Return  : TRUE - Request Message UID processed, FALSE - error
//Notes   : None
//*****************************************************************************
static bool RecieverTaskProcessUID(REQUEST_MSG* stReqMsg)
{
	bool blFlag = FALSE;

	if(stReqMsg != NULL)
	{
		sgulUId =  stReqMsg->ulUId;
		blFlag = TRUE;
	}

	return blFlag;
}

//*********************.RecieverTaskProcessCMD.********************************
//Purpose : Process CMD for Acknowledgment
//Inputs  : stReqMsg - Request Msg from Poller
//Outputs : None
//Return  : TRUE - Request Message CMD processed, FALSE - error
//Notes   : None
//*****************************************************************************
static bool RecieverTaskProcessCMD(REQUEST_MSG* stReqMsg)
{
	bool blFlag = FALSE;

	if(stReqMsg != NULL)
	{
		switch(stReqMsg->ucCmd)
		{
			case CMD_SET:
				if((sgulData & MASK) == MASK)
				{
					gucLEDState = TRUE;
				}
				else
				{
					gucLEDState = FALSE;
				}

				blFlag = TRUE;
				break;

			case CMD_GET:
				//:TO DO: Retrieve the current LED state
				blFlag = TRUE;
				break;

			default:
				printf("Invalid Command: 0x%02X\r\n", stReqMsg->ucCmd);
				break;
		}
	}

	return blFlag;
}

//*********************.RecieverTaskProcessDATA.*******************************
//Purpose : Process DATA for Acknowledgment
//Inputs  : stReqMsg - Request Msg from Poller
//Outputs : None
//Return  : TRUE - Request Message DATA processed, FALSE - error
//Notes   : None
//*****************************************************************************
static bool RecieverTaskProcessDATA(REQUEST_MSG* stReqMsg)
{
	bool blFlag = FALSE;

	if(stReqMsg != NULL)
	{
		sgulData = stReqMsg->ulData;
		blFlag = TRUE;
	}

	return blFlag;
}

//*********************.RecieverTaskBuildLoggerMsg.****************************
//Purpose :	Build the Logger Message
//Inputs  : stLogMsg - Logger Message
//Outputs : None
//Return  : TRUE - Request Message built, FALSE - error
//Notes   : None
//*****************************************************************************
static bool RecieverTaskBuildLoggerMsg(LOGGER_MSG* stLogMsg)
{
	bool blFlag = FALSE;

	if(stLogMsg != NULL)
	{
		stLogMsg->ulUId = sgulUId;
		stLogMsg->ucLEDState = gucLEDState;
		blFlag = TRUE;
	}

	return blFlag;
}
//EOF
