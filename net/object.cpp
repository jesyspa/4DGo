#include <boost/asio.hpp>
#include <net/all.hpp>
#include <exceptions.hpp>

using boost::asio::ip::tcp;

namespace fdgo {
namespace net {

Object::Object() {
}

Object::Object(Header const& header) : header_(header) {
}

Object::Pointer Object::makeFromIncoming(tcp::socket& sock) {
	Header h;
	h.read(sock);
	Object::Pointer p;
	switch (h.getType()) {
		case Header::Null:
			p.reset(new Null(h));
			break;
		case Header::Error:
			p.reset(new Error(h));
			break;
		case Header::Greeting:
			p.reset(new Greeting(h));
			break;
		case Header::Message:
			p.reset(new Message(h));
			break;
		case Header::Move:
			p.reset(new Move(h));
			break;
		case Header::Undo:
			p.reset(new Undo(h));
			break;
		case Header::History:
			BOOST_THROW_EXCEPTION(ExcNotImplemented());
		case Header::CloseConnection:
			p.reset(new CloseConnection(h));
			break;
		default:
			BOOST_THROW_EXCEPTION(ExcIncorrectNetObjectType());
	}
	p->read(sock);
	return p;
}

Header::Type Object::getType() {
	return header_.getType();
}

}
}
