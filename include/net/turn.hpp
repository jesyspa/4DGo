#ifndef FDGO_INCLUDE_NET_TURN_HPP
#define FDGO_INCLUDE_NET_TURN_HPP

#include <net/object.hpp>
#include <net/header.hpp>

namespace fdgo {
namespace net {

//! \brief Message that is sent to the client to inform it about a change of
//!        turn.

class Turn : public Object {
  public:
	typedef boost::shared_ptr<Turn> Pointer;

	Turn(); 
	Turn(bool black);
	Turn(Header const& header);
	
	bool black;

  protected:
	void printOn(QDataStream& ds) const;
	void readFrom(QDataStream& ds);
};

}
}

#endif // Guard
