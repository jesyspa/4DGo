#ifndef FDGO_INCLUDE_GOBAN_HPP
#define FDGO_INCLUDE_GOBAN_HPP

#include "position.hpp"
#include "score.hpp"

typedef unsigned int uint;

class Goban {
    public:
	Goban(uint boardsize);
	~Goban();
	void placeStone(bool black, Position pos);
	void killGroup(Position pos);
	Score makeScore();
	char getIcon(Position pos);
};

#endif // Guard
