################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/button.c \
../Core/Src/demo.c \
../Core/Src/display.c \
../Core/Src/encoder.c \
../Core/Src/gfx.c \
../Core/Src/img.c \
../Core/Src/init.c \
../Core/Src/led.c \
../Core/Src/main.c \
../Core/Src/pot.c \
../Core/Src/stm32f4xx_hal_msp.c \
../Core/Src/stm32f4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f4xx.c \
../Core/Src/timer.c \
../Core/Src/ui.c 

OBJS += \
./Core/Src/button.o \
./Core/Src/demo.o \
./Core/Src/display.o \
./Core/Src/encoder.o \
./Core/Src/gfx.o \
./Core/Src/img.o \
./Core/Src/init.o \
./Core/Src/led.o \
./Core/Src/main.o \
./Core/Src/pot.o \
./Core/Src/stm32f4xx_hal_msp.o \
./Core/Src/stm32f4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f4xx.o \
./Core/Src/timer.o \
./Core/Src/ui.o 

C_DEPS += \
./Core/Src/button.d \
./Core/Src/demo.d \
./Core/Src/display.d \
./Core/Src/encoder.d \
./Core/Src/gfx.d \
./Core/Src/img.d \
./Core/Src/init.d \
./Core/Src/led.d \
./Core/Src/main.d \
./Core/Src/pot.d \
./Core/Src/stm32f4xx_hal_msp.d \
./Core/Src/stm32f4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f4xx.d \
./Core/Src/timer.d \
./Core/Src/ui.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/button.d ./Core/Src/button.o ./Core/Src/button.su ./Core/Src/demo.d ./Core/Src/demo.o ./Core/Src/demo.su ./Core/Src/display.d ./Core/Src/display.o ./Core/Src/display.su ./Core/Src/encoder.d ./Core/Src/encoder.o ./Core/Src/encoder.su ./Core/Src/gfx.d ./Core/Src/gfx.o ./Core/Src/gfx.su ./Core/Src/img.d ./Core/Src/img.o ./Core/Src/img.su ./Core/Src/init.d ./Core/Src/init.o ./Core/Src/init.su ./Core/Src/led.d ./Core/Src/led.o ./Core/Src/led.su ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/pot.d ./Core/Src/pot.o ./Core/Src/pot.su ./Core/Src/stm32f4xx_hal_msp.d ./Core/Src/stm32f4xx_hal_msp.o ./Core/Src/stm32f4xx_hal_msp.su ./Core/Src/stm32f4xx_it.d ./Core/Src/stm32f4xx_it.o ./Core/Src/stm32f4xx_it.su ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f4xx.d ./Core/Src/system_stm32f4xx.o ./Core/Src/system_stm32f4xx.su ./Core/Src/timer.d ./Core/Src/timer.o ./Core/Src/timer.su ./Core/Src/ui.d ./Core/Src/ui.o ./Core/Src/ui.su

.PHONY: clean-Core-2f-Src

