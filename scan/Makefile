include ../Makefile.inc

OUTLIB = ../libscan.a

all: $(OBJS) test $(OUTLIB)

Automat.o: Automat.hpp Status.hpp TType.hpp Constants.hpp

TType.hpp: mkenums
Status.hpp: mkenums
	./mkenums

include ../Makefile.stdrules
