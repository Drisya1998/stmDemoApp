################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/LED/LED.c 

OBJS += \
./Core/Src/LED/LED.o 

C_DEPS += \
./Core/Src/LED/LED.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/LED/%.o Core/Src/LED/%.su Core/Src/LED/%.cyclo: ../Core/Src/LED/%.c Core/Src/LED/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-LED

clean-Core-2f-Src-2f-LED:
	-$(RM) ./Core/Src/LED/LED.cyclo ./Core/Src/LED/LED.d ./Core/Src/LED/LED.o ./Core/Src/LED/LED.su

.PHONY: clean-Core-2f-Src-2f-LED

