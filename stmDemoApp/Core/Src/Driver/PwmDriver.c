//*******************************PwmDriver*********************************
//Copyright (c) 2025 Trenser Technology Solutions
//All Rights Reserved
//*****************************************************************************
//
//File     : PwmDriver.c
//Summary  : Pwm Driver
//Note     : None
//Author   : Drisya P
//Date     : 10/Jul/2025
//
//*****************************************************************************

//*********************Include Files*******************************************
#include "PwmDriver.h"

//*********************Local Types*********************************************

//*********************Local Constants*****************************************

//*********************Local Variables*****************************************
GPIO_REGISTERS* pstGPIOA = GPIOA_BASEADDR;
RCC_REGISTERS* pstRCC = RCC_BASEADDR;
TIM2_REGISTERS* pstTIM2 = TIM2_BASEADR;

//*********************Local Functions*****************************************

//*********************.PwmDriverInit.*************************************
//Purpose : Initialize the Pwm.
//Inputs  : None
//Outputs : None
//Return  : None
//Notes   : None
//*****************************************************************************
void PWMDriverInit()
{
	pstRCC->ulAPB2ENR |= (1 << 2);
	pstRCC->ulAPB1ENR |= (1 << 0);

	pstGPIOA->crl.ulCRL &= ~(0xF << 0);
	pstGPIOA->crl.ulCRL |=  (0xB << 0);
}

//*********************.PwmDriverSet.************************************
//Purpose : Configure TIM2 for PWM output on Channel 1
//Inputs  : None
//Outputs : None
//Return  : None
//Notes   : None
//*****************************************************************************
void PWMDriverSet()
{
	pstTIM2->ulPSC = PRESCALAR;
	pstTIM2->ulARR = AUTO_RELOAD;
	pstTIM2->ulCCMR1 &= ~(0x7 << 4);
	pstTIM2->ulCCMR1 |=  (0x6 << 4);
	pstTIM2->ulCCMR1 |=  (1 << 3);
	pstTIM2->ulCCER |= 1;
	pstTIM2->ulCR1 |= (1 << 7);
	pstTIM2->ulEGR |= (1 << 0);
}

//*********************.PWMDriverStart.************************************
//Purpose : Configure TIM2 for PWM output on Channel 1
//Inputs  : unDuty - dutyCycle
//Outputs : None
//Return  : None
//Notes   : None
//*****************************************************************************
void PWMDriverStart(uint16 unDuty)
{
	pstTIM2->ulCCR1 = unDuty;
	pstTIM2->ulCR1 |= 1;
}
//EOF
