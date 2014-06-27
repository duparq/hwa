
SOURCES		=	main.c

#			misc.sx			\
#			swuart.sx		\

MCU		=	attiny44
BOARD		=	
PROG_SW		=	avrdude
PROG_HW		= 	usbasp

INCLUDES	+= -I$(HOME)/dev/hwa-dev

include Makefile.in
include Makefile.$(MCU)
include Makefile.$(PROG_SW)

_diabolo:
	wxdiabolo.py -b 115200				\
	-f build/out.bin						\
	-x "xterm -e python python/robot.py -b 115200"

diabolo:
	wxdiabolo.py -b 115200 -f build/out.bin
