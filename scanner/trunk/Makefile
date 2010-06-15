CXX = g++
CXXFLAGS = -g -Wall

objects = $(patsubst %.cpp, %.o, $(wildcard *.cpp))

test: $(objects)
	$(CXX) $(CXXFLAGS) -o test $(objects)

Scanner.o: Scanner.hpp
Token.o: Token.hpp
TType.o: TType.hpp
Buffer.o: Buffer.hpp
Symtable.o: Symtable.hpp
Automat.o: Automat.hpp Status.hpp TType.hpp

run: test
	./test Scanner-test.txt out.txt && cat out.txt


clean:
	rm -f $(objects) a.out test
