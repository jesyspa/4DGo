#include "netmove.hpp"
#include "move.hpp"

NetMove::NetMove() {
	for (int a = 0; a < 6; ++a)
		buf[a] = 0;
}

NetMove::NetMove(Move const& mv) {
	buf[0] = mv.type;
	for (int a = 0; a < 4; ++a)
		buf[a+1] = mv.pos[a];
	if (mv.black)
		buf[5] = 1;
	else
		buf[5] = 0;
}
