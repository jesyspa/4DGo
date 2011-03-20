#include <QtGui>
#include <client/gui/mainwidget.hpp>
#include <client/gui/chatbox.hpp>
#include <client/gui/goban.hpp>
#include <client/gui/info.hpp>

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

	QWidget::setTabOrder( cbox_, btnPass_ );
	QWidget::setTabOrder( btnPass_, btnUndo_ );
	QWidget::setTabOrder( btnUndo_, btnExit_ );
	QWidget::setTabOrder( btnExit_, cbox_ );
}

}
}
}


