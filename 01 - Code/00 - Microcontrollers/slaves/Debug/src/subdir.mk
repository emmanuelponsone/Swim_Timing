################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/clkconfig.c \
../src/cr_startup_lpc13.c \
../src/cronos_slave.c \
../src/gpio.c \
../src/lpcxpresso_gpio_int.c \
../src/timer32.c \
../src/uart.c 

OBJS += \
./src/clkconfig.o \
./src/cr_startup_lpc13.o \
./src/cronos_slave.o \
./src/gpio.o \
./src/lpcxpresso_gpio_int.o \
./src/timer32.o \
./src/uart.o 

C_DEPS += \
./src/clkconfig.d \
./src/cr_startup_lpc13.d \
./src/cronos_slave.d \
./src/gpio.d \
./src/lpcxpresso_gpio_int.d \
./src/timer32.d \
./src/uart.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_CMSIS=CMSISv1p30_LPC13xx -I"/home/emmanuel/lpcxpresso4/workspace/CMSISv1p30_LPC13xx/inc" -I"/home/emmanuel/lpcxpresso4/workspace/cronos_slave/headers" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/cr_startup_lpc13.o: ../src/cr_startup_lpc13.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_CMSIS=CMSISv1p30_LPC13xx -I"/home/emmanuel/lpcxpresso4/workspace/CMSISv1p30_LPC13xx/inc" -I"/home/emmanuel/lpcxpresso4/workspace/cronos_slave/headers" -O0 -Os -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"src/cr_startup_lpc13.d" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


