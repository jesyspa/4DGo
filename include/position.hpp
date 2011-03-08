#ifndef FDGO_INCLUDE_POSITION_HPP
#define FDGO_INCLUDE_POSITION_HPP

#include <string>

typedef unsigned int uint;

struct Position {
	Position();
	Position(std::string const& str);
	uint operator[](size_t i) const;

    private:
	uint arr[4];
};

#endif // Guard
