#ifndef FDGO_INCLUDE_STONE_HPP
#define FDGO_INCLUDE_STONE_HPP

#include <vector>

class Chain;
class Intersection;

class Stone {
	friend class Chain;
	// Explicitly forbidden
	Stone(Stone const&);
	Stone& operator=(Stone const&);
    public:
	Stone(Intersection* iPtr, bool black);
	~Stone();
	char getIcon();
    private:
	void connectToNeighbours();
	void connectTo(Intersection* p);
	bool isSameColour(Intersection* p);
	void increaseNeighbourLiberties();
	void giveLiberty(Intersection* p);
	void seeIfAnyoneIsDead();
	void getChain(std::vector<Chain*>& chvec, Intersection* p);
	Chain* chain_;
	Intersection* iPtr_;
	char icon_;
	int libs;
	const bool black_; // Otherwise white
};

#endif // Guard

