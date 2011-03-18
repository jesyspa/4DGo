#ifndef FDGO_INCLUDE_NET_ERROR_HPP
#define FDGO_INCLUDE_NET_ERROR_HPP

#include <string>
#include <vector>
#include <boost/asio.hpp>
#include <net/object.hpp>
#include <net/header.hpp>

namespace fdgo {
namespace net {

//! \brief Base class for sending and receiving errors.
//!
//! Current layout:\n
//! uint16_t type
//! arbitrary amount of data

class Error : public Object {
    public:
	typedef boost::shared_ptr<Error> Pointer;

	enum EType {
		unexpectedType,
		invalidMove
	} type;

	Error(); 
	Error(int er, std::string const& str);
	Error(Header const& header);
	void write(boost::asio::ip::tcp::socket& sock);
	EType getError();
	void setError(int er);
	std::string getString();
	void setString(std::string str);
	
	//! Throws the error it contains (or ExcUnknownError if it can't determine).
	void throwSelf();

    private:
	template<typename T>
	T& msgAs(size_t index);

	void read(boost::asio::ip::tcp::socket& sock);
	std::vector<char> msg_;
};

}
}

#endif // Guard
