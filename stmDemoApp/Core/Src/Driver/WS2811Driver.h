//**************************** WS2811Driver ********************************
// Copyright (c) 2025 Trenser Technology Solutions
// All Rights Reserved
//*****************************************************************************
//
// Summary : WS2811 Driver header File
// Note    : Added Macros
//
//*****************************************************************************

#ifndef INC_WS2811_DRIVER_H_
#define INC_WS2811_DRIVER_H_

//******************************* Include Files *******************************
#include "AppMain.h"
//******************************* Global Types ********************************
typedef struct _TIM3_REGISTERS_
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
}TIM3_REGISTERS;

typedef struct _DMA_CHANNEL_REGISTERS_
{
    uint32 ulCCR;     // DMA channel x configuration register
    uint32 ulCNDTR;   // DMA channel x number of data register
    uint32 ulCPAR;    // DMA channel x peripheral address register
    uint32 ulCMAR;    // DMA channel x memory address register
    uint32 ulRESERVED;
}DMA_CHANNEL_REGISTERS;


//***************************** Global Constants ******************************
#define TIM3_BASEADR		 		((TIM3_REGISTERS *)0x40000400)
#define DMA1_CHANNEL_BASEADR		((DMA_CHANNEL_REGISTERS *)0x4002006C)

#define RCC_TIM3_CLOCK_ENABLE  		(1 << 1)  // Enable TIM3 clock
#define RCC_GPIOA_CLOCK_ENABLE  	(1 << 2)  // Enable GPIOA clock
#define RCC_DMA1_CLOCK_ENABLE		(1 << 0)  // Enable DMA1 Clock

#define PA6_CRL_CLEAR				~(0xF << 24)
#define PA6_CONFIG_SET				(0xB << 24)

#define AUTO_RELOAD_Ws2811			79
#define PWM_MODE_SET				(0x6 << 4)
#define CH1_OUTPUT_SET				(0x1 << 3)
#define CH1_ENABLE 					(0x1 << 0)
#define TIM3_CR1_CEN				(1 << 0)
#define TIM3_DMA_ENABLE				(1 << 9)

#define DMA_DIR_READ_FROM_MEMORY	(0x1 << 4)
#define DMA_MEMORY_INCREMENT_MODE	(0x1 << 7)
#define DMA_PSIZE_16BITS			(0x1 << 8)
#define DMA_MSIZE_MEDIUM			(0x1 << 10)
#define DMA_CHANNEL_ENABLE			(0x1 << 0)

#define WS2811_0  22
#define WS2811_1  45
#define WS2811_RESET_LENGTH  50  // Send at least 50µs of low signal
#define WS2811_BITS_PER_LED 24
//***************************** Global Variables ******************************

//***************************** Function Declaration **************************
void WS2811DriverInit();
void WS2811PrepareBuffer(uint8, uint8, uint8);
void WS2811DriverSendData();
//*********************** Inline Method Implementations ***********************

#endif /* INC_WS2811_DRIVER_H_ */
