#ifndef FDGO_INCLUDE_CLIENT_HPP
#define FDGO_INCLUDE_CLIENT_HPP

//! \brief Main interface for the client side.
//!
//! This is an abstraction for the client side of the server-client
//! connection.

class Client {
    private:
	// Should never be called.
	Client(Client const&); 
	Client& operator=(Client const&);
    public:
	Client(); 
	void connectToIP();
	void placeStone();
	void pass();
    private:
};

#endif // Guard

