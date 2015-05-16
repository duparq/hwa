
.PHONY:clean
clean:
	@find . '(' 			\
		-name '*~' 		\
		-o -name '*.cp.*'	\
		-o -name '*.pyc'	\
		')' -exec rm -rf {} ';'
	@find . -name 'build' -prune -exec rm -rf {} ';'


#  Remove all produced files + check data
#
.PHONY: superclean
superclean:
	@find . '(' 			\
		-name '*~' 		\
		-o -name '*.cp.*'	\
		-o -name '*.pyc'	\
		-o -name '.valid-*'	\
		')' -exec rm -rf {} ';'
	@find . -name 'build' -prune -exec rm -rf {} ';'


#  Produce HTML documentation
#
.PHONY: doc
doc:
	@mkdir -p doxygen/html
	@doxygen doxygen/Doxyfile
#	@cp doxygen/css.css doxygen/html/doxygen.css

#  Compile all the test files
#
.PHONY: tests
tests:
	@for i in examples/??-?-* ; do echo $$i: 	; \
	(cd $$i ; if make 2>/dev/null |grep bytes ; then true ; else echo failed ; fi ) ;\
	 echo ; done


#  Validate all the test files
#
.PHONY: validate
validate:
	@for i in examples/??-?-* ; do echo $$i		;\
	(cd $$i ; make -s validate )			;\
	done


#  Check that all the test machine codes have the same CRC for the same
#  configuration
#
.PHONY: checks
checks:
	@fails=0						;\
	for i in examples/??-?-* ; do echo -n "$$i: "		;\
	cd $$i							;\
	  if make -s check 2>/dev/null ; then 			\
	    true						;\
	  else							\
	    fails=$$((fails+1))					;\
	  fi							;\
	cd - >/dev/null						;\
	done							;\
	if [ $$fails -gt 0 ] ; then 				\
	  echo "$$fails fails."					;\
	else							\
	  echo "Success."					;\
	fi
