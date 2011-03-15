#ifndef FDGO_INCLUDE_MEMLOCK_HPP
#define FDGO_INCLUDE_MEMLOCK_HPP

#include "memory.hpp"

//! \brief Stops a memory object from saving events.
//!
//! This is intended to protect the memory from being permanently locked if an
//! exception is thrown while it is locked.
//!
//! The lock only applies to new entries being appended, popping still works
//! fine.

class MemLock {
    private:
	// Should never be called.
	MemLock(MemLock const&); 
	MemLock& operator=(MemLock const&);
    public:
	MemLock(Memory& m) : m_(m) {
		m_.locked_++;
	}
	~MemLock() {
		m_.locked_--;
	}
    private:
	Memory& m_;
};

#endif // Guard

