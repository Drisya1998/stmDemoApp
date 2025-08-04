//*******************************WS2811Driver*********************************
//Copyright (c) 2025 Trenser Technology Solutions
//All Rights Reserved
//*****************************************************************************
//
//File     : WS2811Driver.c
//Summary  : WS2811 Driver initializes the Registers and
//           send the data to WS2811 LED
//Note     : None
//Author   : Drisya P
//Date     : 14/Jul/2025
//
//*****************************************************************************

//*********************Include Files*******************************************
#include "WS2811Driver.h"
#include "AppMain.h"
#include "PwmDriver.h"

//*********************Local Types*********************************************

//*********************Local Constants*****************************************

//*********************Local Variables*****************************************
GPIO_REGISTERS* pstGPIOA_Ws2811 = GPIOA_BASEADDR;
RCC_REGISTERS* pstRCC_Ws2811 = RCC_BASEADDR;
TIM3_REGISTERS* pstTIM3_Ws2811 = TIM3_BASEADR;
DMA_CHANNEL_REGISTERS* pstDMA1_Ws2811 = DMA1_CHANNEL_BASEADR;
uint16 unWS2811DMABuffer[WS2811_BITS_PER_LED + WS2811_RESET_LENGTH];

//*********************Local Functions*****************************************

//*********************.WS2811DriverInit.*************************************
//Purpose : Initialize the STM GPIOA , TIM3 CH1 and DMA1 Channel6.
//Inputs  : None
//Outputs : None
//Return  : None
//Notes   : None
//*****************************************************************************
void WS2811DriverInit()
{
	pstRCC_Ws2811->ulAPB2ENR |= RCC_GPIOA_CLOCK_ENABLE;
	pstRCC_Ws2811->ulAPB1ENR |= RCC_TIM3_CLOCK_ENABLE;
	pstRCC_Ws2811->ulAHBENR  |= RCC_DMA1_CLOCK_ENABLE;

	pstGPIOA_Ws2811->crl.ulCRL &= PA6_CRL_CLEAR;
	pstGPIOA_Ws2811->crl.ulCRL |= PA6_CONFIG_SET;

	pstTIM3_Ws2811->ulARR = AUTO_RELOAD_Ws2811;
	pstTIM3_Ws2811->ulCCMR1 |= PWM_MODE_SET;
	pstTIM3_Ws2811->ulCCMR1 |= CH1_OUTPUT_SET;
	pstTIM3_Ws2811->ulCCER |= CH1_ENABLE;
	pstTIM3_Ws2811->ulDIER |= TIM3_DMA_ENABLE;

	// DMA config (DMA1 Channel 6 is for TIM3_CH1)
	pstDMA1_Ws2811->ulCCR = 0;
	pstDMA1_Ws2811->ulCPAR = (uint32)&pstTIM3_Ws2811->ulCCR1;
	pstDMA1_Ws2811->ulCMAR = (uint32)unWS2811DMABuffer;

	// Memory to Peripheral, enable memory increment, 16-bit transfer
	pstDMA1_Ws2811->ulCCR |= (DMA_DIR_READ_FROM_MEMORY |
							DMA_MEMORY_INCREMENT_MODE |
							DMA_PSIZE_16BITS |
							DMA_MSIZE_MEDIUM);

	pstTIM3_Ws2811->ulCR1 |= TIM3_CR1_CEN;

}

//*********************.WS2811DriverSendData.************************************
//Purpose : Send Data of RGB from DMA buffer to TIM3 CH1 that connected with PA6
//			then to WS2811
//Inputs  : None
//Outputs : None
//Return  : None
//Notes   : None
//*****************************************************************************
void WS2811DriverSendData()
{
	pstDMA1_Ws2811->ulCNDTR = WS2811_BITS_PER_LED + WS2811_RESET_LENGTH;
	pstDMA1_Ws2811->ulCCR |= DMA_CHANNEL_ENABLE;
}

//********************.WS2811PrepareBuffer.************************************
//Purpose : Prepare a DMA Buffer to store the values of Red , Green  and Blue
//Inputs  : Red , Green , Blue Values
//Outputs : DMA Buffer updating
//Return  : None
//Notes   : None
//*****************************************************************************
void WS2811PrepareBuffer(uint8 ucGreen, uint8 ucRed, uint8 ucBlue)
{
    uint32 ulColor = (((uint32)ucGreen << GREEN_LEFTSHIFT) |
    					((uint32)ucRed << RED_LEFTSHIFT) |
						ucBlue);
    uint8 ucIndex = 0;

    for (ucIndex = 0; ucIndex < WS2811_BITS_PER_LED; ucIndex++)
    {
        if (ulColor & (1 << (WS2811_BITS_PER_LED - 1 - ucIndex)))
        {
        	unWS2811DMABuffer[ucIndex] = WS2811_1;
        }
        else
        {
        	unWS2811DMABuffer[ucIndex] = WS2811_0;
        }
    }

    for (ucIndex = 0; ucIndex < WS2811_RESET_LENGTH; ucIndex++)
    {
    	unWS2811DMABuffer[WS2811_BITS_PER_LED + ucIndex] = 0;
    }
}

//EOF
