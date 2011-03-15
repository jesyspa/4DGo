#include "goban.hpp"
#include "memory.hpp"
#include "intersection.hpp"
#include "stone.hpp"
#include "memlock.hpp"
#include "move.hpp"
#include "exception.hpp"
#include "neighbours.hpp"

Goban::Goban(uint boardsize, Memory& mem) : blackPrisoners_(0), whitePrisoners_(0), mem_(mem) {
	boardsize_ = boardsize = 4; // Let's not get too complex yet.
	boardarea_ = boardsize_*boardsize_*boardsize_*boardsize_;
	iPtr_ = new Intersection[boardarea_];
	for (uint i = 0; i < boardarea_; ++i)
		iPtr_[i].goban_ = this;
}

Goban::~Goban() {
	delete[] iPtr_;
}

void Goban::placeStone(bool black, Position const& pos) {
	Intersection* wrkIntr = getIntersection(pos);
	if(wrkIntr->needNeighbours())
		wrkIntr->giveNeighbours(makeNeighbours(pos));
	wrkIntr->placeStone(black);
	mem_.placeStone(black, pos);
}

void Goban::killGroup(Position const& pos) {
	BOOST_THROW_EXCEPTION(ExcNotImplemented());
}

void Goban::removeStone(Position const& pos) {
	delete getIntersection(pos)->stone_;
}

void Goban::undo() {
	MemLock mlock(mem_);
	Move lastmove = mem_.popLastMove();
	if (lastmove.type != Move::play)
		throw ExcNothingToUndo();
	removeStone(lastmove.pos);
	while (mem_.lastMoveType() == Move::remove) {
		lastmove = mem_.popLastMove();
		placeStone(!lastmove.black, lastmove.pos);
	}
}

void Goban::noteStoneRemoval(Intersection* itr, bool black) {
	mem_.removeStone(getPosition(itr));
	if (black)
		blackPrisoners_++;
	else
		whitePrisoners_++;
}

Score Goban::makeScore() {
	BOOST_THROW_EXCEPTION(ExcNotImplemented());
}

char Goban::getIcon(Position const& pos) {
	return getIntersection(pos)->getIcon();
}

Intersection* Goban::getIntersection(Position const& pos) {
	for (int a = 0; a < 4; ++a)
		if (pos[a] > 3)
			return 0;
	int i = pos[0]*boardsize_*boardsize_*boardsize_ +
	            pos[1]*boardsize_*boardsize_ +
	            pos[2]*boardsize_ +
	            pos[3];
	return iPtr_ + i;
}

Position Goban::getPosition(Intersection* itr) {
	int i = itr - iPtr_;
	Position pos;
	for (int j = 3; j >= 0; --j) {
		pos[j] = i % boardsize_;
		i /= boardsize_;
	}
	return pos;
}

Neighbours const* Goban::makeNeighbours(Position const& pos) {
	Neighbours* nbr = new Neighbours;
	nbr->up = getIntersection(pos.up());
	nbr->down = getIntersection(pos.down());
	nbr->left = getIntersection(pos.left());
	nbr->right = getIntersection(pos.right());
	nbr->farup = getIntersection(pos.farup());
	nbr->fardown = getIntersection(pos.fardown());
	nbr->farleft = getIntersection(pos.farleft());
	nbr->farright = getIntersection(pos.farright());
	return nbr;
}
