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
		pop
	};

	History(); 
	History(int action);
	History(Header const& header);
	void write(boost::asio::ip::tcp::socket& sock);
	AType getAction();
	void setAction(int action);

    private:
	static const size_t size_ = 4;
	void read(boost::asio::ip::tcp::socket& sock);

	template<typename T>
	T& msgAs(size_t index);

	boost::array<char,size_> msg_;
};

}
}

#endif // Guard
