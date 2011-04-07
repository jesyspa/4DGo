#ifndef FDGO_INCLUDE_NET_GREETING_HPP
#define FDGO_INCLUDE_NET_GREETING_HPP

#include <net/object.hpp>
#include <net/header.hpp>

namespace fdgo {
namespace net {

//! \brief Message that is sent when game starts.
//! 
//! Might want to have it inherit from Message, to add a MOTD.

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
