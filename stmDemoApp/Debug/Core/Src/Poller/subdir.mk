################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Poller/PollerTask.c 

OBJS += \
./Core/Src/Poller/PollerTask.o 

C_DEPS += \
./Core/Src/Poller/PollerTask.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Poller/%.o Core/Src/Poller/%.su Core/Src/Poller/%.cyclo: ../Core/Src/Poller/%.c Core/Src/Poller/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/1782/STM32CubeIDE/workspace_1.18.1/stmDemoApp/Core/Src/AppMain" -I"C:/Users/1782/STM32CubeIDE/workspace_1.18.1/stmDemoApp/Core/Src/GPIO" -I"C:/Users/1782/STM32CubeIDE/workspace_1.18.1/stmDemoApp/Core/Src/Poller" -I"C:/Users/1782/STM32CubeIDE/workspace_1.18.1/stmDemoApp/Core/Src/Reciever" -I"C:/Users/1782/STM32CubeIDE/workspace_1.18.1/stmDemoApp/Core/Src/LED" -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I"C:/Users/1782/STM32CubeIDE/workspace_1.18.1/stmDemoApp/Core/Src/OS" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-Poller

clean-Core-2f-Src-2f-Poller:
	-$(RM) ./Core/Src/Poller/PollerTask.cyclo ./Core/Src/Poller/PollerTask.d ./Core/Src/Poller/PollerTask.o ./Core/Src/Poller/PollerTask.su

.PHONY: clean-Core-2f-Src-2f-Poller

