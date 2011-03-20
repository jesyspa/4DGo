#include <net/message.hpp>
#include <exceptions.hpp>

using boost::asio::ip::tcp;

namespace fdgo {
namespace net {

Message::Message() {
	header_.setType(Header::Message);
	header_.setLength(0);
}

Message::Message(Header const& header) : Object(header) {
	if (header_.getType() != Header::Message)
		BOOST_THROW_EXCEPTION(ExcIncorrectNetObjectType());
}

Message::Message(std::string const& str) {
	header_.setType(Header::Message);
	header_.setLength(str.size());
	msg_.resize(str.size());
	std::copy(str.begin(), str.end(), msg_.begin());
}

void Message::write(tcp::socket& sock) {
	header_.write(sock);
	boost::system::error_code error;
	size_t len = sock.write_some(boost::asio::buffer(msg_.data(), msg_.size()), error);
	checkError(error, len);
}

std::string Message::getString() {
	std::string str;
	str.resize(msg_.size());
	std::copy(msg_.begin(), msg_.end(), str.begin());
	return str;
}

void Message::setString(std::string str) {
	header_.setLength(str.size());
	msg_.resize(str.size());
	std::copy(str.begin(), str.end(), msg_.begin());
}

void Message::read(tcp::socket& sock) {
	msg_.resize(header_.getLength());

	boost::system::error_code error;
	size_t len = sock.read_some(boost::asio::buffer(msg_.data(), msg_.size()), error);
	checkError(error, len);
}

}
}
