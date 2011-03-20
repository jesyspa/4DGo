#ifndef FDGO_INCLUDE_CLIENT_CLIENT_HPP
#define FDGO_INCLUDE_CLIENT_CLIENT_HPP

#include <QObject>
#include <string>
#include <boost/asio.hpp>
#include <boost/regex.hpp>
#include <client/chatbox.hpp>
#include <client/fakegoban.hpp>
#include <net/object.hpp>
#include <net/header.hpp>
#include <net/history.hpp>
#include <history.hpp>
#include <histlock.hpp>

namespace fdgo {

class Move;
struct Position;

namespace client {

//! \brief Main interface for the client side.
//!
//! This is an abstraction for the client side of the server-client
//! connection.

class Client : public QObject {
	Q_OBJECT
    public:
	Client(QObject* parent = 0); 
	~Client();

    public slots:
	void cl_connect();
	void playStone(Position const& pos);
	void message(QString const& str);
	void undo();
	void pass();
	void disconnect();

    signals:
	void display(QString const& str);
	void placeStone(bool black, Position const& pos);
	void removeStone(Position const& pos);

    private:
	void sendMessage(std::string const& str);
	void sendPlay(Position const& pos);
	void sendPass();
	void sendUndo();

	void listen();

	template<net::Header::Type T>
	net::Object::Pointer expect();

	void play(Move const& mv);
	void touchHistory(net::History::Pointer nhip);

	History hist_;
	HistLock* hlock_;

	boost::asio::io_service io_;
	boost::asio::ip::tcp::socket sock_;
	std::string ip_;
	std::string port_;
	bool black_;
};

}
}

#endif // Guard
