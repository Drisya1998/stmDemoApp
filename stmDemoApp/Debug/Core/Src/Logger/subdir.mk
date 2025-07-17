################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Logger/LoggerTask.c 

OBJS += \
./Core/Src/Logger/LoggerTask.o 

C_DEPS += \
./Core/Src/Logger/LoggerTask.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Logger/%.o Core/Src/Logger/%.su Core/Src/Logger/%.cyclo: ../Core/Src/Logger/%.c Core/Src/Logger/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I"C:/Users/1782/STM32CubeIDE/workspace_1.18.1/stmDemoApp/Core/Src/RGB" -I"C:/Users/1782/STM32CubeIDE/workspace_1.18.1/stmDemoApp/Core/Src/Pwm" -I"C:/Users/1782/STM32CubeIDE/workspace_1.18.1/stmDemoApp/Core/Src/Logger" -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/1782/STM32CubeIDE/workspace_1.18.1/stmDemoApp/Core/Src/AppMain" -I"C:/Users/1782/STM32CubeIDE/workspace_1.18.1/stmDemoApp/Core/Src/GPIO" -I"C:/Users/1782/STM32CubeIDE/workspace_1.18.1/stmDemoApp/Core/Src/Poller" -I"C:/Users/1782/STM32CubeIDE/workspace_1.18.1/stmDemoApp/Core/Src/Reciever" -I"C:/Users/1782/STM32CubeIDE/workspace_1.18.1/stmDemoApp/Core/Src/LED" -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I"C:/Users/1782/STM32CubeIDE/workspace_1.18.1/stmDemoApp/Core/Src/OS" -I"C:/Users/1782/STM32CubeIDE/workspace_1.18.1/stmDemoApp/Core/Src/WatchDog" -I"C:/Users/1782/STM32CubeIDE/workspace_1.18.1/stmDemoApp/Core/Src/Driver" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-Logger

clean-Core-2f-Src-2f-Logger:
	-$(RM) ./Core/Src/Logger/LoggerTask.cyclo ./Core/Src/Logger/LoggerTask.d ./Core/Src/Logger/LoggerTask.o ./Core/Src/Logger/LoggerTask.su

.PHONY: clean-Core-2f-Src-2f-Logger

