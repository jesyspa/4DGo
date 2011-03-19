#include <server/intersection.hpp>
#include <server/stone.hpp>
#include <server/neighbours.hpp>
#include <exceptions.hpp>

namespace fdgo {
namespace server {

Intersection::Intersection() : goban_(0), stone_(0) {
	
}

Intersection::~Intersection() {
	delete stone_;
}

void Intersection::placeStone(bool black) {
	if (stone_)
		BOOST_THROW_EXCEPTION(ExcInvalidMove() << err_msg("Intersection taken."));
	stone_ = new Stone(this, black);
}

bool Intersection::needNeighbours() {
	return !nbr_;
}

void Intersection::giveNeighbours(Neighbours::Pointer nbr) {
	nbr_ = nbr;
}

}
}
