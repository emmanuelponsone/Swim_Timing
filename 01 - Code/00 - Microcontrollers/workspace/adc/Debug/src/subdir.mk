################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/adc.c \
../src/adc_main.c \
../src/cr_startup_lpc13.c 

OBJS += \
./src/adc.o \
./src/adc_main.o \
./src/cr_startup_lpc13.o 

C_DEPS += \
./src/adc.d \
./src/adc_main.d \
./src/cr_startup_lpc13.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__USE_CMSIS=CMSISv1p30_LPC13xx -DCR_INTEGER_PRINTF -DDEBUG -D__CODE_RED -D__REDLIB__ -I"/home/kerlos/Dropbox/proyectofinal/codigo/workspace/CMSISv1p30_LPC13xx/inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


