
.PHONY:clean
clean:
	@find . '(' 			\
		-name '*~' 		\
		-o -name '*.cp.*'	\
		-o -name '*.pyc'	\
		')' -exec rm -rf {} ';'
	@find . -name 'build' -prune -exec rm -rf {} ';'

.PHONY: doc
doc:
	@mkdir -p doxygen/html
	@doxygen doxygen/Doxyfile
#	@cp doxygen/css.css doxygen/html/doxygen.css

.PHONY: tests
tests:
	@for i in examples/0* ; do echo $$i ; (cd $$i ; make) ; done |grep bytes
