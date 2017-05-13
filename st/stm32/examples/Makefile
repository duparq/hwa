
#  Makefile for STM32 examples
#
#  The compiler must be given the name of the target device. HWA defines this
#  name in its device header file, that is included by the board header file.
#  Then, if the target requires compilation, the board header is first
#  preprocessed in order to get the target device name.


#  Directory of this Makefile
#
MFD		?=	$(dir $(lastword $(MAKEFILE_LIST)))

#$(warning MFD=$(MFD))


#  Speak english
#
LANG		:= C


#  Supported boards
#  The first one is chosen by default
#
ALLBOARDS	=	mini-stm32-v3.0	\
			stm32f103c8t6-vcc-gnd


#  Variables used by external scripts
#
export BOARD
export ALLBOARDS
export SOURCES
export CONFIG
export LANG


#  If BOARD is specified, check that it exists
#
ifneq (,$(BOARD))
  ifeq (,$(wildcard $(MFD)/boards/$(BOARD).h))
    $(error "$(BOARD)" is not a valid board name)
  endif
endif


#  Default target
#
#  If no source file list provided, assume we're not in the directory of an
#  example and select 'all-examples' as default target. Otherwise just do 'all'
#  in the directory of the example.
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
	@find . -name 'build' -prune -exec rm -rf {} ';'	;\
	find . '(' 					\
		-name '*~' 				\
		-o -name '*.cp.*'			\
		-o -name '*.hwa.c'			\
		-o -name '*.pyc'			\
		')' -exec rm {} ';'
else
	@echo Cleaning $(abspath $(MFD)../boards/build/$(BOARD)) $(abspath $(PWD)/../build/$(BOARD))
	rm -rf $(MFD)../boards/build/$(BOARD) build/$(BOARD)
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
	[ -n "$${BOARDS}" ] || BOARDS=$(ALLBOARDS)			;\
	passed=0							;\
	fails=0								;\
	. make/examples-for-board.sh					;\
	for BOARD in $${BOARDS} ; do					\
	  echo Building examples for board $${BOARD}			;\
	  examples_for_board $${BOARD}					;\
	  for i in $${EXAMPLES}						;\
	    do echo -n "  $$i: "					;\
	    cd $$i							;\
	      if $(MAKE) BOARD=$${BOARD} -s all >/dev/null 2>&1 ; then	\
		echo success						;\
		passed=$$((passed+1))					;\
	      else							\
		echo failed						;\
		fails=$$((fails+1))					;\
	      fi							;\
	    cd - >/dev/null						;\
	  done								;\
	done ; echo "$$passed succeeded, $$fails failed."


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
