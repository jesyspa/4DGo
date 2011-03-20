#include <net/greeting.hpp>
#include <exceptions.hpp>

using boost::asio::ip::tcp;

namespace fdgo {
namespace net {

Greeting::Greeting() {
	header_.setType(Header::Greeting);
	header_.setLength(size_);
	for (size_t a = 0; a < size_; ++a)
		msg_[a] = 0;
}

Greeting::Greeting(float komi, bool black) {
	header_.setType(Header::Greeting);
	header_.setLength(size_);
	setKomi(komi);
	setBlack(black);
}

Greeting::Greeting(Header const& header) : Object(header) {
	if (header_.getType() != Header::Greeting)
		BOOST_THROW_EXCEPTION(ExcIncorrectNetObjectType());
}

void Greeting::write(tcp::socket& sock) {
	header_.write(sock);

	boost::system::error_code error;
	size_t len = sock.write_some(boost::asio::buffer(msg_, size_), error);
	checkError(error, len);
}

void Greeting::setKomi(float komi) {
	msgAs<float>(4) = komi;
}

float Greeting::getKomi() {
	return msgAs<float>(4);
}

void Greeting::setBlack(bool black) {
	msgAs<uint8_t>(0) = black ? 1 : 0;
}

bool Greeting::getBlack() {
	return msgAs<uint8_t>(0);
}

void Greeting::read(tcp::socket& sock) {
	boost::system::error_code error;
	size_t len = sock.read_some(boost::asio::buffer(msg_, size_), error);
	checkError(error, len);
}

template <typename T>
T& Greeting::msgAs(size_t index) {
	return *(reinterpret_cast<T*>(&msg_[index]));
}

}
}
