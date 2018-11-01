
.PHONY: default
default:
	@echo "make doc | examples | check | clean"

#  Produce HTML documentation
#
.PHONY: doc
doc:
	@cd doxygen && $(MAKE) --no-print-directory


#  Remove all built files
#
.PHONY:clean
clean:
	@find . '(' 			\
		-name '*~' 		\
		-o -name '*.cp.*'	\
		-o -name '*.pyc'	\
		-o -name '*.bak'	\
		-o -name 'failed'	\
		')' -exec rm -rf {} ';'
	@find . -name 'build' -prune -exec rm -rf {} ';'
	@rm -rf doxygen/html


#  Compile all the examples
#
.PHONY: examples
examples:
	@FAILS=$$(mktemp) ; export FAILS					;\
	(cd atmel/avr/examples         && bash make/make-all.sh)		;\
	(cd st/stm32/examples          && bash make/make-all.sh)		;\
	(cd espressif/esp8266/examples && bash make/make-all.sh)		;\
	fails=$$(cat $$FAILS | wc -l)						;\
	if [ $$fails -eq 0 ] ; then						\
	    echo "Success." ; echo						;\
	else									\
	    echo "$$fails examples failed:"					;\
	    cat $$FAILS	; echo							;\
	fi									;\
	rm $$FAILS


#  Verify the examples CRCs
#
.PHONY: check
check:
	@cd atmel/avr/examples         && $(MAKE) --no-print-directory check-all-examples
	@cd st/stm32/examples          && $(MAKE) --no-print-directory check-all-examples
	@cd espressif/esp8266/examples && $(MAKE) --no-print-directory check-all-examples
