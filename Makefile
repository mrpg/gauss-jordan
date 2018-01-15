CC = clang
CFLAGS = -Wall -march=native -O3 -std=c99

all: matrix

clean:
	rm matrix matrix.o

matrix: main.c matrix.c matrix.h colors.h Makefile
	$(CC) $(CFLAGS) -c -o matrix.o matrix.c
	$(CC) $(CFLAGS) matrix.o main.c -o matrix
