#include <iostream>
#include <string>
#include <boost/program_options.hpp>
#include <boost/regex.hpp>
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
	std::cout << "Enjoy the game.\n" << std::endl;
}

IO::~IO() {
	delete goban_;
}

void IO::giveControl() {
	for(;;)
		mainLoop();
}

void IO::mainLoop() {
	std::string input;
	if (!std::getline(std::cin, input))
		throw ExcEOF();
	try {
		if (regex_match(input, pass)) {
			std::cout << "Player has passed.\n";
		} else if (regex_match(input, move)) {
			std::cout << "Player has moved.\n";
		} else if (regex_match(input, kill)) {
			std::cout << "Player wants to kill something.\n";
		} else if (regex_match(input, getScore)) {
			std::cout << "Player wants the score.\n";
		} else if (regex_match(input, exit)) {
			BOOST_THROW_EXCEPTION(ExcSuccessExit());
		} else {
			std::cerr << "Unknown instruction.\n";
		}
	}
	catch (boost::exception& e) {
		redraw();
		throw;
	}
}

void IO::showScore(Score const& sc) {
	BOOST_THROW_EXCEPTION(ExcNotImplemented());
}

void IO::redraw() {
	BOOST_THROW_EXCEPTION(ExcNotImplemented());
}
