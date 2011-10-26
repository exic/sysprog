CXX = g++
LIBS = -lgtest -lpthread
CXXFLAGS = -g -Wall $(LIBS)

run-test: test
	./test

OBJS = BufferTest.o TestRunner.o

%.o: %.cpp
	echo CC $<
	${CXX} -c ${CXXFLAGS} $<

test: $(OBJS) ../Buffer.o
	$(CXX) $(OBJS) $(CXXFLAGS) -o test $(LIBS) ../Buffer.o


clean:
	rm -f *.o test
