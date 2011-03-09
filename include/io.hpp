#ifndef FDGO_INCLUDE_IO_HPP
#define FDGO_INCLUDE_IO_HPP

#include <boost/regex.hpp>

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
	void redraw();

	Goban* goban_;
	bool blackTurn_;
	float komi_;

	static const boost::regex pass;
	static const boost::regex move;
	static const boost::regex kill;
	static const boost::regex getScore;
	static const boost::regex exit;
};

#endif // Guard

