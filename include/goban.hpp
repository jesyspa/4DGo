#ifndef FDGO_INCLUDE_GOBAN_HPP
#define FDGO_INCLUDE_GOBAN_HPP

#include "position.hpp"
#include "score.hpp"
#include "neighbours.hpp"

class Intersection;

typedef unsigned int uint;

class Goban {
	// Explicitly forbidden
	Goban(Goban const&);
	Goban& operator=(Goban const&);
    public:
	Goban(uint boardsize = 4);
	~Goban();
	void placeStone(bool black, Position const& pos);
	void killGroup(Position const& pos);
	Score makeScore();
	char getIcon(Position const& pos);
    private:
	Intersection* getIntersection(Position const& pos);
	Neighbours const* makeNeighbours(Position const& pos);
	Intersection* iPtr_;
	uint boardsize_;
	uint boardarea_;
};

#endif // Guard
