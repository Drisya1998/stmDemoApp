//**************************** RecieverTask ***********************************
// Copyright (c) 2025 Trenser Technology Solutions
// All Rights Reserved
//*****************************************************************************
//
// Summary : RecieverTask header File
// Note    : Added Macros
//
//*****************************************************************************

#ifndef INC_RECIEVER_TASK_H_
#define INC_RECIEVER_TASK_H_

//******************************* Include Files *******************************

//******************************* Global Types ********************************

//***************************** Global Constants ******************************
#define ACK_STATUS_OK 		0x00
#define ACK_STAUS_ERROR		0x01
#define ACK_DATA			0xFFFFFFFF

typedef enum{
	CMD_ACK,
	CMD_GET,
	CMD_SET
}CMD_TYPE;

//***************************** Global Variables ******************************

//***************************** Function Declaration **************************
void RecieverTask();

//*********************** Inline Method Implementations ***********************

#endif /* INC_RECIEVER_TASK_H_ */
