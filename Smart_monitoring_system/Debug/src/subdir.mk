################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/DigitalIoPin.cpp \
../src/I2C.cpp \
../src/KouluProjekti.cpp \
../src/LiquidCrystal.cpp \
../src/LpcUart.cpp \
../src/ModbusMaster.cpp \
../src/ModbusRegister.cpp \
../src/MotorController.cpp \
../src/PIDcalc.cpp \
../src/SerialPort.cpp \
../src/cr_cpp_config.cpp \
../src/cr_startup_lpc15xx.cpp \
../src/pSensor.cpp 

C_SRCS += \
../src/crp.c \
../src/retarget_itm.c \
../src/sysinit.c 

OBJS += \
./src/DigitalIoPin.o \
./src/I2C.o \
./src/KouluProjekti.o \
./src/LiquidCrystal.o \
./src/LpcUart.o \
./src/ModbusMaster.o \
./src/ModbusRegister.o \
./src/MotorController.o \
./src/PIDcalc.o \
./src/SerialPort.o \
./src/cr_cpp_config.o \
./src/cr_startup_lpc15xx.o \
./src/crp.o \
./src/pSensor.o \
./src/retarget_itm.o \
./src/sysinit.o 

CPP_DEPS += \
./src/DigitalIoPin.d \
./src/I2C.d \
./src/KouluProjekti.d \
./src/LiquidCrystal.d \
./src/LpcUart.d \
./src/ModbusMaster.d \
./src/ModbusRegister.d \
./src/MotorController.d \
./src/PIDcalc.d \
./src/SerialPort.d \
./src/cr_cpp_config.d \
./src/cr_startup_lpc15xx.d \
./src/pSensor.d 

C_DEPS += \
./src/crp.d \
./src/retarget_itm.d \
./src/sysinit.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -DDEBUG -D__CODE_RED -D__NEWLIB__ -DCORE_M3 -D__USE_LPCOPEN -DCPP_USE_HEAP -D__LPC15XX__ -I"C:\Users\pc\Documents\MCUXpressoIDE_10.3.0_2200\workspace\lpc_board_nxp_lpcxpresso_1549\inc" -I"C:\Users\pc\Documents\MCUXpressoIDE_10.3.0_2200\workspace\lpc_chip_15xx\inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fno-rtti -fno-exceptions -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=c11 -DDEBUG -D__CODE_RED -D__NEWLIB__ -DCORE_M3 -D__USE_LPCOPEN -DCPP_USE_HEAP -D__LPC15XX__ -I"C:\Users\pc\Documents\MCUXpressoIDE_10.3.0_2200\workspace\lpc_board_nxp_lpcxpresso_1549\inc" -I"C:\Users\pc\Documents\MCUXpressoIDE_10.3.0_2200\workspace\lpc_chip_15xx\inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


