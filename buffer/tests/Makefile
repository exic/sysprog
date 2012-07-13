include ../../Makefile.inc

LIBS = -lgtest -lpthread
CXXFLAGS += $(LIBS)

OBJS = $(patsubst %.cpp, %.o, $(wildcard *.cpp)) $(wildcard ../*.o)

OUT = test-exec

run-test: $(OUT)
	@rm -f /tmp/buffertestfile /tmp/buffertestfile2
	@cp buffertestfile /tmp
	@./$(OUT)
	@rm -f /tmp/buffertestfile /tmp/buffertestfile2

$(OUT): $(OBJS)
	@$(CXX) $(OBJS) $(CXXFLAGS) -o $(OUT) $(LIBS)

include ../../Makefile.stdrules
