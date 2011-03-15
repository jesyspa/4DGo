#include <iostream>
#include <string>
#include <boost/lexical_cast.hpp>
#include <boost/regex.hpp>
#include <boost/program_options.hpp>
#include "io.hpp"
#include "goban.hpp"
#include "score.hpp"
#include "exception.hpp"

namespace po = boost::program_options;

const boost::regex IO::pass("^pass$");
const boost::regex IO::move("^[A-D][1-4][a-d][1-4]$");
const boost::regex IO::kill("^kill [A-D][1-4][a-d][1-4]$");
const boost::regex IO::getScore("^score$");
const boost::regex IO::exit("^exit$");

IO::IO(int argc, char** argv) : goban_(0), blackTurn_(true), komi_(0.5) {
	goban_ = new Goban(4);
	po::options_description desc("Allowed options");
	desc.add_options()
		("help", "show help message")
		("komi", po::value<float>(), "set komi amount")
	;

	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);    

	if (vm.count("help")) {
		std::cout << desc << "\n";
		throw ExcSuccessExit();
	}
	if (vm.count("komi")) {
		komi_ = vm["komi"].as<float>();
	}
	std::cout << "Initialisation complete.\n";
	std::cout << "The komi is " << komi_ << ".\n";
	std::cout << "Enjoy the game.\n";
}

IO::~IO() {
	delete goban_;
}

void IO::giveControl() {
	for(;;)
		mainLoop();
}

void IO::mainLoop() {
	redraw();
	std::string input;
	if (!std::getline(std::cin, input))
		BOOST_THROW_EXCEPTION(ExcEOF());
	try {
		if (regex_match(input, pass)) {
			goban_->pass(blackTurn_);
			blackTurn_ = !blackTurn_;
		} else if (regex_match(input, move)) {
			goban_->placeStone(blackTurn_, Position(input));
			blackTurn_ = !blackTurn_;
		} else if (regex_match(input, kill)) {
			goban_->killGroup(Position(input));
		} else if (regex_match(input, getScore)) {
			newMsg(pColourUC() + "player wants the score.");
		} else if (regex_match(input, exit)) {
			BOOST_THROW_EXCEPTION(ExcSuccessExit());
		} else {
			newMsg("Unknown instruction: " + input);
		}
	}
	catch (ExcNonFatal& e) {
		if (std::string const* msg = boost::get_error_info<err_msg>(e))
			newMsg(std::string("Error: " + *msg));
	}
}

void IO::showScore(Score const& sc) {
	BOOST_THROW_EXCEPTION(ExcNotImplemented());
}

void IO::redraw() {
	// Print an empty goban.
	std::cout << "\n\n\n|--------------------------|\n";
	std::cout << "\n        A    B    C    D\n\n";
	for (int a = 0; a < 4; ++a) { // Large horizontal
		for (int b = 0; b < 4; ++b) { // Small horizontal
			if (b == 2)
				std::cout << "  " << 4-a << "   ";
			else
				std::cout << "      ";
			for (int c = 0; c < 4; ++c) { // Large vertical
				for (int d = 0; d < 4; ++d) // Small vertical
					std::cout << goban_->getIcon(Position(c,3-a,d,3-b));
				std::cout << " ";
			}
			std::cout << "\n";
		}
		std::cout << "\n";
	}
	std::list<std::string>::iterator it = msgList_.begin();
	for ( ; it != msgList_.end(); ++it) {
		std::cout << *it << "\n";
	}
	std::cout << "\n|--------------------------|\n\n";
}

void IO::newMsg(std::string msg) {
	msgList_.push_back(msg);
	if (msgList_.size() > 5)
		msgList_.pop_front();
}
