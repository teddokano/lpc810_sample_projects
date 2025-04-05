################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/cr_startup_lpc8xx.c \
../src/crp.c \
../src/i2ctest.c 

C_DEPS += \
./src/cr_startup_lpc8xx.d \
./src/crp.d \
./src/i2ctest.d 

OBJS += \
./src/cr_startup_lpc8xx.o \
./src/crp.o \
./src/i2ctest.o 


# Each subdirectory must supply rules for building sources it contributes
src/cr_startup_lpc8xx.o: ../src/cr_startup_lpc8xx.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_CMSIS=CMSIS_CORE_LPC8xx -D__LPC8XX__ -I"/Users/tedd/dev/mcuxpresso/__lpc810/lpc800_driver_lib" -I"/Users/tedd/dev/mcuxpresso/__lpc810/CMSIS_CORE_LPC8xx" -I"/Users/tedd/dev/mcuxpresso/__lpc810/CMSIS_CORE_LPC8xx/inc" -I"/Users/tedd/dev/mcuxpresso/__lpc810/lpc800_driver_lib/inc" -Os -g3 -gdwarf-4 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0 -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_CMSIS=CMSIS_CORE_LPC8xx -D__LPC8XX__ -I"/Users/tedd/dev/mcuxpresso/__lpc810/lpc800_driver_lib" -I"/Users/tedd/dev/mcuxpresso/__lpc810/CMSIS_CORE_LPC8xx" -I"/Users/tedd/dev/mcuxpresso/__lpc810/CMSIS_CORE_LPC8xx/inc" -I"/Users/tedd/dev/mcuxpresso/__lpc810/lpc800_driver_lib/inc" -Os -g3 -gdwarf-4 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0 -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/cr_startup_lpc8xx.d ./src/cr_startup_lpc8xx.o ./src/crp.d ./src/crp.o ./src/i2ctest.d ./src/i2ctest.o

.PHONY: clean-src

