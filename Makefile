MKDIR   := md
RMDIR   := rd /S /Q
CC      := gcc
BIN     := ./bin
OBJ     := ./obj
INCLUDE := ./include
SRC     := ./src
SRCS    := $(wildcard $(SRC)/*.c)
OBJS    := $(patsubst $(SRC)/%.c,$(OBJ)/%.o,$(SRCS))
EXE     := $(BIN)/main.exe
CFLAGS  := -I$(INCLUDE) -O0 -g3
LDLIBS  := -lm

ifeq ($(OS),Windows_NT)
	MKDIR   := md
	RMDIR   := rd /S /Q
else
	MKDIR   := mkdir -p
	RMDIR   := rm -rf
endif

.PHONY: all run clean build

all : clean $(EXE)

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