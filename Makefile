.PHONY: all clean

CC=gcc
C_FLAGS=-I./include -O2


all: build/ read_image exec

exec:
	.\read_image

read_image: src/main.c build/bmp.o build/conversao.o build/detectores.o build/operacaoPixel.o build/matriz.o  build/cnn.o build/pooling.o build/neuralNetwork.o
	${CC} ${C_FLAGS} src/main.c build/operacaoPixel.o build/detectores.o build/bmp.o build/matriz.o build/pooling.o build/conversao.o build/cnn.o build/neuralNetwork.o -o read_image

build/matriz.o: build/ src/matriz.c
	$(CC) ${C_FLAGS} -c src/matriz.c -o build/matriz.o

build/pooling.o: build/ src/pooling.c
	$(CC) ${C_FLAGS} -c src/pooling.c -o build/pooling.o

build/conversao.o: build/ src/conversao.c
	${CC} ${C_FLAGS} -c src/conversao.c -o build/conversao.o

build/operacaoPixel.o: build/ src/operacaoPixel.c
	${CC} ${C_FLAGS} -c src/operacaoPixel.c -o build/operacaoPixel.o

build/bmp.o: build/ src/bmp.c
	${CC} ${C_FLAGS} -c src/bmp.c -o build/bmp.o

build/detectores.o: build/ src/detectores.c
	${CC} ${C_FLAGS} -c src/detectores.c -o build/detectores.o

build/neuralNetwork.o: build/ src/neuralNetwork.c
	${CC} ${C_FLAGS} -c src/neuralNetwork.c -o build/neuralNetwork.o

build/cnn.o: build/ src/cnn.c
	${CC} ${C_FLAGS} -c src/cnn.c -o build/cnn.o

build/:
	if not exist build mkdir build

clean:
	rmdir /Q /S build
	del main.o
	del read_image.exe