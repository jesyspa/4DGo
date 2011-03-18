#ifndef FDGO_INCLUDE_NET_NULL_HPP
#define FDGO_INCLUDE_NET_NULL_HPP

#include <string>
#include <vector>
#include <boost/asio.hpp>
#include <net/object.hpp>
#include <net/header.hpp>

namespace fdgo {
namespace net {

//! \brief Base class for sending and receiving messages.

class Null : public Object {
    public:
	typedef boost::shared_ptr<Null> Pointer;

	Null(); 
	Null(Header const& header);
	void write(boost::asio::ip::tcp::socket& sock);

    private:
	void read(boost::asio::ip::tcp::socket& sock);
};

}
}

#endif // Guard
