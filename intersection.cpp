#include "intersection.hpp"
#include "exception.hpp"
#include "neighbours.hpp"
#include "stone.hpp"

Intersection::Intersection() : stone_(0), nbr_(0) {
	
}

Intersection::~Intersection() {
	delete stone_;
	delete nbr_;
}

void Intersection::placeStone(bool black) {
	if (stone_)
		BOOST_THROW_EXCEPTION(ExcInvalidMove() << err_msg("Intersection taken."));
	stone_ = new Stone(this, black);
}

char Intersection::getIcon() {
	if (stone_)
		return stone_->getIcon();
	else
		return '.';
}

bool Intersection::needNeighbours() {
	return !nbr_;
}

void Intersection::giveNeighbours(Neighbours const* nbr) {
	nbr_ = nbr;
}
