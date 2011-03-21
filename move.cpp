#include <move.hpp>
#include <exceptions.hpp>

namespace fdgo {

Move::Move() : type(none), black(false), pos(0, 0, 0, 0) {
}

Move::Move(Move const& mov) : type(mov.type), black(mov.black), pos(mov.pos) {
}

Move::Move(bool blck, Position const& ps, MType movetype) : type(movetype), black(blck), pos(ps) {
}

QString Move::toString() const {
	QString s;
	switch (type) {
		case play:
			s = (black ? "B" : "W");
			s += " ";
			s += pos.toString();
			s += '\n';
			break;
		case remove:
			s = "R ";
			s += pos.toString();
			s += '\n';
			break;
		case pass:
			s = (black ? "B" : "W");
			s += " PASS\n";
			break;
		case none:
		case kill:
			break;
		default:
			s = "Unknown move\n";
	}
	return s;
}

}
