###############################################################################
# Copyright 2010 Dan Colish
# All rights reserved.
#
# This file is part of 'snoctxt' and is distributed under the BSD license.
# See LICENSE for more details.
###############################################################################

CC=gcc
CFLAGS+= -Wall
.PHONY: all

all: clean build test

build: clean
	cp src/snoctxt.c build/
	cd build && \
	$(CC) $(CFLAGS) -o snoctxt.o -c snoctxt.c && \
	$(CC) $(CFLAGS) -o snoctxt snoctxt.o

debug: clean
	CFLAGS=-g make build

clean:
	rm -r build
	mkdir -p build

test: build

	cd test && \
	cp snoc_dst.txt.bk snoc_dst.txt && \
	../build/snoctxt -s snoc_src.txt -d snoc_dst.txt
	test `grep -c Copyright test/snoc_dst.txt` -eq 1

	cd test && \
	cp snoc_dst.txt.bk snoc_dst.txt && \
	../build/snoctxt --source snoc_src.txt --destination snoc_dst.txt
	test `grep -c Copyright test/snoc_dst.txt` -eq 1
