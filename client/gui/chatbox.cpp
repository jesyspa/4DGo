#include <QtGui>
#include <QString>
#include <QStringList>
#include <client/gui/chatbox.hpp>
#include <position.hpp>

namespace fdgo {
namespace client {
namespace gui {

const QRegExp Chatbox::rgxPos("^[a-d][1-4][a-d][1-4]$");

Chatbox::Chatbox (QWidget* parent) : QWidget(parent) {
        vlMain_ = new QVBoxLayout(this);
        vlMain_->setObjectName(QString::fromUtf8("Chatbox::vlMain"));
	// Adding stuff to main layout {
		tbCBox_ = new QTextBrowser(this);
		tbCBox_->setObjectName(QString::fromUtf8("Chatbox::tbCBox"));
		vlMain_->addWidget(tbCBox_);

		hlInputLine_ = new QHBoxLayout();
		hlInputLine_->setObjectName(QString::fromUtf8("Chatbox::hlInputLine"));
		// Adding stuff to bottom layout {
			leInputLine_ = new QLineEdit(this);
			leInputLine_->setObjectName(QString::fromUtf8("Chatbox::leInputLine"));
			hlInputLine_->addWidget(leInputLine_);

			btnSubmit_ = new QPushButton(tr("&Submit"), this);
			btnSubmit_->setObjectName(QString::fromUtf8("Chatbox::btnSubmit"));
			hlInputLine_->addWidget(btnSubmit_);
		//}
		vlMain_->addLayout(hlInputLine_);
	//}
	btnSubmit_->setEnabled(false);
	
	QWidget::setTabOrder( leInputLine_, btnSubmit_ );

	connect(leInputLine_, SIGNAL(textChanged(QString)),
	                this, SLOT(  inputValid(QString))
	       );
	connect(        this, SIGNAL(setSubmit(bool)),
	          btnSubmit_, SLOT(  setEnabled(bool))
	       );
	connect(  btnSubmit_, SIGNAL(clicked()),
	                this, SLOT(  submitInput())
	       );
	connect(leInputLine_, SIGNAL(returnPressed()),
	                this, SLOT(  submitInput())
	       );
	display(tr("Welcome to 4DGo"));
	display(tr("Enter !help or !h for more information."));
	display("");
}

void Chatbox::inputValid(QString const& text) {
	emit setSubmit(!text.isEmpty());
}

void Chatbox::display(QString const& str) {
	tbCBox_->append(str);
}

void Chatbox::submitInput() {
	QString str = leInputLine_->text();
	leInputLine_->setText("");
	if (!str.isEmpty())
		parseString(str);
}

void Chatbox::parseString(QString str) {
	if (str[0] != '!') {
		emit message(str);
		return;
	}
	str[0] = ' ';
	str = str.trimmed().toLower();
	QStringList list = str.split(QRegExp("\\s+"));
	QStringList::const_iterator it = list.begin();
	if (it->contains(rgxPos)) {
		emit playStone(Position(*it));
	} else if (*it == "pass" || *it == "p") {
		emit pass();
	} else if (*it == "undo" || *it == "u") {
		emit undo();
	} else if (*it == "kill" || *it == "k") {
		if (++it == list.end() || !it->contains(rgxPos))
			display("Expected position as second argument.");
		else
			emit kill(Position(*it));
	} else if (*it == "exit" || *it == "e") {
		emit exit();
	} else if (*it == "connect" || *it == "c") {
		if (++it != list.end()) {
			emit setHost(*it);
			if (++it != list.end()) {
				emit setPort(it->toInt());
			}
		}
		emit cl_connect();
	} else if (*it == "disconnect" || *it == "dc") {
		emit cl_disconnect();
	} else if (*it == "yes" || *it == "y") {
		emit confirm(true);
	} else if (*it == "no" || *it == "n") {
		emit confirm(false);
	} else if (*it == "save" || *it == "s") {
		if (++it == list.end())
			display("Expected filename as second argument.");
		else
			emit writeLogToDisk(*it);
	} else if (*it == "help" || *it == "h" ) {
		display("4DGo -- A four-dimensional goban for online play.");
		display("All commands start with a '!'. Any input that does not is treated as a chat message. All comands are case-insensitive.");
		display("  Commands:");
		display("!connect [hostname] [port]: connect to the game server. By default, localhost:15493 will be used.");
		display("!disconnect: break connection to server and clear the goban.");
		display("!A4d4: on slice A4 (top-left), on intersection d4 (top-right).");
		display("!pass: end your turn without playing a stone.");
		display("!undo: request that your last move be undone.");
		display("!yes: allow the action your opponent requested (usually an undo or kill).");
		display("!yes: refuse to allow the action your opponent requested (usually an undo or kill).");
		display("!kill: request a certain group to be immediately taken off the board. Useful in endgame, to not need to play out all captures.");
		display("!save filename: save the current history to file filename.");
		display("!exit: disconnect and close the window.");
	} else {
		tbCBox_->append(QString("Unknown command: ")+*it);
	}
}

}
}
}
