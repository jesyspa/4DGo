#include <iostream>
#include <string>
#include <vector>
#include <QtCore>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include <client/client.hpp>
#include <net/all.hpp>
#include <move.hpp>
#include <exceptions.hpp>

using boost::asio::ip::tcp;

namespace fdgo {
namespace client {

Client::Client(QObject* parent) : QObject(parent), hist_(false), hlock_(0), sock_(io_), ip_("localhost"), port_("15493") {
}

Client::~Client() {
	delete hlock_;
}

void Client::cl_connect() {
	// Get the connection up.
	tcp::resolver resolver (io_);
	tcp::resolver::query query(ip_, port_);
	tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
	tcp::resolver::iterator end;

	boost::system::error_code error = boost::asio::error::host_not_found;
	while (error && endpoint_iterator != end)
	{
		sock_.close();
		sock_.connect(*endpoint_iterator++, error);
	}
	if (error) // Make sure the connection is okay.
		throw boost::system::system_error(error);
	net::Object::Pointer nobp = expect<net::Header::Greeting>();
	net::Greeting::Pointer ngrp;
	ngrp = boost::dynamic_pointer_cast<net::Greeting>(nobp);
	black_ = ngrp->getBlack();
	emit display(QString("Connection successful, you are %1.\n").arg(black_ ? "black" : "white"));
}

void Client::playStone(Position const& pos) {
	sendPlay(pos);
}

void Client::message(QString const& str) {
	sendMessage(str.toStdString());
}

void Client::undo() {
	sendUndo();
}

void Client::pass() {
	sendPass();
}

void Client::listen() {
	for (;;) {
		try {
			// Not using a switch to be able to only create the objects I need.
			net::Object::Pointer nobp = net::Object::makeFromIncoming(sock_);
			if(nobp->getType() == net::Header::Null) {
				return;
			} else if(nobp->getType() == net::Header::Error) {
				net::Error::Pointer nerrp;
				nerrp = boost::dynamic_pointer_cast<net::Error>(nobp);
				nerrp->throwSelf();
			} else if(nobp->getType() == net::Header::Message) {
				net::Message::Pointer nmsgp;
				nmsgp = boost::dynamic_pointer_cast<net::Message>(nobp);
				emit display(nmsgp->getString().c_str());
			} else if(nobp->getType() == net::Header::Move) {
				net::Move::Pointer nmvp;
				nmvp = boost::dynamic_pointer_cast<net::Move>(nobp);
				play(nmvp->getMove());
			} else if(nobp->getType() == net::Header::History) {
				net::History::Pointer nhip;
				nhip = boost::dynamic_pointer_cast<net::History>(nobp);
				touchHistory(nhip);
			} else if(nobp->getType() == net::Header::CloseConnection) {
				net::CloseConnection ncc;
				ncc.write(sock_);
				BOOST_THROW_EXCEPTION(ExcSafeDisconnect());
			} else {
				BOOST_THROW_EXCEPTION(ExcIncorrectNetObjectType());
			}
		}
		catch (ExcNonFatal& e) {
			if (std::string const* msg = boost::get_error_info<err_msg>(e))
				emit display(msg->c_str());
			#ifndef NDEBUG
				std::cerr << "\nDiagnostics info:\n";
				std::cerr << boost::diagnostic_information(e);
			#endif
		}
	}
}

void Client::sendMessage(std::string const& str) {
	emit display(str.c_str());
	net::Message nmsg(str);
	nmsg.write(sock_);
}

void Client::sendPlay(Position const& pos) {
	Move mv(black_, pos, Move::play);
	net::Move nmv(mv);
	nmv.write(sock_);
	expect<net::Header::Null>();
	listen();
}

void Client::sendPass() {
	Move mv(black_, Position(0,0,0,0), Move::pass);
	net::Move nmv(mv);
	nmv.write(sock_);
	listen();
}

void Client::sendUndo() {
	net::Undo nun;
	nun.write(sock_);
	listen();
}

void Client::disconnect() {
	net::CloseConnection ncc;
	ncc.write(sock_);
	expect<net::Header::CloseConnection>();
}

template<net::Header::Type T>
net::Object::Pointer Client::expect() {
	for (;;) {
		net::Object::Pointer nobp = net::Object::makeFromIncoming(sock_);
		if (nobp->getType() == T) // Server has sent the correct response.
			return nobp;
		if (nobp->getType() == net::Header::Error) {
			net::Error::Pointer nerrp;
			nerrp = boost::dynamic_pointer_cast<net::Error>(nobp);
			nerrp->throwSelf();
		} else {
			net::Error nerr(net::Error::unexpectedType, "");
			nerr.write(sock_);
		}
	}
}

void Client::play(Move const& mv) {
	switch (mv.type) {
		case Move::none:
			hist_.addNull();
			return;
		case Move::pass:
			break;
		case Move::play:
			emit placeStone(mv.black, mv.pos);
			break;
		case Move::remove:
			emit removeStone(mv.pos);
			break;
		default:
			BOOST_THROW_EXCEPTION(ExcInvalidMove());
	}
}

void Client::touchHistory(net::History::Pointer nhip) {
	switch (nhip->getAction()) {
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
			while (hist_.lastMoveType() == Move::remove)
				hist_.popLastMove(); // Get rid of removals.
			hist_.popLastMove(); // Get rid of the placement.
			break;
	}
}

}
}
