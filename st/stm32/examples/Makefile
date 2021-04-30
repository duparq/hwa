
#  Build all the examples
#
examples:
	@for i in ??-?-* ; do echo -n "$$i:" ;					\
	  if $(MAKE) -C $$i elf >/dev/null 2>&1 ; then 				\
	    echo " ok" ; else echo " fail" ; fi ; 				\
	done

rem-examples:
	@for i in ??-?-* ; do echo -n "[bluepill] $$i:" ;			\
	  if $(MAKE) -C $$i BOARD=bluepill elf >/dev/null 2>&1 ; then 		\
	    echo " ok" ; else echo " fail" ; fi ; 				\
	done
	@for i in ??-?-* ; do echo -n "[stm32f411e-disco] $$i:" ;		\
	  if $(MAKE) -C $$i BOARD=stm32f411e-disco elf >/dev/null 2>&1 ; then 	\
	    echo " ok" ; else echo " fail" ; fi ; 				\
	done

#  Cleaning: remove 'build' directories & other useless files
#
.PHONY: clean
clean:
	@find . -name 'build' -prune -exec rm -rf {} ';'
	@find . '(' -name '*~' 			\
		    -o -name '*.cp.*' ')'	\
		-exec rm {} ';'
