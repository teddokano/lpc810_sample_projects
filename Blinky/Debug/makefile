################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := Blinky
BUILD_ARTIFACT_EXTENSION := axf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all:
	+@$(MAKE) --no-print-directory main-build && $(MAKE) --no-print-directory post-build

# Main-build Target
main-build: Blinky.axf

dependents:
	-cd /Users/tedd/dev/mcuxpresso/__lpc810/CMSIS_CORE_LPC8xx/Debug && $(MAKE) all
	-cd /Users/tedd/dev/mcuxpresso/__lpc810/lpc800_driver_lib/Debug && $(MAKE) all

# Tool invocations
Blinky.axf: $(OBJS) $(USER_OBJS) /Users/tedd/dev/mcuxpresso/__lpc810/CMSIS_CORE_LPC8xx/Debug/libCMSIS_CORE_LPC8xx.a /Users/tedd/dev/mcuxpresso/__lpc810/lpc800_driver_lib/Debug/liblpc800_driver_lib.a makefile $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"/Users/tedd/dev/mcuxpresso/__lpc810/CMSIS_CORE_LPC8xx/Debug" -L"/Users/tedd/dev/mcuxpresso/__lpc810/lpc800_driver_lib/Debug" -Xlinker -Map="Blinky.map" -Xlinker --gc-sections -mcpu=cortex-m0 -mthumb -T Blinky_Debug.ld -o "Blinky.axf" $(OBJS) $(USER_OBJS) $(LIBS) -llpc800_driver_lib -lCMSIS_CORE_LPC8xx
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) Blinky.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "Blinky.axf"; # arm-none-eabi-objcopy -O binary "Blinky.axf" "Blinky.bin" ; checksum -p LPC810 -d "Blinky.bin";
	-@echo ' '

.PHONY: all clean dependents main-build post-build
/Users/tedd/dev/mcuxpresso/__lpc810/CMSIS_CORE_LPC8xx/Debug/libCMSIS_CORE_LPC8xx.a:
/Users/tedd/dev/mcuxpresso/__lpc810/lpc800_driver_lib/Debug/liblpc800_driver_lib.a:

-include ../makefile.targets
