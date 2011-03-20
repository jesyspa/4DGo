#include <net/history.hpp>

using boost::asio::ip::tcp;

namespace fdgo {
namespace net {

History::History() {
	header_.setType(Header::History);
	header_.setLength(size_);
	setAction(AType::unlock);
}

History::History(int action) {
	header_.setType(Header::History);
	header_.setLength(size_);
	setAction(action);
}

History::History(Header const& header) : Object(header) {
	if (header.getType() != Header::History)
		BOOST_THROW_EXCEPTION(ExcIncorrectNetObjectType());
}

void History::write(tcp::socket& sock) {
	header_.write(sock);
	boost::system::error_code error;
	size_t len = sock.write_some(boost::asio::buffer(msg_, size_), error);
	checkError(error, len);
}


History::AType History::getAction() {
	return AType(msgAs<uint32_t>(0));
}

void History::setAction(int action) {
	msgAs<uint32_t>(0) = action;
}

void History::read(tcp::socket& sock) {
	boost::system::error_code error;
	size_t len = sock.read_some(boost::asio::buffer(msg_, size_), error);
	checkError(error, len);
}


template<typename T>
T& History::msgAs(size_t index) {
	return *(reinterpret_cast<T*>(&msg_[index]));
}

}
}
