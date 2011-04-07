#ifndef FDGO_INCLUDE_SERVER_SERVER_HPP
#define FDGO_INCLUDE_SERVER_SERVER_HPP

#include <QObject>
#include <QQueue>
#include <QString>
#include <server/goban.hpp>
#include <net/object.hpp>
#include <net/factory.hpp>
#include <history.hpp>

class QTcpSocket;
class QTcpServer;

namespace fdgo {

class Move;

namespace server {

//! Application class for server side. 
//!
//! Needs to be reworked and split up. Currently 

class Server : public QObject {
	Q_OBJECT
    public:
	Server(QObject* parent = 0); 
	~Server();

    public slots:
	void newConnection();
	void listenBlack();
	void listenWhite();

    private:
	// Make the following two one function and have a bool passed to
	// tell them apart? 
	void parse(bool black, net::Object::Pointer sock);
	void confirmedParse(bool black, net::Object::Pointer sock);

	// For sending things to players.
	void message(bool black, QString const& str);
	template<class T>
	void broadcast(T const& t);
	void broadcast(QString const& str);
	void broadcast(Move const& mv);
	void broadcastMoves();

	// For interacting with the goban.
	// Hm, seems like too few -- where's killGroup()? Not good.
	void tryPlay(Move const& mv);
	void undo(bool black);

	// For interacting with the history.
	void disableHistory();
	void enableHistory();
	void popHistory();

	void setTurn(bool black);

	QTcpServer* srv_;
	QTcpSocket* bSock_;
	QTcpSocket* wSock_;

	unsigned int port_;

	History hist_;
	Goban goban_;

	double komi_;

	QQueue<net::Object::Pointer> brQueue_;
	QQueue<net::Object::Pointer> wrQueue_;

	net::Factory bnFact_;
	net::Factory wnFact_;

	bool blackTurn_;
};

}
}

#endif // Guard
