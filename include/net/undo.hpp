#ifndef FDGO_INCLUDE_NET_UNDO_HPP
#define FDGO_INCLUDE_NET_UNDO_HPP

#include <string>
#include <vector>
#include <net/object.hpp>
#include <net/header.hpp>

namespace fdgo {
namespace net {

//! \brief Message that is sent to request an undo.
//!
//! Should inherit net::Null.

class Undo : public Object {
  public:
	typedef boost::shared_ptr<Undo> Pointer;

	Undo(); 
	Undo(Header const& header);

  protected:
	void printOn(QDataStream& ds) const;
	void readFrom(QDataStream& ds);
};

}
}

#endif // Guard
