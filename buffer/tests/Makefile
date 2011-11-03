include ../../Makefile.inc

LIBS = -lgtest -lpthread
CXXFLAGS = $(CXXFLAGS) $(LIBS)

OBJS = BufferTest.o TestRunner.o

OUT = test-exec

run-test: $(OUT)
	./$(OUT)

%.o: %.cpp
	echo CC $<
	${CXX} -c ${CXXFLAGS} $<

$(OUT): $(OBJS) ../Buffer.o
	$(CXX) $(OBJS) $(CXXFLAGS) -o $(OUT) $(LIBS) ../Buffer.o
