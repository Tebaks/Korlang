
korlang: korlang.tab.o lex.yy.o driver.hpp engine.hpp scope.hpp tree.hpp
	g++ -o korlang lex.yy.o korlang.tab.o

# Bison generates a C++ source file and a C++ header file.
korlang.tab.cpp korlang.tab.hpp: korlang.ypp
	bison -d korlang.ypp

# Flex generates just a C++ source file.
lex.yy.cpp: korlang.lpp
	flex -o lex.yy.cpp korlang.lpp

# The lex file includes the header from Bison.
lex.yy.o: lex.yy.cpp korlang.tab.hpp
	g++ -c lex.yy.cpp

korlang.tab.o: korlang.tab.cpp
	g++ -c korlang.tab.cpp

# The following line makes "make" automatically clean up these
# files for you when they are no longer needed.
.INTERMEDIATE: korlang.tab.o lex.yy.o lex.yy.cpp korlang.tab.cpp korlang.tab.hpp

# Run "make clean" to clear all extra files.
.PHONY: clean
clean:
	-rm -f *.o *.yy.cpp *.tab.?pp korlang
