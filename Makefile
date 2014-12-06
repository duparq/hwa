
clean:
	@find . '(' 			\
		-name '*~' 		\
		-o -name '*.cp.*'	\
		-o -name '*.pyc'	\
		')' -exec rm -rf {} ';'
	@find . -name 'build' -prune -exec rm -rf {} ';'

doc:
	@mkdir -p doxygen/html
	@doxygen doxygen/Doxyfile
#	@cp doxygen/css.css doxygen/html/doxygen.css
