#ifndef FDGO_INCLUDE_CLIENT_GUI_MAINWIDGET_HPP
#define FDGO_INCLUDE_CLIENT_GUI_MAINWIDGET_HPP

#include <QtGui/QWidget>

class QWidget;
class QFrame;
class QFormLayout;
class QHBoxLayout;
class QLabel;
class QLineEdit;
class QPushButton;
class QSpacerItem;
class QTextBrowser;
class QVBoxLayout;

namespace fdgo {
namespace client {

class Client;

namespace gui {

class Chatbox;
class Goban;
class Info;

class MainWidget : public QWidget {
	Q_OBJECT
    public:
	MainWidget(QWidget* parent = 0);

    private:
	QVBoxLayout* vlMain_;
	QHBoxLayout* hlGobanInfo_;
	Goban* goban_;
	QFrame* vlnGobanInfo_;
	Info* info_;
	QVBoxLayout* vlInfo_;
	QFormLayout* flInfo_;
	QFrame* lnInfo_;
	QPushButton* btnPass_;
	QPushButton* btnUndo_;
	QPushButton* btnExit_;
	QSpacerItem* vspcInfo_;
	Chatbox* cbox_;
	Client* client_;
};

}
}
}

#endif // Guard
