CC=gcc
CFLAGS=-g
.SUFFIXES: .c .o

all: snoctxt.o
	$(CC) $(CFLAGS) -o snoctxt snoctxt.o

