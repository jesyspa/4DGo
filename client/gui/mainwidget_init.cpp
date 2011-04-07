#include <QtGui>
#include <client/gui/mainwidget.hpp>
#include <client/gui/chatbox.hpp>
#include <client/gui/goban.hpp>
#include <client/gui/info.hpp>
#include <client/client.hpp>

namespace fdgo {
namespace client {
namespace gui {

MainWidget::MainWidget(QWidget* parent) : QWidget(parent) {
	// Initialising the window itself.
        if (this->objectName().isEmpty())
            this->setObjectName(QString::fromUtf8("4DGo"));

	// Main layout
        vlMain_ = new QVBoxLayout(this);
        vlMain_->setObjectName(QString::fromUtf8("vlMain"));

	// Putting stuff in the main layout {
		hlGobanInfo_ = new QHBoxLayout();
		hlGobanInfo_->setObjectName(QString::fromUtf8("hlGobanInfo_"));
		// Putting stuff in the top layout {
			goban_ = new Goban(this);
			hlGobanInfo_->addWidget(goban_);

			vlnGobanInfo_ = new QFrame();
			vlnGobanInfo_->setObjectName(QString::fromUtf8("vlnGobanInfo_"));
			vlnGobanInfo_->setFrameShape(QFrame::VLine);
			vlnGobanInfo_->setFrameShadow(QFrame::Sunken);
			hlGobanInfo_->addWidget(vlnGobanInfo_);

			vlInfo_ = new QVBoxLayout();

			vlInfo_->setObjectName(QString::fromUtf8("vlInfo_"));
			// Putting stuff in the top-right layout {
				info_ = new Info(this);
				vlInfo_->addWidget(info_);

				lnInfo_ = new QFrame(this);
				lnInfo_->setObjectName(QString::fromUtf8("lnInfo_"));
				lnInfo_->setFrameShape(QFrame::HLine);
				lnInfo_->setFrameShadow(QFrame::Sunken);
				vlInfo_->addWidget(lnInfo_);

				btnConnect_ = new QPushButton(tr("&Connect"), this);
				btnConnect_->setObjectName(QString::fromUtf8("btnConnect_"));
				vlInfo_->addWidget(btnConnect_);

				btnPass_ = new QPushButton(tr("&Pass"), this);
				btnPass_->setObjectName(QString::fromUtf8("btnPass_"));
				vlInfo_->addWidget(btnPass_);

				btnUndo_ = new QPushButton(tr("&Undo"), this);
				btnUndo_->setObjectName(QString::fromUtf8("btnUndo"));
				vlInfo_->addWidget(btnUndo_);

				btnExit_ = new QPushButton(tr("E&xit"), this);
				btnExit_->setObjectName(QString::fromUtf8("btnExit"));
				vlInfo_->addWidget(btnExit_);

				vspcInfo_ = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
				vspcInfo_ = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
				vlInfo_->addItem(vspcInfo_);
			// }
			hlGobanInfo_->addLayout(vlInfo_);
		// }
		vlMain_->addLayout(hlGobanInfo_);

		cbox_ = new Chatbox(this);
		vlMain_->addWidget(cbox_);
	// }

	QWidget::setTabOrder(cbox_, btnUndo_);
	QWidget::setTabOrder(btnUndo_, btnPass_);
	QWidget::setTabOrder(btnPass_, btnExit_);
	QWidget::setTabOrder(btnExit_, cbox_);

	client_ = new Client(this);


	connect( btnConnect_, SIGNAL(clicked()),
	             client_, SLOT(  cl_connect())
	       );
	connect(    btnUndo_, SIGNAL(clicked()),
	             client_, SLOT(  undo())
	       );
	connect(    btnPass_, SIGNAL(clicked()),
	             client_, SLOT(  pass())
	       );
	connect(    btnExit_, SIGNAL(clicked()),
	             client_, SLOT(  exit())
	       );
	connect(       cbox_, SIGNAL(message(QString const&)),
	             client_, SLOT(  message(QString const&))
	       );
	connect(       cbox_, SIGNAL(playStone(Position const&)),
	             client_, SLOT(  playStone(Position const&))
	       );
	connect(       cbox_, SIGNAL(undo()),
	             client_, SLOT(  undo())
	       );
	connect(       cbox_, SIGNAL(pass()),
	             client_, SLOT(  pass())
	       );
	connect(       cbox_, SIGNAL(exit()),
	             client_, SLOT(  exit())
	       );
	connect(       cbox_, SIGNAL(confirm(bool)),
	             client_, SLOT(  confirm(bool))
	       );
	connect(       cbox_, SIGNAL(setHost(QString const&)),
	             client_, SLOT(  setHost(QString const&))
	       );
	connect(       cbox_, SIGNAL(setPort(int)),
	             client_, SLOT(  setPort(int))
	       );
	connect(       cbox_, SIGNAL(cl_connect()),
	             client_, SLOT(  cl_connect())
	       );
	connect(       cbox_, SIGNAL(cl_disconnect()),
	             client_, SLOT(  cl_disconnect())
	       );
	connect(       cbox_, SIGNAL(writeLogToDisk(QString const&)),
	             client_, SLOT(  writeLogToDisk(QString const&))
	       );
	connect(       cbox_, SIGNAL(kill(Position const&)),
	             client_, SLOT(  kill(Position const&))
	       );
	connect(     client_, SIGNAL(display(QString const&)),
	               cbox_, SLOT(  display(QString const&))
	       );
	connect(     client_, SIGNAL(placeStone(bool, Position const&)),
	              goban_, SLOT(  placeStone(bool, Position const&))
	       );
	connect(     client_, SIGNAL(removeStone(Position const&)),
	              goban_, SLOT(  removeStone(Position const&))
	       );
	connect(     client_, SIGNAL(setColourVal(bool)),
	               info_, SLOT(  setColour(bool))
	       );
	connect(     client_, SIGNAL(setTurnVal(bool)),
	               info_, SLOT(  setTurn(bool))
	       );
	connect(     client_, SIGNAL(setKomiVal(double)),
	               info_, SLOT(  setKomi(double))
	       );
	connect(     client_, SIGNAL(setBlackCapsVal(int)),
	               info_, SLOT(  setBlackCaps(int))
	       );
	connect(     client_, SIGNAL(setWhiteCapsVal(int)),
	               info_, SLOT(  setWhiteCaps(int))
	       );
	connect(     client_, SIGNAL(setConnectionVal(QString const&)),
	               info_, SLOT(  setConnection(QString const&))
	       );
	connect(     client_, SIGNAL(clear()),
	              goban_, SLOT(  clear())
	       );
	connect(     client_, SIGNAL(closeWindow()),
	                qApp, SLOT(  closeAllWindows())
	       );
}

}
}
}


