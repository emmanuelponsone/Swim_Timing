################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/cdcuser.c \
../src/cr_startup_lpc13.c \
../src/cronos_master.c \
../src/funciones.c \
../src/serial.c \
../src/uart.c \
../src/usbcore.c \
../src/usbdesc.c \
../src/usbhw.c \
../src/usbuser.c 

OBJS += \
./src/cdcuser.o \
./src/cr_startup_lpc13.o \
./src/cronos_master.o \
./src/funciones.o \
./src/serial.o \
./src/uart.o \
./src/usbcore.o \
./src/usbdesc.o \
./src/usbhw.o \
./src/usbuser.o 

C_DEPS += \
./src/cdcuser.d \
./src/cr_startup_lpc13.d \
./src/cronos_master.d \
./src/funciones.d \
./src/serial.d \
./src/uart.d \
./src/usbcore.d \
./src/usbdesc.d \
./src/usbhw.d \
./src/usbuser.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_CMSIS=CMSISv1p30_LPC13xx -I"/home/emmanuel/lpcxpresso4/workspace/CMSISv1p30_LPC13xx/inc" -I"/home/emmanuel/lpcxpresso4/workspace/cronos_master/headers" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


