#ifndef FDGO_INCLUDE_IO_HPP
#define FDGO_INCLUDE_IO_HPP

class Goban;

class IO {
	// Explicitly forbidden
	IO(IO const&);
	IO& operator=(IO const&);
    public:
	IO(int argc, char** argv);
	void giveControl();
    private:
	Goban* goban_;
};

#endif // Guard

