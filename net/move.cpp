#include <QDataStream>
#include <net/move.hpp>
#include <move.hpp>

namespace fdgo {
namespace net {

Move::Move() {
	header_.type = Header::Move;
}

Move::Move(fdgo::Move const& mv) {
	header_.type = Header::Move;
	this->mv = mv;
}

Move::Move(Header const& header) : Object(header) {
	if (header_.type != Header::Move)
		BOOST_THROW_EXCEPTION(ExcIncorrectNetObjectType());
}

void Move::printOn(QDataStream& ds) const {
	ds << mv.black;
	ds << mv.pos[0] << mv.pos[1] << mv.pos[2] << mv.pos[3];
	ds << (qint32) mv.type;
}

void Move::readFrom(QDataStream& ds) {
	qint32 tmp;
	ds >> mv.black;
	ds >> mv.pos[0] >> mv.pos[1] >> mv.pos[2] >> mv.pos[3];
	ds >> tmp;
	mv.type = fdgo::Move::MType(tmp);
}

}
}
