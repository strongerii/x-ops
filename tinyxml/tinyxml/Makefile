############################################################################
#
# Makefile for tinyxml
#
#
#
# arm-mv5sft-linux-gnueabi-gcc 
#
############################################################################
ifndef TOPDIR
	TOPDIR = ../
endif
ifndef SRCDIR
	SRCDIR = ./
endif

CROSS	:= arm-none-linux-gnueabi-
CC	= $(CROSS)gcc
CPP	= $(CROSS)g++
LD	= $(CROSS)ld
AR	= $(CROSS)ar
RM	= rm -f

OBJS =	$(SRCDIR)tinystr.o \
		$(SRCDIR)tinyxml.o \
		$(SRCDIR)tinyxmlerror.o \
		$(SRCDIR)tinyxmlparser.o \
		$(SRCDIR)xmlinterface.o \

TINYXMLINTERFACELIB = $(TOPDIR)lib/libxmlinf.so
TINYXMLINTERFACEINCLUDE = $(SRCDIR)xmlinterface.h
 
CFLAGS	+= -shared -fPIC
CFLAGS	+= -Wall -O2 -Os

CINCLUDE += -I$(SRCDIR)

TARGET	= $(TINYXMLINTERFACELIB)

LINK=$(CPP)

all: $(TARGET) 

$(TARGET): $(OBJS)
	$(RM) $@;
	$(LINK) $(CFLAGS) -o $(TARGET) $(OBJS) $(CLIB)
	cp $(TINYXMLINTERFACEINCLUDE) $(TOPDIR)include
.c.o:
	$(CC)  $(CFLAGS) $(CINCLUDE) -c -o $@ $<
	@echo $@
.cpp.o:
	$(CPP) $(CFLAGS) $(CINCLUDE) -c -o $@ $<
	@echo $@

clean:
	rm -f $(TARGET) $(OBJS);


