#include "goban.hpp"
#include "intersection.hpp"
#include "exception.hpp"
#include "neighbours.hpp"

Goban::Goban(uint boardsize) {
	boardsize_ = boardsize = 4; // Let's not get too complex yet.
	boardarea_ = boardsize_*boardsize_*boardsize_*boardsize_;
	iPtr_ = new Intersection[boardarea_];
}

Goban::~Goban() {
	delete[] iPtr_;
}

void Goban::placeStone(bool black, Position const& pos) {
	Intersection* wrkIntr = getIntersection(pos);
	if(wrkIntr->needNeighbours())
		wrkIntr->giveNeighbours(makeNeighbours(pos));
	wrkIntr->placeStone(black);
}

void Goban::killGroup(Position const& pos) {
	BOOST_THROW_EXCEPTION(ExcNotImplemented());
}

Score Goban::makeScore() {
	BOOST_THROW_EXCEPTION(ExcNotImplemented());
}

char Goban::getIcon(Position const& pos) {
	return getIntersection(pos)->getIcon();
}

Intersection* Goban::getIntersection(Position const& pos) {
	for (int a = 0; a < 4; ++a)
		if (pos[a] > 3)
			return 0;
	int i = pos[0]*boardsize_*boardsize_*boardsize_ +
	            pos[1]*boardsize_*boardsize_ +
	            pos[2]*boardsize_ +
	            pos[3];
	return iPtr_ + i;
}

Neighbours const* Goban::makeNeighbours(Position const& pos) {
	Neighbours* nbr = new Neighbours;
	nbr->up = getIntersection(pos.up());
	nbr->down = getIntersection(pos.down());
	nbr->left = getIntersection(pos.left());
	nbr->right = getIntersection(pos.right());
	nbr->farup = getIntersection(pos.farup());
	nbr->fardown = getIntersection(pos.fardown());
	nbr->farleft = getIntersection(pos.farleft());
	nbr->farright = getIntersection(pos.farright());
	return nbr;
}
