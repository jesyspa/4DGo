#include <net/undo.hpp>
#include <exceptions.hpp>

using boost::asio::ip::tcp;

namespace fdgo {
namespace net {

Undo::Undo() {
	header_.type = Header::Undo;
}

Undo::Undo(Header const& header) : Object(header) {
	if (header_.type != Header::Undo)
		BOOST_THROW_EXCEPTION(ExcIncorrectNetObjectType());
}


void Undo::printOn(QDataStream&) const {
}

void Undo::readFrom(QDataStream&) {
}

}
}

