
#	Source files
#
SOURCES		=	diabolo.sx

LDFLAGS		+= 	-nostartfiles
LDFLAGS		+= 	-nostdlib

PROG_SW		=	avrdude
PROG_HW		=	usbasp


include ../../../../../make/Makefile

$(warning "PATH: $(PATH)")

install: burn write-fuses
