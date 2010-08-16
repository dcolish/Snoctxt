CC=gcc
CFLAGS=-g -Wall
.SUFFIXES: .c .o

.c.o: src/snoctext.c
	$(CC) $(CFLAGS) -o build/$@ src/$<

all: build/snoctxt.o
	$(CC) $(CFLAGS) -o build/snoctxt build/snoctxt.o
