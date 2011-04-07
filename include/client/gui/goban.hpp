#ifndef FDGO_INCLUDE_CLIENT_GUI_GOBAN_HPP
#define FDGO_INCLUDE_CLIENT_GUI_GOBAN_HPP

#include <boost/array.hpp>
#include <QtGui/QWidget>
#include <position.hpp>

class QGridLayout;
class QLabel;

namespace fdgo {
namespace client {
namespace gui {

class GobanSlice;

//! \brief Handles the display of the 4x4x4x4 supergoban.
//!
//! For easier use, instead of having it interact directly with individual
//! intersections, this class contains 16 4x4 gobans. (This also allows for
//! simpler use of QGridLayout.)

class Goban : public QWidget {
	Q_OBJECT
  public:
	Goban(QWidget* parent = 0);

  public slots:
	void placeStone(bool black, Position const& pos);
	void removeStone(Position const& pos);
	void clear();
	void clearHighlight();

  private:
	void setIcon(size_t a, size_t b, size_t c, size_t d, char icon);

	QGridLayout* glMain_;
	boost::array<boost::array<GobanSlice*, 4>, 4> grid_;
	boost::array<QLabel*, 8> lblArr_;
};

}
}
}

#endif // Guard
