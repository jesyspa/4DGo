#ifndef FDGO_INCLUDE_CLIENT_GUI_INFO_HPP
#define FDGO_INCLUDE_CLIENT_GUI_INFO_HPP

#include <boost/array.hpp>
#include <QtGui/QWidget>
#include <QString>

class QFormLayout;
class QLabel;

namespace fdgo {
namespace client {
namespace gui {

//! \brief Displays information about the game.

class Info : public QWidget {
	Q_OBJECT
  public:
	Info(QWidget* parent = 0);

  public slots:
	void setColour(bool black);
	void setTurn(bool black);
	void setKomi(double komi);
	void setBlackCaps(int caps);
	void setWhiteCaps(int caps);
	void setConnection(QString const& str);

  private:
	QFormLayout* flInfo_;
	QLabel* lblColour_;
	QLabel* lblColourVal_;
	QLabel* lblTurn_;
	QLabel* lblTurnVal_;
	QLabel* lblBlackCaps_;
	QLabel* lblBlackCapsVal_;
	QLabel* lblWhiteCaps_;
	QLabel* lblWhiteCapsVal_;
	QLabel* lblKomi_;
	QLabel* lblKomiVal_;
	QLabel* lblConnection_;
	QLabel* lblConnectionVal_;

};

}
}
}

#endif // Guard
