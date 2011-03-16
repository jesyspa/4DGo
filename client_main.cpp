#include <iostream>
#include "client.hpp"
#include "exception.hpp"

int main(int argc, char** argv) {
	try {
		Client c(argc, argv);
		c.connect();
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
