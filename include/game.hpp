#ifndef FDGO_INCLUDE_GAME_HPP
#define FDGO_INCLUDE_GAME_HPP

#include "memory.hpp"
#include "goban.hpp"

class Game {
    private:
	// Should never be called.
	Game(Game const&); 
	Game& operator=(Game const&);
    public:
	Game(int argc, char** argv); 
	void waitForPlayers();
	void playGame();
    private:
    	unsigned int port_;
	Memory mem_;
	Goban goban_;
};

#endif // Guard



