include Makefile.inc

OBJS = $(patsubst %.cpp, %.o, $(wildcard *.cpp))

MODULES = buffer scan symtab
LIBS = libscan.a libsymtab.a libbuffer.a
CXXFLAGS += $(LIBS)

EXE = scanner

all: run

$(EXE): $(OBJS) $(wildcard *.hpp) $(LIBS)
	$(CXX) $(OBJS) $(CXXFLAGS) -o $(EXE)

run: modules $(EXE)
	cp Scanner-test.txt /tmp/test67.txt
	./$(EXE) /tmp/test67.txt /tmp/out67.txt

modules:
	( for module in $(MODULES); do\
		echo ============ ========== $$module =========== ===========;\
		cd $$module && make all && cd -;\
	done );

#clean:
#	find -name '*.o' -or -name '*.a' | xargs rm -f
#	rm -f $(EXE)
#$(OBJS) a.out test tags $(EXE)
#	cd tests && make clean 2>/dev/null || true

include Makefile.stdrules



##################
# ctags stuff... #
##################

tags: *.cpp */*.cpp *.hpp */*.hpp
	ctags -R --c++-kinds=+pl --fields=+iaS --extra=+q .

tags-fetcher:
	( while true; do make tags >/dev/null 2>&1 && sleep 1; done ) &

tags-fetcher-kill:
	ps aux | grep 'make tags' | grep -v grep | awk '{print $$2}' | xargs kill
