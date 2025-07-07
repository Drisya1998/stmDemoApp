# stmDemoApp

stmDemoApp is a application that builds LED Blinking application for STM32-F103C8.
Arm® 32-bit Cortex®-M3 CPU core

## Features

Organized source code in multiple directories
Build and Run in STM32 using STM32CubeIDE platform.

### Build 
In STM32CubeIDE , 
stmDemoApp.ioc file need to edit 
Set USART2_Tx AND USART2_Rx Pins .Set GPIO_Input and GPIO_OutPut Pins.

In Project -> clean Build
Build Project
Run --- Flashing 
Tera Term connected and set UART Parameters see the Messages.

### UART Parameters

baudrate - 115200
Data - 8bits
Parity - None
FlowControl = None

