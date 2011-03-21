#ifndef FDGO_INCLUDE_NET_HISTORY_HPP
#define FDGO_INCLUDE_NET_HISTORY_HPP

#include <string>
#include <vector>
#include <boost/asio.hpp>
#include <net/object.hpp>
#include <net/header.hpp>

namespace fdgo {
namespace net {

//! \brief An object of this class is sent to the client to inform it of the
//!        details of this game.
//!
//! Current layout:\n
//! uint8_t black
//! 
//! double komi

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
