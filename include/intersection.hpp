#ifndef FDGO_INCLUDE_INTERSECTION_HPP
#define FDGO_INCLUDE_INTERSECTION_HPP

#include "neighbours.hpp"

class Stone;

class Intersection {
	friend class Stone;
	
	// Explicitly forbidden
	Intersection(Intersection const&) { throw; }
	Intersection& operator=(Intersection const&) { throw; }
    public:
	Intersection();
	~Intersection();

	void placeStone(bool black);
	char getIcon();
	bool needNeighbours();
	void giveNeighbours(Neighbours const* nbr);
    private:
	Stone* stone_;
	Neighbours const* nbr_;
};

#endif // Guard
