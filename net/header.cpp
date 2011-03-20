#include <net/header.hpp>

using boost::asio::ip::tcp;

namespace fdgo {
namespace net {

Header::Header() {
	setVersion(version);
	for (unsigned int a = 4; a < hs; ++a) // Clear the rest.
		msg[a] = 0;
}

Header::Header(int type, int length) {
	setVersion(version);
	setType(type);
	setLength(length);
}

bool Header::versionsMatch() const {
	return ((getVersion() & ~0xFF) == (version & ~0xFF));
}

Header::Type Header::getType() const {
	return Type(msgAs<const uint16_t>(4));
}

void Header::setType(int type) {
	if (type < 0 || type > 0xFFFF) // Perhaps make this BOOST_THROW_EXCEPTION( for unknown values, too?
		BOOST_THROW_EXCEPTION(ExcInvalidValue() << err_msg("Header provided with a type that is out of bounds."));
	msgAs<uint16_t>(4) = type;
}

size_t Header::getLength() const {
	return msgAs<const uint16_t>(6);
}

void Header::setLength(size_t length) {
	if (length > 0xFFFF) 
		BOOST_THROW_EXCEPTION(ExcInvalidValue() << err_msg("Header provided with a length that is out of bounds."));
	msgAs<uint16_t>(6) = length;
}

void Header::write(tcp::socket& sock) {
	boost::system::error_code error;
	size_t len = sock.write_some(boost::asio::buffer(msg, hs), error);
	if (error == boost::asio::error::eof)
		BOOST_THROW_EXCEPTION(ExcDisconnect());
	else if (error)
		BOOST_THROW_EXCEPTION(boost::system::system_error(error));

	if (len != hs)
		BOOST_THROW_EXCEPTION(ExcWriteLengthMismatch());
}

void Header::read(tcp::socket& sock) {
	boost::system::error_code error;
	size_t len = sock.read_some(boost::asio::buffer(msg, hs), error);
	if (error == boost::asio::error::eof)
		BOOST_THROW_EXCEPTION(ExcDisconnect());
	else if (error)
		BOOST_THROW_EXCEPTION(boost::system::system_error(error));

	if (len != hs)
		BOOST_THROW_EXCEPTION(ExcReadLengthMismatch());
}

template<typename T>
T& Header::msgAs(size_t index) {
	return *(reinterpret_cast<T*>(&msg[index]));
}

template<typename T>
T const& Header::msgAs(size_t index) const {
	return *(reinterpret_cast<T*>(&msg[index]));
}

uint32_t Header::getVersion() const {
	return msgAs<const uint32_t>(0);
}

void Header::setVersion(uint32_t vs) {
	msgAs<uint32_t>(0) = vs;
}

}
}
