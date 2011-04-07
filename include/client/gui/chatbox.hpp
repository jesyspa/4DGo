#ifndef FDGO_INCLUDE_CLIENT_GUI_CHATBOX_HPP
#define FDGO_INCLUDE_CLIENT_GUI_CHATBOX_HPP

#include <QtGui/QWidget>
#include <position.hpp>

class QHBoxLayout;
class QLineEdit;
class QPushButton;
class QTextBrowser;
class QVBoxLayout;

namespace fdgo {
namespace client {
namespace gui {

//! \brief Controls the text I/O.
//!
//! Adding another layer between this and the server may be a good idea.

class Chatbox : public QWidget {
	Q_OBJECT
  public:
	Chatbox(QWidget* parent = 0);

  public slots:
	void inputValid(QString const& text);
	void display(QString const& str);

  private slots:
	void submitInput();

  signals:
	void setSubmit(bool);

	void message(QString const& str);
	void playStone(Position const& pos);
	void undo();
	void pass();
	void kill(Position const& pos);
	void confirm(bool give);
	void setHost(QString const& str);
	void setPort(int p);
	void cl_connect();
	void cl_disconnect();
	void writeLogToDisk(QString const& str);
	void exit();

  private:
	void parseString(QString str);

	QVBoxLayout* vlMain_;
	QTextBrowser* tbCBox_;
	QHBoxLayout* hlInputLine_;
	QLineEdit* leInputLine_;
	QPushButton* btnSubmit_;

	static const QRegExp rgxPos;
};

}
}
}

#endif // Guard
