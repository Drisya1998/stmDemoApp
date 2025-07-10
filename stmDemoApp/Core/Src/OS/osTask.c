//*******************************OSTask*****************************************
//Copyright (c) 2025 Trenser Technology Solutions
//All Rights Reserved
//*****************************************************************************
//
//File     : osTask.c
//Summary  : Handles Thread Operations.
//Note     : None
//Author   : Drisya P
//Date     : 03/Jul/2025
//
//*****************************************************************************

//*********************Include Files*******************************************
#include <osTask.h>
#include <stdio.h>
#include <stdbool.h>
#include "AppMain.h"
#include "cmsis_os2.h"
#include "PollerTask.h"
#include "RecieverTask.h"
#include "WatchDogHandler.h"
#include "stm32f1xx_hal.h"

//*********************Local Types*********************************************

//*********************Local Constants*****************************************

//*********************Local Variables*****************************************
static osThreadId_t ThreadHandles[TASKS_MAX_SIZE] = {0,0};
static uint8 ucThreadIndex = 0;
//osMutexId_t uartMutex = NULL;

TASKS stTasks[TASKS_MAX_SIZE] =
	{
		{(uint8*)"Poller", STACK_SIZE, THREAD_PRIORITY, PollerTask},
		{(uint8*)"Receiver", STACK_SIZE, THREAD_PRIORITY, RecieverTask},
		{(uint8*)"WatchDogHandler", STACK_SIZE, THREAD_PRIORITY, WatchDogHandler}
	};

//*********************Local Functions*****************************************
static bool osTaskCreate();
//*********************.TaskInit.**********************************************
//Purpose :	Infinitely check the button press and send the request to Reciever
//			Task
//Inputs  : None
//Outputs : None
//Return  : TRUE - initialized , FALSE - Error
//Notes   : None
//*****************************************************************************
bool TaskInit()
{
	uint8 ucIndex = 0;
	bool blFlag = FALSE;

	for(ucIndex = 0; ucIndex < TASKS_MAX_SIZE; ucIndex++)
	{
		blFlag = osTaskCreate(&stTasks[ucIndex]);
	}

	return blFlag;
}

//*********************.osTaskCreate.******************************************
//Purpose :	Create each task
//Inputs  : stTask - structure include Thread name , stack size , priority ,
//				and	the function executed by thread.
//Outputs : None
//Return  : TRUE - created thread successfully , FALSE - error
//Notes   : None
//*****************************************************************************
static bool osTaskCreate(TASKS *stTask)
{
	bool blFlag = FALSE;
	osThreadAttr_t attr = {0, 0, 0, 0, 0, 0, 0, 0, 0};

	if(stTask != NULL)
	{
		attr.name = (const char *)stTask->pucTaskName;
		attr.stack_size = stTask->ulStackSize;
		attr.priority = (osPriority_t)osPriorityNormal;

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

//*********************.CreateUARTMutex.***************************************
//Purpose : Create Mutex
//Inputs  : None
//Outputs : None
//Return  : TRUE - return success , FALSE - Failed
//Notes   : None
//*****************************************************************************
/*bool CreateUARTMutex()
{
	bool blFlag = FALSE;

	uartMutex = osMutexNew(NULL);

	if(uartMutex != NULL)
	{
		blFlag = TRUE;
	}

	return blFlag;
}*/


//*********************.UARTMutexRelease.**************************************
//Purpose : unlock Mutex
//Inputs  : None
//Outputs : None
//Return  : TRUE - return success , FALSE - Failed
//Notes   : None
//*****************************************************************************
/*bool UARTMutexRelease()
{
	bool blFlag = FALSE;

	if(osMutexRelease(uartMutex) == osOK)
	{
		blFlag = TRUE;
	}

	return blFlag;
}*/

//*********************.UARTMutexAcquire.**************************************
//Purpose : lock Mutex
//Inputs  : None
//Outputs : None
//Return  : TRUE - return success , FALSE - Failed
//Notes   : None
//*****************************************************************************
/*bool UARTMutexAcquire()
{
	bool blFlag = FALSE;

	if(osMutexAcquire(uartMutex, osWaitForever) == osOK)
	{
		blFlag = TRUE;
	}

	return blFlag;
}*/

//*********************.osTaskDelay.*******************************************
//Purpose : To set delay on LED Blinking
//Inputs  : delay - delay in milliseconds
//Outputs : None
//Return  : None
//Notes   : None
//*****************************************************************************
void osTaskDelay(uint32 delay)
{
	osDelay(delay);
}

//*********************.osGetTime.*******************************************
//Purpose : To get the time
//Inputs  : None
//Outputs : None
//Return  : Time
//Notes   : None
//*****************************************************************************
uint32 osGetTime()
{
	uint32 ulTime;

	ulTime = HAL_GetTick();

	return ulTime;
}
//EOF
