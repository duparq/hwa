
#	Makefile for Diabolo bootloader

#	Target device (atmega8, atmega88, atmega16, etc.)
#	HWA names of pins used
#
MCU		= attiny84
DEFINES		+= -DPIN_TXD=hw_pin_pb0
DEFINES		+= -DPIN_RXD=hw_pin_pb0
DEFINES		+= -DX_SPD=0
#DEFINES		+= -DPIN_DBG=INT0
PROG_HW		= usbasp

#	Source files
#
SOURCES		=	diabolo-$(MCU).sx

#	HWA directory
#
HWA		= $(HOME)/dev/hwa-dev

#	HWA files path
#
INCLUDES	+= -I$(HWA)

#	Toolchain path
#
# PATH		:= $(HOME)/dev/gcc-toolchains/4.7.0/bin:$(PATH)

#	Output basename
#
OUT		= out

#	Build directory
#
BUILDIR		= build

#	Default make target
#
all:	deps hex bin lst size

#	Device-specific makefile
#	Common makefile
#
include make/Makefile.$(MCU) make/Makefile.in
