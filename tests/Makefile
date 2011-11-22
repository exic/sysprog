include ../Makefile.inc

LIBS = -lgtest -lpthread
CXXFLAGS += $(LIBS)

OBJS = ScannerTest.o TestRunner.o ../libscan.a ../libbuffer.a ../libsymtab.a

OUT = test-exec

run-test: $(OUT)
	./$(OUT)

$(OUT): $(OBJS)
	$(CXX) $(OBJS) $(CXXFLAGS) -o $(OUT) $(LIBS)

include ../Makefile.stdrules
