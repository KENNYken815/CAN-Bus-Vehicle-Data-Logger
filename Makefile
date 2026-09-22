CC ?= gcc
CFLAGS ?= -std=c11 -Wall -Wextra -Wpedantic -O2 -Ifirmware/inc
TARGET=build/can_logger
SRC=firmware/src/main.c firmware/src/can_logger.c firmware/src/signal_decoder.c
OBJ=$(SRC:firmware/src/%.c=build/%.o)
all: $(TARGET)
$(TARGET): $(OBJ)
	mkdir -p build
	$(CC) $(OBJ) -o $@
build/%.o: firmware/src/%.c
	mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -rf build
.PHONY: all clean