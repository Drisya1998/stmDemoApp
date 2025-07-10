//*******************************WatchDogHandler*******************************
//Copyright (c) 2025 Trenser Technology Solutions
//All Rights Reserved
//*****************************************************************************
//
//File     : WatchDogHandler.c
//Summary  : Printf via UART and LED blinking
//Note     : None
//Author   : Drisya P
//Date     : 09/Jul/2025
//
//*****************************************************************************

//*********************Include Files*******************************************
#include "WatchDogHandler.h"
#include "WatchDogTimer.h"
#include "AppMain.h"
#include "osMsgq.h"
#include <stdbool.h>
#include <stdio.h>

//*********************Local Types*********************************************

//*********************Local Constants*****************************************

//*********************Local Variables*****************************************
static WATCHDOG_EVENT_FLAGS stFlags = {0};
//*********************Local Functions*****************************************
static bool WatchDogHandlerProcessEvent(WATCHDOG_EVENT*);

//*********************.WatchDogHandler.***************************************
//Purpose : Receive Events from Poller and Reciever threads and Handles
//			WatchDog timers.
//Inputs  : None
//Outputs : None
//Return  : None
//Notes   : None
//*****************************************************************************
void WatchDogHandler()
{
	WATCHDOG_EVENT stEvent = {0};

	WatchDogTimerInit();

	while(1)
	{
		if(osMsgqRcvFromWatchdog(&stEvent))
		{
			if(WatchDogHandlerProcessEvent(&stEvent))
			{
				if(stFlags.ucAll == ALL_EVENTS_SET)
				{
					WatchdogTimerClear();
					if(UARTMutexAcquire())
					{
						printf("Watchdog Cleared\r\n");
					}

					if(!UARTMutexRelease())
					{
						printf("UART Mutex Not Releasing\r\n");
					}
					stFlags.ucAll = 0;  // Reset for next cycle
				}
				/*else
				{
				    printf("Watchdog NOT cleared! Missing from: ");

				    if(!stFlags.BITS.ucPoller)
				    {
				        printf("Poller ");
				    }

				    if(!stFlags.BITS.ucReceiver)
				    {
				        printf("Receiver ");
				    }
				    if(!stFlags.BITS.ucLogger)
				    {
				        printf("Logger ");
				    }

				    printf("\r\n");
				}*/
			}
		}
		osTaskDelay(DELAY_100);
	}
}

//*********************.WatchDogHandlerProcessEvent.***************************
//Purpose : Procees the Event - Check the event that is received from Poller
//			or Receiver
//Inputs  : None
//Outputs : None
//Return  : None
//Notes   : None
//*****************************************************************************
static bool WatchDogHandlerProcessEvent(WATCHDOG_EVENT* stEvent)
{
	bool blFlag = FALSE;

	if(stEvent != NULL)
	{
		switch(stEvent->src)
		{
			case WATCHDOG_SRC_POLLER :
				stFlags.BITS.ucPoller = TRUE;
				blFlag = TRUE;
				break;
			case WATCHDOG_SRC_RECEIVER :
				stFlags.BITS.ucReceiver = TRUE;
				blFlag = TRUE;
				break;
			case WATCHDOG_SRC_LOGGER :
				stFlags.BITS.ucLogger = TRUE;
				blFlag = TRUE;
				break;
			default :
				printf("Invalid Event\r\n");
		}
	}

	return blFlag;
}

//EOF
