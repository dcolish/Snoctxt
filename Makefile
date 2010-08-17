CC=gcc
CFLAGS=-g -Wall
.SUFFIXES: .c .o

all: clean
	cp src/snoctxt.c build/
	cd build && \
	$(CC) $(CFLAGS) -o snoctxt.o -c snoctxt.c && \
	$(CC) $(CFLAGS) -o snoctxt snoctxt.o


clean:
	rm -r build
	mkdir -p build