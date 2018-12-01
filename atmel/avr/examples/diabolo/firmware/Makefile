
#	Source files
#
SOURCES		=	diabolo.sx

CONFIG		=	HW_DEVICE	\
			HW_SYSHZ	\
			DIABOLO_PIN_RX	\
			DIABOLO_PIN_TX  \
			DIABOLO_PIN_DBG	\
			DIABOLO_SYNC

LDFLAGS		+= 	-nostartfiles
LDFLAGS		+= 	-nostdlib

PROG_SW		=	avrdude
PROG_HW		=	usbasp

export LDFLAGS PROG_SW PROG_HW

include ../../make/Makefile
