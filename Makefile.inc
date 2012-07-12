CXX = g++
# debug
CXXFLAGS = -O0 -g -Wall -lpthread
# shipping
# CXXFLAGS = -Wall -lpthread

AR = ar
RANLIB = ranlib

OBJS = $(patsubst %.cpp, %.o, $(wildcard *.cpp))

# vim: set filetype=make : #
