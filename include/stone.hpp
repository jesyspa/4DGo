#ifndef FDGO_INCLUDE_STONE_HPP
#define FDGO_INCLUDE_STONE_HPP
class Chain;
class Intersection;

class Stone {
	// Explicitly forbidden
	Stone(Stone const&);
	Stone& operator=(Stone const&);
    public:
	Stone(Intersection* iPtr, bool black);
	~Stone();
    private:
	Chain* chain_;
	Intersection const* iPtr_;
	const bool black_; // Otherwise white
};

#endif // Guard

