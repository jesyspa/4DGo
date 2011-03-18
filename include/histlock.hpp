#ifndef FDGO_INCLUDE_HISTLOCK_HPP
#define FDGO_INCLUDE_HISTLOCK_HPP

#include <history.hpp>

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
	HistLock(History& m) : m_(m) {
		m_.locked_++;
	}
	~HistLock() {
		m_.locked_--;
	}
    private:
	History& m_;
};

}

#endif // Guard
