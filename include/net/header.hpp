#ifndef FDGO_INCLUDE_NET_HEADER_HPP
#define FDGO_INCLUDE_NET_HEADER_HPP

#include <exceptions.hpp>

class QDataStream;

namespace fdgo {
namespace net {

//! \brief Header for all messages sent.
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
		Greeting, 
		Message,
		Move,
		Undo,
		Turn,
		History, 
		Setting,
		Score,
		Confirmation,
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
