
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


#  If BOARD is specified, check that it exists
#
ifneq (,$(BOARD))
  ifeq (,$(wildcard $(MFD)/boards/$(BOARD).h))
    $(error "$(BOARD)" is not a valid board name)
  endif
endif


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
	@echo Cleaning $(abspath $(PWD)/build)		;\
	find . -name 'build' -prune -exec rm -rf {} ';'	;\
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
	[ -n "$${BOARDS}" ] || BOARDS="attiny84 attiny84-tcs3200 attiny85 nanodccduino"	;\
	fails=0								;\
	runs=0								;\
	for BOARD in $${BOARDS} ; do					\
	  echo ; echo Building all examples for board $${BOARD}		;\
	  if [ $${BOARD} = attiny84 ] ; then				\
	    EXAMPLES="01-1-blink-soft"					;\
	    EXAMPLES="$${EXAMPLES} 02-1-blink-watchdog-stat"		;\
	    EXAMPLES="$${EXAMPLES} 02-2-blink-watchdog-irq"		;\
	    EXAMPLES="$${EXAMPLES} 02-3-blink-watchdog-irq-reset"	;\
	    EXAMPLES="$${EXAMPLES} 03-1-blink-counter-overflow-flag"	;\
	    EXAMPLES="$${EXAMPLES} 03-2-blink-counter-compare-flag"	;\
	    EXAMPLES="$${EXAMPLES} 03-3-blink-counter-overflow-irq"	;\
	    EXAMPLES="$${EXAMPLES} 03-4-blink-counter-compare-irq"	;\
	    EXAMPLES="$${EXAMPLES} 03-5-fade-counter-compare-output"	;\
	    EXAMPLES="$${EXAMPLES} 03-6-fade-counter-compare-output"	;\
	    EXAMPLES="$${EXAMPLES} 04-1-fade-adc"			;\
	    EXAMPLES="$${EXAMPLES} 05-1-swuart-tx"			;\
	    EXAMPLES="$${EXAMPLES} 05-2-swuart-sync-rx-tx"		;\
	    EXAMPLES="$${EXAMPLES} 05-3-dual-swuart"			;\
	    EXAMPLES="$${EXAMPLES} 06-1-swuart-adc"			;\
	    EXAMPLES="$${EXAMPLES} 07-1-swuart-eeprom-read-write"	;\
	    EXAMPLES="$${EXAMPLES} 08-1-swuart-flash-read-write"	;\
	    EXAMPLES="$${EXAMPLES} 10-1-acmp"				;\
	  fi								;\
	  if [ $${BOARD} = attiny84-tcs3200 ] ; then			\
	    EXAMPLES="99-01-TCS3200-color-detector"			;\
	  fi								;\
	  if [ $${BOARD} = attiny85 ] ; then				\
	    EXAMPLES="01-1-blink-soft"					;\
	    EXAMPLES="$${EXAMPLES} 02-1-blink-watchdog-stat"		;\
	    EXAMPLES="$${EXAMPLES} 02-2-blink-watchdog-irq"		;\
	    EXAMPLES="$${EXAMPLES} 02-3-blink-watchdog-irq-reset"	;\
	    EXAMPLES="$${EXAMPLES} 03-1-blink-counter-overflow-flag"	;\
	    EXAMPLES="$${EXAMPLES} 03-2-blink-counter-compare-flag"	;\
	    EXAMPLES="$${EXAMPLES} 03-3-blink-counter-overflow-irq"	;\
	    EXAMPLES="$${EXAMPLES} 03-4-blink-counter-compare-irq"	;\
	    EXAMPLES="$${EXAMPLES} 03-5-fade-counter-compare-output"	;\
	    EXAMPLES="$${EXAMPLES} 03-6-fade-counter-compare-output"	;\
	    EXAMPLES="$${EXAMPLES} 03-7-pwm-dead-time"			;\
	    EXAMPLES="$${EXAMPLES} 04-1-fade-adc"			;\
	    EXAMPLES="$${EXAMPLES} 05-1-swuart-tx"			;\
	    EXAMPLES="$${EXAMPLES} 05-2-swuart-sync-rx-tx"		;\
	    EXAMPLES="$${EXAMPLES} 06-1-swuart-adc"			;\
	    EXAMPLES="$${EXAMPLES} 07-1-swuart-eeprom-read-write"	;\
	    EXAMPLES="$${EXAMPLES} 08-1-swuart-flash-read-write"	;\
	    EXAMPLES="$${EXAMPLES} 10-1-acmp"				;\
	  fi								;\
	  if [ $${BOARD} = nanodccduino ] ; then			\
	    EXAMPLES="01-1-blink-soft"					;\
	    EXAMPLES="$${EXAMPLES} 02-1-blink-watchdog-stat"		;\
	    EXAMPLES="$${EXAMPLES} 02-2-blink-watchdog-irq"		;\
	    EXAMPLES="$${EXAMPLES} 02-3-blink-watchdog-irq-reset"	;\
	    EXAMPLES="$${EXAMPLES} 03-1-blink-counter-overflow-flag"	;\
	    EXAMPLES="$${EXAMPLES} 03-2-blink-counter-compare-flag"	;\
	    EXAMPLES="$${EXAMPLES} 03-3-blink-counter-overflow-irq"	;\
	    EXAMPLES="$${EXAMPLES} 03-4-blink-counter-compare-irq"	;\
	    EXAMPLES="$${EXAMPLES} 03-5-fade-counter-compare-output"	;\
	    EXAMPLES="$${EXAMPLES} 03-6-fade-counter-compare-output"	;\
	    EXAMPLES="$${EXAMPLES} 04-1-fade-adc"			;\
	    EXAMPLES="$${EXAMPLES} 05-1-swuart-tx"			;\
	    EXAMPLES="$${EXAMPLES} 05-2-swuart-sync-rx-tx"		;\
	    EXAMPLES="$${EXAMPLES} 05-3-dual-swuart"			;\
	    EXAMPLES="$${EXAMPLES} 06-1-swuart-adc"			;\
	    EXAMPLES="$${EXAMPLES} 07-1-swuart-eeprom-read-write"	;\
	    EXAMPLES="$${EXAMPLES} 08-1-swuart-flash-read-write"	;\
	    EXAMPLES="$${EXAMPLES} 09-3-uart-spi-nrf24l01+"		;\
	    EXAMPLES="$${EXAMPLES} 10-1-acmp"				;\
	    EXAMPLES="$${EXAMPLES} 11-1-uart-twi-eeprom"		;\
	  fi								;\
	  for i in $${EXAMPLES}						;\
	    do echo -n "$$i: "						;\
	    runs=$$((runs+1))						;\
	    cd $$i							;\
	      if $(MAKE) BOARD=$${BOARD} -s all >/dev/null 2>&1 ; then	\
		echo success						;\
	      else							\
		echo failed						;\
		fails=$$((fails+1))					;\
	      fi							;\
	    cd - >/dev/null						;\
	  done								;\
	done ; echo "$$fails fails / $$runs runs."


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
