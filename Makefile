all:	doc
	
clean:
	rm -rf doc

doc:
	doxygen Doxyfile