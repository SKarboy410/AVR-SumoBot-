# ==============================
# Project settings
# ==============================

PROGRAM_NAME = main
BUILD_DIR    = build
SRC_DIR      = src

PORT         = /dev/ttyUSB0
SIZE         = avr-size

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

# All .c files in src directory
SRCS := $(wildcard $(SRC_DIR)/*.c)

# Convert to build/*.o (flattened)
OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

# Dependency files
DEPS := $(OBJS:.o=.d)

# ==============================
# Default target
# ==============================

all: $(BUILD_DIR)/$(PROGRAM_NAME).elf $(BUILD_DIR)/$(PROGRAM_NAME).hex

# Create build folder
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Compile src/*.c → build/*.o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
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

size: $(BUILD_DIR)/$(PROGRAM_NAME).elf
	$(SIZE) --format=avr --mcu=$(MCU) $<

.PHONY: all upload clean

# Include dependencies
-include $(DEPS)