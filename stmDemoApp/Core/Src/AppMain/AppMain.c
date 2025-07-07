//*******************************AppMain******************************************
//Copyright (c) 2025 Trenser Technology Solutions
//All Rights Reserved
//*****************************************************************************
//
//File     : AppMain.c
//Summary  : Printf via UART and LED blinking
//Note     : None
//Author   : Drisya P
//Date     : 27/Jun/2025
//
//*****************************************************************************

//*********************Include Files*******************************************
#include <stdio.h>
#include <stdbool.h>
#include "AppMain.h"
#include "OSInterface.h"
#include "PollerTask.h"
#include "RecieverTask.h"

//*********************Local Types*********************************************

//*********************Local Constants*****************************************

//*********************Local Variables*****************************************
TASKS stTasks[TASKS_MAX_SIZE] =
	{
			{(uint8*)"Poller", STACK_SIZE, THREAD_PRIORITY, PollerTask},
			{(uint8*)"Receiver", STACK_SIZE, THREAD_PRIORITY, RecieverTask}
	};

//*********************Local Functions*****************************************

//*********************.AppMain.***********************************************
//Purpose : Printf via UART and Initialize the Tasks.
//Inputs  : None
//Outputs : None
//Return  : None
//Notes   : None
//*****************************************************************************
void AppMain()
{
	bool blFlag =  FALSE;

	printf("Hello from STM32 via UART!\r\n");
	blFlag = TaskInit();

	if(blFlag != FALSE)
	{
		printf("Thread Creation Completed\r\n");
	}
	else
	{
		printf("Thread Creation Failed\r\n");
	}

}

//*********************.TaskInit.****************************************
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
	REQUEST_MSG stReqMsg = {0, 0, 0};
	ACK_MSG stAckMsg = {0, 0, 0, 0};

	blFlag = CreateUARTMutex();

	if(blFlag == FALSE)
	{
		printf("Mutex Creation Failed\r\n");
	}

	for(ucIndex = 0; ucIndex < TASKS_MAX_SIZE; ucIndex++)
	{
		blFlag = CreateThread(&stTasks[ucIndex]);
	}

	return blFlag;
}

//EOF
