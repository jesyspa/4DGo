#include <net/close.hpp>
#include <exceptions.hpp>

using boost::asio::ip::tcp;

namespace fdgo {
namespace net {

CloseConnection::CloseConnection() {
	header_.setType(Header::CloseConnection);
	header_.setLength(0);
}

CloseConnection::CloseConnection(Header const& header) : Object(header) {
	if (header_.getType() != Header::CloseConnection)
		BOOST_THROW_EXCEPTION(ExcIncorrectNetObjectType());
}

void CloseConnection::write(tcp::socket& sock) {
	header_.write(sock);
}

void CloseConnection::read(tcp::socket&) {
	// Intentionally left blank -- a null packet shouldn't contain anything.
}

}
}
