#ifndef FDGO_INCLUDE_CLIENT_CHAT_HPP
#define FDGO_INCLUDE_CLIENT_CHAT_HPP

#include <string>
#include <deque>

namespace fdgo {
namespace client {

//! \brief Box where warnings and player messages appear.

class Chatbox {
    private:
	// Should never be called.
	Chatbox(Chatbox const&); 
	Chatbox& operator=(Chatbox const&);
    public:
	Chatbox();
	void addMessage(std::string const& str);
	void clear();
	void draw();
    private:
	std::deque<std::string> messages_;
};

}
}

#endif // Guard

