#include <iostream>
#include <io.hpp>
#include <exception.hpp>

int main(int argc, char** argv) {
	try {
		IO io(argc, argv);
		io.giveControl();
	}
	catch (ExcSuccessExit& e) {
		std::cout << "Successful exit.\n";
	}
	catch (boost::exception& e) { // Exit
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
