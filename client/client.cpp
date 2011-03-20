#include <iostream>
#include <string>
#include <vector>
#include <boost/program_options.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include <client/client.hpp>
#include <client/chatbox.hpp>
#include <client/fakegoban.hpp>
#include <net/all.hpp>
#include <move.hpp>
#include <exceptions.hpp>

namespace po = boost::program_options;
using boost::asio::ip::tcp;

namespace fdgo {
namespace client {

const boost::regex Client::rgxPass("^pass$");
const boost::regex Client::rgxMove("^[A-D][1-4][a-d][1-4]$");
const boost::regex Client::rgxKill("^kill [A-D][1-4][a-d][1-4]$"); // Not used
const boost::regex Client::rgxUndo("^undo$");
const boost::regex Client::rgxSave("^save$");
const boost::regex Client::rgxGetScore("^score$"); // Not used
const boost::regex Client::rgxExit("^exit$");

Client::Client(int argc, char** argv) : hist_(false), hlock_(0), sock_(io_), ip_("localhost"), port_("15493"), colour_("Unknown") {
	po::options_description desc("Allowed options");
	desc.add_options()
		("help", "show help message")
		("ip", po::value<std::string>(), "host to connect to")
		("port", po::value<std::string>(), "port to connect on")
	;

	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);

	if (vm.count("help")) {
		std::cout << desc << "\n";
		throw;
	}
	if (vm.count("ip")) {
		ip_ = vm["ip"].as<std::string>();
	}
	if (vm.count("port")) {
		port_ = vm["port"].as<std::string>();
	}
}

Client::~Client() {
	delete hlock_;
}

void Client::connect() {
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
	std::cout << "Connection successful, you are " << (black_ ? "black" : "white") << ".\n";
}

void Client::run() {
	draw();
	for (;;) {
		listen();
		takeInput();
	}
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
				cbox_.addMessage(nmsgp->getString());
			} else if(nobp->getType() == net::Header::Move) {
				net::Move::Pointer nmvp;
				nmvp = boost::dynamic_pointer_cast<net::Move>(nobp);
				play(nmvp->getMove());
				draw();
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
				cbox_.addMessage(std::string("Error: " + *msg));
			#ifndef NDEBUG
				std::cerr << "\nDiagnostics info:\n";
				std::cerr << boost::diagnostic_information(e);
			#endif
			draw();
		}
	}
}

void Client::takeInput() {
	for (;;) {
		try {
			std::cout << "Server is listening.\n";
			std::string input;
			if (!std::getline(std::cin, input))
				BOOST_THROW_EXCEPTION(ExcEOF());
			if (regex_match(input, rgxPass)) {
				sendPass();
				cbox_.addMessage("You have passed.");
				return;
			} else if (regex_match(input, rgxMove)) {
				sendPlay(Position(input));
				return;
			} else if (regex_match(input, rgxUndo)) {
				sendUndo();
				cbox_.addMessage("Last move undone.");
				draw();
				return;
			} else if (regex_match(input, rgxSave)) {
				hist_.writeToDisk("log.txt");
				cbox_.addMessage("Game saved.");
			} else if (regex_match(input, rgxExit)) {
				disconnect();
				BOOST_THROW_EXCEPTION(ExcSuccessExit());
			} else {
				cbox_.addMessage("Unknown instruction: " + input);
			}
		}
		catch (ExcNonFatal& e) {
			if (std::string const* msg = boost::get_error_info<err_msg>(e))
				cbox_.addMessage(std::string("Error: " + *msg));
			#ifndef NDEBUG
				std::cerr << "\nDiagnostics info:\n";
				std::cerr << boost::diagnostic_information(e);
			#endif
			draw();
		}
	}
}

void Client::sendMessage(std::string const& str) {
	cbox_.addMessage(str);
	net::Message nmsg(str);
	nmsg.write(sock_);
}

void Client::sendPlay(Position const& pos) {
	Move mv(black_, pos, Move::play);
	net::Move nmv(mv);
	nmv.write(sock_);
	expect<net::Header::Null>();
}

void Client::sendPass() {
	Move mv(black_, Position(0,0,0,0), Move::pass);
	net::Move nmv(mv);
	nmv.write(sock_);
}

void Client::sendUndo() {
	net::Undo nun;
	nun.write(sock_);
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
			net::Error nerr(net::Error::unexpectedType, "When waiting for move confirmation.");
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
			goban_.placeStone(mv.black, mv.pos);
			break;
		case Move::remove:
			goban_.removeStone(mv.pos);
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

void Client::draw() {
	goban_.draw();
	cbox_.draw();
}

}
}
