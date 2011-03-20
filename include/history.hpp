#ifndef FDGO_INCLUDE_MEMORY_HPP
#define FDGO_INCLUDE_MEMORY_HPP

#include <vector>
#include <string>
#include <stack>
#include <boost/shared_ptr.hpp>
#include <move.hpp>

namespace fdgo {

class MemLock;

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
	void addNull();
	Move::MType lastMoveType();
	Move popLastMove();

	Move peekStack();
	bool unhandledMoves();
	void confirmTop();

	void writeToDisk(std::string filename);
    private:
	void push(Move const& mv);
	int locked_;
	bool useStack_;
	std::vector<Move> mvec_;
	std::stack<Move> mstack_;
};

}

#endif // Guard

