include Makefile.inc

OBJS = $(patsubst %.cpp, %.o, $(wildcard *.cpp))

MODULES = buffer scan symtab
LIBS = libscan.a libsymtab.a libbuffer.a
# CXXFLAGS += $(LIBS)

EXE = scanner

all: run

$(EXE): $(OBJS) $(LIBS)
	@$(CXX) $(OBJS) $(CXXFLAGS) $(LIBS) -o $(EXE)


TMP_IN = /tmp/test67.txt
TMP_OUT = /tmp/out67.txt

run: modules test $(EXE)
	@cp input2 $(TMP_IN)
	@rm -f $(TMP_OUT)
	@echo Running...; echo
	@./$(EXE) $(TMP_IN) $(TMP_OUT)
	@mv $(TMP_OUT) out.txt
	@rm $(TMP_IN)
	@echo; echo ...done.; echo

modules:
	@( for module in $(MODULES); do\
		echo "###############";\
		echo "#" $$module ;\
		echo "###############";\
		cd $$module && make --no-print-directory all && cd - 2>&1 >/dev/null;\
		echo "# $$module done";\
	done );
	@echo "###############"; echo

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
