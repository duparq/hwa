
clean:
	@find . '(' 			\
		-name '*~' 		\
		-o -name '*.cp.*'	\
		-o -name '*.pyc'	\
		')' -exec rm {} ';'
	@find . -name 'build' -exec rm -rf {} ';'
