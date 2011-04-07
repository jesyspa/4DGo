#include <net/all.hpp>
#include <exceptions.hpp>

namespace fdgo {
namespace net {

Object::Object() {
}

Object::Object(Header const& header) : header_(header) {
}

Header::HType Object::getType() const {
	return header_.type;
}


void Object::write(QTcpSocket* sock) const {
	if (!sock)
		return;
	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_6);
	out << this->header_;
	out << *this;
	out.device()->seek(Header::sizeStart);
	out << quint16((block.size()) - Header::hsize);
	sock->write(block);
}

QDataStream& operator<< (QDataStream& ds, Object const& o) {
	o.printOn(ds);
	return ds;
}

QDataStream& operator>> (QDataStream& ds, Object& o) {
	o.readFrom(ds);
	return ds;
}

}
}
