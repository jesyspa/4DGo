#include <iterator>
#include <fstream>
#include <history.hpp>
#include <position.hpp>
#include <move.hpp>
#include <exceptions.hpp>

namespace fdgo {

History::History() : locked_(0) {
}

History::~History() {
}

void History::placeStone(bool black, Position const& pos) {
	if (locked_) {
		return;
	}
	Move m(black, pos, Move::play);
	mvec_.push_back(m);
}

void History::removeStone(Position const& pos) {
	if (locked_) {
		return;
	}
	Move m(false, pos, Move::remove);
	mvec_.push_back(m);
}

void History::pass(bool black) {
	if (locked_) {
		return;
	}
	Move m(black, Position(), Move::pass);
	mvec_.push_back(m);
}

void History::writeToDisk(std::string filename) {
	std::ofstream log(filename.c_str());
	for (uint i = 0; i < mvec_.size(); ++i) {
		log << mvec_[i].toString() << "\n";
	}
}

Move::MType History::lastMoveType() {
	if (!mvec_.size()) 
		return Move::none;
	return mvec_.back().type;
}

Move History::popLastMove() {
	if (!mvec_.size())
		return Move();
	Move m = mvec_.back();
	mvec_.pop_back();
	return m;
}

}
