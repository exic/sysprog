CXX = g++
INCLUDES = -I/usr/include/cppunit
LIBS = -lcppunit
CXXFLAGS = -g -Wall $(INCLUDES) $(LIBS)

run-test: test
	./test

test: BufferTest.o
	$(CXX) $(CXXFLAGS) -o test TestResult.cpp BufferTest.o ../Buffer.o

BufferTest.o: BufferTest.cpp BufferTest.hpp
	$(CXX) $(CXXFLAGS) -c BufferTest.cpp

clean:
	rm *.o test
