SIMPLELINK_MSP432E4_SDK_INSTALL_DIR ?= $(abspath ../../../../../..)

include $(SIMPLELINK_MSP432E4_SDK_INSTALL_DIR)/imports.mak

ASM = "$(IAR_ARMCOMPILER)/bin/iasmarm"
CC = "$(IAR_ARMCOMPILER)/bin/iccarm"
LNK = "$(IAR_ARMCOMPILER)/bin/ilinkarm"

OBJECTS = system_msp432e401y.obj startup_msp432e401y_ewarm.obj main.obj

NAME = empty

AFLAGS = -I.. "-I$(SIMPLELINK_MSP432E4_SDK_INSTALL_DIR)/source" "-I$(SIMPLELINK_MSP432E4_SDK_INSTALL_DIR)/source/third_party/CMSIS/Include" -DDeviceFamily_MSP432E4 -D__MSP432E401Y__ -S --cpu Cortex-M4F --endian little --thumb "-I$(IAR_ARMCOMPILER)/inc/c"

CFLAGS = -I.. "-I$(SIMPLELINK_MSP432E4_SDK_INSTALL_DIR)/source" "-I$(SIMPLELINK_MSP432E4_SDK_INSTALL_DIR)/source/third_party/CMSIS/Include" -DDeviceFamily_MSP432E4 -D__MSP432E401Y__ --cpu=Cortex-M4F --debug --silent -e --aeabi --thumb --diag_suppress=Pa050 "-I$(IAR_ARMCOMPILER)/inc/c"

LFLAGS = "$(SIMPLELINK_MSP432E4_SDK_INSTALL_DIR)/source/ti/display/lib/display.arm4f" "$(SIMPLELINK_MSP432E4_SDK_INSTALL_DIR)/source/ti/grlib/lib/iar/m4f/grlib.a" "$(SIMPLELINK_MSP432E4_SDK_INSTALL_DIR)/source/third_party/spiffs/lib/iar/m4f/spiffs.a" "$(SIMPLELINK_MSP432E4_SDK_INSTALL_DIR)/source/ti/drivers/lib/drivers_msp432e4.arm4f" "$(SIMPLELINK_MSP432E4_SDK_INSTALL_DIR)/source/third_party/fatfs/lib/iar/m4f/fatfs.a" "$(SIMPLELINK_MSP432E4_SDK_INSTALL_DIR)/source/ti/devices/msp432e4/driverlib/lib/iar/m4f/msp432e4_driverlib.a" --config ../iar/msp432e401y.icf --map "$(NAME).map" --silent --cpu=Cortex-M4F --redirect _Printf=_PrintfSmall --redirect _Scanf=_ScanfSmall --semihosting=iar_breakpoint

all: $(NAME).out

system_msp432e401y.obj: ../system_msp432e401y.c
	@ echo Building $@
	@ $(CC) $(CFLAGS) $< -o $@

startup_msp432e401y_ewarm.obj: ../iar/startup_msp432e401y_ewarm.c
	@ echo Building $@
	@ $(CC) $(CFLAGS) $< -o $@

main.obj: ../main.c
	@ echo Building $@
	@ $(CC) $(CFLAGS) $< -o $@

$(NAME).out: $(OBJECTS)
	@ echo linking...
	@ $(LNK)  $(OBJECTS) $(LFLAGS) -o $(NAME).out

clean:
	@ echo Cleaning...
	@ $(RM) $(OBJECTS) > $(DEVNULL) 2>&1
	@ $(RM) $(NAME).out > $(DEVNULL) 2>&1
	@ $(RM) $(NAME).map > $(DEVNULL) 2>&1
