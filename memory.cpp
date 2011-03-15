#include <iterator>
#include <fstream>
#include "memory.hpp"
#include "exception.hpp"


Memory::Memory() : recording(true) {
}

Memory::~Memory() {
#ifndef NDEBUG
	std::ofstream log("log.txt");
	for (uint i = 0; i < mvec_.size(); ++i) {
		log << mvec_[i].toString() << "\n";
	}
#endif
}

void Memory::placeStone(bool black, Position const& pos) {
	if (!recording)
		return;
	Move m(black, pos, Move::play);
	mvec_.push_back(m);
}

void Memory::removeStone(Position const& pos) {
	if (!recording)
		return;
	Move m(false, pos, Move::remove);
	mvec_.push_back(m);
}

void Memory::pass(bool black) {
	if (!recording)
		return;
	Move m(black, Position(), Move::pass);
	mvec_.push_back(m);
}

Move Memory::peekLastPlay() {
	std::vector<Move>::const_reverse_iterator it = mvec_.rbegin();
	while (it < mvec_.rend()) {
		if (it->type == Move::play)
			return *it;
	}
	return Move();
}

Move Memory::popLastMove() {
	Move m = mvec_.back();
	mvec_.pop_back();
	return m;
}
