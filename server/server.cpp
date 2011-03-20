#include <iostream>
#include <boost/program_options.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include <server/server.hpp>
#include <server/connection.hpp>
#include <net/all.hpp>
#include <history.hpp>
#include <histlock.hpp>
#include <exceptions.hpp>

namespace po = boost::program_options;
using boost::asio::ip::tcp;

namespace fdgo {
namespace server {

Server::Server(int argc, char** argv) : acceptor_(0), port_(15493), goban_(hist_), black_(true) {
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
	}
	
	acceptor_ = new tcp::acceptor(io_, tcp::endpoint(tcp::v4(), port_));
	bCon_ = Connection::create(acceptor_->io_service());
	wCon_ = Connection::create(acceptor_->io_service());
}

Server::~Server() {
	delete acceptor_;
}

void Server::awaitConnections() {
	net::Greeting ngrb(0.5, true);
	net::Greeting ngrw(0.5, false);
	acceptor_->accept(bCon_->socket());
	ngrb.write(bCon_->socket());
	acceptor_->accept(wCon_->socket());
	ngrw.write(wCon_->socket());
}

void Server::run() {
	for (;; black_ = !black_) {
		listen();
		broadcastMoves();
	}
}

void Server::listen() {
	tcp::socket& sock = black_ ? bCon_->socket() : wCon_->socket();
	net::Null nn;
	nn.write(sock);
	for(;;) {
		try {
			net::Object::Pointer nobp = net::Object::makeFromIncoming(sock);
			if(nobp->getType() == net::Header::Null) {
				return;
			} else if(nobp->getType() == net::Header::Error) {
				net::Error::Pointer nerrp;
				nerrp = boost::dynamic_pointer_cast<net::Error>(nobp);
				nerrp->throwSelf();
			} else if(nobp->getType() == net::Header::Message) {
				net::Message::Pointer nmsgp;
				nmsgp = boost::dynamic_pointer_cast<net::Message>(nobp);
				sendMessage(!black_, nmsgp->getString());
			} else if(nobp->getType() == net::Header::Move) {
				net::Move::Pointer nmvp;
				nmvp = boost::dynamic_pointer_cast<net::Move>(nobp);
				tryPlay(nmvp->getMove());
				nn.write(sock);
				return;
			} else if(nobp->getType() == net::Header::Undo ) {
				undo();
				return;
			} else if(nobp->getType() == net::Header::History) {
				BOOST_THROW_EXCEPTION(ExcNotImplemented());
			} else if(nobp->getType() == net::Header::CloseConnection) {
				net::CloseConnection ncc;
				ncc.write(sock);
				BOOST_THROW_EXCEPTION(ExcSafeDisconnect());
			} else {
				BOOST_THROW_EXCEPTION(ExcIncorrectNetObjectType());
			}
		}
		catch (ExcInvalidMove& e) {
			net::Error err;
			err.setError(net::Error::invalidMove);
			if (std::string const* msg = boost::get_error_info<err_msg>(e))
				err.setString(*msg);
			else
				err.setString("Unknown error.");
			err.write(sock);
			nn.write(sock);

		}
		catch (ExcNonFatal& e) {
			std::cerr << "A non-fatal exception has been caught when listening to " << (black_ ? "black" : "white") << "." << std::endl;

			if (std::string const* ti = boost::get_error_info<type_err_msg>(e))
				std::cerr << "Error type info: " << *ti << std::endl;
			else
				std::cerr << "No error type info provided." << std::endl;

			if (std::string const* msg = boost::get_error_info<err_msg>(e))
				std::cerr << "Error message: " << *msg << std::endl;
			else
				std::cerr << "No error message provided." << std::endl;

			#ifndef NDEBUG
				std::cerr << "\nDiagnostics info:\n";
				std::cerr << boost::diagnostic_information(e);
			#endif
		}
	}
}

void Server::sendMessage(bool black, std::string const& str) {
	tcp::socket& sock = black ? bCon_->socket() : wCon_->socket();
	net::Message nmsg(str);
	nmsg.write(sock);
}

void Server::broadcast(std::string const& str) {
	net::Message nmsg(str);
	nmsg.write(bCon_->socket());
	nmsg.write(wCon_->socket());
}

void Server::broadcast(Move const& mv) {
	net::Move nmv(mv);
	nmv.write(bCon_->socket());
	nmv.write(wCon_->socket());
}

void Server::broadcastMoves() {
	while (hist_.unhandledMoves()) {
		broadcast(hist_.peekStack());
		hist_.confirmTop();
	}
}

void Server::tryPlay(Move const& mv) {
	if (mv.black != black_)
		BOOST_THROW_EXCEPTION(ExcInvalidMove() << err_msg("Move played by wrong colour!"));
	if (mv.type == Move::pass)
		return;
	try {
		goban_.placeStone(black_, mv.pos);
	}
	catch (ExcNotImplemented& e) {
		BOOST_THROW_EXCEPTION(ExcInvalidMove() << err_msg("Functionality not implemented yet.\n"));
	}
	catch (ExcInvalidPos& e) {
		BOOST_THROW_EXCEPTION(ExcInvalidMove() << err_msg("Invalid position.\n"));
	}
}

void Server::undo() {
	HistLock bHlock(&hist_, &bCon_->socket());
	HistLock wHlock(&hist_, &wCon_->socket());
	net::History nhi(net::History::pop);
	nhi.write(bCon_->socket());
	nhi.write(wCon_->socket());
	Move lastmove;
	while (hist_.lastMoveType() == Move::remove) {
		lastmove = hist_.popLastMove();
		goban_.placeStone(!lastmove.black, lastmove.pos);
		broadcast(Move(lastmove.black, lastmove.pos, Move::play));
	}
	lastmove = hist_.popLastMove();
	if (lastmove.type != Move::play)
		return;
	goban_.removeStone(lastmove.pos);
	broadcast(Move(lastmove.black, lastmove.pos, Move::remove));
}

}
}
