#include <iostream>
#include <client/fakegoban.hpp>
#include <position.hpp>
#include <exceptions.hpp>

namespace fdgo {
namespace client {

FakeGoban::FakeGoban() {
	for (size_t i = 0; i < boardarea_; ++i)
		intrArr_[i] = '.';
	prisoners_[0] = 0;
	prisoners_[1] = 0;
}

void FakeGoban::placeStone(bool black, Position const& pos) {
	getIntersection(pos) = black ? 'X' : 'O';
}

void FakeGoban::removeStone(Position const& pos) {
	getIntersection(pos) = '.';
}

void FakeGoban::addToPrisonerCount(bool black, unsigned int num) {
	int i = black ? 1 : 0;
	prisoners_[i] -= num;
}

void FakeGoban::subFromPrisonerCount(bool black, unsigned int num) {
	int i = black ? 1 : 0;
	if (prisoners_[i] < num)
		prisoners_[i] = 0;
	else
		prisoners_[i] -= num;
}

void FakeGoban::draw() {
	std::cout << "\n        A    B    C    D\n\n";
	for (int a = 0; a < 4; ++a) { // Large horizontal
		for (int b = 0; b < 4; ++b) { // Small horizontal
			if (b == 2)
				std::cout << "  " << 4-a << "   ";
			else
				std::cout << "      ";
			for (int c = 0; c < 4; ++c) { // Large vertical
				for (int d = 0; d < 4; ++d) // Small vertical
					std::cout << getIntersection(Position(c,3-a,d,3-b));
				std::cout << " ";
			}
			std::cout << "\n";
		}
		std::cout << "\n";
	}
}

char& FakeGoban::getIntersection(Position const& pos) {
	for (int a = 0; a < 4; ++a)
		if (pos[a] > 3)
			throw ExcInvalidPos();
	size_t i = pos[0]*4*4*4 +
	            pos[1]*4*4 +
	            pos[2]*4 +
	            pos[3];
	return intrArr_[i];
}

}
}
