#include <iostream>
#include <QString>
#include <QtCore>
#include <QApplication>
#include <server/server.hpp>
#include <exceptions.hpp>

using namespace fdgo;
using namespace fdgo::server;

int main(int argc, char** argv) {
	try {
		QApplication qapp(argc, argv);
		Server s;
		return qapp.exec();
	}
	catch (ExcSuccessExit& e) {
	}
	catch (boost::exception& e) {
		std::cerr << "An exception has been caught." << std::endl;

		if (QString const* ti = boost::get_error_info<type_err_msg>(e))
			std::cerr << "Error type info: " << ti->toStdString() << std::endl;
		else
			std::cerr << "No error type info provided." << std::endl;

		if (QString const* msg = boost::get_error_info<err_msg>(e))
			std::cerr << "Error message: " << msg->toStdString() << std::endl;
		else
			std::cerr << "No error message provided." << std::endl;

		#ifndef NDEBUG
			std::cerr << "\nDiagnostics info:\n";
			std::cerr << boost::diagnostic_information(e);
		#endif
	}
	return 0;
}
