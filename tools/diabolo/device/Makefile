
#	Source files
#
SOURCES		=	diabolo.sx

LDFLAGS		+= 	-nostartfiles
LDFLAGS		+= 	-nostdlib

PROG_SW		=	avrdude
PROG_HW		=	usbasp


include ../../../examples/make/Makefile


install: burn write-fuses
