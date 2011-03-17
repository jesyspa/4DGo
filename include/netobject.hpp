#ifndef FDGO_INCLUDE_NETOBJECT_HPP
#define FDGO_INCLUDE_NETOBJECT_HPP

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "header.hpp"

//! \brief Base class for sending and receiving objects.

class NetObject : public boost::enable_shared_from_this<NetObject> {
    public:
	typedef boost::shared_ptr<NetObject> Pointer;

	NetObject(); 
	NetObject(Header const& header);

	//! Listen for an incoming object, figure out it's type, and create
	//! something appropriate, returning a shared pointer to it.
	static Pointer makeFromIncoming(boost::asio::ip::tcp::socket& sock);

	//! Writes the object, including the header, over the socket.
	virtual void write(boost::asio::ip::tcp::socket& sock) = 0;
	Header::Type getType();

    protected:
	//! Reads the object, not counting the header, over the socket. The
	//! header does not need to be read, because it has already been read
	//! in order to decide the type.
	virtual void read(boost::asio::ip::tcp::socket& sock) = 0;
	Header header_;
};

#endif // Guard


