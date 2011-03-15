#ifndef FDGO_INCLUDE_SERVER_HPP
#define FDGO_INCLUDE_SERVER_HPP


class Server {
    private:
	// Should never be called.
	Server(Server const&); 
	Server& operator=(Server const&);
    public:
	Server(); 
    private:
};

#endif // Guard


