#include <string>
#include <deque>
#include <iterator>
#include <iostream>
#include <client/chatbox.hpp>

namespace fdgo {
namespace client {

Chatbox::Chatbox() {
}

void Chatbox::addMessage(std::string const& str) {
	messages_.push_back(str);
	if (messages_.size() > 7)
		messages_.pop_front();
}
void Chatbox::clear() {
	messages_.clear();
}
void Chatbox::draw() {
	for (std::deque<std::string>::iterator it = messages_.begin();
	     it != messages_.end();
	     ++it) {
		std::cout << *it << "\n";
	}
}

}
}
