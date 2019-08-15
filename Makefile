.PHONY: all clean

all: read_image

read_image: main.c bmp.o conversao.o
	gcc -I./include main.c bmp.o conversao.o -o read_image

bmp.o: bmp.c
	gcc -I./include -c bmp.c -o bmp.o

conversao.o: conversao.c
	gcc -I./include -c conversao.c -o conversao.o

clean:
	rm read_image
