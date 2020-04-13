
korlang: korlang.tab.o lex.yy.o driver.hpp engine.hpp scope.hpp tree.hpp bucket.hpp util.hpp
	g++ -o korlang lex.yy.o korlang.tab.o

test: int_test if_else_test assign_operators_test logical_operators_test loops_test functions_test error_test


int_test: int_test.cpp
	g++ ./int_test.cpp -o int_test

if_else_test: 
	 ./korlang tests/if_else_test.kor  | ./int_test

assign_operators_test:
	./korlang tests/assign_operators_test.kor  | ./int_test

logical_operators_test:
	 ./korlang tests/logical_operators_test.kor| ./int_test

loops_test:
	./korlang tests/loops_test.kor  | ./int_test

error_test:
	./korlang tests/error_handling.kor  | ./int_test

functions_test:
	./korlang tests/functions_test.kor |  ./int_test

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
