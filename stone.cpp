#include "stone.hpp"
#include "intersection.hpp"
#include "exception.hpp"

Stone::Stone(Intersection* iPtr, bool black) : iPtr_(iPtr), black_(black) {
	icon_ = black ? 'X' : 'O';
	
}

Stone::~Stone() {
}

char Stone::getIcon() {
	return icon_;
}
