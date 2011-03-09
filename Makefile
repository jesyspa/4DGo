CXXFLAGS = -O0 -Wall -Wextra -pedantic -std=c++0x -Winline -Wwrite-strings -Weffc++ -Iinclude/
LFLAGS = -lboost_program_options -lboost_regex
CXX = g++

all: 4dgo

io.o : io.cpp include/io.hpp include/position.hpp include/goban.hpp
	$(CXX) $(CXXFLAGS) -c -o io.o io.cpp
goban.o : goban.cpp include/goban.hpp include/score.hpp include/position.hpp 
	$(CXX) $(CXXFLAGS) -c -o goban.o goban.cpp
position.o : position.cpp include/position.hpp 
	$(CXX) $(CXXFLAGS) -c -o position.o position.cpp
exception.o : exception.cpp include/exception.hpp 
	$(CXX) $(CXXFLAGS) -c -o exception.o exception.cpp
main.o : main.cpp include/io.hpp
	$(CXX) $(CXXFLAGS) -c -o main.o main.cpp
4dgo : io.o goban.o position.o main.o
	$(CXX) $(CXXFLAGS) -o 4dgo io.o goban.o position.o main.o  $(LFLAGS)

.PHONY: clean
clean:
	rm -f *.o 4dgo
