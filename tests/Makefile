include ../Makefile.inc

LIBS = -lgtest -lpthread
CXXFLAGS += $(LIBS)

OBJS = ScannerTest.o TestRunner.o ../libscan.a ../libbuffer.a ../libsymtab.a

ScannerTest.o: ../libscan.a

OUT = test-exec

run-test: $(OUT)
	cp scannertestfil* /tmp/
	./$(OUT)
	rm /tmp/scannertestfil*


$(OUT): $(OBJS)
	$(CXX) $(OBJS) $(CXXFLAGS) -o $(OUT) $(LIBS)

include ../Makefile.stdrules
