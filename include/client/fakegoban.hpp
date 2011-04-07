#ifndef FDGO_INCLUDE_CLIENT_FAKEGOBAN_HPP
#define FDGO_INCLUDE_CLIENT_FAKEGOBAN_HPP

#include <boost/array.hpp>
#include <position.hpp>

namespace fdgo {
namespace client {

//! \brief Visual goban -- stores the stones, but doesn't do anything with them.
//!
//! \deprecated

class FakeGoban {
	// Explicitly forbidden
	FakeGoban(FakeGoban const&);
	FakeGoban& operator=(FakeGoban const&);
  public:
	FakeGoban();
	void placeStone(bool black, Position const& pos);
	void removeStone(Position const& pos);
	void addToPrisonerCount(bool black, unsigned int num);
	void subFromPrisonerCount(bool black, unsigned int num);
	void draw();
  private:
	char& getIntersection(Position const& pos);

	static const unsigned int boardarea_ = 4*4*4*4;

	boost::array<char, boardarea_> intrArr_;
	unsigned int prisoners_[2];
};

}
}

#endif // Guard
