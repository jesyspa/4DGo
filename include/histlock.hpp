#ifndef FDGO_INCLUDE_HISTLOCK_HPP
#define FDGO_INCLUDE_HISTLOCK_HPP

#include <QDataStream>
#include <QTcpSocket>
#include <history.hpp>
#include <net/history.hpp>

namespace fdgo {

//! \brief Stops a history object from saving events.
//!
//! This is intended to protect the history from being permanently locked if an
//! exception is thrown while it is locked.
//!
//! The lock only applies to new entries being appended, popping still works
//! fine.

class HistLock {
    private:
	// Should never be called.
	HistLock(HistLock const&); 
	HistLock& operator=(HistLock const&);
    public:
	HistLock(History* h, QTcpSocket* sock = 0) : h_(h), sock_(sock), locked_(true) {
		if (sock_) {
			net::History nhi(net::History::lock);
			nhi.write(sock_);
		}
		h_->locked_++;
	}

	~HistLock() {
		if (sock_) {
			net::History nhi(net::History::unlock);
			nhi.write(sock_);
		}
		h_->locked_--;
	}
    private:
	History* h_;
	QTcpSocket* sock_;
	bool locked_;
};

}

#endif // Guard
