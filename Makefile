#==========================================
#    Makefile: makefile for car 1.00
#
# Original Copyright:
#    Makefile: makefile for sl 5.1
#	Copyright 1993, 1998, 2014
#                 Toyoda Masashi
#		  (mtoyoda@acm.org)
#	Last Modified: 2014/03/31
#==========================================

CC=cc
CFLAGS=-O -Wall

all: car

car: car.c car.h
	$(CC) $(CFLAGS) -o car car.c -lncurses

clean:
	rm -f car

distclean: clean
