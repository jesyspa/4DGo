#ifndef FDGO_INCLUDE_NET_CLOSE_HPP
#define FDGO_INCLUDE_NET_CLOSE_HPP

#include <string>
#include <vector>
#include <boost/asio.hpp>
#include <net/object.hpp>
#include <net/header.hpp>

namespace fdgo {
namespace net {

//! \brief Base class for sending and receiving messages.

class CloseConnection : public Object {
    public:
	typedef boost::shared_ptr<CloseConnection> Pointer;

	CloseConnection(); 
	CloseConnection(Header const& header);
	void write(boost::asio::ip::tcp::socket& sock);

    private:
	void read(boost::asio::ip::tcp::socket& sock);
};

}
}

#endif // Guard

