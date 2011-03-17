#ifndef FDGO_INCLUDE_FAKEGOBAN_HPP
#define FDGO_INCLUDE_FAKEGOBAN_HPP

#include "score.hpp"

class Intersection;
struct Position;

typedef unsigned int uint;

//! \brief Visual goban -- stores the stones, but doesn't do anything with them.

class FakeGoban {
	// Explicitly forbidden
	FakeGoban(FakeGoban const&);
	FakeGoban& operator=(FakeGoban const&);
    public:
	FakeGoban(uint boardsize, Memory& mem);
	~FakeGoban();
	void placeStone(bool black, Position const& pos);
	void removeStone(Position const& pos);
	void incrementPrisonerCount(bool black);
	Score makeScore();
	char getIcon(Position const& pos);
    private:
	char* getFakeIntersection(Position const& pos);
	char* iPtr_;
	uint boardsize_;
	uint boardarea_;
	uint blackPrisoners_;
	uint whitePrisoners_;
};

#endif // Guard
