
#	Source files
#
#SOURCES		=	blink-01.c
#SOURCES		=	blink-02.c
SOURCES		=	fade.c
#SOURCES		=	servo.c
#SOURCES		=	sonar.c

#	Target device
#
MCU		=	attiny84


#	Chip programming
#
PROG_SW		=	diabolo
DIABOLO_OPTS	=	--read-flash	# programming will be faster


#	HWA directory
#
HWA		= $(HOME)/dev/hwa-dev


#DEFINES		+= -DHWA_DEVICE=$(MCU)


#	HWA files path
#
INCLUDES	+= -I$(HWA)
#INCLUDES	+= -I$(PWD)/lib
#INCLUDES	+= -I$(PWD)/com

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
#all:	deps hex bin lst size
all:	deps bin lst crc

#	Device-specific makefile
#	Common makefile
#
include make/Makefile.$(MCU) make/Makefile.in
