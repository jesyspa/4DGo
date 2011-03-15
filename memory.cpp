#include <iterator>
#include <fstream>
#include "memory.hpp"
#include "exception.hpp"

Memory::Memory() : locked_(0) {
}

Memory::~Memory() {
}

void Memory::placeStone(bool black, Position const& pos) {
	if (locked_) {
		return;
	}
	Move m(black, pos, Move::play);
	mvec_.push_back(m);
}

void Memory::removeStone(Position const& pos) {
	if (locked_) {
		return;
	}
	Move m(false, pos, Move::remove);
	mvec_.push_back(m);
}

void Memory::pass(bool black) {
	if (locked_) {
		return;
	}
	Move m(black, Position(), Move::pass);
	mvec_.push_back(m);
}

void Memory::writeToDisk(std::string filename) {
	std::ofstream log(filename.c_str());
	for (uint i = 0; i < mvec_.size(); ++i) {
		log << mvec_[i].toString() << "\n";
	}
}

Move::MType Memory::lastMoveType() {
	if (!mvec_.size()) 
		return Move::none;
	return mvec_.back().type;
}

Move Memory::popLastMove() {
	if (!mvec_.size())
		return Move();
	Move m = mvec_.back();
	mvec_.pop_back();
	return m;
}
