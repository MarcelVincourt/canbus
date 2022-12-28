
#all: compile upload

#compile:
#	avr-gcc -Os -DF_CPU=16000000L -o main main.c -mmcu=atmega328p
#	avr-objcopy -R .eeprom -O ihex main main.hex
#	avr-size main
#	rm main



#clean:
#	rm main.hex


.PHONY: ${BIN} clean upload hex


CC=avr-gcc
CFLAGS = -std=c99 -Wall -Wextra -Wno-array-bounds -Os -DF_CPU=16000000L -mmcu=atmega328p 

SRC=src
OBJ_DIR=obj
BIN_DIR=bin
SRCS=$(wildcard $(SRC)/*.c) main.c\

C_PATHS=$(dir $(SRCS))
C_FILES:=$(notdir $(SRCS))
OBJS=$(addprefix $(OBJ_DIR)/, $(C_FILES:.c=.o))

$(shell mkdir $(OBJ_DIR)>/dev/null 2>&1)
$(shell mkdir $(BIN_DIR)>/dev/null 2>&1)


BIN=$(BIN_DIR)/main

vpath %.c $(C_PATHS)

all: $(BIN) hex upload

upload:
	avrdude -F -c arduino -p m328p -P COM4 -U flash:w:$(BIN_DIR)/main.hex

hex:
	@echo hex
	avr-objcopy -R .eeprom -O ihex $(BIN_DIR)/main $(BIN_DIR)/main.hex
	avr-size $(BIN_DIR)/main.elf

$(BIN): $(OBJS)
	@echo bin
	$(CC) $(CFLAGS) $(OBJS) -o $@
	$(CC) $(CFLAGS) $(OBJS) -o $(BIN_DIR)/main.elf
	
$(OBJ_DIR)/%.o: %.c
	echo objdir
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm $(OBJ_DIR)/*.o $(BIN_DIR)/* 