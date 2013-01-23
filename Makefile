include Makefile.inc

OBJS = $(patsubst %.cpp, %.o, $(wildcard *.cpp))

MODULES = buffer scan symtab pars
LIBS = libscan.a libsymtab.a libbuffer.a libpars.a
# CXXFLAGS += $(LIBS)

EXE = sysprog

all: run

$(EXE): $(OBJS) $(LIBS)
	@$(CXX) $(OBJS) $(LIBS) $(CXXFLAGS) -o $(EXE)


TMP_IN = /tmp/test67.txt
TMP_OUT = /tmp/out67.txt

run: modules test $(EXE)
	@cp input1 $(TMP_IN)
	@rm -f $(TMP_OUT)
	@echo Running...; echo
	@./$(EXE) parse $(TMP_IN) $(TMP_OUT)
	@mv $(TMP_OUT) out.code 2>/dev/null || true
	@rm $(TMP_IN)
	@echo; echo ...done.; echo

integration-test:
	it/integration-test

modules:
	@( for module in $(MODULES); do\
		echo "###############";\
		echo "#" $$module ;\
		echo "###############";\
		cd $$module && make --no-print-directory all && cd - 2>&1 >/dev/null || exit 1;\
		echo "###############";\
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

tags: *.cpp */*.cpp */*.hpp
	ctags -R --c++-kinds=+pl --fields=+iaS --extra=+q .

tags-fetcher:
	( while true; do make tags >/dev/null 2>&1 && sleep 1; done ) &

tags-fetcher-kill:
	ps aux | grep 'make tags' | grep -v grep | awk '{print $$2}' | xargs kill
