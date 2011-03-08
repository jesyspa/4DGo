#ifndef FDGO_INCLUDE_CHAIN_HPP
#define FDGO_INCLUDE_CHAIN_HPP
class Stone;

class Chain {
    private:
	// Should only ever be called internally.
	~Chain();
    public:
	Chain();
	Chain(Chain& ch);
	Chain(Stone* st); // Create a chain from one stone.
	addStone(Stone& st);
	calcLiberties();
	joinWith(Chain& ch);
};

#endif // Guard
