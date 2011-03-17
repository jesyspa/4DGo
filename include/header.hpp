#ifndef FDGO_INCLUDE_HEADER_HPP
#define FDGO_INCLUDE_HEADER_HPP

#include <cstdint>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include "exception.hpp"

//! \brief Header for everything sent.
//!
//! Current layout:
//!
//! int32_t version
//!
//! uint16_t type
//!
//! uint16_t length
//!
//! Total used: 8 bytes
//! Total size: 32 bytes
class Header {
    public:
	//! Allows to check that the clients are compatible. The comparison is
	//! done with &~0xFF, so versions with only the lowest byte different
	//! will still work together.
	static const uint32_t version = 1; 
	static const unsigned int hs = 32; // Header size
	enum Type {
		Null,
		Error,
		Greeting, // Server sends this to the player to inform him of his colour, etc.
		Message,
		Move,
		History, // Popping, disabling, and enabling history.
		CloseConnection
	};

	Header();
	Header(int type, int length);

	bool versionsMatch();
	Type getType();
	void setType(int type);
	size_t getLength();
	void setLength(size_t length);

	void write(boost::asio::ip::tcp::socket& sock);
	void read(boost::asio::ip::tcp::socket& sock);

    private:
	template<typename T>
	T& msgAs(size_t index);
	uint32_t getVersion();
	void setVersion(uint32_t vs);

	boost::array<uint8_t, hs> msg;
};

#endif // Guard
