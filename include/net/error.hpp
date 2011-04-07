#ifndef FDGO_INCLUDE_NET_ERROR_HPP
#define FDGO_INCLUDE_NET_ERROR_HPP

#include <QString>
#include <net/object.hpp>
#include <net/header.hpp>

class QDataStream;

namespace fdgo {
namespace net {

//! \brief Message sent to denote an error.
//!
//! Contains the type and an error message. Should probably inherit from
//! net::Message.

class Error : public Object {
  public:
	typedef boost::shared_ptr<Error> Pointer;

	enum EType {
		unknownError,
		unexpectedType,
		invalidMove
	} err_type;

	Error(); 
	Error(int er, QString const& str);
	Error(Header const& header);

	//! Throws the error it contains (or ExcUnknownError if it can't determine).
	void throwSelf();

	QString msg;

  protected:
	void printOn(QDataStream& ds) const;
	void readFrom(QDataStream& ds);
};

}
}

#endif // Guard
