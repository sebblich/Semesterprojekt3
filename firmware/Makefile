# Compiler and AVR utility tools
CC = avr-gcc
OBJCOPY = avr-objcopy
SIZE = avr-size

# Target microcontroller and clock frequency
MCU = atmega328pb
F_CPU = 8000000UL

# Compiler flags
CFLAGS = -mmcu=$(MCU)
CFLAGS += -DF_CPU=$(F_CPU)
CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -Os
CFLAGS += -std=c11
CFLAGS += -Iinclude

# Output filename
TARGET = firmware

# Automatically find all .c files in src/
SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c,build/%.o,$(SRC))

.PHONY: all clean

all: build/$(TARGET).hex

# Create build/ if it does not exist
build:
	mkdir -p build

# Convert ELF file to Intel HEX format
build/$(TARGET).hex: build/$(TARGET).elf
	$(OBJCOPY) -O ihex $< $@

# Link object files and display memory usage
build/$(TARGET).elf: $(OBJ) | build
	$(CC) $(CFLAGS) $^ -o $@
	$(SIZE) $@

# Compile each .c file into an object file
build/%.o: src/%.c | build
	$(CC) $(CFLAGS) -c $< -o $@

# Remove generated build artifacts
clean:
	rm -f build/*
