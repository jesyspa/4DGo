#ifndef FDGO_INCLUDE_NET_MESSAGE_HPP
#define FDGO_INCLUDE_NET_MESSAGE_HPP

#include <string>
#include <vector>
#include <boost/asio.hpp>
#include <net/object.hpp>
#include <net/header.hpp>

namespace fdgo {
namespace net {

//! \brief Class for sending and receiving messages.

class Message : public Object {
    public:
	typedef boost::shared_ptr<Message> Pointer;

	Message(); 
	Message(std::string const& str);
	Message(Header const& header);
	void write(boost::asio::ip::tcp::socket& sock);
	std::string getString();
	void setString(std::string str);

    private:
	void read(boost::asio::ip::tcp::socket& sock);
	std::vector<char> msg_;
};

}
}

#endif // Guard
