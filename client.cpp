#include <iostream>
#include <string>
#include <vector>
#include <boost/program_options.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include "client.hpp"
#include "move.hpp"
#include "netmove.hpp"

namespace po = boost::program_options;
using boost::asio::ip::tcp;

Client::Client(int argc, char** argv) : socket_(io_), ip_("localhost"), port_("15493") {
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
		socket_.close();
		socket_.connect(*endpoint_iterator++, error);
	}
	if (error) // Make sure the connection is okay.
		throw boost::system::system_error(error);

	// Read the MOTD.
	std::vector<char> buf;
	size_t len = socket_.read_some(boost::asio::buffer(buf), error);
	if (error) // The server should never close the connection at this point.
		throw boost::system::system_error(error);
	std::cout.write(buf.data(), len);
}

bool Client::amBlack() {
	boost::system::error_code error;
	boost::array<int, 1> buf;
	socket_.read_some(boost::asio::buffer(buf), error);
	return buf[0];
}

NetMove Client::listenForMove() {
	boost::system::error_code error;
	NetMove nm;
	socket_.read_some(boost::asio::buffer(nm.buf), error);
	if (error) {
		throw boost::system::system_error(error); // Some other error.
	}
	return nm;
}

int Client::submitMove(Move const& mv) {
	boost::system::error_code error;
	NetMove nm(mv);
	boost::asio::write(socket_, boost::asio::buffer(nm.buf),
	    boost::asio::transfer_all(), error);
	return 0;
}
