include ../../Makefile.inc

LIBS = -lgtest -lpthread
CXXFLAGS += $(LIBS)

OBJS = BufferTest.o TestRunner.o

OUT = test-exec

run-test: $(OUT)
	./$(OUT)

$(OUT): $(OBJS) ../Buffer.o
	$(CXX) $(OBJS) $(CXXFLAGS) -o $(OUT) $(LIBS) ../Buffer.o

include ../../Makefile.stdrules
