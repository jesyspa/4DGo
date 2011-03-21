#include <net/greeting.hpp>
#include <exceptions.hpp>

namespace fdgo {
namespace net {

Greeting::Greeting() {
	header_.type = Header::Greeting;
}

Greeting::Greeting(double komi, bool black) {
	header_.type = Header::Greeting;
	this->komi = komi;
	this->black = black;
}

Greeting::Greeting(Header const& header) : Object(header) {
	if (header_.type != Header::Greeting)
		BOOST_THROW_EXCEPTION(ExcIncorrectNetObjectType());
}

void Greeting::printOn(QDataStream& ds) const {
	ds << komi << black;
}

void Greeting::readFrom(QDataStream& ds) {
	ds >> komi >> black;
}

}
}
