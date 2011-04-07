#ifndef FDGO_INCLUDE_NET_SETTING_HPP
#define FDGO_INCLUDE_NET_SETTING_HPP

#include <QString>
#include <net/object.hpp>
#include <net/header.hpp>

class QDataStream;

namespace fdgo {
namespace net {

//! \brief Message for changes in setting.

class Setting : public Object {
  public:
	typedef boost::shared_ptr<Setting> Pointer;

	enum SType {
		unknown,
		komi
	} setting_type;

	Setting(); 
	Setting(int set, double dbl, int num, QString const& str);
	Setting(Header const& header);

	double dbl;
	int num;
	QString str;

  protected:
	void printOn(QDataStream& ds) const;
	void readFrom(QDataStream& ds);
};

}
}

#endif // Guard
