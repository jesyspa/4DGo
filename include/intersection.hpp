#ifndef FDGO_INCLUDE_INTERSECTION_HPP
#define FDGO_INCLUDE_INTERSECTION_HPP
class Stone;

class Intersection {
	// Explicitly forbidden
	Intersection(Intersection const&);
	Intersection& operator=(Intersection const&);
    public:
	Intersection();
	~Intersection();
    private:
	bool isEmpty;
	Stone* stone;
};

#endif // Guard
