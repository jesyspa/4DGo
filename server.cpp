#include <iostream>
#include <boost/program_options.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include "server.hpp"
#include "connection.hpp"

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

void Server::run() {
	awaitConnections();
}

void Server::awaitConnections() {
	acceptor_->accept(blackConnection_->socket());
	blackConnection_->sendStr("Server: You have successfully conneced.\n");
	std::cout << "Server: Black has successfully connected.\n";
	acceptor_->accept(whiteConnection_->socket());
	whiteConnection_->sendStr("Server: You have successfully conneced.\n");
	std::cout << "Server: White has successfully connected.\n";
}

