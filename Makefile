#
# Commented PSP Makefile.
# Author: raehik
# Date: 2017-08-16
# Version: 1.0
#

## normal C Makefile stuff {{{
TARGET = hello-raehik
OBJS   = src/main.o src/common/callback.o

INCDIR   =
CFLAGS   = -O2 -Wall -G0
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS  = $(CFLAGS)
#ASFLAGS  = $(CFLAGS) -c ?

LIBDIR  =
LDFLAGS =
LIBS    =
## }}}

## build options {{{
PSP_FW_VERSION = 661
## }}}

## EBOOT options {{{
PSP_EBOOT_TITLE = hello-raehik
#PSP_EBOOT_ICON  = ICON0.png
#PSP_EBOOT_PIC1  = PIC1.png
#PSP_EBOOT_SND0  = SND0.at3
## }}}

## required {{{
BUILD_PRX = 1
EXTRA_TARGETS = EBOOT.PBP
## }}}

## include the master Makefile {{{
PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
## }}}
