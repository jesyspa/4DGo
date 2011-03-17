#include "netobject.hpp"
#include "netmessage.hpp"
#include "header.hpp"
#include "exception.hpp"

using boost::asio::ip::tcp;

NetObject::NetObject() {
}

NetObject::NetObject(Header const& header) : header_(header) {
}

NetObject::Pointer NetObject::makeFromIncoming(tcp::socket& sock) {
	Header h;
	h.read(sock);
	NetObject::Pointer p;
	switch (h.getType()) {
		case Header::Null:
		case Header::Greeting:
			BOOST_THROW_EXCEPTION(ExcNotImplemented());
		case Header::Message:
			p.reset(new NetMessage(h));
			p->read(sock);
			return p;
		case Header::Move:
		case Header::Confirm:
		case Header::Error:
		case Header::CloseConnection:
			BOOST_THROW_EXCEPTION(ExcNotImplemented());
	}
	return p;
}

Header::Type NetObject::getType() {
	return header_.getType();
}
