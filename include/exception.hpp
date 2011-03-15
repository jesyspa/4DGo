#ifndef FDGO_INCLUDE_EXCEPTION_HPP
#define FDGO_INCLUDE_EXCEPTION_HPP

#include <boost/exception/all.hpp>
#include <string>
#include <exception>

typedef boost::error_info<struct tag_err_msg,std::string> err_msg;
typedef boost::error_info<struct tag_type_err_msg,std::string> type_err_msg;


//! \brief Base class for all exceptions that must terminate the program.
struct ExcFatal : virtual boost::exception, virtual std::exception {};

//! \brief Base class for all exceptions that must not terminate the program.
struct ExcNonFatal : virtual boost::exception, virtual std::exception {};

struct ExcSuccessExit : ExcFatal {
	ExcSuccessExit() {
		*this << type_err_msg("Program completed successfully.");
	}
};

struct ExcInvalidMove : ExcNonFatal {};
struct ExcInvalidPos : ExcNonFatal {};
struct ExcNothingToUndo : ExcNonFatal {};

struct ExcNotImplemented : ExcFatal {
	ExcNotImplemented() {
		*this << type_err_msg("Requested functionality not implemented.");
	}
};

struct ExcEOF : ExcFatal {
	ExcEOF() {
		*this << type_err_msg("End of file reached.");
	}
};

#endif // Guard
