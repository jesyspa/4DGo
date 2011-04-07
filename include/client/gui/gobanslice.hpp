#ifndef FDGO_INCLUDE_CLIENT_GUI_GOBANSLICE_HPP
#define FDGO_INCLUDE_CLIENT_GUI_GOBANSLICE_HPP

#include <boost/array.hpp>
#include <QtGui/QFrame>

class QGridLayout;
class QLabel;

namespace fdgo {
namespace client {
namespace gui {

//! \brief A 4x4 goban, part of the 4x4x4x4 supergoban.
//!
//! Handles the display of individual intersections.

class GobanSlice : public QFrame {
	Q_OBJECT
  public:
	GobanSlice(QWidget* parent = 0);

  public slots:
	void setIcon(size_t c, size_t d, char icon);
	void clear();
	void clearHighlight();

  private:
	QGridLayout* glMain_;
	boost::array<boost::array<QLabel*, 4>, 4> grid_;
};

}
}
}

#endif // Guard

