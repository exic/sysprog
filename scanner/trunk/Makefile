CXX = g++
CXXFLAGS = -g -Wall

objects = $(patsubst %.cpp, %.o, $(wildcard *.cpp))

all: test run

Scanner.o: Scanner.hpp
Token.o: Token.hpp
TType.o: TType.hpp
Buffer.o: Buffer.hpp
Symtable.o: Symtable.hpp
Automat.o: Automat.hpp Status.hpp TType.hpp

program: $(objects) $(wildcard *.hpp)
	$(CXX) $(CXXFLAGS) -o program $(objects)

run: program
	./program Scanner-test.txt out.txt

test: $(objects)
	cd tests && make

clean:
	rm -f $(objects) a.out test tags program
	cd tests && make clean

tags: *.cpp */*.cpp *.hpp */*.hpp
	ctags -R --c++-kinds=+pl --fields=+iaS --extra=+q .

tags-fetcher:
	( while true; do make tags >/dev/null 2>&1 && sleep 1; done ) &

tags-fetcher-kill:
	ps aux | grep 'make tags' | grep -v grep | awk '{print $$2}' | xargs kill
