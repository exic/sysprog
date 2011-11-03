CXX = g++
CXXFLAGS = -g -Wall

OBJS = $(patsubst %.cpp, %.o, $(wildcard *.cpp))

test: $(OBJS)
	cd tests && make

clean:
	rm -f $(OBJS) $(OUT)
	[ -d tests ] && ( cd tests && make clean ) || true

%.o: %.cpp
	echo CC $<
	${CXX} -c ${CXXFLAGS} $<

# vim: set filetype=make : #
