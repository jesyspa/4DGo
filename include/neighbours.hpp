#ifndef FDGO_INCLUDE_NEIGHBOURS_HPP
#define FDGO_INCLUDE_NEIGHBOURS_HPP
class Intersection;

struct Neighbours {
	Neighbours() : up(0), down(0), left(0), right(0), 
	    farup(0), fardown(0), farleft(0), farright(0) {}
	Intersection* up;
	Intersection* down;
	Intersection* left;
	Intersection* right;
	Intersection* farup;
	Intersection* fardown;
	Intersection* farleft;
	Intersection* farright;
};

#endif // Guard
