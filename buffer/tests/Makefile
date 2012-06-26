include ../../Makefile.inc

LIBS = -lgtest -lpthread
CXXFLAGS += $(LIBS)

OBJS = $(patsubst %.cpp, %.o, $(wildcard *.cpp)) $(wildcard ../*.o)

OUT = test-exec

run-test: $(OUT)
	@cp buffertestfile /tmp
	@./$(OUT)
	@rm -f /tmp/buffertestfile

$(OUT): $(OBJS) ../Buffer.o
	@$(CXX) $(OBJS) $(CXXFLAGS) -o $(OUT) $(LIBS)

include ../../Makefile.stdrules
