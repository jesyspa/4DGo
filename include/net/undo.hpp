#ifndef FDGO_INCLUDE_NET_UNDO_HPP
#define FDGO_INCLUDE_NET_UNDO_HPP

#include <string>
#include <vector>
#include <boost/asio.hpp>
#include <net/object.hpp>
#include <net/header.hpp>

namespace fdgo {
namespace net {

//! \brief Base class for sending and receiving messages.

class Undo : public Object {
    public:
	typedef boost::shared_ptr<Undo> Pointer;

	Undo(); 
	Undo(Header const& header);

    protected:
	void printOn(QDataStream& ds) const;
	void readFrom(QDataStream& ds);
};

}
}

#endif // Guard
