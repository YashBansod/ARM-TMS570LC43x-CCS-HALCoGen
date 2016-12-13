################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccsv6/tools/compiler/ti-cgt-arm_15.12.1.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./source/HL_epc.obj" \
"./source/HL_errata.obj" \
"./source/HL_esm.obj" \
"./source/HL_nmpu.obj" \
"./source/HL_notification.obj" \
"./source/HL_pinmux.obj" \
"./source/HL_sci.obj" \
"./source/HL_sys_core.obj" \
"./source/HL_sys_dma.obj" \
"./source/HL_sys_intvecs.obj" \
"./source/HL_sys_main.obj" \
"./source/HL_sys_mpu.obj" \
"./source/HL_sys_pcr.obj" \
"./source/HL_sys_phantom.obj" \
"./source/HL_sys_pmm.obj" \
"./source/HL_sys_pmu.obj" \
"./source/HL_sys_startup.obj" \
"./source/HL_sys_vim.obj" \
"./source/HL_system.obj" \
"../source/HL_sys_link.cmd" \
$(GEN_CMDS__FLAG) \
-llibc.a \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include source/subdir_vars.mk
-include source/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
SCI_UART_RX.out \

EXE_OUTPUTS__QUOTED += \
"SCI_UART_RX.out" \

BIN_OUTPUTS += \
SCI_UART_RX.hex \

BIN_OUTPUTS__QUOTED += \
"SCI_UART_RX.hex" \


# All Target
all: SCI_UART_RX.out

# Tool invocations
SCI_UART_RX.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM Linker'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_15.12.1.LTS/bin/armcl" -mv7R5 --code_state=32 --float_support=VFPv3D16 -g --diag_wrap=off --diag_warning=225 --display_error_number --enum_type=packed --abi=eabi -z -m"SCI_UART_RX.map" --stack_size=0x800 --heap_size=0x800 -i"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_15.12.1.LTS/lib" -i"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_15.12.1.LTS/include" --reread_libs --display_error_number --warn_sections --diag_wrap=off --xml_link_info="SCI_UART_RX_linkInfo.xml" --rom_model --be32 -o "SCI_UART_RX.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

SCI_UART_RX.hex: $(EXE_OUTPUTS)
	@echo 'Invoking: ARM Hex Utility'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_15.12.1.LTS/bin/armhex"  -o "SCI_UART_RX.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)$(BIN_OUTPUTS__QUOTED)
	-$(RM) "source\HL_epc.d" "source\HL_errata.d" "source\HL_esm.d" "source\HL_nmpu.d" "source\HL_notification.d" "source\HL_pinmux.d" "source\HL_sci.d" "source\HL_sys_dma.d" "source\HL_sys_main.d" "source\HL_sys_pcr.d" "source\HL_sys_phantom.d" "source\HL_sys_pmm.d" "source\HL_sys_startup.d" "source\HL_sys_vim.d" "source\HL_system.d" 
	-$(RM) "source\HL_epc.obj" "source\HL_errata.obj" "source\HL_esm.obj" "source\HL_nmpu.obj" "source\HL_notification.obj" "source\HL_pinmux.obj" "source\HL_sci.obj" "source\HL_sys_core.obj" "source\HL_sys_dma.obj" "source\HL_sys_intvecs.obj" "source\HL_sys_main.obj" "source\HL_sys_mpu.obj" "source\HL_sys_pcr.obj" "source\HL_sys_phantom.obj" "source\HL_sys_pmm.obj" "source\HL_sys_pmu.obj" "source\HL_sys_startup.obj" "source\HL_sys_vim.obj" "source\HL_system.obj" 
	-$(RM) "source\HL_sys_core.d" "source\HL_sys_intvecs.d" "source\HL_sys_mpu.d" "source\HL_sys_pmu.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

