//**************************** OSTask *****************************************
// Copyright (c) 2025 Trenser Technology Solutions
// All Rights Reserved
//*****************************************************************************
//
// Summary : OSTask header File
// Note    : Added Macros
//
//*****************************************************************************

#ifndef INC_OS_TASK_H_
#define INC_OS_TASK_H_

//******************************* Include Files *******************************
#include "cmsis_os2.h"
#include "AppMain.h"
#include "stdbool.h"
//******************************* Global Types ********************************
typedef struct _TASKS_
{
	uint8 *pucTaskName;
	uint32 ulStackSize;
	uint8 ucPriority;
	void (*pTaskFunc)(void *);
}TASKS;

//***************************** Global Constants ******************************
#define TASKS_MAX_SIZE		4
#define STACK_SIZE			512 * 2
#define THREAD_PRIORITY		24

//***************************** Global Variables ******************************
extern osMutexId_t uartMutex;

//***************************** Function Declaration **************************
bool TaskInit();
bool UARTMutexAcquire();
bool UARTMutexRelease();
void osTaskDelay(uint32);
uint32 osGetTime();

//*********************** Inline Method Implementations ***********************

#endif /* INC_OS_TASK_H_ */
