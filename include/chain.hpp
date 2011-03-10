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
	Chain(Stone* st); // Create a chain from one stone.
	void addStone(Stone* st);
	bool checkLiberties();
	void joinWith(Chain* ch);
	void considerDying(); // DANGER! May cause object to poof!
    private:
	bool const black_;
	std::vector<Stone*> stonevec_;
};

#endif // Guard
