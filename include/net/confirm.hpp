#ifndef FDGO_INCLUDE_NET_CONFIRM_HPP
#define FDGO_INCLUDE_NET_CONFIRM_HPP

#include <QString>
#include <net/object.hpp>
#include <net/header.hpp>

class QDataStream;

namespace fdgo {
namespace net {

//! \brief Message sent to request confirmation of an action.
//!
//! Action is stored in the queue, not passed along. Might want to change
//! this if it proves hard-to-use.

class Confirmation : public Object {
  public:
	typedef boost::shared_ptr<Confirmation> Pointer;

	Confirmation(); 
	Confirmation(bool give);
	Confirmation(Header const& header);

	bool given;

  protected:
	void printOn(QDataStream& ds) const;
	void readFrom(QDataStream& ds);
};

}
}

#endif // Guard

