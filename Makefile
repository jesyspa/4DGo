CXXFLAGS = -O0 -Wall -Wextra -pedantic -std=c++0x -Winline -Wwrite-strings -Weffc++ -Iinclude/
CXX = g++

all: 

io.o : io.cpp include/io.hpp include/position.hpp include/goban.hpp
	$(CXX) $(CXXFLAGS) -c -o io.o io.cpp
position.o : position.cpp include/position.hpp 
	$(CXX) $(CXXFLAGS) -c -o position.o position.cpp

.PHONY: clean
clean:
	rm -f *.o
