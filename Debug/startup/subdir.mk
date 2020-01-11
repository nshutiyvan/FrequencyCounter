################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../startup/startup_stm32f303xe.s 

OBJS += \
./startup/startup_stm32f303xe.o 


# Each subdirectory must supply rules for building sources it contributes
startup/%.o: ../startup/%.s
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Assembler'
	@echo $(PWD)
	arm-none-eabi-as -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -I"C:/Users/vectaa/Desktop/FrequencyCounter/HAL_Driver/Inc/Legacy" -I"C:/Users/vectaa/Desktop/FrequencyCounter/inc" -I"C:/Users/vectaa/Desktop/FrequencyCounter/Utilities/STM32F3xx-Nucleo" -I"C:/Users/vectaa/Desktop/FrequencyCounter/CMSIS/device" -I"C:/Users/vectaa/Desktop/FrequencyCounter/CMSIS/core" -I"C:/Users/vectaa/Desktop/FrequencyCounter/HAL_Driver/Inc" -g -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


