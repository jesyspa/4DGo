#ifndef FDGO_INCLUDE_NET_GREETING_HPP
#define FDGO_INCLUDE_NET_GREETING_HPP

#include <net/object.hpp>
#include <net/header.hpp>

namespace fdgo {
namespace net {

//! \brief An object of this class is sent to the client to inform it of the
//!        details of this game.

class Greeting : public Object {
    public:
	typedef boost::shared_ptr<Greeting> Pointer;

	Greeting(); 
	Greeting(double komi, bool black);
	Greeting(Header const& header);
	
	double komi;
	bool black;

    protected:
	void printOn(QDataStream& ds) const;
	void readFrom(QDataStream& ds);
};

}
}

#endif // Guard
