#ifndef FDGO_INCLUDE_NET_NULL_HPP
#define FDGO_INCLUDE_NET_NULL_HPP

#include <boost/shared_ptr.hpp>
#include <net/object.hpp>
#include <net/header.hpp>

class QDataStream;

namespace fdgo {
namespace net {

//! \brief Base class for sending and receiving messages.

class Null : public Object {
    public:
	typedef boost::shared_ptr<Null> Pointer;

	Null(); 
	Null(Header const& header);

    protected:
	void printOn(QDataStream& ds) const;
	void readFrom(QDataStream& ds);
};

}
}

#endif // Guard
