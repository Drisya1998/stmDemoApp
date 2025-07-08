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
#include "stdbool.h"
#include "PollerTask.h"
#include "GPIO.h"
#include "AppMain.h"

//*********************Local Types*********************************************

//*********************Local Constants*****************************************

//*********************Local Variables*****************************************
static uint32 ulUIdCounter = 0;
uint32 ulDATA = 0x00000000;
uint32 ulMASK = 0x00000001;

//*********************Local Functions*****************************************
static bool PollerTaskBuildRequest(REQUEST_MSG*);

//*********************.PollerTask.********************************************
//Purpose :	Infinitely check the button press and send the request to Reciever
//			Task to toggle the LED
//Inputs  : None
//Outputs : None
//Return  : None
//Notes   : None
//*****************************************************************************
void PollerTask()
{
	REQUEST_MSG stReqMsg = {0, 0, 0};
	ACK_MSG stAckMsg = {0, 0, 0, 0};

	if(osMsgqPollerToRecieverInit(sizeof(stReqMsg)))
	{
		while(1)
		{
			if(GPIOReadButtonPress())
			{
				printf("\nButton Pressed\r\n");

				if(PollerTaskBuildRequest(&stReqMsg))
				{
					printf("Request Processed\r\n");

					if(osMsgqMessageSendToReceiver(stReqMsg))
					{
						osTaskDelay(DELAY_300);
					}

					if(osMsgqMessageRcvFromReceiver(&stAckMsg))
					{
						printf("Poller: ACKUID=%lu, CMD=0x%02X, STATE=0x%02X, \
								DATA=0x%08lX\r\n\n",
								stAckMsg.ulUId, stAckMsg.ucCmd,
								stAckMsg.ucState, stAckMsg.ulData);

					}
				}
			}

			osTaskDelay(DELAY_100);
		}
	}
}

//*********************.PollerTaskProcessRequest.******************************
//Purpose :	Build the Request Message
//Inputs  : None
//Outputs : None
//Return  : TRUE - Request Message built, FALSE - error
//Notes   : None
//*****************************************************************************
bool PollerTaskBuildRequest(REQUEST_MSG* stReqMsg)
{
	bool blFlag = FALSE;

	if(stReqMsg != NULL)
	{
		stReqMsg->ulUId = ++ulUIdCounter;
		stReqMsg->ucCmd = SET_CMD;
		ulDATA = ulDATA ^ ulMASK;
		stReqMsg->ulData = ulDATA;
		blFlag = TRUE;
	}

	return blFlag;
}

//EOF
