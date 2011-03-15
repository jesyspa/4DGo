#include <vector>
#include "chain.hpp"
#include "stone.hpp"
#include "exception.hpp"

typedef unsigned int uint;

Chain::Chain(Stone* st) : black_(st->black_) {
	stonevec_.push_back(st);
	st->chain_ = this;
}

Chain::~Chain() {
	for (uint i = 0; i < stonevec_.size(); ++i) {
		delete stonevec_[i];
	}
}

void Chain::addStone(Stone* st) {
	stonevec_.push_back(st);
	st->chain_ = this;
}

bool Chain::checkLiberties() {
	for (uint i = 0; i < stonevec_.size(); ++i) {
		if (stonevec_[i]->libs)
			return true;
	}
	return false;
}

void Chain::joinWith(Chain* ch) {
	if (ch == this)
		return;
	int end = ch->stonevec_.size(); 
	for (int i = 0; i < end; ++i) {
		stonevec_.push_back(ch->stonevec_.back());
		ch->stonevec_.back()->chain_ = this;
		ch->stonevec_.pop_back();
	}
	delete ch;
}

void Chain::considerDying(bool forbid) {
	if (!checkLiberties()) {
		if (forbid)
			BOOST_THROW_EXCEPTION(ExcInvalidMove() << err_msg("This move is suicidal."));
		delete this;
	}
}
