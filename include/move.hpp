#ifndef FDGO_INCLUDE_MOVE_HPP
#define FDGO_INCLUDE_MOVE_HPP

#include <string>

#include "position.hpp"

//! \brief Contains a full description of a single move.

class Move {
    public:
	enum MType {
		pass,
		play,
		remove,
		none
	} type;
	Move(); 
	Move(Move const&); 
	Move(bool blck, Position const& ps, MType movetype);
	std::string toString();
	bool black;
	Position pos;
};

#endif // Guard


