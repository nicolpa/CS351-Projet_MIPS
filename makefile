CC = gcc
CFLAGS = -Wall -pedantic -ansi --std=c11
BIN = bin
SRC = src
INCLUDE = include
LIB = lib
LIBRARIES = 
EXECUTABLE = emu-mips

all: $(BIN)/$(EXECUTABLE)

run: clean all
	clear
	./$(BIN)/$(EXECUTABLE)
	
$(BIN)/$(EXECUTABLE): $(SRC)/*.c
	$(CC) $(CFLAGS) -I$(INCLUDE) -L$(LIB) $^ -o $@ $(LIBRARIES) -g
	
clean:
	-rm $(BIN)/*
