
korlang: korlang.tab.o ./src/main.cpp lex.yy.o src/driver.hpp src/engine.hpp src/scope.hpp src/tree.hpp src/bucket.hpp src/util.hpp
	g++ -o korlang ./src/main.cpp lex.yy.o korlang.tab.o -pthread

test: korlang int_test if_else_test assign_operators_test logical_operators_test loops_test functions_test error_test

examples: korlang factorial prime fibonacci 

fibonacci: examples/fibonacci.kor
	./korlang examples/fibonacci.kor

prime: examples/prime.kor
	./korlang examples/prime.kor

list : examples/listExample.kor
	./korlang examples/listExample.kor

event : examples/eventEmitter.kor
	./korlang examples/eventEmitter.kor

game : examples/updowngame.kor
	./korlang examples/updowngame.kor

factorial: examples/factorial.kor
	./korlang examples/factorial.kor

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
./src/korlang.tab.cpp ./src/korlang.tab.hpp: ./src/korlang.ypp
	bison -d ./src/korlang.ypp
	mv korlang.tab.cpp ./src/korlang.tab.cpp
	mv korlang.tab.hpp ./src/korlang.tab.hpp
	

# Flex generates just a C++ source file.
src/lex.yy.cpp: ./src/korlang.lpp
	flex -o ./src/lex.yy.cpp ./src/korlang.lpp

# The lex file includes the header from Bison.
lex.yy.o: ./src/lex.yy.cpp ./src/korlang.tab.hpp
	g++ -c ./src/lex.yy.cpp

korlang.tab.o: ./src/korlang.tab.cpp
	g++ -c ./src/korlang.tab.cpp	

# The following line makes "make" automatically clean up these
# files for you when they are no longer needed.
.INTERMEDIATE: ./src/korlang.tab.o ./src/lex.yy.o ./src/lex.yy.cpp ./src/korlang.tab.cpp ./src/korlang.tab.hpp

# Run "make clean" to clear all extra files.
.PHONY: clean
clean:
	-rm -f *.o *.yy.cpp *.tab.?pp korlang
