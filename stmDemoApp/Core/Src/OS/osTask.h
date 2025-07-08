//**************************** OSInterface ***************************************
// Copyright (c) 2025 Trenser Technology Solutions
// All Rights Reserved
//*****************************************************************************
//
// Summary : OSInterface header File
// Note    : Added Macros
//
//*****************************************************************************

#ifndef INC_OS_INTERFACE_H_
#define INC_OS_INTERFACE_H_

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

//***************************** Global Variables ******************************
extern osMutexId_t uartMutex;

//***************************** Function Declaration **************************
bool TaskInit();
bool osTaskCreate();
/*bool CreateUARTMutex();
bool UARTMutexAcquire();
bool UARTMutexRelease();*/
void osTaskDelay(uint32);

//*********************** Inline Method Implementations ***********************

#endif /* INC_OS_INTERFACE_H_ */
