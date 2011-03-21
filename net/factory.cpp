#include <QTcpSocket>
#include <QDataStream>
#include <net/factory.hpp>
#include <net/all.hpp>

namespace fdgo {
namespace net {

Factory::Factory(QTcpSocket* sock) : header_(0), sock_(sock) {
}

Factory::~Factory() {
	delete header_;
}

Object::Pointer Factory::makeFromIncoming() {
	if (!sock_)
		return Object::Pointer();
	QDataStream in(sock_);
	in.setVersion(QDataStream::Qt_4_6);
	if (!header_) { // We don't have a header, let's make one.
		#ifndef NDEBUG
		quint16 b = sock_->bytesAvailable();
		if (b < Header::hsize)
			return Object::Pointer();
		#else
		if (sock_->bytesAvailable() < Header::hsize)
			return Object::Pointer();
		#endif
		// We have enough bytes, let's get the header.
		header_ = new Header();
		in >> *header_;
	}
	if (sock_->bytesAvailable() < header_->psize)
		return Object::Pointer();
	// We have enough bytes for the full packet. :D
	Object::Pointer p;
	switch (header_->type) {
		case Header::Null:
			p.reset(new Null(*header_));
			break;
		case Header::Error:
			p.reset(new Error(*header_));
			break;
		case Header::Greeting:
			p.reset(new Greeting(*header_));
			break;
		case Header::Message:
			p.reset(new Message(*header_));
			break;
		case Header::Move:
			p.reset(new Move(*header_));
			break;
		case Header::Undo:
			p.reset(new Undo(*header_));
			break;
		case Header::Turn:
			p.reset(new Turn(*header_));
			break;
		case Header::History:
			p.reset(new History(*header_));
			break;
		case Header::CloseConnection:
			p.reset(new CloseConnection(*header_));
			break;
		default:
			BOOST_THROW_EXCEPTION(ExcIncorrectNetObjectType());
	}
	in >> *p;
	delete header_;
	header_ = 0;
	return p;
}

void Factory::setSock(QTcpSocket* sock) {
	sock_ = sock;
}

bool Factory::hasMore() {
	return (sock_->bytesAvailable() >= Header::hsize);
}

}
}
