#ifndef FDGO_INCLUDE_MEMORY_HPP
#define FDGO_INCLUDE_MEMORY_HPP

#include <vector>
#include <string>
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
	void writeToDisk(std::string filename);
	Move::MType lastMoveType();
	Move popLastMove();
    private:
	int locked_;
	std::vector<Move> mvec_;
};

}

#endif // Guard

