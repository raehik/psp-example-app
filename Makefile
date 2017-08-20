#
# Commented Makefile for PSP EBOOTS (applications).
# Author: raehik
# Date: 2017-08-16
# Version: 1.2
#

TARGET = hello-raehik
OBJS   = src/main.o src/common/callback.o

PSP_FW_VERSION = 661

PSP_EBOOT_TITLE = hello-raehik
#PSP_EBOOT_ICON  = ICON0.png
#PSP_EBOOT_PIC1  = PIC1.png
#PSP_EBOOT_SND0  = SND0.at3

## EBOOT required {{{
BUILD_PRX = 1
EXTRA_TARGETS = EBOOT.PBP
## }}}

## general {{{
INCDIR   =
CFLAGS   = -std=c11 -O2 -Wall -G0
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS  = $(CFLAGS)

LIBDIR  =
LDFLAGS =
LIBS    =
## }}}

## include master Makefile {{{
PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
## }}}
