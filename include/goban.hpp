#ifndef FDGO_INCLUDE_GOBAN_HPP
#define FDGO_INCLUDE_GOBAN_HPP

#include "position.hpp"
#include "score.hpp"
#include "neighbours.hpp"

class Intersection;
class Memory;

typedef unsigned int uint;

//! \brief Interface to work with the goban.

class Goban {
	// Explicitly forbidden
	Goban(Goban const&);
	Goban& operator=(Goban const&);
    public:
	Goban(uint boardsize, Memory& mem);
	~Goban();
	void placeStone(bool black, Position const& pos);
	void removeStone(Position const& pos);
	void killGroup(Position const& pos);
	void undo();
	void noteStoneRemoval(Intersection* itr, bool black);
	Score makeScore();
	char getIcon(Position const& pos);
    private:
	Intersection* getIntersection(Position const& pos);
	Position getPosition(Intersection* itr);
	Neighbours const* makeNeighbours(Position const& pos);
	Intersection* iPtr_;
	uint boardsize_;
	uint boardarea_;
	uint blackPrisoners_;
	uint whitePrisoners_;
	Memory& mem_;
};

#endif // Guard
