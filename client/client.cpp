#include <iostream>
#include <string>
#include <vector>
#include <QtCore>
#include <QtNetwork>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include <client/client.hpp>
#include <net/all.hpp>
#include <move.hpp>
#include <exceptions.hpp>

namespace fdgo {
namespace client {

Client::Client(QObject* parent) : QObject(parent), hist_(false), hlock_(0), blackCaps_(0), whiteCaps_(0), connected_(false) {
	host_ = "localhost";
	port_ = 15493;
	sock_ = new QTcpSocket(this);
	connect(       sock_, SIGNAL(readyRead()),
	                this, SLOT(  listen())
	       );
	connect(       sock_, SIGNAL(error(QAbstractSocket::SocketError)),
	                this, SLOT(  handleError(QAbstractSocket::SocketError))
	       );
}

Client::~Client() {
	delete hlock_;
}

void Client::setHost(QString const& str) {
	host_ = str;
}

void Client::setPort(int p) {
	port_ = p;
}

void Client::cl_connect() {
	if (connected_) {
		emit display("Already connected.");
		return;
	}
	sock_->connectToHost(host_, port_);
	nfact_.setSock(sock_);
	connect(       sock_, SIGNAL(readyRead()),
	                this, SLOT(  listen())
	       );
}

void Client::acceptGreeting(net::Greeting::Pointer ngrp) {
	if (connected_) {
		emit display(tr("Server sent a second greeting. Funny."));
		return;
	}
	black_ = ngrp->black;
	komi_ = ngrp->komi;
	emit display(QString(tr("Connection successful, you are %1.")).arg(black_ ? tr("black") : tr("white")));
	emit setColourVal(black_);
	emit setTurnVal(true);
	emit setKomiVal(komi_);
	emit setBlackCapsVal(0);
	emit setWhiteCapsVal(0);
	emit setConnectionVal("Active");
	connected_ = true;
	emit display("Succesfully connected.");
}

void Client::cl_disconnect() {
	if (!connected_) {
		emit display("Not connected.");
		return;
	}
	net::CloseConnection ncc;
	ncc.write(sock_);
	emit setConnectionVal("Closed");
	emit clear();
	sock_->close();
	connected_ = false;
	hist_.clear();
	disconnect(    sock_, SIGNAL(readyRead()),
	                this, SLOT(  listen())
	       );
	disconnect(    sock_, SIGNAL(error(QAbstractSocket::SocketError)),
	                this, SLOT(  handleError(QAbstractSocket::SocketError))
	       );
	emit display("Succesfully disconnected.");
}

void Client::playStone(Position const& pos) {
	Move mv(black_, pos, Move::play);
	net::Move nmv(mv);
	nmv.write(sock_);
}

void Client::message(QString const& str) {
	net::Message nmsg(str);
	nmsg.write(sock_);
}

void Client::undo() {
	net::Undo nun;
	nun.write(sock_);
}

void Client::pass() {
	Move mv(black_, Position(0,0,0,0), Move::pass);
	net::Move nmv(mv);
	nmv.write(sock_);
}

void Client::kill(Position const& pos) {
	Move mv(black_, pos, Move::kill);
	net::Move nmv(mv);
	nmv.write(sock_);
}

void Client::listen() {
	net::Object::Pointer nobp = nfact_.makeFromIncoming();
	if (!nobp) // There wasn't enough data.
		return;
	try {
		// Not using a switch to be able to only create the objects I need.
		if(nobp->getType() == net::Header::Null) {
		} else if(nobp->getType() == net::Header::Error) {
			net::Error::Pointer nerrp;
			nerrp = boost::dynamic_pointer_cast<net::Error>(nobp);
			nerrp->throwSelf();
		} else if(nobp->getType() == net::Header::Greeting) {
			net::Greeting::Pointer ngrp;
			ngrp = boost::dynamic_pointer_cast<net::Greeting>(nobp);
			acceptGreeting(ngrp);
		} else if(nobp->getType() == net::Header::Message) {
			net::Message::Pointer nmsgp;
			nmsgp = boost::dynamic_pointer_cast<net::Message>(nobp);
			emit display(nmsgp->msg);
		} else if(nobp->getType() == net::Header::Move) {
			net::Move::Pointer nmvp;
			nmvp = boost::dynamic_pointer_cast<net::Move>(nobp);
			play(nmvp->mv);
		} else if(nobp->getType() == net::Header::History) {
			net::History::Pointer nhip;
			nhip = boost::dynamic_pointer_cast<net::History>(nobp);
			touchHistory(nhip);
		} else if(nobp->getType() == net::Header::Turn) {
			net::Turn::Pointer ntp;
			ntp = boost::dynamic_pointer_cast<net::Turn>(nobp);
			emit setTurnVal(ntp->black);
		} else if(nobp->getType() == net::Header::CloseConnection) {
			net::CloseConnection ncc;
			ncc.write(sock_);
			BOOST_THROW_EXCEPTION(ExcSafeDisconnect());
		} else {
			BOOST_THROW_EXCEPTION(ExcIncorrectNetObjectType());
		}
	}
	catch (ExcNonFatal& e) {
		if (QString const* msg = boost::get_error_info<err_msg>(e))
			emit display(*msg);
		#ifndef NDEBUG
			std::cerr << "\nDiagnostics info:\n";
			std::cerr << boost::diagnostic_information(e);
		#endif
	}
	if (nfact_.hasMore())
		listen();
}

void Client::writeLogToDisk(QString const& filename) {
	hist_.writeToDisk(filename);
}

void Client::exit() {
	cl_disconnect();
	emit closeWindow();
}

void Client::handleError(QAbstractSocket::SocketError socketError) {
	switch (socketError) {
		case QAbstractSocket::RemoteHostClosedError:
			break;
		case QAbstractSocket::HostNotFoundError:
			emit display(tr("The host was not found. Please check the "
				"host name and port settings."));
			break;
		case QAbstractSocket::ConnectionRefusedError:
			emit display(tr("The connection was refused by the peer. "
				"Make sure the server is running, "
				"and check that the host name and port "
				"settings are correct."));
			break;
		default:
			emit display(tr("The following error occurred: %1.")
				.arg(sock_->errorString()));
	}
}

void Client::play(Move const& mv) {
	switch (mv.type) {
		case Move::none:
			hist_.addNull();
			return;
		case Move::pass:
			hist_.pass(mv.black);
			break;
		case Move::play:
			hist_.placeStone(mv.black, mv.pos);
			emit placeStone(mv.black, mv.pos);
			break;
		case Move::remove:
			hist_.removeStone(mv.black, mv.pos);
			if (!hlock_) {
				if (mv.black) {
					blackCaps_++;
					emit setBlackCapsVal(blackCaps_);
				} else {
					whiteCaps_++;
					emit setWhiteCapsVal(whiteCaps_);
				}
			}
			emit removeStone(mv.pos);
			break;
		default:
			BOOST_THROW_EXCEPTION(ExcInvalidMove());
	}
}

void Client::touchHistory(net::History::Pointer nhip) {
	Move mv;
	switch (nhip->action) {
		case net::History::lock:
			if (hlock_)
				break;
			hlock_ = new HistLock(&hist_);
			break;
		case net::History::unlock:
			delete hlock_;
			hlock_ = 0;
			break;
		case net::History::pop:
			while ((mv = hist_.popLastMove()).type != Move::none) {
				if (mv.type == Move::remove) {
					if (mv.black) {
						blackCaps_--;
						emit setBlackCapsVal(blackCaps_);
					} else {
						whiteCaps_--;
						emit setWhiteCapsVal(whiteCaps_);
					}
				}
			}
			break;
		case net::History::null:
			hist_.addNull();
			break;
	}
}

}
}
