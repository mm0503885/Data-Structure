CXX=g++
SRC=$(wildcard *.cpp)
objects = $(patsubst %.cpp,%,$(SRC))

.PHONY: all 

all : $(objects)

%: %.cpp
	$(CXX) $< -o $@ 