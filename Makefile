CXX = g++
CXXFLAGS = -g -Wall

OBJS = $(patsubst %.cpp, %.o, $(wildcard *.cpp))

EXE = scanner

all: test run

Scanner.o: Scanner.hpp
Token.o: Token.hpp
TType.o: TType.hpp
Buffer.o: Buffer.hpp Constants.hpp
Symtable.o: Symtable.hpp
Automat.o: Automat.hpp Status.hpp TType.hpp Constants.hpp

$(EXE): $(OBJS) $(wildcard *.hpp)
	$(CXX) $(CXXFLAGS) -o $(EXE) $(OBJS)

run: $(EXE)
	./$(EXE) Scanner-test.txt out.txt

test: $(OBJS)
	cd tests && make

clean:
	rm -f $(OBJS) a.out test tags $(EXE)
	cd tests && make clean

tags: *.cpp */*.cpp *.hpp */*.hpp
	ctags -R --c++-kinds=+pl --fields=+iaS --extra=+q .

tags-fetcher:
	( while true; do make tags >/dev/null 2>&1 && sleep 1; done ) &

tags-fetcher-kill:
	ps aux | grep 'make tags' | grep -v grep | awk '{print $$2}' | xargs kill
