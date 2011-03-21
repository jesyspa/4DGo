#include <QDataStream>
#include <net/header.hpp>
#include <exceptions.hpp>

using boost::asio::ip::tcp;

namespace fdgo {
namespace net {

Header::Header() : psize(0) {
	type = Null;
}

Header::Header(int type) : psize(0) {
	this->type = HType(type);
}

QDataStream& operator<< (QDataStream& ds, Header const& h) {
	return ds << qint32(h.type) << h.psize;
}

QDataStream& operator>> (QDataStream& ds, Header& h) {
	qint32 tmp;
	ds >> tmp >> h.psize;
	h.type = Header::HType(tmp); 
	return ds;
}

}
}
