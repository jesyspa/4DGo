#include <QDataStream>
#include <net/null.hpp>
#include <exceptions.hpp>

using boost::asio::ip::tcp;

namespace fdgo {
namespace net {

Null::Null() {
	header_.type = Header::Null;
}

Null::Null(Header const& header) : Object(header) {
	if (header_.type != Header::Null)
		BOOST_THROW_EXCEPTION(ExcIncorrectNetObjectType());
}

void Null::printOn(QDataStream&) const {
}

void Null::readFrom(QDataStream&) {
}

}
}
