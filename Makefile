#Project name
PROJECT = final

# Directories
SRC_DIR = src
BUILD_DIR = build
LD_DIR = linker

#Config files for OpenOCD
OPENOCD_INTERFACE = openocd_cfg/picoprobe.cfg
OPENOCD_TARGET = openocd_cfg/stm32g0x.cfg

# Source files and object files
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

OUTPUT = $(BUILD_DIR)/$(PROJECT)

LINKER_SCRIPT = $(LD_DIR)/stm32g0_linker.ld
PREFIX = arm-none-eabi-

CFLAGS = -mcpu=cortex-m0plus -mthumb -O0 -Wall -std=gnu11 \
		 -Wconversion -I.-Wshadow -Werror -g
LDFLAGS = -nostdlib -Wall -g -Wl,-Map,$(OUTPUT).map,--print-memory-usage,--gc-sections,-g

all : $(OUTPUT).bin	

$(OUTPUT).bin : $(OUTPUT).elf 
	@$(PREFIX)objcopy -O binary $^ $@
	@echo Binary file created - $(PROJECT).bin


$(OUTPUT).elf : $(OBJ)
	$(PREFIX)gcc $(LDFLAGS) -T $(LINKER_SCRIPT)  $^ -o $@


$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(PREFIX)gcc $(CFLAGS) -c $^ -o $@


#Flash via OpenOCD
flash : all
	openocd -f $(OPENOCD_INTERFACE) -f $(OPENOCD_TARGET) -c  " program $(OUTPUT).elf verify reset exit"

#Start gdb server for debugging
gdbserver : 
	openocd -f $(OPENOCD_INTERFACE) -f $(OPENOCD_TARGET)

# Ensure the build directory exists
$(BUILD_DIR):
	mkdir $(BUILD_DIR)

# Remove build directory	
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
