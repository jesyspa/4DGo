#include <QDataStream>
#include <net/setting.hpp>
#include <exceptions.hpp>

namespace fdgo {
namespace net {

Setting::Setting() {
	header_.type = Header::Setting;
	setting_type = unknown;
}

Setting::Setting(Header const& header) : Object(header) {
	if (header_.type != Header::Setting)
		BOOST_THROW_EXCEPTION(ExcIncorrectNetObjectType());
	setting_type = unknown;
}

Setting::Setting(int set, double dbl, int num, QString const& str) {
	header_.type = Header::Setting;
	setting_type = SType(set);
	this->dbl = dbl;
	this->num = num;
	this->str = str;
}

void Setting::printOn(QDataStream& ds) const {
	ds << qint32(setting_type);
	if (setting_type == komi) {
		ds << dbl;
	}
}

void Setting::readFrom(QDataStream& ds) {
	qint32 tmp;
	ds >> tmp;
	setting_type = SType(tmp);
	if (setting_type == komi) {
		ds >> dbl;
	}
}

}
}
