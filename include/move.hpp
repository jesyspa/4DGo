#ifndef FDGO_INCLUDE_MOVE_HPP
#define FDGO_INCLUDE_MOVE_HPP

#include <string>
#include "position.hpp"

class NetMove;

//! \brief Contains a full description of a single move.

class Move {
    public:
	enum MType {
		none,
		pass,
		play,
		remove
	} type;
	Move(); 
	Move(Move const&); 
	Move(NetMove const&);
	Move(bool blck, Position const& ps, MType movetype);
	std::string toString();
	bool black;
	Position pos;
};

#endif // Guard


