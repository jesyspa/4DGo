#include <net/error.hpp>
#include <exceptions.hpp>

using boost::asio::ip::tcp;

namespace fdgo {
namespace net {

Error::Error() {
	header_.setType(Header::Error);
	header_.setLength(2);
	msg_.resize(2);
}

Error::Error(Header const& header) : Object(header) {
	if (header_.getType() != Header::Error)
		BOOST_THROW_EXCEPTION(ExcIncorrectNetObjectType());
}

Error::Error(int er, std::string const& str) {
	header_.setType(Header::Error);
	header_.setLength(str.size()+2);
	msg_.resize(str.size()+2);
	setError(er);
	std::copy(str.begin(), str.end(), msg_.begin()+2);
}

void Error::write(tcp::socket& sock) {
	header_.write(sock);
	msg_.resize(header_.getLength()); // Unnecessary?

	boost::system::error_code error;
	size_t len = sock.write_some(boost::asio::buffer(msg_.data(), msg_.size()), error);
	if (error == boost::asio::error::eof)
		BOOST_THROW_EXCEPTION(ExcDisconnect());
	else if (error)
		BOOST_THROW_EXCEPTION(boost::system::system_error(error));

	if (len != header_.getLength())
		BOOST_THROW_EXCEPTION(ExcWriteLengthMismatch());
}

Error::EType Error::getError() {
	return EType(msgAs<uint16_t>(0));
}

void Error::setError(int er) {
	msgAs<uint16_t>(0) = EType(er);
}

std::string Error::getString() {
	std::string str;
	str.resize(msg_.size()-2);
	std::copy(msg_.begin()+2, msg_.end(), str.begin());
	return str;
}

void Error::setString(std::string str) {
	header_.setLength(str.size()+2);
	msg_.resize(str.size()+2);
	std::copy(str.begin(), str.end(), msg_.begin()+2);
}
	
void Error::throwSelf() {
	switch (getError()) {
		case unexpectedType:
			BOOST_THROW_EXCEPTION(ExcIncorrectNetObjectType() << err_msg(getString()));
		case invalidMove:
			BOOST_THROW_EXCEPTION(ExcInvalidMove() << err_msg(getString()));
		default:
			BOOST_THROW_EXCEPTION(ExcUnknownError() << err_msg(getString()));
	}
}

template<typename T>
T& Error::msgAs(size_t index) {
	return *(reinterpret_cast<T*>(msg_.data()+index));
}

void Error::read(tcp::socket& sock) {
	msg_.resize(header_.getLength());

	boost::system::error_code error;
	size_t len = sock.read_some(boost::asio::buffer(msg_.data(), msg_.size()), error);
	if (error == boost::asio::error::eof)
		BOOST_THROW_EXCEPTION(ExcDisconnect());
	else if (error)
		BOOST_THROW_EXCEPTION(boost::system::system_error(error));

	if (len != header_.getLength())
		BOOST_THROW_EXCEPTION(ExcReadLengthMismatch());
}

}
}
