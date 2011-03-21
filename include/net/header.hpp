#ifndef FDGO_INCLUDE_NET_HEADER_HPP
#define FDGO_INCLUDE_NET_HEADER_HPP

#include <cstdint>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <exceptions.hpp>

namespace fdgo {
namespace net {

//! \brief Header for everything sent.
//!
//! Current layout:\n
//! qint32 type\n
//! quint16 length\n
//! Total used: 6 bytes\n
class Header {
    public:
    	static const quint16 hsize = sizeof(qint32) + sizeof(quint16);
	static const quint16 sizeStart = 4;
	enum HType {
		Null,
		Error,
		Greeting, // Server sends this to the player to inform him of his colour, etc.
		Message,
		Move,
		Undo,
		Turn,
		History, // Popping, disabling, and enabling history.
		CloseConnection
	} type;

	Header();
	Header(int type);

	quint16 psize; // packet size

	friend QDataStream& operator<<(QDataStream& ds, Header const& nh);
	friend QDataStream& operator>>(QDataStream& ds, Header& nh);
};

}
}

#endif // Guard
