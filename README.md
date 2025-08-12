# stmDemoApp

stmDemoApp is a application that builds LED Blinking application for STM32-F103RB.
Also there is 3 Tasks Created Poller , Receiver , Logger Reads the button press and send request to Receiver , Receiver handles the request send to the Logger . Logger
Task will toggles the LED according to the data comes from Poller. 
WatchDog Implemented that receives the Events from 3 Tasks with Timer , otherwise
system will restart.
using PWM , LED is blinking Continuously. 
Using PWM and DMA , WS2811 RGB LED will TURN ON.
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

