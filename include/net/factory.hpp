#ifndef FDGO_INCLUDE_NET_FACTORY_HPP
#define FDGO_INCLUDE_NET_FACTORY_HPP

#include <QTcpSocket>
#include <boost/shared_ptr.hpp>
#include <net/header.hpp>
#include <net/object.hpp>

namespace fdgo {
namespace net {

class Factory {
    public:
	Object::Pointer makeFromIncoming();

	Factory(QTcpSocket* sock = 0); 
	~Factory();

	void setSock(QTcpSocket* sock);
	bool hasMore();

    private:
	Header* header_;
	QTcpSocket* sock_;
};

}
}

#endif // Guard
