#include "netmessage.hpp"
#include "exception.hpp"

using boost::asio::ip::tcp;

NetMessage::NetMessage() {
	header_.setType(Header::Message);
	header_.setLength(0);
}

NetMessage::NetMessage(Header const& header) : NetObject(header) {
	if (header_.getType() != Header::Message)
		BOOST_THROW_EXCEPTION(ExcIncorrectNetObjectType());
}

NetMessage::NetMessage(std::string const& str) {
	header_.setType(Header::Message);
	header_.setLength(str.size());
	msg_.resize(str.size());
	std::copy(str.begin(), str.end(), msg_.begin());
}

void NetMessage::write(tcp::socket& sock) {
	header_.write(sock);
	msg_.resize(header_.getLength());

	boost::system::error_code error;
	size_t len = sock.write_some(boost::asio::buffer(msg_.data(), msg_.size()), error);
	if (error == boost::asio::error::eof)
		BOOST_THROW_EXCEPTION(ExcDisconnected());
	else if (error)
		BOOST_THROW_EXCEPTION(boost::system::system_error(error));

	if (len != header_.getLength())
		BOOST_THROW_EXCEPTION(ExcWriteLengthMismatch());
}

std::string NetMessage::getString() {
	std::string str;
	str.resize(msg_.size());
	std::copy(msg_.begin(), msg_.end(), str.begin());
	return str;
}

void NetMessage::setString(std::string str) {
	header_.setLength(str.size());
	msg_.resize(str.size());
	std::copy(str.begin(), str.end(), msg_.begin());
}

void NetMessage::read(tcp::socket& sock) {
	msg_.resize(header_.getLength());

	boost::system::error_code error;
	size_t len = sock.read_some(boost::asio::buffer(msg_.data(), msg_.size()), error);
	if (error == boost::asio::error::eof)
		BOOST_THROW_EXCEPTION(ExcDisconnected());
	else if (error)
		BOOST_THROW_EXCEPTION(boost::system::system_error(error));

	if (len != header_.getLength())
		BOOST_THROW_EXCEPTION(ExcReadLengthMismatch());
}

