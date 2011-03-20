#include <QtGui>
#include <QString>
#include <QChar>
#include <client/gui/gobanslice.hpp>

namespace fdgo {
namespace client {
namespace gui {

GobanSlice::GobanSlice(QWidget* parent) : QFrame(parent) {
	glMain_ = new QGridLayout(this);
	for (size_t i = 0; i < 4; ++i) {
		for (size_t j = 0; j < 4; ++j) {
			grid_[i][j] = new QLabel(".", this);
			grid_[i][j]->setAlignment(Qt::AlignCenter);
			glMain_->addWidget(grid_[i][j], 4-j, i+1);
		}
	}
	this->setFrameStyle(QFrame::StyledPanel);
}

void GobanSlice::setIcon(size_t c, size_t d, char icon) {
	grid_[c][d]->setText(QChar(icon));
}

void GobanSlice::clear() {
	for (size_t c = 0; c < 4; ++c) {
		for (size_t d = 0; d < 4; ++d) {
			grid_[c][d]->setText(".");
		}
	}
}

}
}
}

