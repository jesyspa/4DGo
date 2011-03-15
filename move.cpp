#include <sstream>
#include "move.hpp"
#include "exception.hpp"

Move::Move() : type(pass), black(false), pos(0, 0, 0, 0) {
}

Move::Move(Move const& mov) : type(mov.type), black(mov.black), pos(mov.pos) {
}

Move::Move(bool blck, Position const& ps, MType movetype) : type(movetype), black(blck), pos(ps) {
}

std::string Move::toString() {
	std::stringstream ss;
	switch (type) {
		case play:
			ss << (black ? "B" : "W");
			ss << " ";
			ss << pos.toString();
			break;
		case remove:
			ss << "R ";
			ss << pos.toString();
			break;
		case pass:
			ss << (black ? "B" : "W");
			ss << " PASS";
			break;
	}
	return ss.str();
}
