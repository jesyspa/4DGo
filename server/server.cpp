#include <iostream>
#include <boost/program_options.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include <QtNetwork>
#include <server/server.hpp>
#include <net/all.hpp>
#include <history.hpp>
#include <histlock.hpp>
#include <exceptions.hpp>

namespace po = boost::program_options;
using boost::asio::ip::tcp;

namespace fdgo {
namespace server {

Server::Server(QObject* parent) : QObject(parent), goban_(hist_), blackTurn_(true) {
#if 0
	po::options_description desc("Allowed options");
	desc.add_options()
		("help", "show help message")
		("port", po::value<unsigned int>(), "port to listen on")
	;

	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);

	if (vm.count("help")) {
		std::cout << desc << "\n";
		throw;
	}
	if (vm.count("port")) {
		port_ = vm["port"].as<unsigned int>();
	} else {
		port_ = 15493;
	}
	
#endif
	port_ = 15493;
	srv_ = new QTcpServer(this);

	if (!srv_->listen(QHostAddress::Any, port_)) {
		BOOST_THROW_EXCEPTION(ExcFatal());
	}

	bSock_ = 0;
	wSock_ = 0;

	connect(        srv_, SIGNAL(newConnection()),
	                this, SLOT(  newConnection())
	       );
}

Server::~Server() {
}

void Server::newConnection() {
	if (!bSock_) {
		bSock_ = srv_->nextPendingConnection();
		net::Greeting ngr(0.5, true);
		ngr.write(bSock_);
		bnFact_.setSock(bSock_);
		connect(bSock_, SIGNAL(disconnected()),
		        bSock_, SLOT(  deleteLater())
		       );
		connect(bSock_, SIGNAL(readyRead()),
		          this, SLOT(  listenBlack())
		       );
	} else if (!wSock_) {
		wSock_ = srv_->nextPendingConnection();
		net::Greeting ngr(0.5, false);
		ngr.write(wSock_);
		wnFact_.setSock(wSock_);
		connect(wSock_, SIGNAL(disconnected()),
		        wSock_, SLOT(  deleteLater())
		       );
		connect(wSock_, SIGNAL(readyRead()),
		          this, SLOT(  listenWhite())
		       );
		broadcast(tr("Both players have connected."));
	} else {
		QTcpSocket* s = srv_->nextPendingConnection();
		s->disconnectFromHost();
	}
		
}

void Server::listenBlack() {
	net::Object::Pointer nobp = bnFact_.makeFromIncoming();
	if (!nobp)
		return;
	parse(true, nobp);
	if (bnFact_.hasMore())
		listenBlack();
}

void Server::listenWhite() {
	net::Object::Pointer nobp = wnFact_.makeFromIncoming();
	if (!nobp)
		return;
	parse(false, nobp);
	if (wnFact_.hasMore())
		listenWhite();
}

void Server::parse(bool black, net::Object::Pointer nobp) {
	try {
		if(nobp->getType() == net::Header::Null) {
			return;
		} else if(nobp->getType() == net::Header::Error) {
			net::Error::Pointer nerrp;
			nerrp = boost::dynamic_pointer_cast<net::Error>(nobp);
			nerrp->throwSelf();
		} else if(nobp->getType() == net::Header::Message) {
			net::Message::Pointer nmsgp;
			nmsgp = boost::dynamic_pointer_cast<net::Message>(nobp);
			nmsgp->msg.prepend(black ? "Black: " : "White: ");
			broadcast(*nmsgp);
		} else if(nobp->getType() == net::Header::Move) {
			if (black != blackTurn_)
				return;
			net::Move::Pointer nmvp;
			nmvp = boost::dynamic_pointer_cast<net::Move>(nobp);
			tryPlay(nmvp->mv);
		} else if(nobp->getType() == net::Header::Undo ) {
			broadcast(QString(black ? "Black" : "White") + " has requested an undo.");
			undo();
		} else if(nobp->getType() == net::Header::History) {
			BOOST_THROW_EXCEPTION(ExcNotImplemented());
		} else if(nobp->getType() == net::Header::CloseConnection) {
			net::CloseConnection ncc;
			ncc.write(bSock_);
			ncc.write(wSock_);
			bSock_->disconnectFromHost();
			wSock_->disconnectFromHost();
		} else {
			BOOST_THROW_EXCEPTION(ExcIncorrectNetObjectType());
		}
	}
	catch (ExcInvalidMove& e) {
		net::Error err;
		err.err_type = net::Error::invalidMove;
		if (QString const* msg = boost::get_error_info<err_msg>(e))
			err.msg = *msg;
		else
			err.msg = tr("Unknown error.");
		err.write(black ? bSock_ : wSock_);
	}
	catch (ExcNonFatal& e) {
		std::cerr << "A non-fatal exception has been caught when listening to " << (black ? "black" : "white") << "." << std::endl;

		if (QString const* ti = boost::get_error_info<type_err_msg>(e))
			std::cerr << "Error type info: " << ti->toStdString() << std::endl;
		else
			std::cerr << "No error type info provided." << std::endl;

		if (QString const* msg = boost::get_error_info<err_msg>(e))
			std::cerr << "Error message: " << msg->toStdString() << std::endl;
		else
			std::cerr << "No error message provided." << std::endl;

		#ifndef NDEBUG
			std::cerr << "\nDiagnostics info:\n";
			std::cerr << boost::diagnostic_information(e);
		#endif
	}
	broadcastMoves();
}

template<class T>
void Server::broadcast(T const& t) {
	t.write(bSock_);
	t.write(wSock_);
}

void Server::broadcast(QString const& str) {
	net::Message nmsg(str);
	broadcast(nmsg);
}

void Server::broadcast(Move const& mv) {
	net::Move nmv(mv);
	broadcast(nmv);
}

void Server::broadcastMoves() {
	while (hist_.unhandledMoves()) {
		broadcast(hist_.peekStack());
		hist_.confirmTop();
	}
}

void Server::tryPlay(Move const& mv) {
	if (mv.type == Move::kill) {
		goban_.killGroup(mv.pos);
		hist_.addNull();
		return;
	}
	if (mv.black != blackTurn_)
		BOOST_THROW_EXCEPTION(ExcInvalidMove() << err_msg("Move played by wrong colour!"));
	if (mv.type == Move::pass) {
		broadcast(QString(blackTurn_ ? "Black" : "White") + " has passed.");
		hist_.pass(mv.black);
		setTurn(!blackTurn_);
		hist_.addNull();
		return;
	}
	try {
		goban_.placeStone(blackTurn_, mv.pos);
		hist_.addNull();
		setTurn(!blackTurn_);
	}
	catch (ExcNotImplemented& e) {
		BOOST_THROW_EXCEPTION(ExcInvalidMove() << err_msg("Functionality not implemented yet.\n"));
	}
	catch (ExcInvalidPos& e) {
		BOOST_THROW_EXCEPTION(ExcInvalidMove() << err_msg("Invalid position.\n"));
	}
}

void Server::undo() {
	HistLock bHlock(&hist_, bSock_);
	HistLock wHlock(&hist_, wSock_);
	net::History nhi(net::History::pop);
	broadcast(nhi);
	Move lastmove;
	size_t i = hist_.seekLastTurn();
	hist_.remove(i); // Get rid of the null
	lastmove = hist_.remove(i);
	if (lastmove.type == Move::play) {
		broadcast(net::Message("Move undone."));
		setTurn(!blackTurn_);
		goban_.removeStone(lastmove.pos);
		broadcast(Move(lastmove.black, lastmove.pos, Move::remove));
	} else if (lastmove.type == Move::kill) {
		broadcast(net::Message("Kill undone."));
	} else if (lastmove.type == Move::pass) {
		broadcast(net::Message("Pass undone."));
		setTurn(!blackTurn_);
		return;
	} else {
		broadcast(net::Message("No move to undo."));
		return;
	}
	while (hist_.getType(i) == Move::remove) {
		lastmove = hist_.remove(i);
		goban_.placeStone(lastmove.black, lastmove.pos);
		broadcast(Move(lastmove.black, lastmove.pos, Move::play));
	}
}

void Server::setTurn(bool black) {
	blackTurn_ = black;
	net::Turn nt(black);
	broadcast(nt);
}

}
}
