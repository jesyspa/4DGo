#include <QList>
#include <server/chain.hpp>
#include <server/stone.hpp>
#include <exceptions.hpp>

namespace fdgo {
namespace server {

Chain::Chain(Stone* st) : black_(st->black_) {
	stoneli_.push_back(st);
}

Chain::~Chain() {}

void Chain::addStone(Stone* st) {
	stoneli_.push_back(st);
	st->chain_ = this;
}

void Chain::removeStone(Stone* st) {
	for (int i = 0; i < stoneli_.size(); ++i) {
		if (stoneli_[i] == st) {
			stoneli_.removeAt(i);
			return;
		}
	}
}

bool Chain::checkLiberties() {
	for (int i = 0; i < stoneli_.size(); ++i) {
		if (stoneli_[i]->libs)
			return true;
	}
	return false;
}

void Chain::joinWith(Chain* ch) {
	if (ch == this)
		return;
	while(!ch->stoneli_.empty()) {
		stoneli_.push_back(ch->stoneli_.back());
		ch->stoneli_.pop_back();
		stoneli_.back()->chain_ = this;
	}
	delete ch;
}

void Chain::considerDying(bool forbid) {
	if (!checkLiberties()) {
		if (forbid)
			BOOST_THROW_EXCEPTION(ExcInvalidMove() << err_msg("This move is suicidal."));
		die();
	}
}

void Chain::die() {
	while (!stoneli_.isEmpty())
		delete stoneli_.takeFirst();
	delete this;
}

}
}
