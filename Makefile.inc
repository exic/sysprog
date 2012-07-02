CXX = g++
CXXFLAGS = -g -Wall -lpthread

AR = ar
ARFLAGS =
RANLIB = ranlib

OBJS = $(patsubst %.cpp, %.o, $(wildcard *.cpp))

# vim: set filetype=make : #
