.PHONY: all clean

CC=gcc
C_FLAGS=-I./include -O2


all: build/ read_image

read_image: src/main.c build/bmp.o build/conversao.o build/detectores.o build/operacaoPixel.o
	${CC} ${C_FLAGS} src/main.c build/operacaoPixel.o build/detectores.o build/bmp.o build/conversao.o -o read_image

build/detectores.o: build/ src/detectores.c
	${CC} ${C_FLAGS} -c src/detectores.c -o build/detectores.o

build/bmp.o: build/ src/bmp.c
	${CC} ${C_FLAGS} -c src/bmp.c -o build/bmp.o

build/conversao.o: build/ src/conversao.c
	${CC} ${C_FLAGS} -c src/conversao.c -o build/conversao.o

build/operacaoPixel.o: build/ src/operacaoPixel.c
	${CC} ${C_FLAGS} -c src/operacaoPixel.c -o build/operacaoPixel.o

build/:
	mkdir -p build

clean:
	rm -r build
	rm read_image
