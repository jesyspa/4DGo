#include <QtGui>
#include <client/gui/goban.hpp>
#include <client/gui/gobanslice.hpp>
#include <position.hpp>

namespace fdgo {
namespace client {
namespace gui {

Goban::Goban(QWidget* parent) : QWidget(parent) {
	
	QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	this->setSizePolicy(sizePolicy);
        glMain_ = new QGridLayout(this);
        glMain_->setObjectName(QString::fromUtf8("Goban::glMain"));

	lblArr_[0] = new QLabel("A", this);
	glMain_->addWidget(lblArr_[0], 4, 1);
	lblArr_[1] = new QLabel("B", this);
	glMain_->addWidget(lblArr_[1], 4, 2);
	lblArr_[2] = new QLabel("C", this);
	glMain_->addWidget(lblArr_[2], 4, 3);
	lblArr_[3] = new QLabel("D", this);
	glMain_->addWidget(lblArr_[3], 4, 4);
	lblArr_[4] = new QLabel("1", this);
	glMain_->addWidget(lblArr_[4], 3, 0);
	lblArr_[5] = new QLabel("2", this);
	glMain_->addWidget(lblArr_[5], 2, 0);
	lblArr_[6] = new QLabel("3", this);
	glMain_->addWidget(lblArr_[6], 1, 0);
	lblArr_[7] = new QLabel("4", this);
	glMain_->addWidget(lblArr_[7], 0, 0);
	
	sizePolicy.setHorizontalPolicy(QSizePolicy::Minimum);
	sizePolicy.setVerticalPolicy(QSizePolicy::Minimum);

	for (size_t i = 0; i < 8; ++i) {
		lblArr_[i]->setAlignment(Qt::AlignCenter);
		lblArr_[i]->setSizePolicy(sizePolicy);
	}

	for (size_t i = 0; i < 4; ++i) {
		for (size_t j = 0; j < 4; ++j) {
			grid_[i][j] = new GobanSlice();
			glMain_->addWidget(grid_[i][j], 3-j, i+1);
		}
	}
	glMain_->setColumnStretch(0, 0);
	glMain_->setColumnMinimumWidth(0, 8);
}

void Goban::placeStone(bool black, Position const& pos) {
	clearHighlight();
	setIcon(pos[0], pos[1], pos[2], pos[3], black ? 'X' : 'O');
}

void Goban::removeStone(Position const& pos) {
	setIcon(pos[0], pos[1], pos[2], pos[3], '.');
}

void Goban::setIcon(size_t a, size_t b, size_t c, size_t d, char icon) {
	grid_[a][b]->setIcon(c, d, icon);
}

void Goban::clearHighlight() {
	for (int a = 0; a < 4; ++a) {
		for (int b = 0; b < 4; ++b) {
			grid_[a][b]->clearHighlight();
		}
	}
}

void Goban::clear() {
	for (int a = 0; a < 4; ++a) {
		for (int b = 0; b < 4; ++b) {
			grid_[a][b]->clear();
		}
	}
	clearHighlight();
}

}
}
}
