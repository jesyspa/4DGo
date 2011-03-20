#include <iterator>
#include <fstream>
#include <history.hpp>
#include <position.hpp>
#include <move.hpp>
#include <exceptions.hpp>

namespace fdgo {

History::History(bool useStack) : locked_(0), useStack_(useStack) {
}

History::~History() {
}

void History::placeStone(bool black, Position const& pos) {
	push(Move(black, pos, Move::play));
}

void History::removeStone(bool black, Position const& pos) {
	push(Move(black, pos, Move::remove));
}

void History::pass(bool black) {
	push(Move(black, Position(), Move::pass));
}

void History::addNull() {
	push(Move(false, Position(), Move::none));
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

Move History::peekStack() {
	return mstack_.top();
}

bool History::unhandledMoves() {
	return !mstack_.empty();
}

void History::confirmTop() {
	mvec_.push_back(mstack_.top());
	mstack_.pop();
}

void History::push(Move const& mv) {
	if (locked_)
		return;
	if (useStack_)
		mstack_.push(mv);
	else
		mvec_.push_back(mv);
}

}
