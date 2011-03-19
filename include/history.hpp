#ifndef FDGO_INCLUDE_MEMORY_HPP
#define FDGO_INCLUDE_MEMORY_HPP

#include <vector>
#include <string>
#include <stack>
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
	History(); 
	~History();
	void placeStone(bool black, Position const& pos);
	void removeStone(Position const& pos);
	void pass(bool black);
	Move::MType lastMoveType();
	Move popLastMove();

	Move peekStack();
	bool unhandledMoves();
	void confirmTop();

	void writeToDisk(std::string filename);
    private:
	int locked_;
	std::vector<Move> mvec_;
	std::stack<Move> mstack_;
};

}

#endif // Guard

