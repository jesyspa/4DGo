#ifndef FDGO_INCLUDE_INTERSECTION_HPP
#define FDGO_INCLUDE_INTERSECTION_HPP

#include "neighbours.hpp"

class Stone;
class Goban;

//! \brief Represents a single intersection on the goban.
//!
//! Created to have a persistent ground between the goban and the stones.
//! Stones should clean up after themselves,

class Intersection {
	friend class Stone;
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
	void giveNeighbours(Neighbours const* nbr);
    private:
	Goban* goban_;
	Stone* stone_;
	Neighbours const* nbr_;
};

#endif // Guard
