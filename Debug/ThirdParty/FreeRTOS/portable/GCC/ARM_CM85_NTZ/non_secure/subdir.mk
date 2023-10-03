################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ThirdParty/FreeRTOS/portable/GCC/ARM_CM85_NTZ/non_secure/port.c \
../ThirdParty/FreeRTOS/portable/GCC/ARM_CM85_NTZ/non_secure/portasm.c 

OBJS += \
./ThirdParty/FreeRTOS/portable/GCC/ARM_CM85_NTZ/non_secure/port.o \
./ThirdParty/FreeRTOS/portable/GCC/ARM_CM85_NTZ/non_secure/portasm.o 

C_DEPS += \
./ThirdParty/FreeRTOS/portable/GCC/ARM_CM85_NTZ/non_secure/port.d \
./ThirdParty/FreeRTOS/portable/GCC/ARM_CM85_NTZ/non_secure/portasm.d 


# Each subdirectory must supply rules for building sources it contributes
ThirdParty/FreeRTOS/portable/GCC/ARM_CM85_NTZ/non_secure/%.o ThirdParty/FreeRTOS/portable/GCC/ARM_CM85_NTZ/non_secure/%.su ThirdParty/FreeRTOS/portable/GCC/ARM_CM85_NTZ/non_secure/%.cyclo: ../ThirdParty/FreeRTOS/portable/GCC/ARM_CM85_NTZ/non_secure/%.c ThirdParty/FreeRTOS/portable/GCC/ARM_CM85_NTZ/non_secure/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I"C:/Users/Portillo/OneDrive/Desktop/Work/Mars Rover/RTOS_Workspace/CleanStart/ThirdParty/FreeRTOS" -I"C:/Users/Portillo/OneDrive/Desktop/Work/Mars Rover/RTOS_Workspace/CleanStart/ThirdParty/FreeRTOS/include" -I"C:/Users/Portillo/OneDrive/Desktop/Work/Mars Rover/RTOS_Workspace/CleanStart/ThirdParty/FreeRTOS/portable/GCC/ARM_CM4F" -IC:/Users/Portillo/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Drivers/STM32F4xx_HAL_Driver/Inc -IC:/Users/Portillo/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -IC:/Users/Portillo/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Drivers/CMSIS/Device/ST/STM32F4xx/Include -IC:/Users/Portillo/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-ThirdParty-2f-FreeRTOS-2f-portable-2f-GCC-2f-ARM_CM85_NTZ-2f-non_secure

clean-ThirdParty-2f-FreeRTOS-2f-portable-2f-GCC-2f-ARM_CM85_NTZ-2f-non_secure:
	-$(RM) ./ThirdParty/FreeRTOS/portable/GCC/ARM_CM85_NTZ/non_secure/port.cyclo ./ThirdParty/FreeRTOS/portable/GCC/ARM_CM85_NTZ/non_secure/port.d ./ThirdParty/FreeRTOS/portable/GCC/ARM_CM85_NTZ/non_secure/port.o ./ThirdParty/FreeRTOS/portable/GCC/ARM_CM85_NTZ/non_secure/port.su ./ThirdParty/FreeRTOS/portable/GCC/ARM_CM85_NTZ/non_secure/portasm.cyclo ./ThirdParty/FreeRTOS/portable/GCC/ARM_CM85_NTZ/non_secure/portasm.d ./ThirdParty/FreeRTOS/portable/GCC/ARM_CM85_NTZ/non_secure/portasm.o ./ThirdParty/FreeRTOS/portable/GCC/ARM_CM85_NTZ/non_secure/portasm.su

.PHONY: clean-ThirdParty-2f-FreeRTOS-2f-portable-2f-GCC-2f-ARM_CM85_NTZ-2f-non_secure

