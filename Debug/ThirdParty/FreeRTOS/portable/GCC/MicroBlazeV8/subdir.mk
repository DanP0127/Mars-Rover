################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ThirdParty/FreeRTOS/portable/GCC/MicroBlazeV8/port.c \
../ThirdParty/FreeRTOS/portable/GCC/MicroBlazeV8/port_exceptions.c 

S_UPPER_SRCS += \
../ThirdParty/FreeRTOS/portable/GCC/MicroBlazeV8/portasm.S 

OBJS += \
./ThirdParty/FreeRTOS/portable/GCC/MicroBlazeV8/port.o \
./ThirdParty/FreeRTOS/portable/GCC/MicroBlazeV8/port_exceptions.o \
./ThirdParty/FreeRTOS/portable/GCC/MicroBlazeV8/portasm.o 

S_UPPER_DEPS += \
./ThirdParty/FreeRTOS/portable/GCC/MicroBlazeV8/portasm.d 

C_DEPS += \
./ThirdParty/FreeRTOS/portable/GCC/MicroBlazeV8/port.d \
./ThirdParty/FreeRTOS/portable/GCC/MicroBlazeV8/port_exceptions.d 


# Each subdirectory must supply rules for building sources it contributes
ThirdParty/FreeRTOS/portable/GCC/MicroBlazeV8/%.o ThirdParty/FreeRTOS/portable/GCC/MicroBlazeV8/%.su ThirdParty/FreeRTOS/portable/GCC/MicroBlazeV8/%.cyclo: ../ThirdParty/FreeRTOS/portable/GCC/MicroBlazeV8/%.c ThirdParty/FreeRTOS/portable/GCC/MicroBlazeV8/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I"C:/Users/Portillo/OneDrive/Desktop/Work/Mars Rover/RTOS_Workspace/CleanStart/ThirdParty/FreeRTOS" -I"C:/Users/Portillo/OneDrive/Desktop/Work/Mars Rover/RTOS_Workspace/CleanStart/ThirdParty/FreeRTOS/include" -I"C:/Users/Portillo/OneDrive/Desktop/Work/Mars Rover/RTOS_Workspace/CleanStart/ThirdParty/FreeRTOS/portable/GCC/ARM_CM4F" -IC:/Users/Portillo/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Drivers/STM32F4xx_HAL_Driver/Inc -IC:/Users/Portillo/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -IC:/Users/Portillo/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Drivers/CMSIS/Device/ST/STM32F4xx/Include -IC:/Users/Portillo/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThirdParty/FreeRTOS/portable/GCC/MicroBlazeV8/%.o: ../ThirdParty/FreeRTOS/portable/GCC/MicroBlazeV8/%.S ThirdParty/FreeRTOS/portable/GCC/MicroBlazeV8/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-ThirdParty-2f-FreeRTOS-2f-portable-2f-GCC-2f-MicroBlazeV8

clean-ThirdParty-2f-FreeRTOS-2f-portable-2f-GCC-2f-MicroBlazeV8:
	-$(RM) ./ThirdParty/FreeRTOS/portable/GCC/MicroBlazeV8/port.cyclo ./ThirdParty/FreeRTOS/portable/GCC/MicroBlazeV8/port.d ./ThirdParty/FreeRTOS/portable/GCC/MicroBlazeV8/port.o ./ThirdParty/FreeRTOS/portable/GCC/MicroBlazeV8/port.su ./ThirdParty/FreeRTOS/portable/GCC/MicroBlazeV8/port_exceptions.cyclo ./ThirdParty/FreeRTOS/portable/GCC/MicroBlazeV8/port_exceptions.d ./ThirdParty/FreeRTOS/portable/GCC/MicroBlazeV8/port_exceptions.o ./ThirdParty/FreeRTOS/portable/GCC/MicroBlazeV8/port_exceptions.su ./ThirdParty/FreeRTOS/portable/GCC/MicroBlazeV8/portasm.d ./ThirdParty/FreeRTOS/portable/GCC/MicroBlazeV8/portasm.o

.PHONY: clean-ThirdParty-2f-FreeRTOS-2f-portable-2f-GCC-2f-MicroBlazeV8

