#ifndef FDGO_INCLUDE_NET_HISTORY_HPP
#define FDGO_INCLUDE_NET_HISTORY_HPP

#include <string>
#include <vector>
#include <net/object.hpp>
#include <net/header.hpp>

namespace fdgo {
namespace net {

//! \brief Message that contains instructions on what to do with history.
//!
//! Should only ever be sent from server to client. Not sure how to ensure
//! that.

class History : public Object {
  public:
	typedef boost::shared_ptr<History> Pointer;

	enum AType {
		lock,
		unlock,
		pop,
		null
	} action;

	History(); 
	History(int action);
	History(Header const& header);

  protected:
	void printOn(QDataStream& ds) const;
	void readFrom(QDataStream& ds);
};

}
}

#endif // Guard
