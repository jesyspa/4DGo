#include <QDataStream>
#include <net/error.hpp>
#include <exceptions.hpp>

namespace fdgo {
namespace net {

Error::Error() {
	header_.type = Header::Error;
	err_type = unknownError;
}

Error::Error(Header const& header) : Object(header) {
	if (header_.type != Header::Error)
		BOOST_THROW_EXCEPTION(ExcIncorrectNetObjectType());
	err_type = unknownError;
}

Error::Error(int er, QString const& str) {
	header_.type = Header::Error;
	err_type = EType(er);
	msg = str;
}

void Error::throwSelf() {
	switch (err_type) {
		case unexpectedType:
			BOOST_THROW_EXCEPTION(ExcIncorrectNetObjectType() << err_msg(msg));
		case invalidMove:
			BOOST_THROW_EXCEPTION(ExcInvalidMove() << err_msg(msg));
		default:
			BOOST_THROW_EXCEPTION(ExcUnknownError() << err_msg(msg));
	}
}

void Error::printOn(QDataStream& ds) const {
	ds << qint32(err_type) << msg;
}

void Error::readFrom(QDataStream& ds) {
	qint32 tmp;
	ds >> tmp >> msg;
	err_type = EType(tmp);
}

}
}
