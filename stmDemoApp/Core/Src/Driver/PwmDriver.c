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
	pstRCC->ulAPB2ENR |= GPIOA_CLOCK_ENABLE;
	pstRCC->ulAPB1ENR |= TIM2_CLOCK_ENABLE;

	pstGPIOA->crl.ulCRL &= PA0_CRL_CLEAR;
	pstGPIOA->crl.ulCRL |= PA0_CONFIG_SET;
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
	pstTIM2->ulCCMR1 &= CH1_OC1M_CLEAR;
	pstTIM2->ulCCMR1 |= CH1_PWM_MODE_SET;
	pstTIM2->ulCCMR1 |= CH1_OC1PE_SET;
	pstTIM2->ulCCER |= ENABLE_PWM;
	pstTIM2->ulCR1 |= ARPE_SET;
	pstTIM2->ulEGR |= UPDATE_EVENT;
}

//*********************.PWMDriverStart.************************************
//Purpose : Start TIM2 for PWM output on Channel 1
//Inputs  : unDuty - dutyCycle
//Outputs : None
//Return  : None
//Notes   : None
//*****************************************************************************
void PWMDriverStart(uint16 unDuty)
{
	pstTIM2->ulCCR1 = unDuty;
	pstTIM2->ulCR1 |= ENABLE_PWM;
}
//EOF
