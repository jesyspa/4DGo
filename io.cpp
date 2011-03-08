#include <iostream>
#include <string>
#include "io.hpp"
#include "goban.hpp"
#include "score.hpp"

IO::IO(int argc, char** argv) : goban_(0), blackTurn_(true) {

}

IO::~IO() {

}

void IO::giveControl() {
	try {
		for(;;)
			mainLoop();
	}
	catch (...) { // Exit
		
	}
}

void IO::mainLoop() {
	std::string input;
	if (!std::getline(std::cin, input))
		throw 'e'; // exit.
	if (input.find("pass") == 0) {
		blackTurn_ = !blackTurn_;
	} else if (input.find("score") == 0) {
		showScore(goban_->makeScore());
	} else if (input.find("kill ") == 0) {
		input = input.substr(5);
		
	}
}
