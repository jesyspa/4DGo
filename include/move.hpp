#ifndef FDGO_INCLUDE_MOVE_HPP
#define FDGO_INCLUDE_MOVE_HPP

#include <QString>
#include <position.hpp>

namespace fdgo {

//! \brief Contains a full description of a single move.

class Move {
    public:
	enum MType {
		none,
		pass,
		play,
		remove,
		kill
	} type;
	Move(); 
	Move(Move const&); 
	Move(bool blck, Position const& ps, MType movetype);
	QString toString() const;
	bool black;
	Position pos;
};

}

#endif // Guard
