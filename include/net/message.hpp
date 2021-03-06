#ifndef FDGO_INCLUDE_NET_MESSAGE_HPP
#define FDGO_INCLUDE_NET_MESSAGE_HPP

#include <QString>
#include <net/object.hpp>
#include <net/header.hpp>

class QDataStream;

namespace fdgo {
namespace net {

//! \brief Message for chat messages.
//!
//! Perhaps calling instances of the net:: classes `messages' was not a good
//! idea.

class Message : public Object {
  public:
	typedef boost::shared_ptr<Message> Pointer;

	Message(); 
	Message(QString const& str);
	Message(Header const& header);

	QString msg;

  protected:
	void printOn(QDataStream& ds) const;
	void readFrom(QDataStream& ds);
};

}
}

#endif // Guard
