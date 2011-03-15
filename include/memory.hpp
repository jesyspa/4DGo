#ifndef FDGO_INCLUDE_MEMORY_HPP
#define FDGO_INCLUDE_MEMORY_HPP

#include <vector>
#include <string>
#include "move.hpp"

class MemLock;

//! \brief Stores the moves made.

class Memory {
	friend class MemLock;
    private:
	// Should never be called.
	Memory(Memory const&); 
	Memory& operator=(Memory const&);
    public:
	Memory(); 
	~Memory();
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

#endif // Guard

