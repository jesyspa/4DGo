#ifndef FDGO_INCLUDE_SERVER_CHAIN_HPP
#define FDGO_INCLUDE_SERVER_CHAIN_HPP

#include <QVector>
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
	// Should only be called internally
	~Chain();
  public:
	Chain(Stone* st); // Create a chain from one stone.
	void addStone(Stone* st);
	void removeStone(Stone* st);
	void joinWith(Chain* ch);
	//! \brief Request that the chain check whether there are any stones with
	//!        liberties in it, and if not, die.
	//!
	//! Passing true will cause an exception to be thrown, instead of the
	//! chain dying.
	//!
	//! TODO: Check that the exception causes the chain to be deleted
	//! successfully!
	void considerDying(bool forbid = false); 
	void die();
  private:
	bool checkLiberties();
	bool const black_;
	QList<Stone*> stoneli_;
};

}
}

#endif // Guard
