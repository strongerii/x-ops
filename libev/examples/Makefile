############################################################################
#
# Makefile for libev
#
#
#
# arm-none-linux-gnueabi-gcc 
#
############################################################################
ifndef TOPDIR
	TOPDIR = ./
endif
ifndef SRCDIR
	SRCDIR = ./
endif

include $(TOPDIR)config.mak

OBJS =	$(SRCDIR)libev_test.o $(SRCDIR)utils/ev_mgr/ev_mgr.o
		
CLIB = $(TOPDIR)lib/libev.so

CFLAGS	+= -Wall -O2 -Os -Wl,-rpath=./lib

CINCLUDE	+= -I$(SRCDIR)include -I$(SRCDIR)utils/ev_mgr/

TARGET	= libev_test

LINK=$(CPP)

include $(TOPDIR)rules.mak

