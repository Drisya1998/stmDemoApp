//*******************************PollerTask************************************
//Copyright (c) 2025 Trenser Technology Solutions
//All Rights Reserved
//*****************************************************************************
//
//File     : PollerTask.c
//Summary  : Infinitely check the button press and send the request to Reciever
//			 Task and handles the request data
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
#include "LoggerTask.h"
#include "LED.h"
#include "AppMain.h"
#include "WatchDogHandler.h"

//*********************Local Types*********************************************

//*********************Local Constants*****************************************

//*********************Local Variables*****************************************
static uint32 sgulUId = 0;
static uint8 sgulLEDSate = FALSE;

//*********************Local Functions*****************************************
static bool LoggerTaskProcessLoggerMsg(LOGGER_MSG*);
static bool LoggerTaskProcessUID(LOGGER_MSG*);
static bool LoggerTaskProcessLEDState(LOGGER_MSG*);
static bool LoggerTaskSetAckMsg(LOGACK_MSG*, uint8);

//*********************.LoggerTask.********************************************
//Purpose :	Inifinitely receive the Request from Receiver Task and toggles the
//			LED
//Inputs  : None
//Outputs : None
//Return  : None
//Notes   : None
//*****************************************************************************
void LoggerTask()
{
	LOGGER_MSG stLogMsg = {0, 0};
	LOGACK_MSG stLogAckMsg ={0, 0};
	WATCHDOG_EVENT stLoggerEvent = {0};
	bool blFlag = FALSE;
	uint8 ucStatus = 0;

	if(osMsgqLoggerToReceiverInit(sizeof(stLogAckMsg)))
	{
		while(1)
		{
			if(osMsgqMsgRcvFromReceiver(&stLogMsg))
			{
				LOG("Logger: LOGUID=%lu LEDState=0x%02X\r\n",
						stLogMsg.ulUId, stLogMsg.ucLEDState);


				if(LoggerTaskProcessLoggerMsg(&stLogMsg))
				{
					blFlag = LEDToggle(sgulLEDSate);
					ucStatus = (blFlag != FALSE) ? ACK_STATUS_OK : ACK_STAUS_ERROR;

					if(LoggerTaskSetAckMsg(&stLogAckMsg, ucStatus))
					{
						if(osMsgqMsgSendToReceiver(stLogAckMsg))
						{
							osTaskDelay(DELAY_200);
						}
					}
				}
			}
			stLoggerEvent.src = WATCHDOG_SRC_LOGGER;
			if(!osMsgqSendToWatchdog(stLoggerEvent))
			{
				LOG("Logger : Send Event to watchDogHandler Failed");
			}
			osTaskDelay(DELAY_100);
		}
	}
}

//*********************.LoggerTaskProcessLoggerMsg.****************************
//Purpose : Proceess Request Message received from Poller Task
//Inputs  : stReqMsg - Request Msg from Poller
//Outputs : None
//Return  : TRUE - Request Message Processed, FALSE - error
//Notes   : None
//*****************************************************************************
static bool LoggerTaskProcessLoggerMsg(LOGGER_MSG* stLogMsg)
{
	bool blFlag = FALSE;

	do
	{
		if(stLogMsg == NULL)
		{
			break;
		}

		if(!LoggerTaskProcessUID(stLogMsg))
		{
			break;
		}

		if(!LoggerTaskProcessLEDState(stLogMsg))
		{
			break;
		}

		// If all succeeded
		blFlag = TRUE;

	}while(0);

	return blFlag;
}

//*********************.LoggerTaskProcessUID.********************************
//Purpose : Process UID for Acknowledgment
//Inputs  : stReqMsg - Request Msg from Poller
//Outputs : None
//Return  : TRUE - Request Message UID processed, FALSE - error
//Notes   : None
//*****************************************************************************
static bool LoggerTaskProcessUID(LOGGER_MSG* stLogMsg)
{
	bool blFlag = FALSE;

	if(stLogMsg != NULL)
	{
		sgulUId =  stLogMsg->ulUId;
		blFlag = TRUE;
	}

	return blFlag;
}

//*********************.LoggerTaskProcessLEDState.*******************************
//Purpose : Process DATA for Acknowledgment
//Inputs  : stReqMsg - Request Msg from Poller
//Outputs : None
//Return  : TRUE - Request Message DATA processed, FALSE - error
//Notes   : None
//*****************************************************************************
static bool LoggerTaskProcessLEDState(LOGGER_MSG* stLogMsg)
{
	bool blFlag = FALSE;

	if(stLogMsg != NULL)
	{
		sgulLEDSate = stLogMsg->ucLEDState;
		blFlag = TRUE;
	}

	return blFlag;
}

//*********************.LoggerTaskSetAckMsg.*********************************
//Purpose : Set Ack Message according LED toggling success or not.
//Inputs  : stReqMsg - Request Msg from Poller,ucState - Ack State Ok or Error
//Inputs  : stAckMsg - Ack Message that going to send from Receiver
//Outputs : None
//Return  : None
//Notes   : None
//*****************************************************************************
static bool LoggerTaskSetAckMsg(LOGACK_MSG* stLogAckMsg, uint8 ucState)
{
	bool blFlag = FALSE;

	if(stLogAckMsg != NULL)
	{
		stLogAckMsg->ulUId = sgulUId;
		stLogAckMsg->ucState = ucState;
		blFlag = TRUE;
	}

	return blFlag;
}
//EOF
