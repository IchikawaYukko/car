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
DEB_BUILD_DIR=debbuild
DEB_PACKAGE_NAME=car
DEB_VERSION=1.0.0
DEB_ARCH=$(shell dpkg --print-architecture)

all: car

car: car.c car.h
	$(CC) $(CFLAGS) -o car car.c -lncurses

rpm: car car.spec
	# To install dependenciesm run:
	#   dnf install install -y git make gcc ncurses-devel rpm-build
	echo pwd=$(pwd)
	export SRC_ROOT=$(shell pwd) && $(RPMBUILD) -D "_topdir $(shell pwd)/rpmbuild" -D "_commit_id $(shell git log -1 --oneline|cut -b -7)" -ba car.spec

deb: car car.spec
	@rm -rf $(DEB_BUILD_DIR)
	mkdir -p $(DEB_BUILD_DIR)/DEBIAN
	install -D car $(DEB_BUILD_DIR)/usr/bin/car
	cp control $(DEB_BUILD_DIR)/DEBIAN/
	sed "s/^Architecture: .*/Architecture: $(DEB_ARCH)/" control > $(DEB_BUILD_DIR)/DEBIAN/control
	fakeroot dpkg-deb --build $(DEB_BUILD_DIR) .
	rm -rf $(DEB_BUILD_DIR)

clean:
	rm -f car
	rm -rf rpmbuild/

distclean: clean
