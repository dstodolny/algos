# Makefile for algos

CC = gcc
CFLAGS = -g -Wall

all: 739 61

algos.o: algos.c
	$(CC) $(CFLAGS) -c algos.c

61: 61.c algos.o
	$(CC) $(CFLAGS) -o 61 61.c algos.o

739: 739.c algos.o
	$(CC) $(CFLAGS) -o 739 739.c algos.o

clean:
	rm -f 739 *~ *.o
