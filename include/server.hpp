#ifndef FDGO_INCLUDE_SERVER_HPP
#define FDGO_INCLUDE_SERVER_HPP

#include <string>
#include <boost/asio.hpp>
#include "connection.hpp"

class Game;

class Server {
    private:
	// Should never be called.
	Server(Server const&); 
	Server& operator=(Server const&);
    public:
	Server(int argc, char** argv); 
	~Server();
	void run();
	void awaitConnections();
    private:
	void blackPlayerConnected();
	void whitePlayerConnected();
	boost::asio::io_service io_;
	boost::asio::ip::tcp::acceptor* acceptor_;
	Connection::Pointer blackConnection_;
	Connection::Pointer whiteConnection_;
    	unsigned int port_;
};

#endif // Guard
