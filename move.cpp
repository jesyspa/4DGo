#include <sstream>
#include "move.hpp"
#include "netmove.hpp"
#include "exception.hpp"

Move::Move() : type(pass), black(false), pos(0, 0, 0, 0) {
}

Move::Move(Move const& mov) : type(mov.type), black(mov.black), pos(mov.pos) {
}

Move::Move(NetMove const& nm ) {
	type = static_cast<Move::MType> (nm.buf[0]);
	for (int i = 0; i < 4; ++i)
		pos[i] = nm.buf[i+1];
	if (nm.buf[5])
		black = true;
	else
		black = false;
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
		case quit:
			ss << "END";
			break;
		default:
			ss << "Unknown move";
	}
	return ss.str();
}
