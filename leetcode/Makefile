# Makefile for algos

CC = gcc
CFLAGS = -g -Wall
FILES = 61 739

all: $(FILES)

algos.o: algos.c
	$(CC) $(CFLAGS) -c algos.c

61: 61.c algos.o
	$(CC) $(CFLAGS) -o 61 61.c algos.o

739: 739.c algos.o
	$(CC) $(CFLAGS) -o 739 739.c algos.o

clean:
	rm -f $(FILES) *~ *.o
