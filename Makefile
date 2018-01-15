CC = gcc
CFLAGS = -Wall -O3 -g -std=c99
INSTALL_PROGRAM = install
BINDIR = /usr/bin

all: matrix

clean:
	rm matrix matrix.o

matrix: main.c matrix.c matrix.h colors.h Makefile
	$(CC) $(CFLAGS) -c -o matrix.o matrix.c
	$(CC) $(CFLAGS) matrix.o main.c -o matrix
