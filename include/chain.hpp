#ifndef FDGO_INCLUDE_CHAIN_HPP
#define FDGO_INCLUDE_CHAIN_HPP

#include <vector>

class Stone;

class Chain {
    private:
	// Should only ever be called internally.
	~Chain();
	// Should never be called.
	Chain(Chain const&); 
	Chain& operator=(Chain const&);
    public:
	Chain();
	Chain(Stone* st); // Create a chain from one stone.
	addStone(Stone* st);
	calcLiberties();
	joinWith(Chain* ch);
    private:
	std::vector<Stone*> stonevec_;
};

#endif // Guard
