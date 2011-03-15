#include <string>
#include <boost/regex.hpp>
#include "position.hpp"
#include "exception.hpp"

const boost::regex Position::validPos_("^[A-D][1-4][a-d][1-4]$");

Position::Position() {
	for (int a = 0; a < 4; ++a)
		arr_[a] = 0;
}

Position::Position(std::string const& str) {
	#ifndef NDEBUG
	// Check for illegal string. Should be done elsewhere already, so only
	// doing it when debugging.
	if (!regex_match(str, validPos_)) {
		BOOST_THROW_EXCEPTION(ExcInvalidPos()); 
	}
	#endif
	arr_[0] = str[0] - 'A';
	arr_[1] = str[1] - '1';
	arr_[2] = str[2] - 'a';
	arr_[3] = str[3] - '1';
}

Position::Position(int a, int b, int c, int d) {
	arr_[0] = a;
	arr_[1] = b;
	arr_[2] = c;
	arr_[3] = d;
}

uint& Position::operator[](size_t i) {
	if (i > 3)
		return arr_[0];
	else
		return arr_[i];
}

uint const& Position::operator[](size_t i) const {
	if (i > 3)
		return arr_[0];
	else
		return arr_[i];
}

