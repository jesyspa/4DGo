#include <boost/bind.hpp>
#include <iostream>
#include "connection.hpp"
#include "exception.hpp"

using boost::asio::ip::tcp;

Connection::Pointer Connection::create(boost::asio::io_service& io) {
	return Pointer(new Connection(io));
}

Connection::Connection(boost::asio::io_service& io_service) : socket_(io_service) {
}

Connection::~Connection() {
	socket_.close();
}

tcp::socket& Connection::socket() {
	return socket_;
}

void Connection::sendStr(std::string const& str) {
	boost::system::error_code error;
	boost::asio::write(socket_, boost::asio::buffer(str),
	    boost::asio::transfer_all(), error);
	if (error == boost::asio::error::eof) {
		throw ExcSuccessExit();
	} else if (error) {
		throw boost::system::system_error(error); // Some other error.
	}
}
