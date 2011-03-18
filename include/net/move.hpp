#ifndef FDGO_INCLUDE_NET_MOVE_HPP
#define FDGO_INCLUDE_NET_MOVE_HPP

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <net/object.hpp>
#include <net/header.hpp>
#include <move.hpp>
#include <position.hpp>

namespace fdgo {
namespace net {

//! \brief Base class for sending and receiving messages.
//!
//! Current layout:\n
//! uint16_t type
//! uint8_t black\n
//! 1 byte padding
//! 16 bytes of position (4*uint32_t)
//!
//! Total used: 20 bytes\n
//! Total size: 32 bytes

class Move : public Object {
    public:
	typedef boost::shared_ptr<Move> Pointer;

	Move(); 
	Move(fdgo::Move const& mv);
	Move(Header const& header);
	void write(boost::asio::ip::tcp::socket& sock);
	fdgo::Move getMove();
	void setMove(fdgo::Move const& mv);

    private:
	static const size_t size_ = 32;

	void read(boost::asio::ip::tcp::socket& sock);

	template<typename T>
	T& msgAs(size_t index);

	void setType(fdgo::Move::MType type);
	void setType(int type);
	fdgo::Move::MType getType();
	void setPosition(Position const& pos);
	Position getPosition();
	void setBlack(bool black);
	bool getBlack();

	boost::array<char, size_> msg_;
};

}
}

#endif // Guard
