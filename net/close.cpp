#include <QDataStream>
#include <net/close.hpp>
#include <exceptions.hpp>

namespace fdgo {
namespace net {

CloseConnection::CloseConnection() {
	header_.type = Header::CloseConnection;
}

CloseConnection::CloseConnection(Header const& header) : Object(header) {
	if (header_.type != Header::CloseConnection)
		BOOST_THROW_EXCEPTION(ExcIncorrectNetObjectType());
}

void CloseConnection::printOn(QDataStream&) const {
}

void CloseConnection::readFrom(QDataStream&) {
}

}
}
