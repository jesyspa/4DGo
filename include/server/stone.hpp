#ifndef FDGO_INCLUDE_SERVER_STONE_HPP
#define FDGO_INCLUDE_SERVER_STONE_HPP

#include <QList>
#include <server/chain.hpp>

namespace fdgo {
namespace server {

class Intersection;
class Chain;

//! \brief Represents a stone on the goban.
//!
//! Tricky class, seeing as it is responsible for a lot of the game mechanics.
//! Splitting the liberty logic off to something else would be nice, but for
//! now, the stones have to do all checks in relation to what the chains are,
//! and whether they are alive or not.

class Stone {
	friend class Goban;
	friend class Chain;
	// Explicitly forbidden
	Stone(Stone const&);
	Stone& operator=(Stone const&);
  public:
	Stone(Intersection* iPtr, bool black);
	~Stone();

  private:
	void connectToNeighbours();
	void connectTo(Intersection* p);
	bool isSameColour(Intersection* p);
	void increaseNeighbourLiberties();
	void giveLiberty(Intersection* p);
	void seeIfAnyoneIsDead();
	void getChain(QList<Chain*>& chvec, Intersection* p);
	void spawnMore();
	void spawn(Intersection* p);

	Chain* chain_;
	Intersection* intrPtr_;
	const bool black_; // Otherwise white
	int libs;
};

}
}

#endif // Guard
