#ifndef FDGO_INCLUDE_SERVER_SERVER_HPP
#define FDGO_INCLUDE_SERVER_SERVER_HPP

#include <string>
#include <boost/asio.hpp>
#include <server/connection.hpp>
#include <server/goban.hpp>
#include <history.hpp>

namespace fdgo {

class Move;

namespace server {

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
    private:
	void listen();

	void sendMessage(bool black, std::string const& str);
	void broadcast(std::string const& str);
	void broadcast(Move const& mv);
	void broadcastMoves();

	void tryPlay(Move const& mv);

	void undo();

	void disableHistory();
	void enableHistory();
	void popHistory();

	boost::asio::io_service io_;
	boost::asio::ip::tcp::acceptor* acceptor_;
	Connection::Pointer bCon_;
	Connection::Pointer wCon_;
    	unsigned int port_;

	History hist_;
	Goban goban_;

	bool black_;
};

}
}

#endif // Guard
