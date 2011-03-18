#include <net/null.hpp>
#include <exceptions.hpp>

using boost::asio::ip::tcp;

namespace fdgo {
namespace net {

Null::Null() {
	header_.setType(Header::Null);
	header_.setLength(0);
}

Null::Null(Header const& header) : Object(header) {
	if (header_.getType() != Header::Null)
		BOOST_THROW_EXCEPTION(ExcIncorrectNetObjectType());
}

void Null::write(tcp::socket& sock) {
	header_.write(sock);
}

void Null::read(tcp::socket&) {
	// Intentionally left blank -- a null packet shouldn't contain anything.
}

}
}
