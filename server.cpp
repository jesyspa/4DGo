#include <iostream>
#include <boost/program_options.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include "server.hpp"
#include "connection.hpp"
#include "netobject.hpp"
#include "netmessage.hpp"
#include "exception.hpp"

namespace po = boost::program_options;
using boost::asio::ip::tcp;

Server::Server(int argc, char** argv) : acceptor_(0), port_(15493) {
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
	blackConnection_ = Connection::create(acceptor_->io_service());
	whiteConnection_ = Connection::create(acceptor_->io_service());
}

Server::~Server() {
	delete acceptor_;
}

void Server::awaitConnections() {
	acceptor_->accept(blackConnection_->socket());
	std::cout << "Client has connected.\n";
}

void Server::waitForMessage() {
	NetObject::Pointer nop = NetObject::makeFromIncoming(blackConnection_->socket());
	NetMessage::Pointer nmp;
	if (nop->getType() == Header::Message)
		nmp = boost::dynamic_pointer_cast<NetMessage>(nop);
	else
		BOOST_THROW_EXCEPTION(ExcIncorrectNetObjectType());
	std::cout << nmp->getString() << "\n";
}

void Server::sendMessage() {
	std::string str;
	std::getline(std::cin, str);
	NetMessage nm(str);
	nm.write(blackConnection_->socket());
	std::cout << "Message sent.\n";
}
