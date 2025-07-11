//**************************** PwmDriver ********************************
// Copyright (c) 2025 Trenser Technology Solutions
// All Rights Reserved
//*****************************************************************************
//
// Summary : Pwm Driver header File
// Note    : Added Macros
//
//*****************************************************************************

#ifndef INC_PWM_DRIVER_H_
#define INC_PWM_DRIVER_H_

//******************************* Include Files *******************************
#include "AppMain.h"
//******************************* Global Types ********************************
typedef struct _PORTS_
{
		uint8 ucPA0 : 4;
		uint8 ucPA1 : 4;
		uint8 ucPA2 : 4;
		uint8 ucPA3 : 4;
		uint8 ucPA4 : 4;
		uint8 ucPA5 : 4;
		uint8 ucPA6 : 4;
		uint8 ucPA7 : 4;
}PORTS;

typedef union _CRL_
{
	PORTS stPorts;
	uint32 ulCRL;
}CRL;

typedef struct _GPIO_REGISTERS_
{
    CRL crl;
    uint32 ulCRH;
    uint32 ulIDR;
    uint32 ulODR;
    uint32 ulBSRR;
    uint32 ulBRR;
    uint32 ulLCKR;
}GPIO_REGISTERS;

typedef struct _RCC_REGISTERS_
{
	uint32 ulCR;
	uint32 ulCFGR;
	uint32 ulCIR;
	uint32 ulAPB2RSTR;
	uint32 ulAPB1RSTR;
	uint32 ulAHBENR;
	uint32 ulAPB2ENR;
	uint32 ulAPB1ENR;
}RCC_REGISTERS;

typedef struct _TIM2_REGISTERS_
{
	uint32 ulCR1;
	uint32 ulCR2;
	uint32 ulSMCR;
	uint32 ulDIER;
	uint32 ulSR;
	uint32 ulEGR;
	uint32 ulCCMR1;
	uint32 ulCCMR2;
	uint32 ulCCER;
	uint32 ulCNT;
	uint32 ulPSC;
	uint32 ulARR;
	uint32 ulRCR;
	uint32 ulCCR1;
	uint32 ulCCR2;
	uint32 ulCCR3;
	uint32 ulCCR4;
	uint32 ulDCR;
	uint32 ulDMAR;
}TIM2_REGISTERS;

//***************************** Global Constants ******************************
#define GPIOA_BASEADDR		 ((GPIO_REGISTERS *) 0x40010800)
#define RCC_BASEADDR		 ((RCC_REGISTERS *) 0x40021000)
#define TIM2_BASEADR		 ((TIM2_REGISTERS *)0x40000000)
//***************************** Global Variables ******************************
#define PRESCALAR			7199
#define AUTO_RELOAD			4999
//***************************** Function Declaration **************************
void PWMDriverInit();
void PWMDriverSet();
void PWMDriverStart(uint16);

//*********************** Inline Method Implementations ***********************

#endif /* INC_PWM_DRIVER_H_ */
