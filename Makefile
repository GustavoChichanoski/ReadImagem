MKDIR   := mkdir
RMDIR   := rmdir /S /Q
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

.PHONY: all run clean build

all : clean $(EXE) gdb

gdb :
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