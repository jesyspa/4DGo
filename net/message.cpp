#include <QDataStream>
#include <net/message.hpp>
#include <exceptions.hpp>

namespace fdgo {
namespace net {

Message::Message() {
	header_.type = Header::Message;
}

Message::Message(Header const& header) : Object(header) {
	if (header_.type != Header::Message)
		BOOST_THROW_EXCEPTION(ExcIncorrectNetObjectType());
}

Message::Message(QString const& str) {
	header_.type = Header::Message;
	msg = str;
}

void Message::printOn(QDataStream& ds) const {
	ds << msg;
}

void Message::readFrom(QDataStream& ds) {
	ds >> msg;
}

}
}
