#ifndef FDGO_INCLUDE_IO_HPP
#define FDGO_INCLUDE_IO_HPP

#include <boost/regex.hpp>
#include <list>
#include <string>

class Memory;
class Goban;
struct Score;

//! \brief Handles all input and output from the user.

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
	void newMsg(std::string msg);
	
	std::string pColourUC() {
		return blackTurn_ ? "Black " : "White ";
	}

	Memory* mem_;
	Goban* goban_;
	bool blackTurn_;
	float komi_;
	std::list<std::string> msgList_;

	static const boost::regex pass;
	static const boost::regex move;
	static const boost::regex kill;
	static const boost::regex undo;
	static const boost::regex save;
	static const boost::regex getScore;
	static const boost::regex exit;
};

#endif // Guard

