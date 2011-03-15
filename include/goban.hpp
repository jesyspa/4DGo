#ifndef FDGO_INCLUDE_GOBAN_HPP
#define FDGO_INCLUDE_GOBAN_HPP

#include "position.hpp"
#include "score.hpp"
#include "neighbours.hpp"
#include "memory.hpp"

class Intersection;

typedef unsigned int uint;

//! \brief Interface to work with the goban.

class Goban {
	// Explicitly forbidden
	Goban(Goban const&);
	Goban& operator=(Goban const&);
    public:
	Goban(uint boardsize = 4);
	~Goban();
	void placeStone(bool black, Position const& pos);
	void killGroup(Position const& pos);
	void noteStoneRemoval(Intersection* itr);
	void pass(bool black);
	Score makeScore();
	char getIcon(Position const& pos);
    private:
	Intersection* getIntersection(Position const& pos);
	Position getPosition(Intersection* itr);
	Neighbours const* makeNeighbours(Position const& pos);
	Intersection* iPtr_;
	uint boardsize_;
	uint boardarea_;
	Memory mem_;
};

#endif // Guard
