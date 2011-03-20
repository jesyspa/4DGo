#ifndef FDGO_INCLUDE_NET_HEADER_HPP
#define FDGO_INCLUDE_NET_HEADER_HPP

#include <cstdint>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <exceptions.hpp>

namespace fdgo {
namespace net {

//! \brief Header for everything sent.
//!
//! Current layout:\n
//! int32_t version\n
//! uint16_t type\n
//! uint16_t length\n
//! Total used: 8 bytes\n
//! Total size: 32 bytes
class Header {
    public:
	//! Allows to check that the clients are compatible. The comparison is
	//! done with &~0xFF, so versions with only the lowest byte different
	//! will still work together.
	static const uint32_t version = 2; 
	static const unsigned int hs = 32; // Header size
	enum Type {
		Null,
		Error,
		Greeting, // Server sends this to the player to inform him of his colour, etc.
		Message,
		Move,
		Undo,
		History, // Popping, disabling, and enabling history.
		CloseConnection
	};

	Header();
	Header(int type, int length);

	bool versionsMatch() const;
	Type getType() const;
	void setType(int type);
	size_t getLength() const;
	void setLength(size_t length);

	void write(boost::asio::ip::tcp::socket& sock);
	void read(boost::asio::ip::tcp::socket& sock);

    private:
	template<typename T>
	T& msgAs(size_t index);
	template<typename T>
	T const& msgAs(size_t index) const;

	uint32_t getVersion() const;
	void setVersion(uint32_t vs);

	boost::array<uint8_t, hs> msg;
};

}
}

#endif // Guard
