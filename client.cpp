#include <iostream>
#include <string>
#include <vector>
#include <boost/program_options.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include "client.hpp"
#include "move.hpp"
#include "netmove.hpp"
#include "netobject.hpp"
#include "netmessage.hpp"

namespace po = boost::program_options;
using boost::asio::ip::tcp;

Client::Client(int argc, char** argv) : sock_(io_), ip_("localhost"), port_("15493"), colour_("Unknown") {
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
	std::cout << "Connection successful.\n";
}

void Client::waitForMessage() {
	NetObject::Pointer nop = NetObject::makeFromIncoming(sock_);
	NetMessage::Pointer nmp;
	if (nop->getType() == Header::Message)
		nmp = boost::dynamic_pointer_cast<NetMessage>(nop);
	else
		BOOST_THROW_EXCEPTION(ExcIncorrectNetObjectType());
	std::cout << nmp->getString() << "\n";
}

void Client::sendMessage() {
	std::string str;
	std::getline(std::cin, str);
	NetMessage nm(str);
	nm.write(sock_);
	std::cout << "Message sent.\n";
}
