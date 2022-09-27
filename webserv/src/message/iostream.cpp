#include <message.hpp>

ostream &operator<<(ostream &ostr, const message &msg) {
	cout << msg.getOriginal();
	return ostr;
}
