#ifndef FDGO_INCLUDE_CLIENT_HPP
#define FDGO_INCLUDE_CLIENT_HPP

#include <string>
#include <boost/asio.hpp>
#include <boost/regex.hpp>

class Move;
struct Position;

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
	void run();
	void waitForMessage();
	void sendMessage();
    private:
	void sendMessage(std::string const& str);
	void placeStone(Position const& pos);
	void pass();
	void undo();
	void disconnect();

	bool moveConfirmed();
	void listenForMoves();

	boost::asio::io_service io_;
	boost::asio::ip::tcp::socket sock_;
	std::string ip_;
	std::string port_;
	bool black_;
	std::string colour_;

	static const boost::regex rgxPass;
	static const boost::regex rgxMove;
	static const boost::regex rgxKill;
	static const boost::regex rgxUndo;
	static const boost::regex rgxSave;
	static const boost::regex rgxGetScore;
	static const boost::regex rgxExit;
};

#endif // Guard

