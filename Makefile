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

.PHONY: all run clean

all: $(EXE)

$(EXE): $(OBJS) | $(BIN)
	$(CC) $(CFLAGS) src/main.c $^ -o $@ $(LDLIBS)

$(OBJ)/%.o: $(SRC)/%.c | $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN) $(OBJ):
	$(MKDIR) $@

run: $(EXE)
	$<

clean:
	$(RMDIR) obj
	$(RMDIR) bin

# foo: $(OBJ)
# 	cc -o foo $(C_FLAGS) $(OBJ)

# read_image: src/main.c build/bmp.o build/conversao.o build/detectores.o build/operacaoPixel.o build/matriz.o build/cnn.o build/pooling.o build/complex.o build/neuralNetwork.o
# 	${CC} ${C_FLAGS} src/main.c build/operacaoPixel.o build/detectores.o build/bmp.o build/matriz.o build/pooling.o build/conversao.o build/cnn.o build/neuralNetwork.o build/complex.o -o read_image

# build/matriz.o: build/ src/operacaoMatriz.c
# 	$(CC) ${C_FLAGS} -c src/operacaoMatriz.c -o build/matriz.o

# build/pooling.o: build/ src/pooling.c
# 	$(CC) ${C_FLAGS} -c src/pooling.c -o build/pooling.o

# build/complex.o: build/ src/complex.c
# 	$(CC) ${C_FLAGS} -c src/complex.c -o build/complex.o

# build/conversao.o: build/ src/conversao.c
# 	${CC} ${C_FLAGS} -c src/conversao.c -o build/conversao.o

# build/operacaoPixel.o: build/ src/operacaoPixel.c
# 	${CC} ${C_FLAGS} -c src/operacaoPixel.c -o build/operacaoPixel.o

# build/bmp.o: build/ src/bmp.c
# 	${CC} ${C_FLAGS} -c src/bmp.c -o build/bmp.o

# build/detectores.o: build/ src/detectores.c
# 	${CC} ${C_FLAGS} -c src/detectores.c -o build/detectores.o

# build/neuralNetwork.o: build/ src/neuralNetwork.c
# 	${CC} ${C_FLAGS} -c src/neuralNetwork.c -o build/neuralNetwork.o

# build/cnn.o: build/ src/cnn.c
# 	${CC} ${C_FLAGS} -c src/cnn.c -o build/cnn.o

# build/:
# 	if not exist build mkdir build

# print: scr/*.c
# 	lpr -p $?
# 	touch print

# clean:
# 	del *.exe
# 	rmdir /Q /S build
# 	del out.txt