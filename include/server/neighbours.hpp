#ifndef FDGO_INCLUDE_SERVER_NEIGHBOURS_HPP
#define FDGO_INCLUDE_SERVER_NEIGHBOURS_HPP

#include <boost/shared_ptr.hpp>

namespace fdgo {
namespace server {

class Intersection;

struct Neighbours {
	typedef boost::shared_ptr<Neighbours> Pointer;

	Neighbours(
		Intersection* u, Intersection* d,
		Intersection* l, Intersection* r,
		Intersection* fu, Intersection* fd,
		Intersection* fl, Intersection* fr ) :
		up(u), down(d), left(l), right(r), 
		farup(fu), fardown(fd), farleft(fl), farright(fr) {}
	Intersection* up;
	Intersection* down;
	Intersection* left;
	Intersection* right;
	Intersection* farup;
	Intersection* fardown;
	Intersection* farleft;
	Intersection* farright;
};

}
}

#endif // Guard
