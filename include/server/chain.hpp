#ifndef FDGO_INCLUDE_SERVER_CHAIN_HPP
#define FDGO_INCLUDE_SERVER_CHAIN_HPP

#include <vector>
#include <boost/shared_ptr.hpp>
namespace fdgo {
namespace server {

class Stone;

//! \brief Represents a chain of stones. Should not be copied or deleted.
//!
//! Every stone should be a member of one, and only one chain. A stone that
//! cannot connect to a chain (due to being alone, for example) should create
//! a new chain with itself as the base.
class Chain {
    private:
	// Should never be called.
	Chain(Chain const&);
	Chain& operator=(Chain const&);
    public:
	typedef boost::shared_ptr<Chain> Pointer;

	Chain(Stone* st); // Create a chain from one stone.
	void addStone(Stone* st);
	void removeStone(Stone* st);
	void joinWith(Chain::Pointer ch);
	void considerDying(bool forbid = false); // DANGER! May cause object to poof!
	void die();
    private:
	bool checkLiberties();
	bool const black_;
	std::vector<Stone*> stonevec_;
};

}
}

#endif // Guard
