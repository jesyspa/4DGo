#include <net/undo.hpp>
#include <exceptions.hpp>

using boost::asio::ip::tcp;

namespace fdgo {
namespace net {

Undo::Undo() {
	header_.setType(Header::Undo);
	header_.setLength(0);
}

Undo::Undo(Header const& header) : Object(header) {
	if (header_.getType() != Header::Undo)
		BOOST_THROW_EXCEPTION(ExcIncorrectNetObjectType());
}

void Undo::write(tcp::socket& sock) {
	header_.write(sock);
}

void Undo::read(tcp::socket&) {
}

}
}

