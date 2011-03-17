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

