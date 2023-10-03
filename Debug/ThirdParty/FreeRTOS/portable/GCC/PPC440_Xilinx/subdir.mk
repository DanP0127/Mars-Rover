################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ThirdParty/FreeRTOS/portable/GCC/PPC440_Xilinx/port.c 

S_UPPER_SRCS += \
../ThirdParty/FreeRTOS/portable/GCC/PPC440_Xilinx/portasm.S 

OBJS += \
./ThirdParty/FreeRTOS/portable/GCC/PPC440_Xilinx/port.o \
./ThirdParty/FreeRTOS/portable/GCC/PPC440_Xilinx/portasm.o 

S_UPPER_DEPS += \
./ThirdParty/FreeRTOS/portable/GCC/PPC440_Xilinx/portasm.d 

C_DEPS += \
./ThirdParty/FreeRTOS/portable/GCC/PPC440_Xilinx/port.d 


# Each subdirectory must supply rules for building sources it contributes
ThirdParty/FreeRTOS/portable/GCC/PPC440_Xilinx/%.o ThirdParty/FreeRTOS/portable/GCC/PPC440_Xilinx/%.su ThirdParty/FreeRTOS/portable/GCC/PPC440_Xilinx/%.cyclo: ../ThirdParty/FreeRTOS/portable/GCC/PPC440_Xilinx/%.c ThirdParty/FreeRTOS/portable/GCC/PPC440_Xilinx/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I"C:/Users/Portillo/OneDrive/Desktop/Work/Mars Rover/RTOS_Workspace/CleanStart/ThirdParty/FreeRTOS" -I"C:/Users/Portillo/OneDrive/Desktop/Work/Mars Rover/RTOS_Workspace/CleanStart/ThirdParty/FreeRTOS/include" -I"C:/Users/Portillo/OneDrive/Desktop/Work/Mars Rover/RTOS_Workspace/CleanStart/ThirdParty/FreeRTOS/portable/GCC/ARM_CM4F" -IC:/Users/Portillo/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Drivers/STM32F4xx_HAL_Driver/Inc -IC:/Users/Portillo/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -IC:/Users/Portillo/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Drivers/CMSIS/Device/ST/STM32F4xx/Include -IC:/Users/Portillo/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThirdParty/FreeRTOS/portable/GCC/PPC440_Xilinx/%.o: ../ThirdParty/FreeRTOS/portable/GCC/PPC440_Xilinx/%.S ThirdParty/FreeRTOS/portable/GCC/PPC440_Xilinx/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-ThirdParty-2f-FreeRTOS-2f-portable-2f-GCC-2f-PPC440_Xilinx

clean-ThirdParty-2f-FreeRTOS-2f-portable-2f-GCC-2f-PPC440_Xilinx:
	-$(RM) ./ThirdParty/FreeRTOS/portable/GCC/PPC440_Xilinx/port.cyclo ./ThirdParty/FreeRTOS/portable/GCC/PPC440_Xilinx/port.d ./ThirdParty/FreeRTOS/portable/GCC/PPC440_Xilinx/port.o ./ThirdParty/FreeRTOS/portable/GCC/PPC440_Xilinx/port.su ./ThirdParty/FreeRTOS/portable/GCC/PPC440_Xilinx/portasm.d ./ThirdParty/FreeRTOS/portable/GCC/PPC440_Xilinx/portasm.o

.PHONY: clean-ThirdParty-2f-FreeRTOS-2f-portable-2f-GCC-2f-PPC440_Xilinx

