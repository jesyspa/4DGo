#ifndef FDGO_INCLUDE_CLIENT_CLIENT_HPP
#define FDGO_INCLUDE_CLIENT_CLIENT_HPP

#include <QTcpSocket>
#include <QObject>
#include <QString>
#include <net/object.hpp>
#include <net/header.hpp>
#include <net/factory.hpp>
#include <net/history.hpp>
#include <net/greeting.hpp>
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
	void setHost(QString const& str);
	void setPort(int p);
	void cl_connect();
	void cl_disconnect();

	void playStone(Position const& pos);
	void message(QString const& str);
	void undo();
	void pass();
	void kill(Position const& pos);
	void confirm(bool give);

	void handleError(QAbstractSocket::SocketError);

	void listen();

	void writeLogToDisk(QString const& filename);
	void exit();

  signals:
	void display(QString const& str);
	void placeStone(bool black, Position const& pos);
	void removeStone(Position const& pos);
	void setColourVal(bool black);
	void setTurnVal(bool black);
	void setKomiVal(double komi);
	void setBlackCapsVal(int caps);
	void setWhiteCapsVal(int caps);
	void setConnectionVal(QString const& str);
	void clear();
	void closeWindow();

  private:
	void acceptGreeting(net::Greeting::Pointer ngrp);

	template<net::Header::HType T>
	net::Object::Pointer expect();

	void play(Move const& mv);
	void touchHistory(net::History::Pointer nhip);

	History hist_;
	HistLock* hlock_;
	net::Factory nfact_;

	QTcpSocket* sock_;
	QString host_;
	int port_;
	int blackCaps_;
	int whiteCaps_;

	double komi_;
	bool black_;
	bool connected_;
};

}
}

#endif // Guard
