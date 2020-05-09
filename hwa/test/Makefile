
#	Source files
#
SOURCES		=	main.c


#  This Makefile is responsible for building the example projects. It needs a
#  board name to be defined and a corresponding board definition header file
#  that defines the target device.


#  MFD contains the directory name of this Makefile whatever has been included
#
MFD		:=	$(dir $(lastword $(MAKEFILE_LIST)))

#  Default target
#
.PHONY: all
all:	main.cp.c


#  Messages in english
#
LANG		:= C

#  Toolchain commands
#
ARCH		:= 
CPP		:= $(ARCH)cpp
CC		:= $(ARCH)gcc

AFLAGS		+= $(FLAGS)
AFLAGS		+= -Wall
AFLAGS		+= -fno-diagnostics-show-caret	# GCC 4.8
AFLAGS		+= $(DEFINES)
AFLAGS		+= $(INCLUDES)

#  It is sometimes useful to just preprocess the source file to determine what
#  went wrong with the HWA macros. Use the -B option to force make rebuild the
#  target.
#
%.cp.c: %.c
#	@echo "RULE $@: $^"
	@echo "$(CPP) $(CFLAGS) $< >$@"
	@$(CPP) $(CFLAGS) $< >$@
#	$(CPP) $(CFLAGS) $< |sed -e 's/;/;\n/g'|bcpp -s -i 2 -bcl | sed -e 's/#/\/\//g' > $@

#  Compiling options
#
CFLAGS		+= $(FLAGS)
CFLAGS		+= -std=c1x
CFLAGS		+= -Wall
CFLAGS		+= -Wextra
#CFLAGS		+= -pedantic
CFLAGS		+= -Wpedantic	# GCC 4.8
CFLAGS		+= -fno-diagnostics-show-caret	# GCC 4.8
#CFLAGS		+= -ftrack-macro-expansion=0
#CFLAGS		+= -fomit-frame-pointer
CFLAGS		+= -ffunction-sections
#CFLAGS		+= -fno-builtins
CFLAGS		+= -fpack-struct
#CFLAGS		+= -fshort-enums
#CFLAGS		+= -mcall-prologues
CFLAGS		+= -g
#CFLAGS		+= -pipe
CFLAGS		+= -Os
#CFLAGS		+= -O0
#CFLAGS		+= -O1
#CFLAGS		+= -O2
#CFLAGS		+= -O3
CFLAGS		+= $(DEFINES)
CFLAGS		+= $(INCLUDES)
#CFLAGS		+= -save-temps


################################################################################
#									       #
#			Misc						       #
#									       #
################################################################################


#  Remove built files under the working directory
#
.PHONY: clean
clean:
	@find . -name 'build' -prune -exec rm -rf {} ';'
	@find . '(' 					\
		-name '*~' 				\
		-o -name '*.cp.*'			\
		-o -name '*.hwa.c'			\
		-o -name '*.pyc'			\
		')' -exec rm {} ';'
