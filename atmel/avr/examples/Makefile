
#	Makefile for Atmel AVR examples
#
#  The compiler must be given the name of the target device. HWA defines this
#  name in its device header file, that is included by the board header file.
#  Then, if the target requires compilation, the board header is first
#  preprocessed in order to get the target device name.

#$(warning INCLUDE)

#CWD		+=	$(dir $(lastword $(MAKEFILE_LIST)))
#MFD		?=	$(dir $(firstword $(CWD)))
MFD		?=	$(dir $(lastword $(MAKEFILE_LIST)))

#$(warning MFD=$(MFD))

#  Messages in english
#
LANG		:= C

#  Variables used by external scripts
#
# export OUTDIR
# export OUT
export BOARD
export SOURCES
export CONFIG
export LANG


#  Default target
#
#    If no source file list provided, assume we're not in the directory of an
#    example and select 'all-examples' as default target. Otherwise just do
#    'all' in the directory of the example.
#
.PHONY: default

ifeq ($(SOURCES),)
  default:	all-examples
else
  default:	all
endif


#  Remove built files under the working directory
#
.PHONY: clean
clean:
ifeq (,$(BOARD))
	@echo Cleaning $(abspath $(MFD)..)
	@find $(MFD).. -name 'build' -prune -exec rm -rf {} ';'
	@find . '(' 			\
		-name '*~' 		\
		-o -name '*.cp.*'	\
		-o -name '*.hwa.c'	\
		-o -name '*.pyc'	\
		')' -exec rm {} ';'
else
	@echo Cleaning $(abspath $(MFD)../boards/build/$(BOARD))
	rm -rf build/$(BOARD) $(MFD)../boards/build/$(BOARD)
endif


#  Produce HTML documentation
#
.PHONY: doc
doc:
	@cd $(MFD)../../../doxygen && $(MAKE) --no-print-directory


#  Default target: check that the compilation of all the examples produces the
#  same machine code for the same configuration
#
.PHONY: check-all-examples
check-all-examples:
#	@echo "RULE $@: $^"
	@BOARD=$(BOARD) bash $(MFD)make/check-all-examples.sh


#  Compile all the examples
#
.PHONY: all-examples
all-examples:
#	@echo "RULE $@: $^"
	@BOARDS=$(BOARD)						;\
	[ -n "$${BOARDS}" ] || BOARDS="attiny84 attiny85 nanodccduino"	;\
	fails=0								;\
	for BOARD in $${BOARDS} ; do					\
	  echo ; echo Building all examples for board $${BOARD}		;\
	  for i in ??-*							;\
	    do echo -n "$$i: "						;\
	    cd $$i							;\
	      if $(MAKE) BOARD=$${BOARD} -s all >/dev/null 2>&1 ; then	\
		echo success						;\
	      else							\
		echo failed						;\
		fails=$$((fails+1))					;\
	      fi							;\
	    cd - >/dev/null						;\
	  done								;\
	done ; echo "$$fails fails."


#  Validate all the examples
#
.PHONY: validate-all-examples
validate-all-examples:
	@for i in ??-* ; do echo $$i	;\
	(cd $$i ; $(MAKE) -s validate )	;\
	done


#  This target automatically takes the name of the target 
#  that was not found in this Makefile
#
.DEFAULT:
#	@echo ".DEFAULT: $@"
	@$(MAKE) -f $(MFD)make/Makefile.cc --no-print-directory $@
