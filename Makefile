# SI 413 Fall 2012
# Lab 4
# Makefile for simple calculator

# This is the executable that will run the calculator.
# Since it is the first rule, it is also what will get made if
# we call "make" with no arguments.
calc: calc.tab.o lex.yy.o driver.hpp engine.hpp scope.hpp tree.hpp
	g++ -o calc lex.yy.o calc.tab.o

# Bison generates a C++ source file and a C++ header file.
calc.tab.cpp calc.tab.hpp: calc.ypp
	bison -d calc.ypp

# Flex generates just a C++ source file.
lex.yy.cpp: calc.lpp
	flex -o lex.yy.cpp calc.lpp

# The lex file includes the header from Bison.
lex.yy.o: lex.yy.cpp calc.tab.hpp
	g++ -c lex.yy.cpp

calc.tab.o: calc.tab.cpp
	g++ -c calc.tab.cpp

# The following line makes "make" automatically clean up these
# files for you when they are no longer needed.
.INTERMEDIATE: calc.tab.o lex.yy.o lex.yy.cpp calc.tab.cpp calc.tab.hpp

# Run "make clean" to clear all extra files.
.PHONY: clean
clean:
	-rm -f *.o *.yy.cpp *.tab.?pp calc
