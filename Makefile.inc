CXX = g++
CXXFLAGS = -g -Wall

AR = ar
ARFLAGS =
RANLIB = ranlib

OBJS = $(patsubst %.cpp, %.o, $(wildcard *.cpp))

# vim: set filetype=make : #
