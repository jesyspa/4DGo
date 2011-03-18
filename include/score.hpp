#ifndef FDGO_INCLUDE_SCORE_HPP
#define FDGO_INCLUDE_SCORE_HPP

namespace fdgo {

struct Score {
	Score();
	unsigned int black, white;
	bool blackVictory;
};

}

#endif // Guard
