#include <fstream>
#include <QString>
#include <QList>
#include <QFile>
#include <QTextStream>
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

void History::kill(Position const& pos) {
	push(Move(true, pos, Move::kill));
}

void History::addNull() {
	push(Move(false, Position(), Move::none));
}

void History::writeToDisk(QString const& filename) {
	QFile log(filename);
	if (!log.open(QIODevice::WriteOnly | QIODevice::Text))
	         return;
	QTextStream out(&log);
	for (int i = 0; i < mlist_.size(); ++i) {
		out << mlist_[i].toString();
	}
	log.flush();
}

Move History::popLastMove() {
	if (mlist_.empty()) 
		return Move();
	Move mv = mlist_.back();
	mlist_.pop_back();
	return mv;
}

int History::seekLastTurn() {
	for (int i = mlist_.size() - 1; i >= 0; --i) {
		if (mlist_[i].type == Move::none)
			return i;
	}
	return -1;
}

Move History::remove(int i) {
	if (i >= mlist_.size() || i < 0)
		return Move();
	Move tmp = mlist_[i];
	mlist_.removeAt(i);
	return tmp;
}

Move::MType History::getType(int i) {
	if (i >= mlist_.size() || i < 0)
		return Move::none;
	return mlist_[i].type;
}

void History::clear() {
	mlist_.erase(mlist_.begin(), mlist_.end());
	mstack_.erase(mstack_.begin(), mstack_.end());
}

Move History::peekStack() {
	if (mstack_.empty())
		return Move();
	return mstack_.top();
}

bool History::unhandledMoves() {
	return !mstack_.empty();
}

void History::confirmTop() {
	mlist_.push_back(mstack_.top());
	mstack_.pop();
}

void History::push(Move const& mv) {
	if (locked_)
		return;
	if (useStack_)
		mstack_.push(mv);
	else
		mlist_.push_back(mv);
}

}
