#ifndef FDGO_INCLUDE_CHAIN_INTERSECTION_HPP
#define FDGO_INCLUDE_CHAIN_INTERSECTION_HPP

#include <server/neighbours.hpp>

namespace fdgo {
namespace server {

class Goban;
class Stone;

//! \brief Represents a single intersection on the goban.
//!
//! Created to have a persistent ground between the goban and the stones.
//! Stones should clean up after themselves,

class Intersection {
	friend class Stone;
	friend class ScoreStone;
	friend class Goban;
	
	// Explicitly forbidden
	Intersection(Intersection const&);
	Intersection& operator=(Intersection const&);
  public:
	Intersection();
	~Intersection();

	void placeStone(bool black);
	void removeStone();
	char getIcon();
	bool needNeighbours();
	void giveNeighbours(const Neighbours::Pointer nbr);
  private:
	Goban* goban_;
	Stone* stone_;
	Neighbours::Pointer nbr_;
};

}
}

#endif // Guard
