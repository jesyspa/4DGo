#ifndef FDGO_INCLUDE_CLIENT_HPP
#define FDGO_INCLUDE_CLIENT_HPP

#include <string>
#include <boost/asio.hpp>
#include "netmove.hpp"

class Move;

//! \brief Main interface for the client side.
//!
//! This is an abstraction for the client side of the server-client
//! connection.

class Client {
    private:
	// Should never be called.
	Client(Client const&); 
	Client& operator=(Client const&);
    public:
	Client(int argc, char** argv); 
	~Client();
	void connect();
	void waitForMessage();
	void sendMessage();
    private:
	boost::asio::io_service io_;
	boost::asio::ip::tcp::socket sock_;
	std::string ip_;
	std::string port_;
};

#endif // Guard

