#include <server/goban.hpp>
#include <server/intersection.hpp>
#include <server/stone.hpp>
#include <server/neighbours.hpp>
#include <history.hpp>
#include <histlock.hpp>
#include <move.hpp>
#include <score.hpp>
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
	Intersection* wrkIntr = getIntersection(pos);
	if (wrkIntr->stone_)
		if (wrkIntr->stone_->chain_)
			wrkIntr->stone_->chain_->die();
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
	Score sc;
	Intersection* intr;
	for (size_t a = 0; a < 4; ++a) {
		for (size_t b = 0; b < 4; ++b) {
			for (size_t c = 0; c < 4; ++c) {
				for (size_t d = 0; d < 4; ++d) {
					Position pos(a,b,c,d);
					intr = getIntersection(pos);
					if (intr->needNeighbours())
						intr->giveNeighbours(makeNeighbours(pos));
				}
			}
		}
	}
	for (size_t i = 0; i < 4*4*4*4; ++i) {
		if (intrArr_[i].stone_)
			intrArr_[i].stone_->libs = 13; // Makes the stone immortal.
	}
	for (size_t i = 0; i < 4*4*4*4; ++i) {
		if (intrArr_[i].stone_)
			intrArr_[i].stone_->spawnMore(); // Adds more stones around existing ones.
	}
	for (size_t i = 0; i < 4*4*4*4; ++i) {
		if (!intrArr_[i].stone_)
			continue;
		if (intrArr_[i].stone_->black_)
			sc.black++;
		else
			sc.white++;
	}
	return sc;
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
