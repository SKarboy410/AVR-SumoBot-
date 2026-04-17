# ==============================
# Project settings
# ==============================

PROGRAM_NAME = main
BUILD_DIR    = build

SRC_DIR      = src
APP_DIR      = $(SRC_DIR)/app
DRIVERS_DIR  = $(SRC_DIR)/drivers

PORT         = /dev/ttyUSB0
SIZE         = avr-size

MCU   = atmega328p
F_CPU = 16000000UL

CC      = avr-gcc
OBJCOPY = avr-objcopy
AVRDUDE = avrdude

CFLAGS  = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Wall -Os -MMD -MP \
          -I$(APP_DIR) -I$(DRIVERS_DIR)
LDFLAGS = -mmcu=$(MCU)

# ==============================
# Source files
# ==============================

APP_SRCS     := $(wildcard $(APP_DIR)/*.c)
DRIVER_SRCS  := $(wildcard $(DRIVERS_DIR)/*.c)
MAIN_SRC     := $(SRC_DIR)/main.c

SRCS := $(APP_SRCS) $(DRIVER_SRCS) $(MAIN_SRC)

# Object files (preserve structure)
OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

DEPS := $(OBJS:.o=.d)

# ==============================
# Build targets
# ==============================

all: $(BUILD_DIR)/$(PROGRAM_NAME).elf $(BUILD_DIR)/$(PROGRAM_NAME).hex

# Compile (auto-create folders)
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Link
$(BUILD_DIR)/$(PROGRAM_NAME).elf: $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

# HEX
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

# Dependencies
-include $(DEPS)