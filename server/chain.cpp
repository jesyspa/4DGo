#include <vector>
#include <iterator>
#include <server/chain.hpp>
#include <server/stone.hpp>
#include <exceptions.hpp>

typedef unsigned int uint;

namespace fdgo {
namespace server {

Chain::Chain(Stone* st) : black_(st->black_) {
	stonevec_.push_back(st);
	st->chain_.reset(this);
}

void Chain::addStone(Stone* st) {
	stonevec_.push_back(st);
	st->chain_.reset(this);
}

void Chain::removeStone(Stone* st) {
	std::vector<Stone*>::iterator it = stonevec_.begin();
	while (it != stonevec_.end()) {
		if (*it == st) {
			stonevec_.erase(it);
			break;
		}
	}
}

bool Chain::checkLiberties() {
	for (uint i = 0; i < stonevec_.size(); ++i) {
		if (stonevec_[i]->libs)
			return true;
	}
	return false;
}

void Chain::joinWith(Chain::Pointer ch) {
	if (ch.get() == this)
		return;
	int end = ch->stonevec_.size(); 
	for (int i = 0; i < end; ++i) {
		stonevec_.push_back(ch->stonevec_.back());
		ch->stonevec_.back()->chain_.reset(this);
		ch->stonevec_.pop_back();
	}
}

void Chain::considerDying(bool forbid) {
	if (!checkLiberties()) {
		if (forbid)
			BOOST_THROW_EXCEPTION(ExcInvalidMove() << err_msg("This move is suicidal."));
		die();
	}
}

void Chain::die() {
	for (uint i = 0; i < stonevec_.size(); ++i) {
		delete stonevec_[i];
	}
}

}
}
