#ifndef FDGO_INCLUDE_SERVER_SERVER_HPP
#define FDGO_INCLUDE_SERVER_SERVER_HPP

#include <QObject>
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
	void parse(bool black, net::Object::Pointer sock);

	template<class T>
	void broadcast(T const& t);
	void broadcast(QString const& str);
	void broadcast(Move const& mv);
	void broadcastMoves();

	void tryPlay(Move const& mv);

	void undo();

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

	net::Factory bnFact_;
	net::Factory wnFact_;

	bool blackTurn_;
};

}
}

#endif // Guard
