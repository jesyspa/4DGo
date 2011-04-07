#ifndef FDGO_INCLUDE_SERVER_GOBAN_HPP
#define FDGO_INCLUDE_SERVER_GOBAN_HPP

#include <boost/array.hpp>
#include <server/intersection.hpp>
#include <server/neighbours.hpp>
#include <score.hpp>
#include <position.hpp>

namespace fdgo {
class History;

namespace server {

class Intersection;

//! \brief Interface to work with the goban.
//!
//! All game logic is done through here.

class Goban {
	// Explicitly forbidden
	Goban(Goban const&);
	Goban& operator=(Goban const&);
  public:
	Goban(History& mem);
	~Goban();
	void placeStone(bool black, Position const& pos);
	void removeStone(Position const& pos);
	void killGroup(Position const& pos);
	void noteStoneRemoval(Intersection* itr, bool black);
	//! \brief Calculates and returns the score.
	//!
	//! At the moment, this leads to severe changes in the board position, and
	//! it becomes impossible to play any further.
	Score makeScore(); 

  private:
	Intersection* getIntersection(Position const& pos);
	Position getPosition(Intersection* itr);
	Neighbours::Pointer makeNeighbours(Position const& pos);

	static const unsigned int boardarea_ = 4*4*4*4;
	boost::array<Intersection, boardarea_> intrArr_;

	unsigned int blackPrisoners_;
	unsigned int whitePrisoners_;
	History& hist_;
};

}
}

#endif // Guard
