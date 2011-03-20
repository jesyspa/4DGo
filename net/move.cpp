#include <net/move.hpp>
#include <move.hpp>

using boost::asio::ip::tcp;

namespace fdgo {
namespace net {

Move::Move() {
	header_.setType(Header::Move);
	header_.setLength(size_);
	for (size_t a = 0; a < size_; ++a)
		msg_[a] = 0;
}

Move::Move(fdgo::Move const& mv) {
	header_.setType(Header::Move);
	header_.setLength(size_);
	setType(mv.type);
	setBlack(mv.black);
	setPosition(mv.pos);
	for (size_t a = 20; a < size_; ++a)
		msg_[a] = 0;
}

Move::Move(Header const& header) : Object(header) {
	if (header_.getType() != Header::Move)
		BOOST_THROW_EXCEPTION(ExcIncorrectNetObjectType());
}

void Move::write(tcp::socket& sock) {
	header_.write(sock);
	boost::system::error_code error;
	size_t len = sock.write_some(boost::asio::buffer(msg_, size_), error);
	checkError(error, len);
}

fdgo::Move Move::getMove() {
	return fdgo::Move(getBlack(), getPosition(), getType());
}

void Move::setMove(fdgo::Move const& mv) {
	setType(mv.type);
	setBlack(mv.black);
	setPosition(mv.pos);
}

void Move::read(tcp::socket& sock) {
	boost::system::error_code error;
	size_t len = sock.read_some(boost::asio::buffer(msg_, size_), error);
	checkError(error, len);
}

template <typename T>
T& Move::msgAs(size_t index) {
	return *(reinterpret_cast<T*>(&msg_[index]));
}

void Move::setType(fdgo::Move::MType type) {
	msgAs<uint16_t>(0) = type;
}

void Move::setType(int type) {
	msgAs<uint16_t>(0) = fdgo::Move::MType(type);
}

fdgo::Move::MType Move::getType() {
	return fdgo::Move::MType(msgAs<uint16_t>(0));
}

void Move::setPosition(Position const& pos) {
	msgAs<uint32_t>(4) = pos[0];
	msgAs<uint32_t>(8) = pos[1];
	msgAs<uint32_t>(12) = pos[2];
	msgAs<uint32_t>(16) = pos[3];
}

Position Move::getPosition() {
	return Position(msgAs<uint32_t>(4), msgAs<uint32_t>(8), msgAs<uint32_t>(12), msgAs<uint32_t>(16));
}

void Move::setBlack(bool black) {
	msgAs<uint8_t>(2) = black;
}

bool Move::getBlack() {
	return msgAs<uint8_t>(2);
}

}
}
