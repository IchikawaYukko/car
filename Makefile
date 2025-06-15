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
RPMBUILD=rpmbuild

all: car

car: car.c car.h
	$(CC) $(CFLAGS) -o car car.c -lncurses

rpm: car car.spec
	# To install dependenciesm run:
	#   dnf install install -y git make gcc ncurses-devel rpm-build
	echo pwd=$(pwd)
	export SRC_ROOT=$(shell pwd) && $(RPMBUILD) -D "_topdir $(shell pwd)/rpmbuild" -D "_commit_id $(shell git log -1 --oneline|cut -b -7)" -ba car.spec

clean:
	rm -f car
	rm -rf rpmbuild/

distclean: clean
