#ifndef FDGO_INCLUDE_HISTORY_HPP
#define FDGO_INCLUDE_HISTORY_HPP

#include <boost/shared_ptr.hpp>
#include <QList>
#include <QStack>
#include <move.hpp>

namespace fdgo {

//! \brief Stores the moves made.

class History {
	friend class HistLock;
  private:
	// Should never be called.
	History(History const&); 
	History& operator=(History const&);
  public:
	typedef boost::shared_ptr<History> Pointer;
	History(bool useStack = true); 
	~History();
	void placeStone(bool black, Position const& pos);
	void removeStone(bool black, Position const& pos);
	void pass(bool black);
	void kill(Position const& pos);
	void addNull();
	Move popLastMove();
	int seekLastTurn();
	Move remove(int i);
	Move::MType getType(int i);
	void clear();

	Move peekStack();
	bool unhandledMoves();
	void confirmTop();

	void writeToDisk(QString const& filename);
  private:
	void push(Move const& mv);
	int locked_;
	bool useStack_;
	QList<Move> mlist_;
	QStack<Move> mstack_;
};

}

#endif // Guard

