################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/stm32f3xx_it.c \
../src/syscalls.c \
../src/system_stm32f3xx.c 

CPP_SRCS += \
../src/FrequencyCounter.cpp \
../src/GPIO.cpp \
../src/main.cpp 

OBJS += \
./src/FrequencyCounter.o \
./src/GPIO.o \
./src/main.o \
./src/stm32f3xx_it.o \
./src/syscalls.o \
./src/system_stm32f3xx.o 

C_DEPS += \
./src/stm32f3xx_it.d \
./src/syscalls.d \
./src/system_stm32f3xx.d 

CPP_DEPS += \
./src/FrequencyCounter.d \
./src/GPIO.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU G++ Compiler'
	@echo $(PWD)
	arm-none-eabi-g++ -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DSTM32F3 -DSTM32F30 -DSTM32F303RETx -DNUCLEO_F303RE -DDEBUG -DSTM32F303xE -DUSE_HAL_DRIVER -I"C:/Users/vectaa/Desktop/FrequencyCounter/HAL_Driver/Inc/Legacy" -I"C:/Users/vectaa/Desktop/FrequencyCounter/inc" -I"C:/Users/vectaa/Desktop/FrequencyCounter/Utilities/STM32F3xx-Nucleo" -I"C:/Users/vectaa/Desktop/FrequencyCounter/CMSIS/device" -I"C:/Users/vectaa/Desktop/FrequencyCounter/CMSIS/core" -I"C:/Users/vectaa/Desktop/FrequencyCounter/HAL_Driver/Inc" -I"C:/Users/vectaa/Desktop/FrequencyCounter/HAL_Driver/Inc" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fno-exceptions -fno-rtti -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DSTM32F3 -DSTM32F30 -DSTM32F303RETx -DNUCLEO_F303RE -DDEBUG -DSTM32F303xE -DUSE_HAL_DRIVER -I"C:/Users/vectaa/Desktop/FrequencyCounter/HAL_Driver/Inc/Legacy" -I"C:/Users/vectaa/Desktop/FrequencyCounter/inc" -I"C:/Users/vectaa/Desktop/FrequencyCounter/HAL_Driver/Inc" -I"C:/Users/vectaa/Desktop/FrequencyCounter/Utilities/STM32F3xx-Nucleo" -I"C:/Users/vectaa/Desktop/FrequencyCounter/CMSIS/device" -I"C:/Users/vectaa/Desktop/FrequencyCounter/CMSIS/core" -I"C:/Users/vectaa/Desktop/FrequencyCounter/HAL_Driver/Inc" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


