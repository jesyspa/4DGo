#ifndef FDGO_INCLUDE_SERVER_CONNECTION_HPP
#define FDGO_INCLUDE_SERVER_CONNECTION_HPP

#include <string>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

namespace fdgo {
namespace server {

//! \brief Main interface for the client side.
//!
//! This is an abstraction for the client side of the server-client
//! connection.


class Connection : public boost::enable_shared_from_this<Connection> {
    public:
	typedef boost::shared_ptr<Connection> Pointer;

	~Connection();
	static Pointer create(boost::asio::io_service& io);
	boost::asio::ip::tcp::socket& socket();

    private:
	void checkForErrors(const boost::system::error_code& error);
	Connection(boost::asio::io_service& io_service);

	boost::asio::ip::tcp::socket socket_;
};

}
}

#endif // Guard
