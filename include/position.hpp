#ifndef FDGO_INCLUDE_POSITION_HPP
#define FDGO_INCLUDE_POSITION_HPP

typedef unsigned int uint;

struct Position {
	Position() : a(0), b(0), c(0), d(0) {}
	uint a, b, c, d;
};

#endif // Guard
