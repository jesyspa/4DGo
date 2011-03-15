#ifndef FDGO_INCLUDE_MEMORY_HPP
#define FDGO_INCLUDE_MEMORY_HPP

#include <vector>
#include "move.hpp"

//! \brief Stores the moves made.

class Memory {
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
	Move peekLastPlay();
	Move popLastMove();
	bool recording;
    private:
	std::vector<Move> mvec_;
};

#endif // Guard

