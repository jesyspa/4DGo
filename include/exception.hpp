#ifndef FDGO_INCLUDE_EXCEPTION_HPP
#define FDGO_INCLUDE_EXCEPTION_HPP

#include <boost/exception/all.hpp>
#include <string>
#include <exception>

typedef boost::error_info<struct tag_err_msg,std::string> err_msg;
typedef boost::error_info<struct tag_type_err_msg,std::string> type_err_msg;

struct ExcSuccessExit : virtual boost::exception, virtual std::exception {
	ExcSuccessExit() {
		*this << type_err_msg("Program completed successfully.");
	}
};

struct ExcInvalidMove : virtual boost::exception, virtual std::exception {};

struct ExcNotImplemented : virtual boost::exception, virtual std::exception {
	ExcNotImplemented() {
		*this << type_err_msg("Requested functionality not implemented.");
	}
};

struct ExcEOF : virtual boost::exception, virtual std::exception {
	ExcEOF() {
		*this << type_err_msg("End of file reached.");
	}
};

#endif // Guard
