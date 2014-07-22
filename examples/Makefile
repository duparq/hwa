
#	Source files
#
SOURCES		=	blink-02.c
#SOURCES		=	fade.c
#SOURCES		=	servo.c
#SOURCES		=	servo-adc.c
#SOURCES		=	servo-adc-sm.c
#SOURCES		=	sonar.c
#SOURCES		=	adc.c
#SOURCES		=	usi.c


#	Target device
#
MCU		=	attiny84
PKG		=	dil

#	Chip programming
#
PROG_SW		=	diabolo
DIABOLO_OPTS	+=	--read-flash	# programming will be faster
DIABOLO_OPTS	+=	--mcu=$(MCU)

#	HWA
#
#HWA		= 	$(HOME)/dev/hwa-dev
HWA		= 	$(abspath $(PWD)/..)
INCLUDES	+= 	-I$(HWA)
DEFINES		+=	-DHWA_DEVICE=$(MCU)
DEFINES		+=	-DHWA_DEVICE_PACKAGE=$(PKG)

#	Toolchain path
#
# PATH		:= $(HOME)/dev/gcc-toolchains/4.7.0/bin:$(PATH)

#	Output basename
#
OUT		= out

#	Build directory
#
OBJDIR		= build


#	Default target
#
#all:	deps hex bin lst size
all:	deps bin lst crc


#	Device-specific makefile
#	Common makefile
#
include make/Makefile.$(MCU) make/Makefile.in
