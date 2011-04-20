#ifndef FDGO_INCLUDE_NET_CLOSE_HPP
#define FDGO_INCLUDE_NET_CLOSE_HPP

#include <string>
#include <vector>
#include <net/object.hpp>
#include <net/header.hpp>

namespace fdgo {
namespace net {

//! \brief Message sent to warn that the connection will be closed.

class CloseConnection : public Object {
  public:
	typedef boost::shared_ptr<CloseConnection> Pointer;

	CloseConnection(); 
	CloseConnection(Header const& header);
  protected:
	void printOn(QDataStream& ds) const;
	void readFrom(QDataStream& ds);
};

}
}

#endif // Guard

