# ==============================
# Project settings
# ==============================

PROGRAM_NAME = main
BUILD_DIR    = build
PORT         = /dev/ttyUSB0

MCU   = atmega328p
F_CPU = 16000000UL

CC      = avr-gcc
OBJCOPY = avr-objcopy
AVRDUDE = avrdude

CFLAGS  = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Wall -Os -MMD -MP
LDFLAGS = -mmcu=$(MCU)

# ==============================
# Automatically detect files
# ==============================

# All .c files in current directory
SRCS := $(wildcard *.c)

# Convert to build/*.o
OBJS := $(SRCS:%.c=$(BUILD_DIR)/%.o)

# Dependency files generated automatically
DEPS := $(OBJS:.o=.d)

# ==============================
# Default target
# ==============================

all: $(BUILD_DIR)/$(PROGRAM_NAME).elf $(BUILD_DIR)/$(PROGRAM_NAME).hex

# Create build folder if missing
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Compile .c → build/.o
$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Link
$(BUILD_DIR)/$(PROGRAM_NAME).elf: $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

# Create HEX
$(BUILD_DIR)/$(PROGRAM_NAME).hex: $(BUILD_DIR)/$(PROGRAM_NAME).elf
	$(OBJCOPY) -j .text -j .data -O ihex $< $@

# Upload
upload: $(BUILD_DIR)/$(PROGRAM_NAME).hex
	$(AVRDUDE) -c arduino -p m328p -P $(PORT) -b 115200 -U flash:w:$<

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all upload clean

# Include auto-generated dependency files
-include $(DEPS)										