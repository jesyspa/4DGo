#include <boost/lexical_cast.hpp>
#include <QtGui>
#include <client/gui/info.hpp>

namespace fdgo {
namespace client {
namespace gui {

Info::Info(QWidget* parent) : QWidget(parent) {
	flInfo_ = new QFormLayout(this);
	flInfo_->setObjectName(QString::fromUtf8("flInfo_"));
	flInfo_->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
	// Adding stuff to the form {
		lblColour_ = new QLabel(tr("Colour:"), this);
		lblColour_->setObjectName(QString::fromUtf8("lblColour"));
		flInfo_->setWidget(0, QFormLayout::LabelRole, lblColour_);

		lblColourVal_ = new QLabel(tr("Unknown"), this);
		lblColourVal_->setObjectName(QString::fromUtf8("lblColourVal_"));
		lblColourVal_->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
		flInfo_->setWidget(0, QFormLayout::FieldRole, lblColourVal_);

		lblTurn_ = new QLabel(tr("Turn:"), this);
		lblTurn_->setObjectName(QString::fromUtf8("lblTurn"));
		flInfo_->setWidget(1, QFormLayout::LabelRole, lblTurn_);

		lblTurnVal_ = new QLabel(tr("Unknown"), this);
		lblTurnVal_->setObjectName(QString::fromUtf8("lblTurnVal_"));
		lblTurnVal_->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
		flInfo_->setWidget(1, QFormLayout::FieldRole, lblTurnVal_);

		lblBlackCaps_ = new QLabel(tr("Black caps:"), this);
		lblBlackCaps_->setObjectName(QString::fromUtf8("lblBlackCaps"));
		flInfo_->setWidget(2, QFormLayout::LabelRole, lblBlackCaps_);

		lblBlackCapsVal_ = new QLabel(tr("Unknown"), this);
		lblBlackCapsVal_->setObjectName(QString::fromUtf8("lblBlackCapsVal_"));
		lblBlackCapsVal_->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
		flInfo_->setWidget(2, QFormLayout::FieldRole, lblBlackCapsVal_);

		lblWhiteCaps_ = new QLabel(tr("White caps:"), this);
		lblWhiteCaps_->setObjectName(QString::fromUtf8("lblWhiteCaps"));
		flInfo_->setWidget(3, QFormLayout::LabelRole, lblWhiteCaps_);

		lblWhiteCapsVal_ = new QLabel(tr("Unknown"), this);
		lblWhiteCapsVal_->setObjectName(QString::fromUtf8("lblWhiteCapsVal_"));
		lblWhiteCapsVal_->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
		flInfo_->setWidget(3, QFormLayout::FieldRole, lblWhiteCapsVal_);

		lblKomi_ = new QLabel(tr("Komi:"), this);
		lblKomi_->setObjectName(QString::fromUtf8("lblKomi"));
		flInfo_->setWidget(4, QFormLayout::LabelRole, lblKomi_);

		lblKomiVal_ = new QLabel(tr("Unknown"), this);
		lblKomiVal_->setObjectName(QString::fromUtf8("lblKomiVal_"));
		lblKomiVal_->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
		flInfo_->setWidget(4, QFormLayout::FieldRole, lblKomiVal_);

		lblConnection_ = new QLabel(tr("Connection:"), this);
		lblConnection_->setObjectName(QString::fromUtf8("lblConnection"));
		flInfo_->setWidget(5, QFormLayout::LabelRole, lblConnection_);

		lblConnectionVal_ = new QLabel(tr("Not active"), this);
		lblConnectionVal_->setObjectName(QString::fromUtf8("lblConnectionVal_"));
		lblConnectionVal_->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
		flInfo_->setWidget(5, QFormLayout::FieldRole, lblConnectionVal_);
	// } 
}

void Info::setColour(bool black) {
	lblColourVal_->setText(black ? "Black" : "White");
}

void Info::setTurn(bool black) {
	lblTurnVal_->setText(black ? "Black" : "White");
}

void Info::setBlackCaps(int caps) {
	lblWhiteCapsVal_->setText(boost::lexical_cast<std::string>(caps).c_str());
}

void Info::setWhiteCaps(int caps) {
	lblWhiteCapsVal_->setText(boost::lexical_cast<std::string>(caps).c_str());
}

void Info::setKomi(float komi) {
	lblKomiVal_->setText(boost::lexical_cast<std::string>(komi).c_str());
}

void Info::setConnection(QString const& str) {
	lblConnectionVal_->setText(str);
}

}
}
}
