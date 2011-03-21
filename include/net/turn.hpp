#ifndef FDGO_INCLUDE_NET_TURN_HPP
#define FDGO_INCLUDE_NET_TURN_HPP

#include <net/object.hpp>
#include <net/header.hpp>

namespace fdgo {
namespace net {

//! \brief An object of this class is sent to the client to inform it of the
//!        details of this game.

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
