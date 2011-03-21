#include <net/turn.hpp>
#include <exceptions.hpp>

namespace fdgo {
namespace net {

Turn::Turn() {
	header_.type = Header::Turn;
}

Turn::Turn(bool black) {
	header_.type = Header::Turn;
	this->black = black;
}

Turn::Turn(Header const& header) : Object(header) {
	if (header_.type != Header::Turn)
		BOOST_THROW_EXCEPTION(ExcIncorrectNetObjectType());
}

void Turn::printOn(QDataStream& ds) const {
	ds << black;
}

void Turn::readFrom(QDataStream& ds) {
	ds >> black;
}

}
}
