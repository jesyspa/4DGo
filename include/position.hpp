#ifndef FDGO_INCLUDE_POSITION_HPP
#define FDGO_INCLUDE_POSITION_HPP

#include <QString>
#include <QRegExp>
#include <boost/array.hpp>

namespace fdgo {

//! \brief Contains coordinates on the goban.
//!
//! String should be of format A1a1.

struct Position {
	Position();
	Position(QString const& str);
	Position(int a, int b, int c, int d);
	quint32& operator[](size_t i);
	quint32 const& operator[](size_t i) const;
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
	QString toString() const {
		QString s;
		s += arr_[0] + 'A';
		s += arr_[1] + '1';
		s += arr_[2] + 'a';
		s += arr_[3] + '1';
		return s;
	}

  private:
	boost::array<quint32,4> arr_;
};

}

#endif // Guard
