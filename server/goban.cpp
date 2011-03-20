#include <server/goban.hpp>
#include <server/intersection.hpp>
#include <server/stone.hpp>
#include <server/neighbours.hpp>
#include <history.hpp>
#include <histlock.hpp>
#include <move.hpp>
#include <exceptions.hpp>

namespace fdgo {
namespace server {

Goban::Goban(History& mem) : blackPrisoners_(0), whitePrisoners_(0), hist_(mem) {
	for (unsigned int i = 0; i < boardarea_; ++i)
		intrArr_[i].goban_ = this;
}

Goban::~Goban() {
}

void Goban::placeStone(bool black, Position const& pos) {
	Intersection* wrkIntr = getIntersection(pos);
	if(wrkIntr->needNeighbours())
		wrkIntr->giveNeighbours(makeNeighbours(pos));
	wrkIntr->placeStone(black);
	hist_.placeStone(black, pos);
}

void Goban::killGroup(Position const& pos) {
	BOOST_THROW_EXCEPTION(ExcNotImplemented());
}

void Goban::removeStone(Position const& pos) {
	Intersection* wrkIntr = getIntersection(pos);
	if (!wrkIntr)
		BOOST_THROW_EXCEPTION(ExcInvalidPos());
	if (wrkIntr->stone_)
		delete wrkIntr->stone_;
	else
		BOOST_THROW_EXCEPTION(ExcNoStonePresent());
}

void Goban::noteStoneRemoval(Intersection* itr, bool black) {
	hist_.removeStone(black, getPosition(itr));
	if (black)
		blackPrisoners_++;
	else
		whitePrisoners_++;
}

Score Goban::makeScore() {
	BOOST_THROW_EXCEPTION(ExcNotImplemented());
}

Intersection* Goban::getIntersection(Position const& pos) {
	for (int a = 0; a < 4; ++a)
		if (pos[a] > 3)
			return 0;
	int i = pos[0]*4*4*4 +
	            pos[1]*4*4 +
	            pos[2]*4 +
	            pos[3];
	return &intrArr_[i];
}

Position Goban::getPosition(Intersection* itr) {
	int i = itr - &intrArr_[0];
	Position pos;
	for (int j = 3; j >= 0; --j) {
		pos[j] = i % 4;
		i /= 4;
	}
	return pos;
}

Neighbours::Pointer Goban::makeNeighbours(Position const& pos) {
	return Neighbours::Pointer(new Neighbours(
		getIntersection(pos.up()),
		getIntersection(pos.down()),
		getIntersection(pos.left()),
		getIntersection(pos.right()),
		getIntersection(pos.farup()),
		getIntersection(pos.fardown()),
		getIntersection(pos.farleft()),
		getIntersection(pos.farright())
	));
}

}
}
