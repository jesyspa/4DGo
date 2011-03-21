#include <QDataStream>
#include <net/history.hpp>

namespace fdgo {
namespace net {

History::History() {
	header_.type = Header::History;
	action = unlock;
}

History::History(int action) {
	header_.type = Header::History;
	this->action = AType(action);
}

History::History(Header const& header) : Object(header) {
	if (header.type != Header::History)
		BOOST_THROW_EXCEPTION(ExcIncorrectNetObjectType());
}

void History::printOn(QDataStream&) const {
}

void History::readFrom(QDataStream&) {
}

}
}
