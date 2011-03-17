#ifndef FDGO_INCLUDE_NETMESSAGE_HPP
#define FDGO_INCLUDE_NETMESSAGE_HPP

#include <string>
#include <vector>
#include <boost/asio.hpp>
#include "netobject.hpp"
#include "header.hpp"

//! \brief Base class for sending and receiving messages.

class NetMessage : public NetObject {
    public:
	typedef boost::shared_ptr<NetMessage> Pointer;

	NetMessage(); 
	NetMessage(std::string const& str);
	NetMessage(Header const& header);
	void write(boost::asio::ip::tcp::socket& sock);
	std::string getString();
	void setString(std::string str);

    private:
	void read(boost::asio::ip::tcp::socket& sock);
	std::vector<char> msg_;
};

#endif // Guard
