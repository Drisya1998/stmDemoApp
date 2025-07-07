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
#include <stdio.h>
#include "stdbool.h"
#include "RecieverTask.h"
#include "OSInterface.h"
#include "LED.h"
#include "AppMain.h"

//*********************Local Types*********************************************

//*********************Local Constants*****************************************

//*********************Local Variables*****************************************
static uint32 ulUId = 0;
static uint32 ulData = ACK_DATA;

//*********************Local Functions*****************************************
static bool ReceiverTaskSetAckMsg(uint32, ACK_MSG*, uint8);
static bool RecieverTaskProcessRequest(REQUEST_MSG*);
static bool RecieverTaskProcessUID(REQUEST_MSG*);
static bool RecieverTaskProcessCMD(REQUEST_MSG*);
static bool RecieverTaskProcessDATA(REQUEST_MSG*);

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
	bool blFlag = FALSE;
	uint8 ucStatus = 0;

	if(RecieverToPollerMsgQInit(sizeof(stAckMsg)))
	{
		while(1)
		{
			if(MessageRcvFromPoller(&stReqMsg))
			{
				printf("Receiver: REQUID=%lu CMD=0x%02X DATA=0x%08lX\r\n", stReqMsg.ulUId,
														stReqMsg.ucCmd, stReqMsg.ulData);
				blFlag = RecieverTaskProcessRequest(&stReqMsg);
				ucStatus = (blFlag != FALSE) ? ACK_STATUS_OK : ACK_STAUS_ERROR;

				if(ReceiverTaskSetAckMsg(ulUId, &stAckMsg, ucStatus))
				{
					if(MessageSendToPoller(stAckMsg))
					{
						Delay(DELAY_100);
					}
				}
			}
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
static bool ReceiverTaskSetAckMsg(uint32 ulUId, ACK_MSG* stAckMsg,
															uint8 ucState)
{
	bool blFlag = FALSE;
	CMD_TYPE cmd = CMD_ACK;

	if(stAckMsg != NULL)
	{
		stAckMsg->ulUId = ulUId;
		stAckMsg->ucCmd = cmd;
		stAckMsg->ulData = ulData;
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
bool RecieverTaskProcessRequest(REQUEST_MSG* stReqMsg)
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

		if(!RecieverTaskProcessCMD(stReqMsg))
		{
			break;
		}

		if(!RecieverTaskProcessDATA(stReqMsg))
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
bool RecieverTaskProcessUID(REQUEST_MSG* stReqMsg)
{
	bool blFlag = FALSE;

	if(stReqMsg != NULL)
	{
		ulUId =  stReqMsg->ulUId;
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
bool RecieverTaskProcessCMD(REQUEST_MSG* stReqMsg)
{
	bool blFlag = FALSE;

	if(stReqMsg != NULL)
	{
		switch(stReqMsg->ucCmd)
		{
			case CMD_SET:
				if(LEDBlink())
				{
					blFlag = TRUE;
				}
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
bool RecieverTaskProcessDATA(REQUEST_MSG* stReqMsg)
{
	bool blFlag = FALSE;

	if(stReqMsg != NULL)
	{
		ulData = stReqMsg->ulData;
		blFlag = TRUE;
	}

	return blFlag;
}
//EOF
