#ifndef FDGO_INCLUDE_NETMOVE_HPP
#define FDGO_INCLUDE_NETMOVE_HPP

#include <boost/array.hpp>
#include "move.hpp"

//! \brief Class that contains a move while it is being sent over the net.
class NetMove {
    public:
	NetMove(); 
	NetMove(Move const&);
    	boost::array<int, 6> buf;
};

#endif // Guard


