#include <QDataStream>
#include <net/confirm.hpp>
#include <exceptions.hpp>

namespace fdgo {
namespace net {

Confirmation::Confirmation() {
	header_.type = Header::Confirmation;
	given = false;
}

Confirmation::Confirmation(Header const& header) : Object(header) {
	if (header_.type != Header::Confirmation)
		BOOST_THROW_EXCEPTION(ExcIncorrectNetObjectType());
}

Confirmation::Confirmation(bool give) {
	header_.type = Header::Confirmation;
	given = give;
}

void Confirmation::printOn(QDataStream& ds) const {
	ds << given;
}

void Confirmation::readFrom(QDataStream& ds) {
	ds >> given;
}

}
}
