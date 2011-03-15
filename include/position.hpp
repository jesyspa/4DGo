#ifndef FDGO_INCLUDE_POSITION_HPP
#define FDGO_INCLUDE_POSITION_HPP

#include <string>
#include <boost/regex.hpp>
#include <boost/array.hpp>

typedef unsigned int uint;

struct Position {
	Position();
	Position(std::string const& str);
	Position(int a, int b, int c, int d);
	uint& operator[](size_t i);
	uint const& operator[](size_t i) const;
	Position up() const {
		Position pos = *this;
		pos[3]++;
		return pos;
	}
	Position down() const {
		Position pos = *this;
		pos[3]--;
		return pos;
	}
	Position left() const {
		Position pos = *this;
		pos[2]--;
		return pos;
	}
	Position right() const {
		Position pos = *this;
		pos[2]++;
		return pos;
	}
	Position farup() const {
		Position pos = *this;
		pos[1]++;
		return pos;
	}
	Position fardown() const {
		Position pos = *this;
		pos[1]--;
		return pos;
	}
	Position farleft() const {
		Position pos = *this;
		pos[0]--;
		return pos;
	}
	Position farright() const {
		Position pos = *this;
		pos[0]++;
		return pos;
	}
	std::string toString() const {
		std::string s("Lnln");
		s[0] = arr_[0] + 'A';
		s[1] = arr_[1] + '1';
		s[2] = arr_[2] + 'a';
		s[3] = arr_[3] + '1';
		return s;
	}

    private:
	boost::array<uint,4> arr_;
	static const boost::regex validPos_;
};

#endif // Guard
