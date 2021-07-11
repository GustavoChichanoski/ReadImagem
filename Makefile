MKDIR   := md
RMDIR   := rd /S /Q
CC      := gcc

SHELL := /bin/sh	

BIN_DIR := ./bin
OBJ_DIR := ./obj
INC_DIR := ./include
SRC_DIR := ./src

SRCS    := $(wildcard $(SRC_DIR)/*/*.c)
OBJS    := $(patsubst $(OBJ_DIR),$(SRC_DIR),$(SRCS))
EXE     := $(BIN)/main.exe
CFLAGS  := -I$(INCLUDE) -O0 -g3 -Wall
LDLIBS  := -lm

ifeq ($(OS),Windows_NT)
	MKDIR   := md
	RMDIR   := rd /S /Q
else
	MKDIR   := mkdir -p
	RMDIR   := rm -rf
endif

.PHONY: all run clean build

all :
	@echo "Iniciando"
	@echo $(OBJS)

gdb : all
	gdb ./bin/main.exe

$(EXE) : $(OBJS) | $(BIN)
	$(CC) $(CFLAGS) ./main.c $^ -o $@ $(LDLIBS)
	
$(OBJ)/%.o : $(SRC)/%.c | $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN) $(OBJ):
	$(MKDIR) $@

run: $(EXE)
	$<

clean:
	if exist obj $(RMDIR) obj
	if exist bin $(RMDIR) bin