#include <iostream>
#include <QtGui>
#include <client/client.hpp>
#include <client/gui/mainwidget.hpp>
#include <exceptions.hpp>

using namespace fdgo;
using namespace fdgo::client;

int main(int argc, char** argv) {
	try {
		QApplication qapp(argc, argv);
		gui::MainWidget mw;
		mw.show();
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
}
