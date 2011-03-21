#include <QtGui>
#include <QString>
#include <QStringList>
#include <client/gui/chatbox.hpp>
#include <position.hpp>

namespace fdgo {
namespace client {
namespace gui {

const QRegExp Chatbox::rgxPos("^[A-D][1-4][a-d][1-4]$");

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
	str = str.trimmed();
	QStringList list = str.split(QRegExp("\\s+"));
	QStringList::const_iterator it = list.begin();
	if (it->contains(rgxPos)) {
		emit playStone(Position(*it));
	} else if (*it == "pass") {
		emit pass();
	} else if (*it == "undo") {
		emit undo();
	} else if (*it == "kill") {
		if (++it == list.end() || !it->contains(rgxPos))
			tbCBox_->append("Expected position as second argument.");
		else
			emit kill(Position(*it));
	} else if (*it == "exit") {
		emit exit();
	} else if (*it == "connect") {
		emit cl_connect();
	} else if (*it == "disconnect") {
		emit cl_disconnect();
	} else if (*it == "save") {
		if (++it == list.end())
			tbCBox_->append("Expected filename as second argument.");
		else
			emit writeLogToDisk(*it);
	} else {
		tbCBox_->append(QString("Unknown command: ")+*it);
	}
}

}
}
}
