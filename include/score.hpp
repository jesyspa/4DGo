#ifndef FDGO_INCLUDE_SCORE_HPP
#define FDGO_INCLUDE_SCORE_HPP

namespace fdgo {

struct Score {
	Score() : black(0), white(0), komi(0.5) {}
	unsigned int black, white;
	double komi;
};

}

#endif // Guard
