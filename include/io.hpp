#ifndef FDGO_INCLUDE_IO_HPP
#define FDGO_INCLUDE_IO_HPP

class Goban;
struct Score;

class IO {
	// Explicitly forbidden
	IO(IO const&);
	IO& operator=(IO const&);
    public:
	IO(int argc, char** argv);
	~IO();
	void giveControl();
    private:
	void mainLoop();
	void showScore(Score const& sc);

	Goban* goban_;
	bool blackTurn_;
};

#endif // Guard

