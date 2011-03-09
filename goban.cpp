#include "goban.hpp"
#include "exception.hpp"

Goban::~Goban() {

}

void Goban::placeStone(bool black, Position pos) {
	BOOST_THROW_EXCEPTION(ExcNotImplemented());
}

void Goban::killGroup(Position pos) {
	BOOST_THROW_EXCEPTION(ExcNotImplemented());
}

Score Goban::makeScore() {
	BOOST_THROW_EXCEPTION(ExcNotImplemented());
}

char Goban::getIcon(Position pos) {
	BOOST_THROW_EXCEPTION(ExcNotImplemented());
}

