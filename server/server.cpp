#include <iostream>
#include <boost/program_options.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include <server/server.hpp>
#include <server/connection.hpp>
#include <net/all.hpp>
#include <exceptions.hpp>

namespace po = boost::program_options;
using boost::asio::ip::tcp;

namespace fdgo {
namespace server {

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
	bCon_ = Connection::create(acceptor_->io_service());
	wCon_ = Connection::create(acceptor_->io_service());
}

Server::~Server() {
	delete acceptor_;
}

void Server::awaitConnections() {
	acceptor_->accept(bCon_->socket());
	std::cout << "Client has connected.\n";
}

void Server::waitForMessage() {
	net::Object::Pointer nop = net::Object::makeFromIncoming(bCon_->socket());
	net::Message::Pointer nmp;
	if (nop->getType() == net::Header::Message)
		nmp = boost::dynamic_pointer_cast<net::Message>(nop);
	else
		BOOST_THROW_EXCEPTION(ExcIncorrectNetObjectType());
	std::cout << nmp->getString() << "\n";
}

void Server::sendMessage() {
	std::string str;
	std::getline(std::cin, str);
	net::Message nm(str);
	nm.write(bCon_->socket());
	net::Null nn;
	nn.write(bCon_->socket());
	std::cout << "Message sent.\n";
}

}
}
