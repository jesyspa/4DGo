#include <QString>
#include <QRegExp>
#include <position.hpp>
#include <exceptions.hpp>

namespace fdgo {

Position::Position() {
	for (int a = 0; a < 4; ++a)
		arr_[a] = 0;
}

Position::Position(QString const& str) {
	arr_[0] = str.toAscii()[0] - 'a';
	arr_[1] = str.toAscii()[1] - '1';
	arr_[2] = str.toAscii()[2] - 'a';
	arr_[3] = str.toAscii()[3] - '1';
}

Position::Position(int a, int b, int c, int d) {
	arr_[0] = a;
	arr_[1] = b;
	arr_[2] = c;
	arr_[3] = d;
}

quint32& Position::operator[](size_t i) {
	if (i > 3)
		return arr_[0];
	else
		return arr_[i];
}

quint32 const& Position::operator[](size_t i) const {
	if (i > 3)
		return arr_[0];
	else
		return arr_[i];
}

}
