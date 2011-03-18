#ifndef FDGO_INCLUDE_SERVER_STONE_HPP
#define FDGO_INCLUDE_SERVER_STONE_HPP

#include <vector>
#include <server/chain.hpp>

namespace fdgo {
namespace server {

class Intersection;
class Chain;

class Stone {
	friend class Chain;
	// Explicitly forbidden
	Stone(Stone const&);
	Stone& operator=(Stone const&);
    public:
	typedef boost::shared_ptr<Stone> Pointer;

	Stone(Intersection* iPtr, bool black);
	~Stone();
    private:
	void connectToNeighbours();
	void connectTo(Intersection* p);
	bool isSameColour(Intersection* p);
	void increaseNeighbourLiberties();
	void giveLiberty(Intersection* p);
	void seeIfAnyoneIsDead();
	void getChain(std::vector<Chain::Pointer>& chvec, Intersection* p);
	Chain::Pointer chain_;
	Intersection* intrPtr_;
	int libs;
	const bool black_; // Otherwise white
};

}
}

#endif // Guard
