# Compiler and AVR utility tools
CC = avr-gcc
OBJCOPY = avr-objcopy
SIZE = avr-size

# Target microcontroller and clock frequency
MCU = atmega328pb
F_CPU = 8000000UL

# Compiler flags
# -mmcu      : Generate code for the selected MCU
# -DF_CPU    : Make F_CPU available as a preprocessor macro
# -Wall      : Enable common warnings
# -Wextra    : Enable additional warnings
# -Os        : Optimize for code size
# -std=c17   : Use the C17 standard
# -Iinclude  : Search for header files in the include directory
CFLAGS = -mmcu=$(MCU)
CFLAGS += -DF_CPU=$(F_CPU)
CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -Os
CFLAGS += -std=c11
CFLAGS += -Iinclude

# Output filename (firmware.elf and firmware.hex)
TARGET = firmware

# Automatically find all .c files in src/
SRC = $(wildcard src/*.c)

# Convert:
# src/main.c      -> build/main.o
# src/twi.c       -> build/twi.o
# src/sensor.c    -> build/sensor.o
OBJ = $(patsubst src/%.c,build/%.o,$(SRC))

# Default target executed when running 'make'
all: build/$(TARGET).hex

# Convert ELF file to Intel HEX format for flashing
build/$(TARGET).hex: build/$(TARGET).elf
	$(OBJCOPY) -O ihex $< $@

# Link all object files into the final ELF executable
# Then display memory usage statistics
build/$(TARGET).elf: $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@
	$(SIZE) $@

# Compile each .c file into a corresponding .o file in build/
#
# Example:
#   src/main.c -> build/main.o
#   src/twi.c  -> build/twi.o
#
# Automatic variables:
#   $< = source file
#   $@ = output file
build/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Remove all generated build artifacts
clean:
	rm -f build/*