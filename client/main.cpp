#include <iostream>
#include <client/client.hpp>
#include <exceptions.hpp>

using namespace fdgo;

int main(int argc, char** argv) {
	try {
		client::Client c(argc, argv);
		c.connect();
		c.run();
	}
	catch (ExcSuccessExit& e) {
	}
	catch (boost::exception& e) {
		std::cerr << "An exception has been caught." << std::endl;

		if (std::string const* ti = boost::get_error_info<type_err_msg>(e))
			std::cerr << "Error type info: " << *ti << std::endl;
		else
			std::cerr << "No error type info provided." << std::endl;

		if (std::string const* msg = boost::get_error_info<err_msg>(e))
			std::cerr << "Error message: " << *msg << std::endl;
		else
			std::cerr << "No error message provided." << std::endl;

		#ifndef NDEBUG
			std::cerr << "\nDiagnostics info:\n";
			std::cerr << boost::diagnostic_information(e);
		#endif
	}
	return 0;
}