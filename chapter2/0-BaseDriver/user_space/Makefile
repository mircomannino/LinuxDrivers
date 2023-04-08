CXX=g++
CXXFLAGS= -O3 -I./ -std=c++17

all: test

test: test.cpp
	$(CXX) $(CXXFLAGS) $< -o $@ 

clean:
	rm test