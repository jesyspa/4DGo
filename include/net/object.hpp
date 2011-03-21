#ifndef FDGO_INCLUDE_NET_OBJECT_HPP
#define FDGO_INCLUDE_NET_OBJECT_HPP

#include <QDataStream>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <net/header.hpp>

class QTcpSocket;

namespace fdgo {
namespace net {

//! \brief Base class for sending and receiving objects.

class Object : public boost::enable_shared_from_this<Object> {
	friend class Factory;
    public:
	typedef boost::shared_ptr<Object> Pointer;

	Object(); 
	Object(Header const& header);

	void write(QTcpSocket* sock) const;
	// No need for a read() -- the factory handles this.

	Header::HType getType() const;
    protected:
	virtual void printOn(QDataStream& ds) const = 0;
	virtual void readFrom(QDataStream& ds) = 0;
	Header header_;

    private:
	friend QDataStream& operator<<(QDataStream& ds, Object const& no);
	friend QDataStream& operator>>(QDataStream& ds, Object& no);
};

}
}

#endif // Guard
