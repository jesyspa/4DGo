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
	void awaitConnections();
	void run();
	
	void waitForMessage();
	void sendMessage();
    private:
	void listenToClient(bool black);

	void sendMessage(bool black, std::string const& str);
	void broadcast(std::string const& str);
	void broadcast(Move const& mv);

	void disableHistory();
	void enableHistory();
	void popHistory();

	boost::asio::io_service io_;
	boost::asio::ip::tcp::acceptor* acceptor_;
	Connection::Pointer blackConnection_;
	Connection::Pointer whiteConnection_;
    	unsigned int port_;
};

#endif // Guard
