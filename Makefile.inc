CXX = g++
CXXFLAGS = -g -Wall

OBJS = $(patsubst %.cpp, %.o, $(wildcard *.cpp))

# vim: set filetype=make : #
