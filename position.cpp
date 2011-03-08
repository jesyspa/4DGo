#include <string>
#include "position.hpp"

Position::Position() {
	for (int a = 0; a < 4; ++a)
		arr[a] = 0;
}

Position::Position(std::string const& str) {
	if (str.size() < 4) {
		throw 'e'; // Illegal length.
	}
}

uint Position::operator[](size_t i) const {
	if (i > 3)
		return 0;
	else
		return arr[i];
}
