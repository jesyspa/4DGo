#ifndef FDGO_INCLUDE_NET_MOVE_HPP
#define FDGO_INCLUDE_NET_MOVE_HPP

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <net/object.hpp>
#include <net/header.hpp>
#include <move.hpp>
#include <position.hpp>

namespace fdgo {
namespace net {

//! \brief Message for denoting moves. 

class Move : public Object {
  public:
	typedef boost::shared_ptr<Move> Pointer;

	Move(); 
	Move(fdgo::Move const& mv);
	Move(Header const& header);
	
	fdgo::Move mv;

  protected:
	void printOn(QDataStream& ds) const;
	void readFrom(QDataStream& ds);
};

}
}

#endif // Guard
